import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

try:
    df = pd.read_csv("../results/task2b/output.csv")
except FileNotFoundError:
    print("WARNING: Data file not found. Using dummy data for demonstration.")
    t = np.linspace(0, 50, 500)
    alpha = 0.1
    m = 1.0
    k = 1.0
    x0 = 1.0
    omega0 = np.sqrt(k/m)
    omega_d = np.sqrt(omega0**2 - (alpha/(2*m))**2)
    x = x0 * np.exp(-alpha * t / (2*m)) * np.cos(omega_d * t) * 0.95
    v = -x0 * omega_d * np.exp(-alpha * t / (2*m)) * np.sin(omega_d * t)
    Ekin = 0.5 * m * v**2
    Epot = 0.5 * k * x**2
    Etot = Ekin + Epot

t = df["t"]
x = df["x"]
v = df["v"]
Ekin = df["Ekin"]
Epot = df["Epot"]
Etot = df["Etot"]

m = 1.0
k = 1.0
alpha = 0.1
x0 = 1.0
omega0 = np.sqrt(k/m)
omega_d = np.sqrt(omega0**2 - (alpha/(2*m))**2)
x_exact = x0 * np.exp(-alpha * t / (2*m)) * np.cos(omega_d * t)

fig, ax = plt.subplots(nrows = 2, ncols = 2, figsize=(12, 10))
fig.suptitle(f"Damped Harmonic Oscillator ($\\alpha={alpha}$)", fontsize=16)

# Plot 1: Displacement x(t) and Exact Solution (ax[0, 0])
ax[0, 0].plot(t, x, label="Numerical $x(t)$")
ax[0, 0].plot(t, x_exact, "--", label="Exact")
ax[0, 0].set_xlabel("Time $t$")
ax[0, 0].set_ylabel("Displacement $x$")
ax[0, 0].set_title("Displacement vs. Time")
ax[0, 0].legend()
ax[0, 0].grid(True)

# Plot 2: Phase-space trajectory v(x) (ax[0, 1])
ax[0, 1].plot(x, v, color="orange")
ax[0, 1].set_xlabel("Displacement $x$")
ax[0, 1].set_xlim(-1.05 * x0, 1.05 * x0)
ax[0, 1].set_ylabel("Velocity $v$")
ax[0, 1].set_ylim(-1.05 * x0 * omega0, 1.05 * x0 * omega0)
ax[0, 1].set_title("Phase-Space Trajectory $v(x)$")
ax[0, 1].grid(True)

# Plot 3: Energy variations (ax[1, 0]) ---
ax[1, 0].plot(t, Ekin, label="$E_{kin}$")
ax[1, 0].plot(t, Epot, label="$E_{pot}$")
ax[1, 0].plot(t, Etot, label="$E_{tot}$", linewidth=2)
ax[1, 0].set_xlabel("Time $t$")
ax[1, 0].set_ylabel("Energy")
ax[1, 0].set_title("Energy Variations vs. Time")
ax[1, 0].legend()
ax[1, 0].grid(True)

# Plot 4
ax[1, 1].plot(t, v, label="v")
ax[1, 1].set_xlabel("Time $t$")
ax[1, 1].set_ylabel("velocity")
ax[1, 1].set_title("v(t)")
ax[1, 1].legend()
ax[1, 1].grid(True)
plt.tight_layout(rect=[0, 0.03, 1, 0.95])

out_png = "../results/task2b/plot2b_combined.png"
plt.savefig(out_png, dpi=300)
