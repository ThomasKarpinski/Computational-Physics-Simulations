#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

double rho(double y, double a, double T0, double alpha) {
    double t = 1.0 - a * y / T0;
    if (t <= 0.0) return 0.0;
    return std::pow(t, alpha);
}

double runSimulation(double v0, double theta0, double delta_t, double D, double a, double m, double alpha, const std::string& filename) {

    double t = 0.0;
    const double g = 9.81;
    const double T0 = 293;
    
    // at the beginning
    double x = 0.0;
    double y = 0.0;

    // velocities
    double vx = v0 * std::cos(theta0);
    double vy = v0 * std::sin(theta0);

    bool RUN = true;

    std::ofstream results(filename);
    if (!results.is_open()) {
        std::cerr << "Error with opening the file: " << filename << std::endl;
        return -1.0; 
    }

    double x_final = 0.0;

    do {
        double v = sqrt(vx * vx + vy * vy);

        // save for collision correction
        double x_old = x;
        double y_old = y;
        double t_old = t;

        // calculating new position
        // Fx = Eq.15, Fy = Eq.15
        double Fx = -D * v * vx * rho(y, a, T0, alpha);
        double Fy = -D * v * vy * rho(y, a, T0, alpha);

        // Euler formula
        x = x + delta_t * vx;
        vx = vx + delta_t * (Fx / m);
        y = y + delta_t * vy;
        vy = vy + delta_t * ((Fy / m) - g);

        // time step
        t = t + delta_t; 

        // detect the collision + correct position
        if (y < 0.0) {
            // the fraction of time step after which the collision will be registered
            double r = y_old / (y_old - y);

            // position correction
            x = x_old + (x - x_old) * r;
            y = y_old + (y - y_old) * r; 

            // time correction
            t = t_old + (t - t_old) * r; // Use t_old and new t to correct time

            RUN = false; // stop
        }

        results << t << ", " << x << ", " << y << std::endl;
        x_final = x;

    } while (RUN);

    results.close();
    return x_final; // numerical x_max
}

double runSimulationRangeOnly(double v0, double theta0, double delta_t, double D, double a, double m, double alpha) {
    const double g = 9.81;
    const double T0 = 293;

    double t = 0.0;
    double x = 0.0;
    double y = 0.0;

    double vx = v0 * std::cos(theta0);
    double vy = v0 * std::sin(theta0);

    while (y >= 0.0) {
        double v = std::sqrt(vx * vx + vy * vy);
        double Fx = -D * v * vx * std::pow((1.0 - a * y / T0), alpha);
        double Fy = -D * v * vy * std::pow((1.0 - a * y / T0), alpha);

        double x_old = x;
        double y_old = y;

        x += delta_t * vx;
        vx += delta_t * (Fx / m);
        y += delta_t * vy;
        vy += delta_t * ((Fy / m) - g);

        t += delta_t;

        if (y < 0.0) {
            double r = y_old / (y_old - y);
            x = x_old + (x - x_old) * r;
            break;
        }

        if (t > 10000) {
            std::cerr << "Simulation timeout (no collision detected)" << std::endl;
            break;
        }
    }

    return x; // zwracamy tylko zasięg lotu
}

