# Molecular Dynamics Simulations

This project contains C++ code for Molecular Dynamics simulations and Python scripts for analysis and plotting.

## Structure
- `src/`: C++ source code for the simulation engine.
- `data/`: Input and output data.
- `docs/`: Project documentation.
- `notebooks/`: Jupyter notebooks for analysis.
- `plots/`: Python scripts for generating plots.
- `build/`: Compiled C++ binaries.
- `tests/`: Unit tests for the C++ code.

## Building (C++)
To compile the C++ simulation:
```bash
make
```

## Running (C++)
```bash
./build/md_simulation
```

## Python Environment
To set up the Python environment for plotting and analysis:
```bash
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```
