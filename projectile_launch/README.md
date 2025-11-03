# Projectile Motion Simulation

This project is a C++ simulation of projectile motion, with and without air resistance. It uses the Euler method to solve the equations of motion and outputs the trajectory data to CSV files. The project also includes Python scripts for plotting the data and an interactive web dashboard for visualizing the results.

## Features

*   Simulates projectile motion with and without air drag.
*   Models air density variation with altitude.
*   Calculates the global error of the numerical solution.
*   Generates CSV files with trajectory data.
*   Includes Python scripts for plotting the trajectories.
*   Provides an interactive web dashboard to visualize the simulation results.

## File Descriptions

*   `projectile_trajectory.cpp`: The main C++ source file for the simulation.
*   `program`: The compiled C++ executable.
*   `*.csv`: CSV files containing the trajectory data.
*   `plots/`: Directory with Python scripts for generating plots from the CSV data.
*   `dashboard/`: Directory containing the Dash web application for interactive data visualization.
*   `task3_1/`, `task3_2/`, `task4/`: Directories containing the output of the simulation for different tasks.

## How to Run the Simulation

1.  Compile the C++ code:
    ```bash
    g++ projectile_trajectory.cpp -o program
    ```
2.  Run the simulation:
    ```bash
    ./program
    ```
    This will generate the CSV files with the trajectory data.

## How to Generate the Plots

1.  Install the required Python libraries:
    ```bash
    pip install matplotlib pandas
    ```
2.  Run the Python scripts in the `plots/` directory:
    ```bash
    python plots/drag.py
    ```
    This will generate the plots in the `plots/` directory.

## How to Run the Dashboard

1.  Go to the `dashboard/` directory:
    ```bash
    cd dashboard
    ```
2.  Install the required Python libraries from `requirements.txt`:
    ```bash
    pip install -r requirements.txt
    ```
3.  Run the Dash application:
    ```bash
    python app.py
    ```
4.  Open your web browser and go to `http://127.0.0.1:8050/` to view the dashboard.

## Dependencies

*   **C++ Compiler**: A C++ compiler that supports C++17 (for `std::filesystem`).
*   **Python 3**: For running the plotting scripts and the dashboard.
*   **Python Libraries**:
    *   `matplotlib`
    *   `pandas`
    *   `dash`
    *   `dash-bootstrap-components`
    *   `plotly`
