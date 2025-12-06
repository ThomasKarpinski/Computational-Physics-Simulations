import numpy as np
import matplotlib.pyplot as plt
import sys

def plot_displacement_map(task_name):
    """
    Plots a 2D displacement map for a given task.
    """
    displacement_file = f"{task_name}_displacement.csv"
    try:
        data = np.loadtxt(displacement_file, delimiter=",")
    except FileNotFoundError:
        print(f"Error: {displacement_file} not found.")
        return

    plt.figure(figsize=(8, 6))
    plt.imshow(data, aspect='auto', origin='lower',
               extent=[0, data.shape[1], 0, data.shape[0]])
    plt.colorbar(label="Displacement u(x,t)")
    plt.xlabel("Position x (node index)")
    plt.ylabel("Time t (step)")
    plt.title(f"Displacement map u(x,t) for {task_name}")
    plt.savefig(f"{task_name}_map.png", dpi=200)
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python plot_map.py <task_name>")
        sys.exit(1)
    
    task_name = sys.argv[1]
    plot_displacement_map(task_name)
