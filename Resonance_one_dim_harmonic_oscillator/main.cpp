#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <filesystem>
#include <string>
#include <sstream>
#include <algorithm>

#include "ode.h"
#include "rk4.h"

namespace fs = std::filesystem;


void run_simulation(const std::string& task_name,
                    const Params& p,
                    double x0, double v0, double t0, double tmax, int N,
                    const std::string& suffix = "")
{
    std::string dir_path = "results/" + task_name;
    fs::create_directories(dir_path);

    std::string file_path;
    if (suffix.empty())
        file_path = dir_path + "/output.csv";
    else
        file_path = dir_path + "/" + suffix + ".csv";

    std::ofstream fout(file_path);
    if (!fout.is_open()) {
        std::cerr << "Cannot open " << file_path << " for writing\n";
        return;
    }

    fout << "t,x,v,Ekin,Epot,Etot\n";
    fout << std::fixed << std::setprecision(12);

    std::vector<double> u = {x0, v0};
    double dt = (tmax - t0) / double(N);
    double t = t0;

    // initial energy
    double Ekin = 0.5 * p.m * u[1] * u[1];
    double Epot = 0.5 * p.k * u[0] * u[0];
    fout << t << "," << u[0] << "," << u[1] << "," << Ekin << "," << Epot << "," << (Ekin + Epot) << "\n";

    for (int i = 0; i < N; ++i) {
        rk4_step(u, t, dt, p);
        Ekin = 0.5 * p.m * u[1] * u[1];
        Epot = 0.5 * p.k * u[0] * u[0];
        fout << t << "," << u[0] << "," << u[1] << "," << Ekin << "," << Epot << "," << (Ekin + Epot) << "\n";
    }

    fout.close();
    std::cout << "Saved results → " << file_path << std::endl;
}


void run_simulation_collect(const Params& p,
                            double x0, double v0, double t0, double tmax, int N,
                            std::vector<double>& times, std::vector<double>& xs)
{
    times.clear();
    xs.clear();

    std::vector<double> u = {x0, v0};
    double dt = (tmax - t0) / double(N);
    double t = t0;

    times.reserve(N + 1);
    xs.reserve(N + 1);

    times.push_back(t);
    xs.push_back(u[0]);

    for (int i = 0; i < N; ++i) {
        rk4_step(u, t, dt, p);
        times.push_back(t);
        xs.push_back(u[0]);
    }
}


double estimate_steady_amplitude(const std::vector<double>& times,
                                 const std::vector<double>& xs,
                                 double t_transient,
                                 int max_peaks_to_average = 10)
{
    std::vector<double> peaks;

    const size_t n = xs.size();
    if (n < 3) return 0.0;

    for (size_t i = 1; i + 1 < n; ++i) {
        if (times[i] < t_transient) continue;
        if (xs[i] > xs[i - 1] && xs[i] > xs[i + 1]) {
            peaks.push_back(std::abs(xs[i]));
        }
    }

    if (peaks.empty()) {
        double maxv = 0.0;
        for (size_t i = 0; i < n; ++i) if (times[i] >= t_transient) maxv = std::max(maxv, std::abs(xs[i]));
        return maxv;
    }

    int count = 0;
    double sum = 0.0;
    for (int i = int(peaks.size()) - 1; i >= 0 && count < max_peaks_to_average; --i, ++count) {
        sum += peaks[i];
    }
    return sum / double(count);
}

void save_timeseries(const std::string& dir, double omega, const std::vector<double>& times, const std::vector<double>& xs)
{
    std::ostringstream fname;
    fname << dir << "/omega_" << std::fixed << std::setprecision(3) << omega << ".csv";
    std::ofstream fout(fname.str());
    if (!fout.is_open()) {
        std::cerr << "Cannot open " << fname.str() << " for writing\n";
        return;
    }
    fout << "t,x\n";
    fout << std::fixed << std::setprecision(12);
    for (size_t i = 0; i < times.size(); ++i) {
        fout << times[i] << "," << xs[i] << "\n";
    }
    fout.close();
}


