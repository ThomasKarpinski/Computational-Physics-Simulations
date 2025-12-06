import numpy as np
import matplotlib.pyplot as plt
import os

def load_csv(filename):
    return np.loadtxt(filename, delimiter=",", skiprows=1)

def plot_task6_all():
    fig, axs = plt.subplots(3, 3, figsize=(15, 12))
    fig.subplots_adjust(hspace=0.4, wspace=0.3)
    
    tasks = ['a', 'b', 'c']
    
    for i, sub in enumerate(tasks):
        task_name = f"task6{sub}"
        
        # 1. Energies
        try:
            en = load_csv(f"energies_{task_name}.csv")
            t = en[:, 0]
            Ek, Ep, Et = en[:, 1], en[:, 2], en[:, 3]
            
            ax = axs[i, 0]
            ax.plot(t, Ek, color="red", label="E_k")
            ax.plot(t, Ep, color="blue", label="E_p")
            ax.plot(t, Et, color="black", label="E_tot")
            ax.set_title(f"{task_name} Energies")
            ax.set_xlabel("t")
            ax.set_ylabel("Energy")
            if i == 0: ax.legend()
        except FileNotFoundError:
            print(f"energies_{task_name}.csv not found")

        # 2. Modal Energies
        try:
            spec = load_csv(f"{task_name}_spectral.csv")
            t_spec = spec[:, 0]
            e1 = spec[:, 1]
            e2 = spec[:, 2]
            e3 = spec[:, 3]
            
            ax = axs[i, 1]
            ax.plot(t_spec, e1, color="red", label="e1")
            ax.plot(t_spec, e2, color="blue", label="e2")
            ax.plot(t_spec, e3, color="black", label="e3")
            ax.set_title(f"{task_name} Modal Energies")
            ax.set_xlabel("t")
            ax.set_ylabel("Energy")
            if i == 0: ax.legend()
        except FileNotFoundError:
             print(f"{task_name}_spectral.csv not found")

        # 3. Map
        try:
            u_map = np.loadtxt(f"{task_name}_displacement.csv", delimiter=",")
            ax = axs[i, 2]
            # Aspect ratio 'auto' fills the plot
            im = ax.imshow(u_map, origin="lower", aspect="auto", cmap="seismic",
                           extent=[0, u_map.shape[1], 0, u_map.shape[0]])
            ax.set_title(f"{task_name} Map")
            ax.set_xlabel("x")
            ax.set_ylabel("t")
            fig.colorbar(im, ax=ax)
        except FileNotFoundError:
             print(f"{task_name}_displacement.csv not found")

    plt.savefig("task6_full_panel.png", dpi=200)
    # plt.show()
    print("Saved task6_full_panel.png")

if __name__ == "__main__":
    plot_task6_all()
