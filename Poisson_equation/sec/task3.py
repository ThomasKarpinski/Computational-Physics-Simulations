import numpy as np
import matplotlib.pyplot as plt
import os

omegas = [1.0, 1.3, 1.6, 1.9]

plt.figure(figsize=(8, 6))
plt.title("Energy functional S vs iteration for different omega")
plt.xlabel("iteration")
plt.ylabel("S")

for omega in omegas:
    hist_file = f"S_delta_history_task3_omega_{omega:.1f}.csv"
    if os.path.exists(hist_file):
        history = np.loadtxt(hist_file, delimiter=",", skiprows=1)
        iters = history[:, 0]
        S_vals = history[:, 1]
        plt.plot(iters, S_vals, label=f"omega = {omega:.1f}")

plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("S_vs_iteration_task3.png")
plt.close()

plt.figure(figsize=(8, 6))
plt.title("Relative change delta vs iteration for different omega (log-log)")
plt.xlabel("iteration")
plt.ylabel("delta")

for omega in omegas:
    hist_file = f"S_delta_history_task3_omega_{omega:.1f}.csv"
    if os.path.exists(hist_file):
        history = np.loadtxt(hist_file, delimiter=",", skiprows=1)
        iters = history[:, 0]
        d_vals = history[:, 2]
        valid_indices = ~np.isnan(d_vals)
        plt.loglog(iters[valid_indices], d_vals[valid_indices], label=f"omega = {omega:.1f}")

plt.grid(True, which="both", ls="--")
plt.legend()
plt.tight_layout()
plt.savefig("delta_vs_iteration_task3.png")
plt.close()

print("Plots saved as S_vs_iteration_task3.png and delta_vs_iteration_task3.png")
