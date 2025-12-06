import numpy as np
import matplotlib.pyplot as plt

# 1. Energies
data = np.loadtxt("energies_task5.csv", delimiter=",", skiprows=1)
t = data[:, 0]
Ekin = data[:, 1]
Epot = data[:, 2]
Etot = data[:, 3]

plt.figure(figsize=(10, 6))
plt.plot(t, Ekin, label="E_kin")
plt.plot(t, Epot, label="E_pot")
plt.plot(t, Etot, label="E_tot", linestyle='--')
plt.xlabel("t")
plt.ylabel("Energy")
plt.title("Energies (Task 5)")
plt.legend()
plt.grid()
plt.savefig("energy_task5.png", dpi=200)

# 2. Spectral d_k and Etot
spec_data = np.loadtxt("task5_spectral.csv", delimiter=",", skiprows=1)
# Header: t, e1, e2, e3, b1, b2, b3, d1, d2, d3
t_spec = spec_data[:, 0]
# d1 is at index 7 (0-based: t=0, e=1..3, b=4..6, d=7..9)
d1 = spec_data[:, 7]
d2 = spec_data[:, 8]
d3 = spec_data[:, 9]

plt.figure(figsize=(10, 6))
plt.plot(t_spec, d1, label="d1")
plt.plot(t_spec, d2, label="d2")
plt.plot(t_spec, d3, label="d3")
plt.plot(t, Etot, label="E_tot", color='black', linestyle='--', linewidth=1)
plt.xlabel("t")
plt.ylabel("Value")
plt.title("Coefficients d_k and Total Energy (Task 5)")
plt.legend()
plt.grid()
plt.savefig("spectral_task5.png", dpi=200)

# 3. Map
try:
    u_map = np.loadtxt("task5_displacement.csv", delimiter=",")
    plt.figure(figsize=(8, 6))
    plt.imshow(u_map, aspect='auto', origin='lower',
               extent=[0, u_map.shape[1], 0, u_map.shape[0]]) # Adjust extent if needed: x, t
    plt.colorbar(label="u(x,t)")
    plt.xlabel("x (node)")
    plt.ylabel("t (step)")
    plt.title("Displacement Map (Task 5)")
    plt.savefig("map_task5.png", dpi=200)
except FileNotFoundError:
    print("task5_displacement.csv not found")

# plt.show()

