# HNN_predict.py
import numpy as np
import torch
import torch.nn as nn
from torchdiffeq import odeint_adjoint as odeint

# ---- Re-declare the same classes used when training ----
class HamiltonianNN(nn.Module):
    def __init__(self, input_dim=6, hidden_dim=200, output_dim=1):
        super(HamiltonianNN, self).__init__()
        self.fc1 = nn.Linear(input_dim, hidden_dim)
        self.fc2 = nn.Tanh()
        self.fc3 = nn.Linear(hidden_dim, output_dim)

    def forward(self, x):
        # expect x shape (batch,4) raw: [theta1,theta2,p1,p2]
        # transform inside to match training transform
        sin_theta1 = torch.sin(x[:, 0])
        cos_theta1 = torch.cos(x[:, 0])
        sin_theta2 = torch.sin(x[:, 1])
        cos_theta2 = torch.cos(x[:, 1])
        p1 = x[:, 2]
        p2 = x[:, 3]
        x_transformed = torch.stack([sin_theta1, cos_theta1, sin_theta2, cos_theta2, p1, p2], dim=1)
        return self.fc3(self.fc2(self.fc1(x_transformed)))  # (batch,1)

class HamiltonianODEFunc(nn.Module):
    def __init__(self):
        super(HamiltonianODEFunc, self).__init__()
        self.hnn = HamiltonianNN()

    def forward(self, t, x):
        # x shape (batch,4)
        with torch.enable_grad():
            x = x.clone().detach().requires_grad_(True)
            H = self.hnn(x)                    # (batch,1)
            dH = torch.autograd.grad(outputs=H, inputs=x,
                                     grad_outputs=torch.ones_like(H),
                                     create_graph=True)[0]     # (batch,4)
            # Hamiltonian dynamics mapping (match your original)
            dtheta1_dt = dH[:, 2]
            dtheta2_dt = dH[:, 3]
            dp1_dt = -dH[:, 0]
            dp2_dt = -dH[:, 1]
        return torch.stack([dtheta1_dt, dtheta2_dt, dp1_dt, dp2_dt], dim=1)

# ---- Load weights once on import ----
_global_model = HamiltonianODEFunc()
try:
    # adjust path/name if your .pth is elsewhere
    _global_model.load_state_dict(torch.load("hnn_double_pendulum.pth", map_location="cpu"))
    _global_model.eval()
except Exception as e:
    print("Warning: could not load weights 'hnn_double_pendulum.pth' on import:", e)

# ---- Exported function for MATLAB ----
def predict_next(x_numpy, dt):
    """
    x_numpy: shape (4,) or (batch,4) numpy array (theta1,theta2,p1,p2)
    dt: float scalar time step
    returns numpy array of same batch shape (batch,4) representing x(t+dt)
    """
    x_np = np.asarray(x_numpy, dtype=np.float32)
    squeeze = False
    if x_np.ndim == 1:
        x_np = x_np.reshape(1, -1)
        squeeze = True

    xt = torch.tensor(x_np, dtype=torch.float32)  # (batch,4)
    t_span = torch.tensor([0.0, float(dt)], dtype=torch.float32)

    # use torch.no_grad to avoid creating huge graph during inference
    with torch.no_grad():
        x_next = odeint(_global_model, xt, t_span, rtol=1e-6, atol=1e-9)[-1]  # (batch,4)

    out = x_next.cpu().numpy()
    if squeeze:
        return out[0]
    return out
