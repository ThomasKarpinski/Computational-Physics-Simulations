#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <filesystem>

#include "sympletic.h"

namespace fs = std::filesystem;

int main() {
    const double Tm = 0.240846;
    double tmax = 0.95 * Tm;
    double dt = 1e-4;
    double alpha = 0.0;

    const double a = 0.397098;
    const double e = 0.206;
    const double GMs = 4.0 * M_PI * M_PI;
    const double Ms = 1.998*1e30;
    const double m = 2.4 * 1e23;

    const double rmax = a * (1.0 + e);
    double vmin = std::sqrt(GMs * (1.0 - e) / (a * (1.0 + e)) * (1 + m / Ms));

    State mercury {rmax, 0.0, 0.0, vmin};

    std::vector<double> x1, y1;

    symplecticIntegrate(tmax, dt, alpha, mercury, x1, y1);

    fs::create_directory("data/task2");
    std::ofstream fout("data/task2/trajectory_alpha0.csv");
    fout << "x" << "," << "y" << "\n";
    for (size_t i = 0; i < x1.size(); ++i)
        fout << x1[i] << "," << y1[i] << "\n";
    fout.close();

    std::cout << "Simulation finished. Data saved to data/task2/trajectory_alpha0.csv\n";

    // Task 3
    tmax = 100 * Tm;

    std::vector<double> x2, y2;

    symplecticIntegrate(tmax, dt, alpha, mercury, x2, y2);

    fs::create_directory("data/task3");
    std::ofstream fout2("data/task3/trajectory_alpha0.csv");
    fout2 << "x" << "," << "y" << "\n";
    for (size_t i = 0; i < x2.size(); ++i)
        fout2 << x2[i] << "," << y2[i] << "\n";
    fout2.close();

    std::cout << "Simulation finished. Data saved to data/task3/trajectory_alpha0.csv\n";

    // Task 4
    tmax = 4 * Tm;
    alpha = 0.01;

    std::vector<double> x3, y3;
    symplecticIntegrate(tmax, dt, alpha, mercury, x3, y3);

    std::vector<double> r;
    for (size_t i = 0; i < x3.size(); ++i){
        r.push_back(std::sqrt(x3[i]*x3[i] + y3[i]*y3[i]));
    }
    
    fs::create_directory("data/task4");
    std::ofstream fout3("data/task4/trajectory_alpha01.csv");
    fout3 << "x" << "," << "y" << "\n";
    for (size_t i = 0; i < x3.size(); i++)
    {
        fout3 << x3[i] << "," << y3[i] << "\n";
    }
    fout3.close();

    std::ofstream fout4("data/task4/extrema.csv");
    fout4 << "r" << "\n";
    for (double i :r) {
        fout4 << i << "\n";
    }
    std::cout << "Simulation finished. Data saved to data/task4/extrema.csv\n";

    std::vector<size_t> perihelium_indices, aphelium_indices;
    std::vector<double> perihelium_values, aphelium_values;

    for (size_t i = 1; i + 1 < r.size(); ++i) {
        if (r[i] < r[i - 1] && r[i] < r[i + 1]) {
            perihelium_indices.push_back(i);
            perihelium_values.push_back(r[i]);
        }
        if (r[i] > r[i - 1] && r[i] > r[i + 1]) {
            aphelium_indices.push_back(i);
            aphelium_values.push_back(r[i]);
        }
    }

    std::ofstream fout_extrema("data/task4/peri_aphe.csv");
    fout_extrema << "type,index,r\n";
    for (size_t j = 0; j < perihelium_indices.size(); ++j) {
        fout_extrema << "perihelium," << perihelium_indices[j] << "," << perihelium_values[j] << "\n";
    }
    for (size_t j = 0; j < aphelium_indices.size(); ++j) {
        fout_extrema << "aphelium," << aphelium_indices[j] << "," << aphelium_values[j] << "\n";
    }
    fout_extrema.close();

    std::cout << "Perihelium and aphelium results saved to data/task4/peri_aphe.csv\n";

    // Task 5
    dt = 1e-5;
    tmax = 3;
    const double aplpha_max = 0.001;
    std::vector<double> alphas;
    for (int i = 0; i <= 6; i++)
    {
        alphas.push_back(aplpha_max / pow(2,i));
    }

    fs::create_directory("data/task5");
    std::ofstream fout_omega("data/task5/alpha_omega.csv");
    fout_omega << "alpha,omega\n";

    for (size_t i = 0; i < alphas.size(); i++)
    {
        std::vector<double> x, y;
        symplecticIntegrate(tmax, dt, alphas[i], mercury, x, y);

        std::vector<double> r, theta;
        for (size_t j = 0; j < x.size(); ++j) {
            r.push_back(std::sqrt(x[j]*x[j] + y[j]*y[j]));
            theta.push_back(std::atan2(y[j], x[j]));
        }

        size_t first = -1, second = -1;
        for (size_t j = 1; j + 1 < r.size(); ++j) {
            if (r[j] < r[j-1] && r[j] < r[j+1]) {
                if (first == (size_t)-1)
                    first = j;
                else if (second == (size_t)-1) {
                    second = j;
                    break;
                }
            }
        }

        if (first != (size_t)-1 && second != (size_t)-1) {
            double theta1 = theta[first];
            double theta2 = theta[second];
            double t1 = first * dt;
            double t2 = second * dt;
            double omega = (theta2 - theta1) / (t2 - t1);

            if (omega < 0) omega += 2*M_PI/(t2-t1);

            fout_omega << alphas[i] << "," << omega << "\n";
        }
    }
    fout_omega.close();
    std::cout << "Alpha and omega results saved to data/task5/alpha_omega.csv\n";
    
    
}

