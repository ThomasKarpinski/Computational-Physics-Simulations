#include "verlet.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cassert>

Verlet::Verlet(const VerletParams &p) : params(p) {
    N = params.N;
    L = params.L;
    dx = L / (N - 1);
    double c0 = std::sqrt(params.T / params.Q);
    dt = params.alpha * dx / c0;

    initialize_mesh();
    set_initial_conditions();
}

void Verlet::initialize_mesh() {
    rho.assign(N, params.Q);
    if (params.nonhomogeneous) {
        for (int i = 0; i < N; ++i) {
            double xi = dx * i;
            if (xi > L/2.0) rho[i] = 10.0 * params.Q;
            else rho[i] = params.Q;
        }
    }
    c.assign(N, 0.0);
    for (int i = 0; i < N; ++i) c[i] = std::sqrt(params.T / rho[i]);

    u.assign(N, 0.0);
    v.assign(N, 0.0);
    a.assign(N, 0.0);
    vhalf.assign(N, 0.0);
}

void Verlet::set_initial_conditions() {
    if (params.task_name == "task5") {
        for (int i = 0; i < N; ++i) {
            double xi = dx * i;
            u[i] = params.uinit * (std::sin(1.0 * M_PI * xi / L) + 
                                   std::sin(2.0 * M_PI * xi / L) + 
                                   std::sin(3.0 * M_PI * xi / L));
            v[i] = 0.0;
        }
    } else {
        double sigma = params.sigma * L;
        for (int i = 0; i < N; ++i) {
            double xi = dx * i;
            u[i] = params.uinit * std::exp(-((xi - params.xA)*(xi - params.xA)) / (2.0 * sigma * sigma));
        }
        for (int i = 0; i < N; ++i) {
            double xi = dx * i;
            v[i] = params.vinit * ((xi - params.xA) / (sigma * sigma)) * u[i];
        }
    }

    compute_acceleration(u, v, a, 0.0);
}

void Verlet::apply_boundary_conditions(std::vector<double> &uvec) {
    if (params.bc == FIXED) {
        uvec[0] = 0.0;
        uvec[N-1] = 0.0;
    } else {
        uvec[0] = uvec[1];
        uvec[N-1] = uvec[N-2];
    }
}

void Verlet::compute_acceleration(const std::vector<double> &uvec,
                                  const std::vector<double> &vvec,
                                  std::vector<double> &avec,
                                  double t) {
    for (int i = 1; i <= N-2; ++i) {
        double lap = (uvec[i+1] - 2.0*uvec[i] + uvec[i-1]) / (dx * dx);
        double forcing = 0.0;
        if (i == params.ip) forcing = params.Fext * std::sin(params.Omega * t);
        avec[i] = c[i]*c[i] * lap - params.gamma * vvec[i] + forcing;
    }
    avec[0] = 0.0;
    avec[N-1] = 0.0;
}

double Verlet::compute_Ekin() const {
    double E = 0.0;
    for (int i = 1; i <= N-2; ++i) {
        double mi = dx * rho[i];
        E += mi * v[i] * v[i] / 2.0;
    }
    return E;
}

double Verlet::compute_Epot() const {
    double E = 0.0;
    for (int i = 1; i <= N-1; ++i) {
        double deriv = (u[i] - u[i-1]) / dx;
        E += dx * params.T / 2.0 * (deriv * deriv);
    }
    return E;
}

double Verlet::omega_k(int k) const {
    double c0 = std::sqrt(params.T / params.Q);
    double angle = (double)k * M_PI / (double)(N - 1);
    double val = c0 / dx * std::sqrt(2.0 * (1.0 - std::cos(angle)));
    return val;
}

void Verlet::compute_spectral(int step, std::vector<double> &bk, std::vector<double> &dk, std::vector<double> &ek) const {
    int Km = params.Kmodes;
    if (Km <= 0) return;

    bk.assign(Km+1, 0.0);
    dk.assign(Km+1, 0.0);
    ek.assign(Km+1, 0.0);

    for (int k = 1; k <= Km; ++k) {
        double sum_b = 0.0;
        double sum_d = 0.0;
        for (int i = 1; i <= N-2; ++i) {
            double s = std::sin((double)k * M_PI * (double)i / (double)(N - 1));
            sum_b += u[i] * s;
            sum_d += v[i] * s;
        }
        bk[k] = 2.0 / (double)(N - 1) * sum_b;
        dk[k] = 2.0 / (double)(N - 1) * sum_d;

        double sin2 = std::sin((double)k * M_PI / (double)(N - 1));
        sin2 = sin2 * sin2;
        double term_pot = params.T * dx * sin2 / (dx * dx) * (bk[k] * bk[k]);
        double term_kin = params.Q * dx * (dk[k] * dk[k]);
        ek[k] = (double)(N - 1) / 4.0 * (term_pot + term_kin);
    }
}

