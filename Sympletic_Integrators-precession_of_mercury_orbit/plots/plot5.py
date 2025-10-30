import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

df = pd.read_csv("../data/task5/alpha_omega.csv")
alpha = df["alpha"].values
omega = df["omega"].values

def linear_model(x, a):
    return a * x

popt, pcov = curve_fit(linear_model, alpha, omega)
a_fit = popt[0]

print(f"Slope a = {a_fit:.6g}")

alpha_plot = alpha * 1e4
omega_plot = omega * 180 / np.pi

plt.scatter(alpha_plot, omega_plot, color='k', label="numerical")
alpha_fit = np.linspace(min(alpha), max(alpha), 100)
plt.plot(alpha_fit * 1e4, linear_model(alpha_fit, a_fit) * 180 / np.pi, 'r-', label="fit: dθ/dt=a*α")

plt.xlabel(r"$\alpha \times 10^{-4}$ [AU$^2$]")
plt.ylabel(r"$d\theta/dt$ [degree/year]")
plt.ylim(0,12)
plt.legend(loc="upper left")
plt.title(r"$\Delta t=10^{-5}$")
plt.tight_layout()
plt.savefig("task5_fit.png", dpi=300)

alpha_real = 1.1e-8
omega_real = a_fit * alpha_real
print(f"Predicted precession velocity for α = {alpha_real}: ω = {omega_real:.6g} rad/year")

omega_arcsec_century = omega_real * 206264.806 * 100
print(f"Predicted precession: {omega_arcsec_century:.4f} arcsec/century")
print("Reference value: 42.9799 arcsec/century")