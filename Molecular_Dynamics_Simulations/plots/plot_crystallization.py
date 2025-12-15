import matplotlib.pyplot as plt
import numpy as np
import os

def plot_crystallization(output_dir="plots", data_dir="data/output"):
    Nit_values = [10000, 100000]
    box_size = 25.0
    
    os.makedirs(output_dir, exist_ok=True)
    
    plt.figure(figsize=(10, 6))
    colors = ['red', 'blue']
    labels = ['Fast cooling ($N_{it}=10^4$)', 'Slow cooling ($N_{it}=10^5$)']
    
    for i, Nit in enumerate(Nit_values):
        temp_file = os.path.join(data_dir, f"crystallization_temp_Nit_{Nit}.txt")
        try:
            data = np.loadtxt(temp_file, comments='#')
            if data.size == 0:
                continue
            
            steps = data[:, 0]
            temp_eff = data[:, 2]
            
            plt.plot(steps, temp_eff, color=colors[i], label=labels[i], alpha=0.7, linewidth=0.5)
            
        except Exception as e:
            print(f"Error reading {temp_file}: {e}")

    plt.xlabel("Iteration Step")
    plt.ylabel("Temperature (Effective Units)")
    plt.title("Task 5: Cooling Process")
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.5)
    
    out_temp = os.path.join(output_dir, "crystallization_temperature.png")
    plt.savefig(out_temp, dpi=300)
    print(f"Plot saved to {out_temp}")
    
    fig, axes = plt.subplots(1, 2, figsize=(16, 8))
    
    for i, Nit in enumerate(Nit_values):
        pos_file = os.path.join(data_dir, f"crystallization_pos_Nit_{Nit}.txt")
        ax = axes[i]
        
        try:
            data = np.loadtxt(pos_file, comments='#')
            if data.size == 0:
                ax.text(0.5, 0.5, f"No data for Nit={Nit}", ha='center', va='center')
                continue
            
            if len(data.shape) == 1:
                data = data.reshape(1, -1)
                
            x = data[:, 1]
            y = data[:, 2]
            
            plot_color = 'red' if Nit == 10000 else 'blue'
            ax.scatter(x, y, s=20, c=plot_color)
            
            ax.set_xlim(0, box_size)
            ax.set_ylim(0, box_size)
            ax.set_aspect('equal', adjustable='box')
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_title(f"Final Positions (Nit={Nit})")
            ax.grid(True, linestyle='--', alpha=0.5)
            
            ax.plot([0, box_size, box_size, 0, 0], [0, 0, box_size, box_size, 0], 'b-')

        except Exception as e:
            print(f"Error reading {pos_file}: {e}")
            ax.text(0.5, 0.5, f"Error: {e}", ha='center', va='center')

    plt.tight_layout()
    out_pos = os.path.join(output_dir, "crystallization_positions.png")
    plt.savefig(out_pos, dpi=300)
    print(f"Plot saved to {out_pos}")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    data_dir = os.path.join(project_root, "data", "output")
    
    plot_crystallization(output_dir=script_dir, data_dir=data_dir)
