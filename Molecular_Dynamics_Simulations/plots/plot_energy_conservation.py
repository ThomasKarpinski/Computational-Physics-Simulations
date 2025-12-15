import matplotlib.pyplot as plt
import numpy as np
import os

def plot_energy_conservation(filename, output_dir="."):
    try:
        data = np.loadtxt(filename, comments='#')
        if data.size == 0:
            print(f"No data in {filename}")
            return

        steps = data[:, 0]
        time = data[:, 1]
        kinetic_energy = data[:, 2]
        potential_energy = data[:, 3]
        total_energy = data[:, 4]
        temperature = data[:, 5]

        os.makedirs(output_dir, exist_ok=True)

        plt.figure(figsize=(10, 6))
        plt.plot(time, kinetic_energy, label='Kinetic Energy')
        plt.plot(time, potential_energy, label='Potential Energy')
        plt.plot(time, total_energy, label='Total Energy')
        plt.xlabel('Time')
        plt.ylabel('Energy')
        plt.title('Task 2a: Energy Conservation Over Time')
        plt.legend()
        plt.grid(True, linestyle='--', alpha=0.5)
        
        out_energy = os.path.join(output_dir, 'energy_conservation.png')
        plt.savefig(out_energy)
        print(f"Plot saved to {out_energy}")

        plt.figure(figsize=(10, 6))
        plt.plot(time, temperature, label='Temperature')
        plt.xlabel('Time')
        plt.ylabel('Temperature')
        plt.title('Task 2a: Temperature Over Time')
        plt.legend()
        plt.grid(True, linestyle='--', alpha=0.5)
        
        out_temp = os.path.join(output_dir, 'temperature_over_time.png')
        plt.savefig(out_temp)
        print(f"Plot saved to {out_temp}")

    except Exception as e:
        print(f"Error reading or plotting data: {e}")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    data_file = os.path.join(project_root, "data", "output", "energy_conservation.txt")
    
    plot_energy_conservation(data_file, output_dir=script_dir)
