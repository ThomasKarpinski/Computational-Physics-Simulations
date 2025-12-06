# String Oscillations Simulation using Velocity Verlet Method

This project simulates the oscillations of a 1D string under various physical conditions using the Velocity Verlet numerical integration method. It investigates different boundary conditions, wave packet propagation, non-homogeneous media effects, spectral decomposition, and mechanical resonance.

## Table of Contents
1.  [Project Overview](#project-overview)
2.  [Prerequisites](#prerequisites)
3.  [Compilation](#compilation)
4.  [Running the Simulation](#running-the-simulation)
5.  [Generating Plots](#generating-plots)
6.  [Cleaning Up](#cleaning-up)

## Project Overview
The simulation is based on solving the 1D wave equation with additional terms for damping and external forces. The core numerical method employs Finite Differences for spatial discretization and the Velocity Verlet algorithm for time integration. The project includes C++ code for the simulation and Python scripts for data processing and visualization.

## Prerequisites
Before running the simulation and plotting scripts, ensure you have the following installed:

*   **C++ Compiler**: A C++11 compatible compiler (e.g., `g++`).
*   **Python 3**: A Python 3 interpreter.
*   **Python Libraries**: `numpy` and `matplotlib`. You can install them using pip:
    ```bash
    pip install numpy matplotlib
    ```

## Compilation
Navigate to the project's root directory in your terminal and compile the C++ source code:

```bash
g++ -O2 -o string_verlet main.cpp verlet.cpp
```
This command will create an executable named `string_verlet`.

## Running the Simulation
Execute the compiled program to generate all simulation data files (`.csv` format). This process might take some time as it runs multiple tasks sequentially.

```bash
./string_verlet
```
The simulation will generate various CSV files for energies, displacements, snapshots, and spectral coefficients (e.g., `energies_task1.csv`, `u_snap_task1_100.csv`, `task1_displacement.csv`, `task5_spectral.csv`).

## Generating Plots
After generating the data, run the Python plotting scripts to create the corresponding `.png` image files. It's recommended to run them in the following order:

```bash
python3 plot_task1.py
python3 plot_task2.py
python3 plot_task3.py
python3 plot_task4.py
python3 plot_task5.py
python3 plot_task6.py
# Generate displacement maps for tasks that don't have them in their main plot script
python3 plot_map.py task1
python3 plot_map.py task2
python3 plot_map.py task3a
python3 plot_map.py task3b
python3 plot_map.py task4
```
This will generate various `.png` files (e.g., `energy_task1.png`, `task1_map.png`, `task6_full_panel.png`) in the project directory.

## Cleaning Up
To remove all generated data files, plot images, and the executable, you can run the following commands:

```bash
rm -f string_verlet
rm -f *.csv
rm -f *.png
```
This will leave only the source code, plotting scripts, and documentation files.
