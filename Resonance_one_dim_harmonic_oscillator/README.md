# Compilation and Execution

To compile and run the simulation, follow these steps:

1.  **Compile the code:**
    Open a terminal in the project directory and run the `make` command. This will compile the source files and create an executable named `sim`.

    ```bash
    make
    ```

2.  **Run the simulation:**
    After compilation, run the simulation by executing the `sim` file.

    ```bash
    ./sim
    ```

3.  **Clean up:**
    To remove the compiled object files and the executable, you can use the `clean` target in the Makefile.

    ```bash
    make clean
    ```

The simulation will generate output files in the `results` directory. The `plots` directory contains Python scripts to visualize the results.