int main() {
    const double k = 1.0;
    const double m = 1.0;
    const double x0 = 1.0;
    const double v0 = 0.0;

    // baseline time settings for tasks 2 & 3
    const double t0 = 0.0;
    const double tmax_23 = 50.0;
    const int N_23 = 10000;

    // Task 2a (undamped)
    {
        Params p2a {k, m, 0.0, 0.0, 0.0};
        run_simulation("task2a", p2a, x0, v0, t0, tmax_23, N_23);
    }

    // Task 2b (damped)
    {
        Params p2b {k, m, 0.1, 0.0, 0.0};
        run_simulation("task2b", p2b, x0, v0, t0, tmax_23, N_23);
    }

    // Task 3: sweep alphas
    {
        std::vector<double> alphas = {1e-4, 0.1, 0.5, 1.95};
        for (double alpha : alphas) {
            Params p {k, m, alpha, 0.0, 0.0};
            std::ostringstream suffix;
            suffix << "alpha_" << std::fixed << std::setprecision(2) << alpha;
            run_simulation("task3", p, x0, v0, t0, tmax_23, N_23, suffix.str());
        }
    }

    // Task 4: driven oscillator
    {
    const double F0 = 1;
    const double t0_4 = 0.0;
    const double tmax_4 = 1e3;
    const int N_4 = 20000;
    const double t_transient = tmax_4 * 0.5;

    std::vector<double> alphas = {0.01, 0.1, 0.5, 1.0};

    std::vector<double> omegas;
    const double om_min = 0.1;
    const double om_max = 2.0;
    const double om_step = 0.01;
    for (double om = om_min; om <= om_max + 1e-12; om += om_step) omegas.push_back(om);

    std::string task4_dir = "results/task4";
    fs::create_directories(task4_dir);

    std::string out_csv = task4_dir + "/response_all_alphas.csv";
    std::ofstream fout(out_csv);
    if (!fout.is_open()) {
        std::cerr << "Cannot open " << out_csv << " for writing\n";
        return 1;
    }

    fout << "omega";
    for (double a : alphas) {
        std::ostringstream h;
        h << ",amp_a" << std::fixed << std::setprecision(2) << a;
        fout << h.str();
    }
    fout << "\n";
    fout << std::fixed << std::setprecision(12);

    std::vector<double> times, xs;
    std::vector<std::vector<double>> amps(alphas.size(), std::vector<double>(omegas.size(), 0.0));

    for (size_t ia = 0; ia < alphas.size(); ++ia) {
        double alpha = alphas[ia];
        std::ostringstream adir;
        adir << task4_dir << "/alpha_" << std::fixed << std::setprecision(2) << alpha;
        fs::create_directories(adir.str());

        for (size_t io = 0; io < omegas.size(); ++io) {
            double omega_ext = omegas[io];
            Params p {k, m, alpha, F0, omega_ext};

            run_simulation_collect(p, x0, v0, t0_4, tmax_4, N_4, times, xs);
            double amp = estimate_steady_amplitude(times, xs, t_transient, 10);
            amps[ia][io] = amp;

            std::ostringstream fname;
            fname << adir.str() << "/omega_" << std::fixed << std::setprecision(3) << omega_ext << ".csv";
            std::ofstream tf(fname.str());
            if (tf.is_open()) {
                tf << "t,x\n";
                tf << std::fixed << std::setprecision(12);
                for (size_t i = 0; i < times.size(); ++i) tf << times[i] << "," << xs[i] << "\n";
                tf.close();
            }

            if ((io % 50) == 0) {
                std::cout << "alpha=" << std::fixed << std::setprecision(2) << alpha
                          << " omega=" << std::fixed << std::setprecision(3) << omega_ext
                          << " amp=" << std::setprecision(6) << amp << "\n";
            }
        }
    }

    for (size_t io = 0; io < omegas.size(); ++io) {
        fout << omegas[io];
        for (size_t ia = 0; ia < alphas.size(); ++ia) {
            fout << "," << amps[ia][io];
        }
        fout << "\n";
    }

    fout.close();
    std::cout << "Task 4 (all alphas) completed. Combined response: " << out_csv << "\n";
}
    return 0;
}
