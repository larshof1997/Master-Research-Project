"""
2-DOF planar rigid-link manipulator simulation (no gravity)
Dynamics: M(q) ddq + C(q,dq) dq = tau(t)

- Each joint torque is a sinusoid: tau_i(t) = A_i * sin(2*pi*f_i*t + phi_i)
- Sweeps a few amplitude/frequency combos across multiple runs
- Saves trajectories and plots kinetic energy, theta1 vs theta2, and example torques

"""

import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt
from dataclasses import dataclass

# System parameters
m1 = 1.6537
l1 = 0.343
r1 = 0.29
I1 = 0.039

m2 = 0.9982
l2 = 0.267
r2 = 0.175
I2 = 0.0081

# Shorthand constants 
a1 = m1 * r1**2 + m2 * l1**2 + I1
a2 = m2 * r2**2 + I2
b  = m2 * l1 * r2

#Simulation parameters
dt = 1e-3

# Helpers
def M_mat(theta2: float) -> np.ndarray:
    """Inertia matrix M(q). Only theta2 enters explicitly."""
    return np.array([
        [a1 + a2 + 2 * b * np.cos(theta2),  a2 + b * np.cos(theta2)],
        [a2 + b * np.cos(theta2),           a2]
    ], dtype=float)

def C_mat(theta2: float, dtheta1: float, dtheta2: float) -> np.ndarray:
    """Coriolis/centrifugal matrix C(q, dq) using Christoffel form."""
    s2 = np.sin(theta2)
    return np.array([
        [-b * s2 * dtheta2,               -b * s2 * (dtheta1 + dtheta2)],
        [ b * s2 * dtheta1,                0.0]
    ], dtype=float)

@dataclass
class TorqueParams:
    A1: float = 1.0   # amplitude joint 1 [Nm]
    f1: float = 1.0   # frequency joint 1 [Hz]
    phi1: float = 0.0 # phase joint 1 [rad]
    A2: float = 1.0   # amplitude joint 2 [Nm]
    f2: float = 1.0   # frequency joint 2 [Hz]
    phi2: float = 0.0 # phase joint 2 [rad]

def tau_of_t(t: float, pars: TorqueParams) -> np.ndarray:
    """Sinusoidal torque input vector tau(t)."""
    tau1 = pars.A1 * np.sin(2 * np.pi * pars.f1 * t + pars.phi1)
    tau2 = pars.A2 * np.sin(2 * np.pi * pars.f2 * t + pars.phi2)
    return np.array([tau1, tau2], dtype=float)

# Dynamics
def odefun(t: float, state: np.ndarray, pars: TorqueParams):
    """State = [theta1, theta2, dtheta1, dtheta2]."""
    theta1, theta2, dtheta1, dtheta2 = state
    M = M_mat(theta2)
    C = C_mat(theta2, dtheta1, dtheta2)
    tau = tau_of_t(t, pars)
    ddq = np.linalg.solve(M, (tau - C @ np.array([dtheta1, dtheta2])))
    return [dtheta1, dtheta2, ddq[0], ddq[1]]

def kinetic_energy(state: np.ndarray) -> float:
    """Kinetic energy T = 1/2 dq^T M dq (no potential, horizontal plane)"""
    _, theta2, dtheta1, dtheta2 = state
    M = M_mat(theta2)
    v = np.array([dtheta1, dtheta2])
    return 0.5 * v @ M @ v

def momentum(state: np.ndarray) -> np.ndarray:
    """Generalized momentum p = M dq."""
    _, theta2, dtheta1, dtheta2 = state
    M = M_mat(theta2)
    v = np.array([dtheta1, dtheta2])
    return M @ v

