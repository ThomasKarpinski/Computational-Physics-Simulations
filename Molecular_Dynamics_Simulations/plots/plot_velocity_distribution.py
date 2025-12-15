import matplotlib.pyplot as plt
import numpy as np
import os

def maxwellian_2d(v, T):
    """
    Maxwellian velocity distribution for 2D gas in effective units (m=1, kB=1).
    f(v) = (m / (kB * T)) * v * exp(- m * v^2 / (2 * kB * T))
         = (1 / T) * v * exp(- v^2 / (2 * T))
    """
    return (v / T) * np.exp(- (v**2) / (2 * T))

def plot_velocity_distribution(output_dir="plots", data_dir="data/output"):
    Nit_values = [1000, 10000, 100000]
    T_target = 300.0
    T_ref = 119.0
    T_eff = T_target / T_ref
    
    fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=True)
    
    os.makedirs(output_dir, exist_ok=True)

    for i, Nit in enumerate(Nit_values):
        filename = os.path.join(data_dir, f"velocity_hist_{Nit}.txt")
        ax = axes[i]
        
        try:
            data = np.loadtxt(filename)
            if data.size == 0:
                ax.text(0.5, 0.5, f"No data for N_it={Nit}", ha='center', va='center')
                continue
                
            v_center = data[:, 0]
            prob_density = data[:, 1]
            
            width = v_center[1] - v_center[0]
            ax.bar(v_center, prob_density, width=width, align='center', alpha=0.5, color='red', label='Simulation (Hist)')
            
            v_plot = np.linspace(0, max(v_center) + width, 200)
            f_plot = maxwellian_2d(v_plot, T_eff)
            ax.plot(v_plot, f_plot, 'k-', linewidth=2, label='Maxwellian (Analytical)')
            
            ax.set_title(f'N_it = {Nit}')
            ax.set_xlabel('Velocity v')
            if i == 0:
                ax.set_ylabel('Probability Density f(v)')
            
            ax.legend()
            ax.grid(True, linestyle='--', alpha=0.5)
            
        except Exception as e:
            print(f"Error processing N_it={Nit}: {e}")
            ax.text(0.5, 0.5, f"Error: {e}", ha='center', va='center')

    plt.tight_layout()
    output_file = os.path.join(output_dir, "velocity_distribution.png")
    plt.savefig(output_file, dpi=300)
    print(f"Plot saved to {output_file}")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    data_dir = os.path.join(project_root, "data", "output")
    
    plot_velocity_distribution(output_dir=script_dir, data_dir=data_dir)
