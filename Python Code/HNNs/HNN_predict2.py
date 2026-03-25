import torch
import torch.nn as nn
import torch.optim as optim
from torchdiffeq import odeint_adjoint as odeint
import torch.nn.functional as F
import numpy as np


def make_mlp(in_dim, out_dim, hidden=(128,128), activation=nn.Tanh):
    layers = []
    d = in_dim
    for h in hidden:
        layers.append(nn.Linear(d, h))
        layers.append(activation())
        d = h
    layers.append(nn.Linear(d, out_dim))   # last layer no activation
    return nn.Sequential(*layers)

class LowerTriangularNN(nn.Module):
    """
    This neural network outputs (N^2 + N)/2 values corresponding to
    the lower triangular entries of a symmetric matrix.

    The last-layer activation ensures diagonal positivity (Softplus + ε).
    """
    def __init__(self, n_dim, input_dim = 2, hidden_dims=(64, 64), eps=1e-3):
        super().__init__()

        self.n_dim = n_dim
        self.eps = eps

        # Number of parameters needed for lower triangular matrix
        self.out_dim = (n_dim * (n_dim + 1)) // 2

        # Build feed-forward network
        layers = []
        for h in hidden_dims:
            layers.append(nn.Linear(input_dim, h))
            layers.append(nn.Tanh())
            input_dim = h

        # Final layer outputs LT matrix entries
        layers.append(nn.Linear(input_dim, self.out_dim))

        self.net = nn.Sequential(*layers)
        self.softplus = nn.Softplus()

    def forward(self, x):
        """
        Returns a symmetric positive-definite matrix for each sample x.
        """
        batch_size = x.shape[0]

        raw_output = self.net(x)

        # Split indices: diagonal first, then off-diagonals
        L = x.new_zeros(batch_size, self.n_dim, self.n_dim)

        # Fill lower-triangular entries
        idx = 0
        for i in range(self.n_dim):
            # Diagonal entry: force positivity
            L[:, i, i] = self.softplus(raw_output[:, idx]) + self.eps
            idx += 1

            # Off-diagonal entries
            for j in range(i + 1, self.n_dim):
                L[:, j, i] = raw_output[:, idx]
                idx += 1

        # Construct symmetric PD matrix:
        # M = L * L^T 
        M = L @ L.transpose(1, 2)
        return M


