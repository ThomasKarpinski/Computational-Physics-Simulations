import numpy as np
import matplotlib.pyplot as plt
import os

def plot_task(task_label):
    """
    Reads data for a given task and creates plots for potential and residual.
    """
    pot_file = f"potential_task4{task_label}.csv"
    res_file = f"residual_task4{task_label}.csv"

    if not (os.path.exists(pot_file) and os.path.exists(res_file)):
        print(f"Data files for task 4{task_label} not found.")
        return

    V = np.loadtxt(pot_file, delimiter=",")
    residual = np.loadtxt(res_file, delimiter=",")

    N = V.shape[0]
    L = 4.0
    x = np.linspace(-L, L, N)
    y = np.linspace(-L, L, N)

    plt.figure(figsize=(6, 5))
    plt.title(f"Potential V(x,y) - Task 4{task_label}")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.imshow(V.T, origin='lower', extent=[x[0], x[-1], y[0], y[-1]])
    plt.colorbar(label='V')
    plt.tight_layout()
    plt.savefig(f"potential_task4{task_label}.png")
    plt.close()

    plt.figure(figsize=(6, 5))
    plt.title(f"Absolute residual |r(i,j)| - Task 4{task_label}")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.imshow(np.abs(residual).T, origin='lower', extent=[x[0], x[-1], y[0], y[-1]])
    plt.colorbar(label='|r|')
    plt.tight_layout()
    plt.savefig(f"residual_task4{task_label}.png")
    plt.close()

    print(f"Plots for task 4{task_label} saved.")

if __name__ == "__main__":
    plot_task("a")
    plot_task("b")
