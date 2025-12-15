#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "simulation.hpp"
#include "potentials.hpp"
#include "integrator.hpp"

const int NUM_PARTICLES = 201;
const double BOX_SIZE = 25.0;
const double DT = 0.002;
const double T_TARGET_KELVIN = 300.0;
const double T_REF = 119.0;
const double TEMP_EFF = T_TARGET_KELVIN / T_REF;
const double EPSILON = 1.0;
const double SIGMA = 1.0;
const double R_CUT = 2.7 * SIGMA;

void run_task_1(MD::Simulation& sim) {
    std::cout << "--- Task 1: Initialization Check ---" << std::endl;
    sim.initialize_particles(TEMP_EFF);
    
    std::string out_file = "data/output/initial_positions.txt";
    sim.save_positions(out_file);
    std::cout << "Initial positions saved to " << out_file << std::endl;
}

void run_task_2a(MD::Simulation& sim) {
    std::cout << "--- Task 2a: Energy Conservation (Microcanonical) ---" << std::endl;
    sim.initialize_particles(TEMP_EFF);
    
    double Q = 1e20;
    sim.set_thermostat(Q, TEMP_EFF);

    int steps = 10000;
    std::ofstream out("data/output/energy_conservation.txt");
    out << "# step time kinetic potential total temperature" << std::endl;

    for (int i = 1; i <= steps; ++i) {
        sim.step();
        
        if (i % 10 == 0) {
            double time = i * DT;
            double ek = sim.get_kinetic_energy();
            double ep = sim.get_potential_energy();
            double et = sim.get_total_energy();
            double temp = sim.calculate_temperature();

            out << i << " " << time << " " << ek << " " << ep << " " << et << " " << temp << std::endl;
        }
    }
    std::cout << "Task 2a completed. Data saved to data/output/energy_conservation.txt" << std::endl;
}

void run_task_2b(MD::Simulation& sim) {
    std::cout << "--- Task 2b: Particle Trajectory ---" << std::endl;
    sim.initialize_particles(TEMP_EFF);
    
    double Q = 1e20;
    sim.set_thermostat(Q, TEMP_EFF);

    int steps = 50000;
    std::ofstream out("data/output/trajectory.txt");
    out << "# step x y" << std::endl;

    int tracked_id = NUM_PARTICLES / 2;

    for (int i = 1; i <= steps; ++i) {
        sim.step();

        if (i % 10 == 0) {
            const auto& particles = sim.get_particles();
            const auto& p = particles[tracked_id];
            out << i << " " << p.position.x << " " << p.position.y << std::endl;
        }
    }
    std::cout << "Task 2b completed. Data saved to data/output/trajectory.txt" << std::endl;
}

void run_task_3(MD::Simulation& sim) {
    std::cout << "--- Task 3: Thermalization Process ---" << std::endl;
    std::vector<double> Q_values = {1.0, 0.1, 0.01};
    int steps = 10000;

    for (double Q : Q_values) {
        std::cout << "Running for Q = " << Q << "..." << std::endl;
        sim.initialize_particles(TEMP_EFF);
        sim.set_thermostat(Q, TEMP_EFF);

        std::stringstream ss;
        ss << "data/output/thermalization_Q_" << std::fixed << std::setprecision(2) << Q << ".txt";
        std::string filename = ss.str();
        std::ofstream out(filename);
        out << "# step time kinetic potential total temperature" << std::endl;

        double total_temp = 0.0;
        int count = 0;

        for (int i = 1; i <= steps; ++i) {
            sim.step();
            
            double temp = sim.calculate_temperature();
            total_temp += temp;
            count++;
            
            if (i % 10 == 0) {
                double time = i * DT;
                double ek = sim.get_kinetic_energy();
                double ep = sim.get_potential_energy();
                double et = sim.get_total_energy();
                out << i << " " << time << " " << ek << " " << ep << " " << et << " " << temp << std::endl;
            }
        }
        
        double mean_temp = total_temp / count;
        std::cout << "  Mean Temperature (Effective): " << mean_temp << std::endl;
        std::cout << "  Mean Temperature (Kelvin): " << mean_temp * T_REF << " K" << std::endl; 
        std::cout << "  Data saved to " << filename << std::endl;
    }
}