class ActuatorNN(nn.Module):
    """Map q -> B(q) (n x m) matrix. Input: q [B,n], Output: [B, n, m]."""
    def __init__(self, q_dim, u_dim, hidden=(128,128)):
        super().__init__()
        out_dim = q_dim * u_dim
        self.net = make_mlp(2*q_dim, out_dim, hidden=hidden)

    def forward(self, q):
        inp = torch.cat([torch.sin(q), torch.cos(q)], dim=-1)
        vec = self.net(inp)  # [B, n*m]
        Bmat = vec.view(vec.shape[0], -1, int(vec.shape[-1] // q.shape[-1]))  # [B, n, m]
        return Bmat

# Define the Hamiltonian Neural Network 
class HamiltonianNN(nn.Module):
    # def __init__(self, input_dim=6, hidden_dim=200, output_dim=1): old
    def __init__(self, q_dim, mass_nn,p_dim=None):
        super().__init__()
        self.q_dim = q_dim
        self.p_dim = q_dim if p_dim is None else p_dim
        self.mass_nn = mass_nn
        # self.diss_nn = diss_nn
        # self.actuator_nn = actuator_nn

    def kinetic_energy(self, q, p):
        # q: [B, q_dim], p: [B, q_dim]

        #NN mass matrix:
        q2 = q[:, 1:2]               # <-- ONLY q2 used
        M = self.mass_nn(q2)                # [B, q, q]
        #both q
        # M = self.mass_nn(q)                # [B, q, q]

        #Real mass matrix
        # M = FixedMassMatrix(q)

        Minv = torch.linalg.inv(M)         # [B, q, q]
        # compute 0.5 p^T Minv p
        p_col = p.unsqueeze(-1)            # [B, q, 1]
        tmp = Minv @ p_col                 # [B, q, 1]
        T = 0.5 * (p_col * tmp).sum(dim=1).squeeze(-1)  # [B]
        return T

    def forward(self, q, p):
        T = self.kinetic_energy(q, p)
        return T  # H (no potentialk)

class HamiltonianDynamics(nn.Module):
    """
    Given HamiltonianModel H(q,p), compute (dq/dt, dp/dt) using autograd:
      dq/dt =  ∂H/∂p
      dp/dt = -∂H/∂q + damping + actuators
    """
    def __init__(self, hamiltonian_model, mass_nn=None, diss_nn=None, actuator_nn=None):
        super().__init__()
        self.hamiltonian_model = hamiltonian_model
        self.mass_nn = mass_nn
        self.diss_nn = diss_nn
        self.actuator_nn = actuator_nn
    # Define the learned Hamiltonian dynamics
    def forward(self, t, x, u):
        # x: [B, 2*q_dim] concatenated [q, p]
        # q, p = torch.split(x, x.shape[-1]//2, dim=-1)
        # q.requires_grad_(True)
        # p.requires_grad_(True)
        # x_for_grad = torch.cat([q, p], dim=-1)

        # H = self.hamiltonian_model(q, p)  # [B]

        # x = x.clone().detach().requires_grad_(True)  # Ensure x requires gradients
        q, p = torch.split(x, x.shape[-1]//2, dim=-1)
        q.requires_grad_(True)
        p.requires_grad_(True)
        H = self.hamiltonian_model(q,p)  # Compute Hamiltonian

        # compute gradient dH/dx = [dH/dq, dH/dp]
        # Compute gradients ∂H/∂x
        # dH = torch.autograd.grad(outputs=H, inputs=x, grad_outputs=torch.ones_like(H), create_graph=True)[0]
        # dH_dq = dH[:, :q.shape[-1]]
        # dH_dp = dH[:, q.shape[-1]:]

        dH_dq, dH_dp = torch.autograd.grad(H.sum(), (q, p), create_graph=True)

        dq_dt = dH_dp
        dp_dt = -dH_dq

        # add damping and actuation
        D = self.diss_nn(q)

        damping = -torch.bmm(D,dq_dt.unsqueeze(-1)).squeeze(-1)
 
        A = self.actuator_nn(q)
        # tau = torch.bmm(A,u.unsqueeze(-1)).squeeze(-1)
        # actuation = tau
        actuation = u
        dp_dt = dp_dt + damping + actuation  # add to generalized forces 
        
        return torch.cat([dq_dt, dp_dt], dim=-1)

class BatchDynamics(nn.Module):
    def __init__(self, dynamics, u_batch):
        super().__init__()
        self.dynamics = dynamics
        self.u_batch = u_batch  # store the control for this batch

    def forward(self, t, x):
        # x: [B, 2*q_dim]
        return self.dynamics(t, x, self.u_batch)

def rk4_step(odefunc, x, t, dt):
    # odefunc: callable(t, x) 
    k1 = odefunc(t, x)
    k2 = odefunc(t + dt/2, x + dt * k1 / 2)
    k3 = odefunc(t + dt/2, x + dt * k2 / 2)
    k4 = odefunc(t + dt,   x + dt * k3)
    x_next = x + dt * (k1 + 2*k2 + 2*k3 + k4) / 6
    return x_next



def predict_next(x_numpy, dt, u_numpy):
    """
    x_numpy: (4,) or (batch,4) array [q1,q2,p1,p2]
    dt: float
    u_numpy: optional (batch, u_dim) control input for the step (if None, zero)
    """
    x_np = np.asarray(x_numpy, dtype=np.float32)
    squeeze = False
    if x_np.ndim == 1:
        x_np = x_np.reshape(1, -1)
        squeeze = True

    xt = torch.tensor(x_np, dtype=torch.float32)  # device cpu by default

    # control
    u_np = np.asarray(u_numpy, dtype=np.float32)
    if u_np.ndim == 1:
        u_np = u_np.reshape(1, -1)
    zero_u = torch.tensor(u_np, dtype=torch.float32)

    with torch.set_grad_enabled(True):
        def ode_fn(t, x, u_in=zero_u):
            return dynamics(t, x, u_in)

        # one RK4 integration step
        x_next = rk4_step(ode_fn, xt, 0.0, dt)

    out = x_next.detach().cpu().numpy()
    if squeeze:
        return out[0]
    return out

def load_model():
    # Load weights and build full model 
    q_dim = 2   # must match training
    u_dim = 2   # must match training 
    device = torch.device("cpu")

    # instantiate networks 
    mass_nn = LowerTriangularNN(q_dim, input_dim = 1, hidden_dims=(128,128)).to(device) #input only q2
    diss_nn = LowerTriangularNN(q_dim, hidden_dims=(128,128)).to(device)
    actuator_nn = ActuatorNN(q_dim, u_dim=2, hidden=(2,2)).to(device)

    # load saved state dict (make sure path is correct)
    state = torch.load("modular_hnn_state.pth", map_location=device)

    # If you saved separate state_dicts under keys, load them:
    if 'mass_nn' in state or 'diss_nn' in state or 'actuator_nn' in state:
        if 'mass_nn' in state:
            mass_nn.load_state_dict(state['mass_nn'])
        if 'diss_nn' in state:
            diss_nn.load_state_dict(state['diss_nn'])
        if 'actuator_nn' in state:
            actuator_nn.load_state_dict(state['actuator_nn'])
    else:
        # if you saved a single state_dict (older variant), try to load into whole model later
        print("Warning: expected keys mass_nn/diss_nn/actuator_nn not found in the PTH file.")

    # build ham model and dynamics wrapper
    ham_model = HamiltonianNN(q_dim, mass_nn)
    global dynamics
    dynamics = HamiltonianDynamics(ham_model, diss_nn=diss_nn, actuator_nn=actuator_nn).to(device)
    dynamics.eval()

    


    

if __name__ == "__main__":
    print("Self-test (inference-only) ...")
    x0 = np.array([0.5, -0.3, 0.1, -0.2], dtype=np.float32)
    u = np.array([0.1, -0.1], dtype=np.float32)
    dt = 0.01
    x1 = predict_next(x0, dt, u)
    print("x0 ->", x1)
    for i in range(10):
        x1 = predict_next(x1, dt, u)
        print("x0 ->", x1)
