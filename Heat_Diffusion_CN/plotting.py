import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def plot_sensor_temperature(task_name):
    dir_name = "task_" + task_name
    data = np.loadtxt(os.path.join(dir_name, "sensor_temp.txt"))
    time = data[:, 0]
    temp = data[:, 1]

    plt.figure(figsize=(10, 6))
    plt.plot(time, temp)
    plt.xlabel("Time")
    plt.ylabel("Sensor Temperature")
    plt.title(f"Sensor Temperature vs. Time (Task {task_name})")
    plt.grid(True)
    plt.savefig(os.path.join(dir_name, "sensor_temperature.png"))
    plt.close()

def plot_heat_map(time, task_name):
    dir_name = "task_" + task_name
    filename = os.path.join(dir_name, f"map_{time}.txt")
    data = np.loadtxt(filename)
    
    if data.size == 0:
        print(f"No data for time {time} in task {task_name}")
        return

    x = data[:, 0]
    y = data[:, 1]
    temp = data[:, 2]

    N = int(np.sqrt(len(temp)))
    X = x.reshape((N, N))
    Y = y.reshape((N, N))
    T = temp.reshape((N, N))

    plt.figure(figsize=(10, 8))
    plt.contourf(X, Y, T, levels=50, cmap='inferno')
    plt.colorbar(label="Temperature")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title(f"Heat Map at t = {time} (Task {task_name})")
    plt.gca().set_aspect('equal', adjustable='box')
    plt.savefig(os.path.join(dir_name, f"heat_map_{time}.png"))
    plt.close()

def plot_energies(task_name):
    dir_name = "task_" + task_name
    data = np.loadtxt(os.path.join(dir_name, "energies.txt"))
    time = data[:, 0]
    e_supplied = data[:, 1]
    e_window = data[:, 2]

    plt.figure(figsize=(10, 6))
    plt.plot(time, e_supplied, label="Supplied Energy")
    plt.plot(time, e_window, label="Window Energy Loss")
    plt.xlabel("Time")
    plt.ylabel("Energy")
    plt.title(f"Energy vs. Time (Task {task_name})")
    plt.legend()
    plt.grid(True)
    plt.savefig(os.path.join(dir_name, "energies.png"))
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) not in [2, 3]:
        print("Usage: python3 plotting.py <task_name> [plot_type]")
        sys.exit(1)
    
    task_name = sys.argv[1]
    plot_type = "default"
    if len(sys.argv) == 3:
        plot_type = sys.argv[2]

    if plot_type == "default":
        plot_sensor_temperature(task_name)
        plot_heat_map(10, task_name)
        plot_heat_map(100, task_name)
        plot_heat_map(1000, task_name)
        plot_heat_map(10000, task_name)
    elif plot_type == "energy":
        plot_energies(task_name)