void run_task_4(MD::Simulation& sim) {
    std::cout << "--- Task 4: Velocity Distribution ---" << std::endl;
    std::vector<int> Nit_values = {1000, 10000, 100000};
    double Q = 10.0;
    
    double vc = std::sqrt(2.0 * TEMP_EFF);
    double vmax = 4.0 * vc;
    int nv = 50;
    double delta_v = vmax / nv;

    for (int Nit : Nit_values) {
        std::cout << "Running for Nit = " << Nit << "..." << std::endl;
        
        sim.initialize_particles(TEMP_EFF);
        sim.set_thermostat(Q, TEMP_EFF);
        
        std::vector<double> histogram(nv, 0.0);
        
        for (int step = 1; step <= Nit; ++step) {
            sim.step();
            
            const auto& particles = sim.get_particles();
            for (const auto& p : particles) {
                double v = p.velocity.mag();
                int k = static_cast<int>(std::floor(v / delta_v));
                
                if (k < nv) {
                    histogram[k] += 1.0;
                }
            }
        }
        
        std::stringstream ss;
        ss << "data/output/velocity_hist_" << Nit << ".txt";
        std::string filename = ss.str();
        std::ofstream out(filename);
        out << "# v_center probability_density" << std::endl;
        
        
        double norm_factor = 1.0 / (static_cast<double>(Nit) * NUM_PARTICLES * delta_v);
        
        for (int k = 0; k < nv; ++k) {
            double bin_center = (k + 0.5) * delta_v;
            double val = histogram[k] * norm_factor;
            out << bin_center << " " << val << std::endl;
        }
        
        std::cout << "  Data saved to " << filename << std::endl;
    }
}

void run_task_5(MD::Simulation& sim) {
    std::cout << "--- Task 5: Crystallization ---" << std::endl;
    double Q = 1.0;
    double T_max_K = 300.0;
    double T_min_K = 5.0;
    int nT = 500;
    std::vector<int> Nit_values = {10000, 100000};
    
    for (int Nit : Nit_values) {
        std::cout << "Running crystallization for Nit = " << Nit << "..." << std::endl;
        
        int Kit = Nit / nT;
        double dT_K = (T_max_K - T_min_K) / static_cast<double>(nT);
        
        double T_max_eff = T_max_K / T_REF;
        sim.initialize_particles(T_max_eff);
        sim.set_thermostat(Q, T_max_eff);
        
        std::stringstream ss_temp, ss_pos;
        ss_temp << "data/output/crystallization_temp_Nit_" << Nit << ".txt";
        ss_pos << "data/output/crystallization_pos_Nit_" << Nit << ".txt";
        
        std::ofstream out_temp(ss_temp.str());
        out_temp << "# step time temp_eff target_temp_eff" << std::endl;
        
        for (int step = 1; step <= Nit; ++step) {
            double T_curr_K = T_max_K - dT_K * std::floor(static_cast<double>(step) / Kit);
            if (T_curr_K < T_min_K) T_curr_K = T_min_K;
            
            double T_curr_eff = T_curr_K / T_REF;
            
            sim.set_thermostat(Q, T_curr_eff);
            sim.step();
            
            if (step % 10 == 0) {
                double temp = sim.calculate_temperature();
                double time = step * DT;
                out_temp << step << " " << time << " " << temp << " " << T_curr_eff << std::endl;
            }
        }
        
        sim.save_positions(ss_pos.str());
        std::cout << "  Data saved to " << ss_temp.str() << " and " << ss_pos.str() << std::endl;
    }
}

int main() {
    std::unique_ptr<MD::Potentials> lj_potentials =
        std::make_unique<MD::LennardJonesPotentials>(EPSILON, SIGMA, R_CUT);
    
    std::unique_ptr<MD::Integrator> vv_integrator =
        std::make_unique<MD::VelocityVerletIntegrator>();

    MD::Simulation sim(NUM_PARTICLES, DT, BOX_SIZE, std::move(lj_potentials), std::move(vv_integrator));

    run_task_1(sim);
    run_task_2a(sim);
    run_task_2b(sim);
    run_task_3(sim);
    run_task_4(sim);
    run_task_5(sim);

    return 0;
}
