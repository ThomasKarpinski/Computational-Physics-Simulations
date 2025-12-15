import matplotlib.pyplot as plt
import numpy as np
import os

def plot_trajectory(filename, box_size, output_file="trajectory.png"):
    try:
        data = np.loadtxt(filename, comments='#')
        if data.size == 0:
            print(f"No data in {filename}")
            return
            
        steps = data[:, 0]
        x = data[:, 1]
        y = data[:, 2]

        plt.figure(figsize=(8, 8))
        plt.plot(x, y, label='Particle Trajectory', alpha=0.7)
        plt.scatter(x[0], y[0], color='red', marker='o', s=50, label='Start')
        plt.scatter(x[-1], y[-1], color='green', marker='x', s=50, label='End')
        
        plt.xlim(0, box_size)
        plt.ylim(0, box_size)
        plt.gca().set_aspect('equal', adjustable='box')
        plt.xlabel("x")
        plt.ylabel("y")
        plt.title("Task 2b: Particle Trajectory")
        plt.grid(True, linestyle='--', alpha=0.5)
        plt.legend()
        
        plt.plot([0, box_size, box_size, 0, 0], [0, 0, box_size, box_size, 0], 'b-')

        plt.savefig(output_file, dpi=300)
        print(f"Plot saved to {output_file}")
        
    except Exception as e:
        print(f"Error reading or plotting data: {e}")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    data_file = os.path.join(project_root, "data", "output", "trajectory.txt")
    out_file = os.path.join(script_dir, "trajectory.png")

    plot_trajectory(data_file, 25.0, output_file=out_file)
