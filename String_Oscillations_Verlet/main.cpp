#include "verlet.h"
#include <iostream>
#include <cmath>
#include <string>

double calculate_omega(int k, double T, double Q, double L, int N) {
    double c = std::sqrt(T / Q);
    double dx = L / (N - 1);
    double angle = (double)k * M_PI / (double)(N - 1);
    return (c / dx) * std::sqrt(2.0 * (1.0 - std::cos(angle)));
}

void run_task(VerletParams p, std::string spectral_out = "") {
    std::cout << "Running " << p.task_name << "..." << std::endl;
    Verlet solver(p);
    solver.run("energies_" + p.task_name + ".csv", "u_snap_" + p.task_name, spectral_out);
}

int main() {
    // Common parameters
    double L = 1.0;
    double Q = 1.0;
    double T = 100.0;
    int N = 301;
    double c = std::sqrt(T / Q);

    // Task 1
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = FIXED;
        p.uinit = 0.01;
        p.xA = L / 2.0;
        p.sigma = L / 20.0;
        p.vinit = 0.0;
        p.Nt = 2000;
        p.task_name = "task1";
        run_task(p);
    }

    // Task 2
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = OPEN;
        p.uinit = 0.01;
        p.xA = L / 2.0;
        p.sigma = L / 20.0;
        p.vinit = 0.0;
        p.Nt = 2000;
        p.task_name = "task2";
        run_task(p);
    }

    // Task 3a
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = OPEN;
        p.uinit = 0.01;
        p.xA = L / 2.0;
        p.sigma = L / 20.0;
        p.vinit = c / 2.0;
        p.Nt = 4000;
        p.task_name = "task3a";
        run_task(p);
    }

    // Task 3b
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = OPEN;
        p.uinit = 0.01;
        p.xA = L / 2.0;
        p.sigma = L / 20.0;
        p.vinit = c;
        p.Nt = 4000;
        p.task_name = "task3b";
        run_task(p);
    }

    // Task 4
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = OPEN;
        p.uinit = 0.01;
        p.xA = L / 4.0;
        p.sigma = L / 20.0;
        p.vinit = c;
        p.Nt = 4000;
        p.nonhomogeneous = true;
        p.task_name = "task4";
        run_task(p);
    }

    // Task 5
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = FIXED;
        p.uinit = 0.01;
        p.vinit = 0.0;
        p.gamma = 150.0;
        p.Kmodes = 3;
        p.Nt = 4000;
        p.task_name = "task5";
        run_task(p, "task5_spectral.csv");
    }

    // Task 6
    double omega1 = calculate_omega(1, T, Q, L, N);
    double omega2 = calculate_omega(2, T, Q, L, N);

    // Task 6a
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = FIXED;
        p.uinit = 0.0;
        p.vinit = 0.0;
        p.gamma = 0.0;
        p.Fext = 100.0;
        p.Omega = omega1;
        p.ip = 30;
        p.Kmodes = 3;
        p.Nt = 10000;
        p.task_name = "task6a";
        run_task(p, "task6a_spectral.csv");
    }

    // Task 6b
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = FIXED;
        p.uinit = 0.0;
        p.vinit = 0.0;
        p.gamma = 0.0;
        p.Fext = 100.0;
        p.Omega = omega2;
        p.ip = 30;
        p.Kmodes = 3;
        p.Nt = 10000;
        p.task_name = "task6b";
        run_task(p, "task6b_spectral.csv");
    }

    // Task 6c
    {
        VerletParams p;
        p.L = L; p.Q = Q; p.T = T; p.N = N;
        p.bc = FIXED;
        p.uinit = 0.0;
        p.vinit = 0.0;
        p.gamma = 0.0;
        p.Fext = 100.0;
        p.Omega = omega2;
        p.ip = (N - 1) / 2;
        p.Kmodes = 3;
        p.Nt = 10000;
        p.task_name = "task6c";
        run_task(p, "task6c_spectral.csv");
    }

    return 0;
}