void Verlet::write_energies_header(std::ofstream &ofs) const {
    ofs << "t,Ekin,Epot,Etot\n";
}

void Verlet::write_energies_line(std::ofstream &ofs, double t, double Ekin, double Epot) const {
    ofs << std::fixed << std::setprecision(10) << t << "," << Ekin << "," << Epot << "," << (Ekin + Epot) << "\n";
}

void Verlet::run(const std::string &energy_out, const std::string &u_snapshot_prefix, const std::string &spectral_out) {

    std::string disp_file = params.task_name + "_displacement.csv";
    std::ofstream dispofs(disp_file);
    if (!dispofs.is_open()) {
        std::cerr << "Cannot open displacement output file: " << disp_file << std::endl;
        return;
    }

    
    for (int i = 0; i < N; ++i) {
        dispofs << u[i];
        if (i < N-1) dispofs << ",";
    }
    dispofs << "\n";

    std::ofstream eofs(energy_out);
    if (!eofs.is_open()) {
        std::cerr << "Cannot open energy output file: " << energy_out << std::endl;
        return;
    }
    write_energies_header(eofs);

    std::ofstream sofs;
    bool spectral = false;
    if (!spectral_out.empty() && params.Kmodes > 0) {
        sofs.open(spectral_out);
        if (!sofs.is_open()) {
             std::cerr << "Cannot open spectral output file: " << spectral_out << std::endl;
        } else {
            spectral = true;
            sofs << "t";
            for (int k = 1; k <= params.Kmodes; ++k) sofs << ",e" << k;
            for (int k = 1; k <= params.Kmodes; ++k) sofs << ",b" << k;
            for (int k = 1; k <= params.Kmodes; ++k) sofs << ",d" << k;
            sofs << "\n";
        }
    }

    double t = 0.0;
    double Ekin = compute_Ekin();
    double Epot = compute_Epot();
    write_energies_line(eofs, t, Ekin, Epot);

    if (spectral) {
        std::vector<double> bk, dk, ek;
        compute_spectral(0, bk, dk, ek);
        sofs << std::fixed << std::setprecision(10) << t;
        for (int k = 1; k <= params.Kmodes; ++k) sofs << "," << ek[k];
        for (int k = 1; k <= params.Kmodes; ++k) sofs << "," << bk[k];
        for (int k = 1; k <= params.Kmodes; ++k) sofs << "," << dk[k];
        sofs << "\n";
    }

    int Nt = params.Nt;
    for (int it = 1; it <= Nt; ++it) {
        t = (it - 1) * dt;

        compute_acceleration(u, v, a, t);

        for (int i = 1; i <= N-2; ++i) {
            vhalf[i] = v[i] + 0.5 * dt * a[i];
        }

        std::vector<double> u_new = u;
        for (int i = 1; i <= N-2; ++i) {
            u_new[i] = u[i] + vhalf[i] * dt;
        }

        apply_boundary_conditions(u_new);

        std::vector<double> a_new(N, 0.0);
        compute_acceleration(u_new, vhalf, a_new, t + dt);

        for (int i = 1; i <= N-2; ++i) {
            v[i] = vhalf[i] + 0.5 * dt * a_new[i];
        }

        u.swap(u_new);

        for (int i = 0; i < N; ++i) {
            dispofs << u[i];
            if (i < N-1) dispofs << ",";
        }
        dispofs << "\n";

        double tt = t + dt;
        double Ekin_now = compute_Ekin();
        double Epot_now = compute_Epot();
        write_energies_line(eofs, tt, Ekin_now, Epot_now);

        if (spectral) {
            std::vector<double> bk, dk, ek;
            compute_spectral(it, bk, dk, ek);
            sofs << std::fixed << std::setprecision(10) << tt;
            for (int k = 1; k <= params.Kmodes; ++k) sofs << "," << ek[k];
            for (int k = 1; k <= params.Kmodes; ++k) sofs << "," << bk[k];
            for (int k = 1; k <= params.Kmodes; ++k) sofs << "," << dk[k];
            sofs << "\n";
        }

        if (it % 100 == 0) {
            std::ofstream uof(u_snapshot_prefix + "_" + std::to_string(it) + ".csv");
            for (int i = 0; i < N; ++i) {
                uof << (i * dx) << "," << u[i] << "\n";
            }
            uof.close();
        }
    }

    eofs.close();
    dispofs.close();
    if (spectral) sofs.close();
    std::cout << "Simulation finished. Energies saved to '" << energy_out << "'.\n";
}
