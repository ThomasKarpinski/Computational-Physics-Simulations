import numpy as np
import matplotlib.pyplot as plt
import glob

def plot_task(task_name, ax_energy, ax_snap):
    # Energy
    try:
        data = np.loadtxt(f"energies_{task_name}.csv", delimiter=",", skiprows=1)
        t = data[:, 0]
        Ekin = data[:, 1]
        Epot = data[:, 2]
        Etot = data[:, 3]

        ax_energy.plot(t, Ekin, label="E_kin")
        ax_energy.plot(t, Epot, label="E_pot")
        ax_energy.plot(t, Etot, label="E_tot")
        ax_energy.set_xlabel("t")
        ax_energy.set_ylabel("Energy")
        ax_energy.set_title(f"Energy ({task_name})")
        ax_energy.legend()
        ax_energy.grid()
    except FileNotFoundError:
        print(f"File energies_{task_name}.csv not found")

    # Snapshots
    snap_files = sorted(glob.glob(f"u_snap_{task_name}_*.csv"),
                        key=lambda s: int(s.split("_")[-1].split(".")[0]))
    
    for f in snap_files:
        arr = np.loadtxt(f, delimiter=",")
        x = arr[:, 0]
        u = arr[:, 1]
        step = f.split("_")[-1].split(".")[0]
        ax_snap.plot(x, u, label=f"step {step}")

    ax_snap.set_xlabel("x")
    ax_snap.set_ylabel("u(x)")
    ax_snap.set_title(f"Snapshots ({task_name})")
    # ax_snap.legend(fontsize="x-small") 
    ax_snap.grid()

fig, axs = plt.subplots(2, 2, figsize=(12, 10))

plot_task("task3a", axs[0, 0], axs[0, 1])
plot_task("task3b", axs[1, 0], axs[1, 1])

plt.tight_layout()
plt.savefig("energy_snapshots_task3.png", dpi=200)
plt.show()
