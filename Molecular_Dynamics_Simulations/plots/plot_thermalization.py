import matplotlib.pyplot as plt
import numpy as np
import os

def plot_thermalization(output_dir="plots", data_dir="data/output"):
    Q_values = [1.00, 0.10, 0.01]
    
    fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=False)
    
    os.makedirs(output_dir, exist_ok=True)

    for i, Q in enumerate(Q_values):
        filename = os.path.join(data_dir, f"thermalization_Q_{Q:.2f}.txt")
        ax = axes[i]
        
        try:
            data = np.loadtxt(filename, comments='#')
            if data.size == 0:
                ax.text(0.5, 0.5, f"No data for Q={Q}", ha='center', va='center')
                continue

            time = data[:, 1]
            kinetic_energy = data[:, 2]
            potential_energy = data[:, 3] 
            total_energy = data[:, 4]
            temperature = data[:, 5]

            
            ax.plot(time, kinetic_energy, label='Kinetic E', color='blue', alpha=0.7, linewidth=1)
            ax.plot(time, potential_energy, label='Potential E', color='orange', alpha=0.7, linewidth=1) # Added potential energy
            ax.plot(time, total_energy, label='Total E', color='green', alpha=0.7, linewidth=1)
            
            
            ax2 = ax.twinx()
            ax2.plot(time, temperature, label='Temp', color='red', alpha=0.6, linewidth=1)
            
            ax.set_xlabel('Time')
            ax.set_ylabel('Energy')
            ax2.set_ylabel('Temperature', color='red')
            ax2.tick_params(axis='y', labelcolor='red')
            
            ax.set_title(f'Q = {Q}')
            
            lines_1, labels_1 = ax.get_legend_handles_labels()
            lines_2, labels_2 = ax2.get_legend_handles_labels()
            ax.legend(lines_1 + lines_2, labels_1 + labels_2, loc='upper right')
            
            ax.grid(True, linestyle='--', alpha=0.5)

        except Exception as e:
            print(f"Error processing Q={Q}: {e}")
            ax.text(0.5, 0.5, f"Error: {e}", ha='center', va='center')

    plt.tight_layout()
    output_file = os.path.join(output_dir, "thermalization_comparison.png")
    plt.savefig(output_file, dpi=300)
    print(f"Plot saved to {output_file}")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    data_dir = os.path.join(project_root, "data", "output")
    
    plot_thermalization(output_dir=script_dir, data_dir=data_dir)
