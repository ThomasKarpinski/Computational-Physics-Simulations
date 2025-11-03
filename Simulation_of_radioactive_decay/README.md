# Simulation of Radioactive Decay

This project simulates the radioactive decay of a three-isotope chain using a C++ program and visualizes the results with Python.

## Features

*   C++ simulation of a three-isotope radioactive decay chain.
*   Adaptive step-size control using the trapezoid method.
*   Comparison of simulation results with the analytical solution.
*   Python scripts for plotting the results.

## How to Run

1.  **Compile the C++ code:**
    ```bash
    make
    ```
2.  **Run the simulation:**
    ```bash
    ./sim
    ```
3.  **Generate the plots:**
    ```bash
    cd plots
    python3 plot2.py
    python3 plot3.py
    ```

## File Structure

*   `simulation.cpp`: The main C++ file that runs the simulation.
*   `adaptive.h`, `adaptive.cpp`: Contain the adaptive step-size solver.
*   `trapezoid.h`, `trapezoid.cpp`: Contain the trapezoid method for numerical integration.
*   `Makefile`: The makefile for compiling the C++ code.
*   `data/`: Directory containing the output data from the simulation.
*   `plots/`: Directory containing the Python scripts for plotting the results.
*   `plots/plot2.py`: Python script for plotting the results of task 2.
*   `plots/plot3.py`: Python script for plotting the results of task 3.
