# Port-Hamiltonian Neural Networks for System Identification and Control of a 2-DOF Robotic Manipulator

> **Master Research Project** — University of Groningen  
> For a complete description of the methods and results, see the [thesis (link to be added)]().

This repository contains all code, data, and Simulink models for:

1. **DC motor calibration** — custom torque sensing setup with Teensy, external torque sensors, and signal conditioning PCB
2. **Classical system identification** — IDIM-OLS and Nonlinear Least Squares (NLS)
3. **Port-Hamiltonian Neural Network (HNN)** — structured sub-networks for mass, damping, and actuation, warm-started from OLS parameters (PyTorch)
4. **Velocity-free tracking control** — comparison of three controllers (Ferguson KPES, Rascón, Cruz-Zavala) using only position measurements
5. **Simulation studies and real hardware experiments** on a Quanser 2-DOF Serial Flexible Link manipulator

---

## Repository Structure

```
Master-Research-Project/
│
├── Data/                                  # Simulated and real experiment data
│   ├── Simulated data/                    # Generated datasets (various noise/friction configs)
│   ├── Real data/                         # Processed real experiment data
│   ├── simulation_data_generation.m       # Generate simulated data with desired parameters
│   └── preprocessing_quanser_data.m       # Process raw Quanser measurements
│
├── Matlab Code Motor Identification/      # DC motor parameter identification
│   ├── LS_Sgolay_dummy.m                  # ★ Best results — LS with Savitzky-Golay filtering
│   ├── LS_Kalman_dummy.m                  # LS with Kalman smoother for derivatives
│   ├── LS_Kalman_Smoother.m               # Alternative Kalman approach
│   ├── Motor_Kalman.m                     # Kalman filter for motor states
│   └── torque_sensor_calibration.m        # Torque sensor ADC-to-Nm calibration
│
├── Matlab Code System Identification/     # System identification (simulation + real)
│   ├── NLS_sim.m                          # NLS on simulated data
│   ├── NLS_2DOF_Quanser_Multi_Traj.m      # NLS on real multi-trajectory data
│   ├── trajectory_generation.m            # Fourier + Lissajous trajectory generation
│   ├── fourier_trajectory_generation.m    # Fourier-only trajectory generation
│   ├── DATA-*/                            # Date-labelled real experiment data
│   └── results/                           # Stored identification results (.mat)
│
├── Momentum Observer/                     # Simulation of observer + controller
│   ├── kpes_sim.m                         # KPES controller simulation
│   ├── kpes_tuning.m                      # Gain tuning for KPES
│   ├── KPES_control.m                     # Controller implementation
│   └── Momentum_Observer.m                # Hybrid momentum observer
│
├── Python Code/                           # HNN training and all plotting
│   ├── HNNs/                              # Jupyter notebooks for training HNNs
│   │   ├── HNNs_momentum_transformation_quanser_windowed.ipynb  # ★ Main training notebook
│   │   ├── HNN_predict.py                 # Forward prediction scripts
│   │   ├── HNN_Momentum_Observer.py       # HNN-based momentum observer
│   │   └── *.pth                          # Saved model weights
│   ├── plotting.ipynb                     # ★ All thesis plots (one cell per figure)
│   ├── ISS_exp/                           # ISS experiment data (KPES)
│   ├── Cruz_ISS_exp/                      # ISS experiment data (Cruz-Zavala)
│   ├── Rascon_ISS_exp/                    # ISS experiment data (Rascón)
│   ├── Plots/                             # Generated figures (PDF + PNG)
│   └── *.mat                              # Data files used for plotting
│
├── Quanser/                               # Simulink models + hardware interface
│   ├── TRACKING_CONTROL_SETUP.m           # ★ Setup script for all tracking experiments
│   ├── TRACKING_CONTROL_KPES.mdl          # KPES controller (Ferguson 2025)
│   ├── TRACKING_CONTROL_Cruz.mdl          # Cruz-Zavala controller (2021)
│   ├── TRACKING_CONTROL_RasconIET.mdl     # Rascón controller (2020)
│   ├── TRACKING_CONTROL_RasconISA.mdl     # Rascón ISA variant
│   ├── torque_control.mdl                 # Low-level torque control loop
│   ├── DATA_COLLECTION.mdl                # Data collection with simple PD control
│   ├── DATA_COLLECTION_SETUP.m            # Setup for data collection
│   ├── process_tracking_control_data.m    # Post-process tracking experiment data
│   ├── config_2dslf.m                     # Quanser plant model parameters
│   ├── config_2dslf_sensors.m             # Sensor calibration gains
│   ├── Motor Calibration/                 # Motor calibration experiments
│   │   ├── motor_calibration.mdl          # Simulink model (Quanser side)
│   │   ├── teensy_read.m                  # MATLAB serial reader (separate instance)
│   │   ├── quanser_motor_calibration_electric.m   # Electrical parameter derivation
│   │   └── quanser_motor_calibration_mechanical.m # Mechanical parameter derivation
│   ├── motor_calibration_data_shoulder/   # Raw calibration data (motor 1)
│   └── motor_calibration_data_elbow/      # Raw calibration data (motor 2)
│
├── Teensy/                                # Microcontroller code
│   ├── read_teensy_interupt/
│   │   └── read_teensy_interupt.ino       # ★ Main Teensy ADC acquisition code
│   └── sensor_calibration/
│       └── sensor_calibration.ino         # Torque sensor calibration routine
│
└── Old/                                   # Deprecated files (kept for reference)
```

