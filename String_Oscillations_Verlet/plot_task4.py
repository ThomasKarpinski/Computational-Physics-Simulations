import numpy as np
import matplotlib.pyplot as plt
import glob

data = np.loadtxt("energies_task4.csv", delimiter=",", skiprows=1)
t = data[:, 0]
Ekin = data[:, 1]
Epot = data[:, 2]
Etot = data[:, 3]

plt.figure()
plt.plot(t, Ekin, label="E_kin")
plt.plot(t, Epot, label="E_pot")
plt.plot(t, Etot, label="E_tot")
plt.xlabel("t")
plt.ylabel("Energy")
plt.title("Energy vs Time (Task 4)")
plt.legend()
plt.grid()
plt.savefig("energy_task4.png", dpi=200)

snap_files = sorted(glob.glob("u_snap_task4_*.csv"),
                    key=lambda s: int(s.split("_")[-1].split(".")[0]))

plt.figure()
for f in snap_files:
    arr = np.loadtxt(f, delimiter=",")
    x = arr[:, 0]
    u = arr[:, 1]
    step = f.split("_")[-1].split(".")[0]
    plt.plot(x, u, label=f"step {step}")

plt.xlabel("x")
plt.ylabel("u(x)")
plt.title("Snapshots of u(x,t) (Task 4)")
plt.legend(fontsize="small")
plt.grid()
plt.savefig("snapshots_task4.png", dpi=200)

plt.show()
