import subprocess
import os

def run_task(task_name, h, hw, t_high, plot_type="default"):
    print(f"Running task {task_name}...")
    
    try:
        subprocess.run(["make"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred during compilation: {e}")
        return
    except FileNotFoundError:
        print("Error with makefile")
        return
        
    try:
        subprocess.run(["./heat_diffusion", task_name, str(h), str(hw), str(t_high)], check=True)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred during C++ simulation for task {task_name}: {e}")
        return

    try:
        subprocess.run(["python3", "plotting.py", task_name, plot_type], check=True)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred during plotting for task {task_name}: {e}")
    except FileNotFoundError:
        print("Error with python")

def main():
    # Task 1
    run_task("1", 0.0, 0.0, 10000.0)
    # Task 2
    run_task("2", 0.002, 0.002, 10000.0)
    # Task 3
    run_task("3", 0.002, 0.01, 10000.0)
    # Task 4
    run_task("4", 0.002, 0.01, 298.0)
    # Task 5
    run_task("5", 0.0, 1.0, 298.0, "energy")
    # Task 6
    run_task("6", 0.0, 1.0, 10000.0, "energy")

if __name__ == "__main__":
    main()
