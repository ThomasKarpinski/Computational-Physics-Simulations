import matplotlib.pyplot as plt
import numpy as np
import os

def plot_initial_positions(filename, box_size, output_file="initial_positions.png"):
    try:
        data = np.loadtxt(filename, comments='#')
        if data.size == 0:
            print(f"No data in {filename}")
            return
            
        if len(data.shape) == 1:
            data = data.reshape(1, -1)
            
        x = data[:, 1]
        y = data[:, 2]
        vx = data[:, 3]
        vy = data[:, 4]
        
        plt.figure(figsize=(8, 8))
        plt.quiver(x, y, vx, vy, color='red', scale=20, width=0.003, headwidth=3)
        plt.scatter(x, y, s=10, c='blue')
        
        plt.xlim(0, box_size)
        plt.ylim(0, box_size)
        plt.gca().set_aspect('equal', adjustable='box')
        plt.xlabel("x")
        plt.ylabel("y")
        plt.title("Task 1: Initial Positions and Velocities")
        plt.grid(True, linestyle='--', alpha=0.5)
        
        plt.plot([0, box_size, box_size, 0, 0], [0, 0, box_size, box_size, 0], 'b-')
        
        plt.savefig(output_file, dpi=300)
        print(f"Plot saved to {output_file}")
        
    except Exception as e:
        print(f"Error reading or plotting data: {e}")

if __name__ == "__main__":
    from plot_energy_conservation import plot_energy_conservation
    from plot_trajectory import plot_trajectory
    from plot_thermalization import plot_thermalization
    from plot_velocity_distribution import plot_velocity_distribution
    from plot_crystallization import plot_crystallization
    
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    t1_data = os.path.join(project_root, "data/output/initial_positions.txt")
    t1_out = os.path.join(script_dir, "initial_positions.png")
    plot_initial_positions(t1_data, 25.0, output_file=t1_out)
    
    t2a_data = os.path.join(project_root, "data/output/energy_conservation.txt")
    plot_energy_conservation(t2a_data, output_dir=script_dir)

    t2b_data = os.path.join(project_root, "data/output/trajectory.txt")
    t2b_out = os.path.join(script_dir, "trajectory.png")
    plot_trajectory(t2b_data, 25.0, output_file=t2b_out)

    t3_data_dir = os.path.join(project_root, "data/output")
    plot_thermalization(output_dir=script_dir, data_dir=t3_data_dir)

    t4_data_dir = os.path.join(project_root, "data/output")
    plot_velocity_distribution(output_dir=script_dir, data_dir=t4_data_dir)

    t5_data_dir = os.path.join(project_root, "data/output")
    plot_crystallization(output_dir=script_dir, data_dir=t5_data_dir)
