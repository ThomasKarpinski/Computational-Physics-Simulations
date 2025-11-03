# Symplectic Integrators for Simulating the Precession of Mercury's Orbit

This project is a C++ simulation of the precession of Mercury's orbit using a 4th order Neri symplectic integrator. The simulation takes into account the effects of general relativity, which are approximated by adding a term to the gravitational potential. The project also includes Python scripts for plotting the simulation results.

## How to Build and Run

To build the C++ simulation, you need a C++ compiler that supports C++17. Then, you can use the provided `Makefile`:

```bash
make
```

This will create an executable file named `sim`. To run the simulation, execute the following command:

```bash
./sim
```

The simulation will run through several tasks and save the output data to the `data` directory.

## How to Generate Plots

The Python scripts for generating the plots are located in the `plots` directory. To run them, you need to have Python 3 installed with the following libraries:

*   `matplotlib`
*   `pandas`
*   `numpy`
*   `scipy`

You can install these libraries using pip:

```bash
pip install matplotlib pandas numpy scipy
```

To generate the plots, navigate to the `plots` directory and run the Python scripts:

```bash
cd plots
python plot2.py
python plot3.py
python plot4.py
python plot5.py
```

The generated plots will be saved as PNG files in the `plots` directory.

## Project Structure

*   `main.cpp`: The main C++ source file that sets up and runs the simulations for the different tasks.
*   `sympletic.h`: The header file for the symplectic integrator.
*   `sympletic.cpp`: The implementation of the 4th order Neri symplectic integrator.
*   `Makefile`: The makefile for building the C++ simulation.
*   `data/`: This directory contains the output data from the simulations, organized into subdirectories for each task.
*   `plots/`: This directory contains the Python scripts for plotting the simulation results, as well as the generated plots.
*   `3_simplectic_mercury.pdf`: A document describing the project in more detail.
*   `TomaszKarpiński_report.pdf`: The project report.

## Tasks

The `main.cpp` file performs the following simulation tasks:

*   **Task 2**: Simulates Mercury's orbit for a short time with `alpha = 0` (no relativistic effects) and saves the trajectory.
*   **Task 3**: Simulates Mercury's orbit for a longer time (100 orbits) with `alpha = 0` and saves the trajectory.
*   **Task 4**: Simulates Mercury's orbit with `alpha = 0.01` to visualize the precession. It saves the trajectory, the radial distance, and the perihelion and aphelion points.
*   **Task 5**: Runs simulations for different values of `alpha` and calculates the precession rate `omega`. The results are used to fit a linear model and predict the precession of Mercury's orbit.

## Results

The simulation in **Task 5** predicts the precession of Mercury's orbit to be approximately 43 arcseconds per century, which is in good agreement with the observed value of 42.98 arcseconds per century.