> **Note:** The `slprj/` and `*_quarc_windows/` folders are auto-generated by Simulink/QUARC and can be ignored. The `.rt-windows`, `.slxc`, `.err`, and `.autosave` files are Simulink internals.

---

## How to Run Experiments

### Prerequisites

- **MATLAB/Simulink** with QUARC toolbox (for Quanser hardware)
- **Python 3.x** with PyTorch (for HNN training)
- **Arduino IDE** (for Teensy firmware upload)
- The Quanser 2-DOF Serial Flexible Link manipulator must be connected and powered

### Important: Update File Paths

Many scripts contain hardcoded paths (e.g. `/Users/lars/Documents/GitHub/Master-Research-Project/...`). **Update these to your local clone location before running anything.**

---

### 1. DC Motor Calibration

Motor calibration requires three processes running in parallel:

| Process | What to run | Where |
|---------|-------------|-------|
| **Quanser side** | Open `Quanser/Motor Calibration/motor_calibration.mdl` in Simulink | MATLAB instance 1 |
| **Teensy serial reader** | Run `Quanser/Motor Calibration/teensy_read.m` | MATLAB instance 2 |
| **Teensy firmware** | Upload and run `Teensy/read_teensy_interupt/read_teensy_interupt.ino` | Arduino IDE |

**Workflow:**
1. Upload the Teensy firmware via Arduino IDE and confirm serial output is active.
2. In MATLAB instance 2, start `teensy_read.m` to begin listening for serial data.
3. In MATLAB instance 1, build and run `motor_calibration.mdl` via QUARC.
4. After the experiment, process the data with:
   - `quanser_motor_calibration_electric.m` — electrical parameters (R, L, Kt, Ke)
   - `quanser_motor_calibration_mechanical.m` — mechanical parameters (J, B, Fc)

Raw data is stored in `Quanser/motor_calibration_data_shoulder/` and `Quanser/motor_calibration_data_elbow/`. Check paths inside the processing scripts before running.

---

### 2. Torque Sensor Calibration

Run `Matlab Code Motor Identification/torque_sensor_calibration.m` to obtain the ADC-to-Nm linear mapping (parameters `a` and `b` used in the setup files).

---

### 3. System Identification

#### Simulated data
1. Generate data: `Data/simulation_data_generation.m` (set desired noise level and friction model).
2. Run identification: `Matlab Code System Identification/NLS_sim.m`.

#### Real data
1. Collect data using a tracking controller (recommended over `DATA_COLLECTION.mdl` — see note below).
2. Process raw Quanser data: `Data/preprocessing_quanser_data.m`.
3. Run identification: `Matlab Code System Identification/NLS_2DOF_Quanser_Multi_Traj.m`.

> **Tip:** For HNN training data, use an accurate tracking controller rather than `DATA_COLLECTION.mdl` (which uses simple PD control with poor tracking). If the tracked trajectory is close to the desired one, you can use analytical derivatives instead of noisy numerical differentiation.

#### Trajectory generation
- `trajectory_generation.m` — generates both Fourier and Lissajous excitation trajectories
- `fourier_trajectory_generation.m` — Fourier trajectories only

These produce trajectory files that the Simulink models load via `timeseries`.

---

### 4. HNN Training (Python)