# Simulation
if __name__ == "__main__":
    # Time grid
    t_span = (0.0, 5.0)
    t_eval = np.arange(t_span[0], t_span[1], dt)

    # Define a small sweep of amplitude/frequency values
    A1_vals = [0.5, 1.0]
    A2_vals = [0.5, 1.0]
    f1_vals = [0.5, 1.5]
    f2_vals = [0.5, 2.0]

    # Number of simulations and random initial conditions
    num_simulations = 12
    rng = np.random.default_rng(42)
    initial_conditions = rng.uniform(
        low=[-np.pi, -np.pi, -1.0, -1.0],
        high=[ np.pi,  np.pi,  1.0,  1.0],
        size=(num_simulations, 4)
    )

    # Build torque parameter list of equal length (cycle through the grid)
    grid = [(A1, A2, f1, f2) for A1 in A1_vals for A2 in A2_vals for f1 in f1_vals for f2 in f2_vals]
    pars_list = []
    for i in range(num_simulations):
        A1, A2, f1, f2 = grid[i % len(grid)]
        pars_list.append(TorqueParams(A1=A1, A2=A2, f1=f1, f2=f2))

    # Run simulations
    trajectories = {"time": t_eval, "states": []}
    for i, (x0, pars) in enumerate(zip(initial_conditions, pars_list), start=1):
        sol = solve_ivp(
            odefun, t_span, x0, t_eval=t_eval,
            rtol=1e-7, atol=1e-9, args=(pars,)
        )

        KE = np.array([kinetic_energy(sol.y[:, j]) for j in range(sol.y.shape[1])])
        P  = np.array([momentum(sol.y[:, j]) for j in range(sol.y.shape[1])])

        trajectories["states"].append({
            "initial_condition": x0,
            "theta1": sol.y[0],
            "theta2": sol.y[1],
            "dtheta1": sol.y[2],
            "dtheta2": sol.y[3],
            "p1": P[:, 0],
            "p2": P[:, 1],
            "kinetic_energy": KE,
            "torque_params": pars.__dict__
        })

    # Save results
    np.save("planar_2dof_sinusoidal_tau_trajectories.npy", trajectories)
    print("Saved: planar_2dof_sinusoidal_tau_trajectories.npy")

    # Plots
    # 1) Kinetic energy across runs
    plt.figure(figsize=(9, 5))
    for i, traj in enumerate(trajectories["states"], start=1):
        plt.plot(trajectories["time"], traj["kinetic_energy"], label=f"Run {i}")
    plt.title("Kinetic Energy Over Time (No Gravity, Sinusoidal Torques)")
    plt.xlabel("Time [s]")
    plt.ylabel("Kinetic Energy [J]")
    plt.grid(True)
    plt.legend(loc="upper right", fontsize=7)
    plt.tight_layout()
    plt.show()

    # 2) Phase-plane style: theta1 vs theta2 across runs
    plt.figure(figsize=(7, 7))
    for traj in trajectories["states"]:
        plt.plot(traj["theta1"], traj["theta2"])
    plt.title(r"$\theta_1$ vs $\theta_2$")
    plt.xlabel(r"$\theta_1$ [rad]")
    plt.ylabel(r"$\theta_2$ [rad]")
    plt.grid(True)
    plt.tight_layout()
    plt.show()

    # 3) Example torques for the first run
    first_pars = pars_list[0]
    tt = trajectories["time"]
    tau_ex1 = np.array([tau_of_t(t, first_pars) for t in tt])
    plt.figure(figsize=(9, 4))
    plt.plot(tt, tau_ex1[:, 0], label="tau1(t)")
    plt.plot(tt, tau_ex1[:, 1], label="tau2(t)")
    plt.title("Example Input Torques (Run 1)")
    plt.xlabel("Time [s]")
    plt.ylabel("Torque [Nm]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

    # 4) Example trajectory (θ₁, θ₂, ω₁, ω₂ over time)
    example = trajectories["states"][0]
    plt.figure(figsize=(10, 6))
    plt.subplot(2, 1, 1)
    plt.plot(tt, example["theta1"], label=r"$\theta_1$")
    plt.plot(tt, example["theta2"], label=r"$\theta_2$")
    plt.title("Example Joint Angles (Run 1)")
    plt.ylabel("Angle [rad]")
    plt.grid(True)
    plt.legend()

    plt.subplot(2, 1, 2)
    plt.plot(tt, example["dtheta1"], label=r"$\dot{\theta}_1$")
    plt.plot(tt, example["dtheta2"], label=r"$\dot{\theta}_2$")
    plt.title("Example Joint Velocities (Run 1)")
    plt.xlabel("Time [s]")
    plt.ylabel("Angular Velocity [rad/s]")
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    plt.show()
