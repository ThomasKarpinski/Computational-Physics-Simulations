#include "adaptive.h"
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <filesystem>
#include <cmath>

namespace fs = std::filesystem;

int main() {
    // Task 1 - implementation
    std::array<double, 3> lambda = {1.0, 5.0, 50.0};
    std::array<double, 3> N0 = {1.0, 0.0, 0.0};
    double tmax = 200.0;

    // Task 2 - test of corretness

    std::vector<std::pair<double, std::array<double, 3>>> results = adaptive_solver(lambda, N0, tmax);

    fs::create_directory("data/task2");
    std::ofstream fout("data/task2/test.csv");
    fout << "t" << "," << "N0" << "," << "N1" << "," << "N2" << "," << "N0_analytical" << "," << "N1_analytical" << "," << "N2_analytical" << "\n";
    
    for (const auto& result : results) {
        double t = result.first;
        double N0_analytical = N0[0] * exp(-lambda[0] * t);
        double N1_analytical = (lambda[0] * N0[0] / (lambda[1] - lambda[0])) * (exp(-lambda[0] * t) - exp(-lambda[1] * t));
        double N2_analytical = N0[0] * (1 + (lambda[0] * exp(-lambda[1] * t) - lambda[1] * exp(-lambda[0] * t)) / (lambda[1] - lambda[0]));
        fout << t << "," << result.second[0] << "," << result.second[1] << "," << result.second[2] << "," << N0_analytical << "," << N1_analytical << "," << N2_analytical << std::endl;
    }

    fout.close();

    return 0;
}