The main training notebook is `Python Code/HNNs/HNNs_momentum_transformation_quanser_windowed.ipynb`. It trains a port-Hamiltonian neural network with dedicated sub-networks for the mass matrix M(q), damping D(q), and actuation, using Cholesky parameterization to enforce positive definiteness. The network is warm-started from OLS-identified parameters.

Trained model weights are saved as `.pth` files in the same folder.

For plotting all thesis figures, open `Python Code/plotting.ipynb` — each cell generates a different plot. The `.mat` files in `Python Code/` are the data sources for these plots.

---

### 5. Tracking Control Experiments (Quanser)

This is the main experiment workflow:

#### Step 1: Prepare the setup
```matlab
% In MATLAB, navigate to the Quanser/ folder and run:
TRACKING_CONTROL_SETUP
```

This loads all parameters into the workspace:
- **Motor parameters:** electrical model (R, L, Ke, Kt) and torque control gains (kp, ki, kd)
- **Identified dynamics:** Euler-Lagrange inertial parameters (a1, a2, b) and damping (b1, b2)
- **Controller gains:** specific to each controller (KPES: alpha, Kp, Kd, kappa; Cruz: P1, P2, D1, D2, etc.)
- **Trajectory:** loaded as `timeseries` objects (qd, dqd, ddqd) with a 2-second idle prefix for robot wake-up
- **Perturbation signal:** sinusoidal input for ISS experiments (amplitude `a`, frequency `f`)

#### Step 2: Open the Simulink model

Open the `.mdl` file for the controller you want to test:
- `TRACKING_CONTROL_KPES.mdl` — Ferguson KPES (port-Hamiltonian + momentum observer)
- `TRACKING_CONTROL_Cruz.mdl` — Cruz-Zavala (finite-time, nonlinear velocity filter)
- `TRACKING_CONTROL_RasconIET.mdl` — Rascón (discontinuous output-feedback)

#### Step 3: Build and run
1. In Simulink: **Ctrl+B** or menu → QUARC → Build.
2. Connect to target: QUARC → Connect to Target.
3. Run the experiment.

> **Tip:** If you are tuning gains, change them directly in the Simulink model rather than in the setup file — this way you don't need to rebuild every time.

#### Step 4: Save and process data
1. After the experiment, the data appears in the MATLAB command window. The variable name is specified inside the Simulink model.
2. Save the workspace variable.
3. Process for plotting: run `process_tracking_control_data.m`.

#### Step 5: ISS perturbation experiments
For ISS experiments, set the perturbation amplitude in `TRACKING_CONTROL_SETUP.m`:
```matlab
a = 1;      % perturbation amplitude (Nm)
a1 = a;     % shoulder
a2 = a;     % elbow
f = 2;      % frequency (Hz)
```
Run experiments at increasing amplitudes to observe the ISS gain relationship. Data for three controllers is stored in the `Python Code/*_ISS_exp/` folders.

---

### 6. Momentum Observer (Simulation Only)

The `Momentum Observer/` folder contains MATLAB scripts for tuning and simulating the momentum observer and KPES controller without hardware:
- `kpes_tuning.m` — sweep observer gain κ and controller gains
- `kpes_sim.m` — full closed-loop simulation
- `KPES_control.m` and `Momentum_Observer.m` — implementations

---

## Key Identified Parameters

These are the parameters used in `TRACKING_CONTROL_SETUP.m` (from IDIM-OLS):

| Parameter | Description | Value |
|-----------|-------------|-------|
| `a1_hat` | Shoulder composite inertia | 0.0922 |
| `a2_hat` | Elbow composite inertia | 0.0232 |
| `b_hat` | Coupling inertia | 0.0275 |
| `b1_hat` | Shoulder viscous damping | 0.3962 |
| `b2_hat` | Elbow viscous damping | 0.1950 |

Motor parameters (shoulder / elbow): Kt = 3.019 / 1.111, R = 4.274 / 4.036, L = 47.5 / 48.2 mH.

---

## Notes for Future Work

- The `Old/` folder contains deprecated files including data from a broken elbow motor. Kept for reference only.
- The Quanser platform is older hardware — if motors misbehave, check the motor calibration first.
- `DATA_COLLECTION.mdl` uses simple PD control. For generating identification data, a proper tracking controller gives cleaner results.
- All plots in the thesis can be regenerated from `Python Code/plotting.ipynb`.
- When changing the identified model (e.g. after re-running NLS or training a new HNN), update the parameters in `TRACKING_CONTROL_SETUP.m` accordingly.