int main() {
    const double g = 9.81;
    double D = 0.0;
    double m = 1.0;
    double v0 = 100.0;
    double theta0 = M_PI / 4.0; // 45 stopni

    // anaitical
    double t_max_exact = 2 * v0 * std::sin(theta0) / g;
    double x_max_exact = (v0 * v0 * std::sin(2 * theta0)) / g;

    std::vector<int> n_values = {10, 20, 50, 100, 200, 500};
    std::ofstream errorFile("global_error.csv");
    errorFile << "n,delta_t,x_exact,x_num,E_global\n";

    for (int n : n_values) {
        double delta_t = t_max_exact / n;

        std::string filename = "trajectory_no_drag_" + std::to_string(n) + ".csv";
        double x_num = runSimulation(v0, theta0, delta_t, D, 0.0, m, 0.0, filename);

        double E_global = std::abs(x_max_exact - x_num);

        errorFile << n << "," << delta_t << "," << x_max_exact << "," << x_num << "," << E_global << "\n";

        std::cout << "n = " << n
                  << ", Δt = " << delta_t
                  << ", x_exact = " << x_max_exact
                  << ", x_num = " << x_num
                  << ", E_global = " << E_global << std::endl;
    }

    errorFile.close();
    std::cout << "All simulations completed. Global errors saved to global_error.csv" << std::endl;


    // first part of the third task

    std::vector<double> D_values_1 = {0, 1 * pow(10, -4), 2 * pow(10, -4), 5 * pow(10, -4), 1 * pow(10, -3)};
    double delta_t = t_max_exact / 500;
    double a = 0.0;
    double alpha = 0.0;

    std::string folder_name = "task3_1";
    std::filesystem::create_directory(folder_name);

    for (double D : D_values_1) {
    std::filesystem::path filepath = std::filesystem::path(folder_name) /
        ("trajectory_diff_drag_a0_D" + std::to_string(D) + ".csv");

    std::cout << "Running simulation for D = " << D << std::endl;

    double x_final = runSimulation(v0, theta0, delta_t, D, a, m, alpha, filepath.string());

    std::cout << "Range for D=" << D << " : " << x_final << " m" << std::endl;
}

    // second part of the third task
    double t_max_approx = 2 * v0 * std::sin(M_PI / 4.0) / g;
    double delta_t_2 = t_max_approx / 500.0;

    std::vector<double> D_values = {0.0, 1e-3, 2e-3};

    folder_name = "task3_2";
    std::filesystem::create_directory(folder_name);

    for (double D : D_values) {
        std::filesystem::path filepath = std::filesystem::path(folder_name) /
            ("range_vs_angle_D" + std::to_string(D) + ".csv");

        std::ofstream fout(filepath);
        if (!fout.is_open()) {
            std::cerr << "Error opening file " << filepath << std::endl;
            continue;
        }

        std::cout << "\n=== Simulations for D = " << D << " ===" << std::endl;

        // skanowanie kąta 15–65 (co 1)
        for (int deg = 15; deg <= 65; ++deg) {
            double theta_rad = deg * M_PI / 180.0;
            double x_range = runSimulationRangeOnly(v0, theta_rad, delta_t_2, D, a, m, alpha);
            fout << deg << "," << x_range << "\n";
            std::cout << "θ = " << deg << "°  →  range = " << x_range << " m" << std::endl;
        }

        fout.close();
        std::cout << "Saved results to: " << filepath << std::endl;
    }

    // task 4
    v0 = 700.0;
    m = 20.0;
    D = 1e-3;
    double alpha_air = 2.5;

    std::vector<double> angles_deg = {35.0, 45.0};
    std::vector<double> a_values = {0.0, 6.5e-3};

    folder_name = "task4";
    std::filesystem::create_directory(folder_name);

    t_max_approx = 2 * v0 * std::sin(M_PI / 4.0) / g;
    delta_t = t_max_approx / 500.0; // mały krok

    for (double a : a_values) {
        for (double deg : angles_deg) {
            double theta_rad = deg * M_PI / 180.0;

            std::filesystem::path filepath = std::filesystem::path(folder_name) /
                ("trajectory_D" + std::to_string(D) +
                 "_a" + std::to_string(a) +
                 "_alpha" + std::to_string((int)deg) + ".csv");

            std::cout << "Running simulation for alpha=" << deg
                      << "°, a=" << a
                      << " -> " << filepath.string() << std::endl;


            runSimulation(v0, theta_rad, delta_t, D, a, m, alpha_air, filepath.string());
        }
    }

    

    std::cout << "\nAll scans completed successfully!" << std::endl;
    return 0;
}