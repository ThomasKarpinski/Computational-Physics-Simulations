import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import re

m = 1.0
k = 1.0
F0 = 0.5
alpha_choice = 0.10

fn_combined = "../results/task4/response_all_alphas.csv"
if not os.path.exists(fn_combined):
    raise FileNotFoundError(f"{fn_combined} not found. Please produce response_all_alphas.csv in results/task4/")

df = pd.read_csv(fn_combined)
omega = df["omega"].values
amp_cols = [c for c in df.columns if c != "omega"]

alphas = []
amps = []
for c in amp_cols:
    mobj = re.search(r"(\d+\.\d+|\d+)", c)
    if mobj:
        alphas.append(float(mobj.group(1)))
    else:
        alphas.append(c)
    amps.append(df[c].values)

fig, ax = plt.subplots(1, 1, figsize=(8, 5))
ax = np.atleast_1d(ax)
y_ticks = [0.1, 1, 10, 100]

for a, A in zip(alphas, amps):
    ax[0].plot(omega, A, label=f"α={a:.2f}")


omega_dense = np.linspace(np.min(omega), np.max(omega), 1000)
omega0 = np.sqrt(k / m)
A_exact = (F0 / m) / np.sqrt((omega0**2 - omega_dense**2)**2 + (alpha_choice * omega_dense / m)**2)
ax[0].plot(omega_dense, A_exact, "--", linewidth=2, label=f"Analytical alpha={alpha_choice:.2f}")

ax[0].set_xlabel(r"$\omega_{\mathrm{ext}}$")
ax[0].set_ylabel("Amplitude")
ax[0].set_title("Steady-state amplitude vs driving frequency")
ax[0].grid(True)
ax[0].set_yscale('log')
ax[0].set_yticks(y_ticks)
ax[0].legend()
plt.tight_layout()
out_png = "../results/task4/response_all_alphas.png"
os.makedirs(os.path.dirname(out_png), exist_ok=True)
plt.savefig(out_png, dpi=300)
plt.show()
