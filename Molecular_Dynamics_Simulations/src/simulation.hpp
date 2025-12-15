#pragma once

#include <vector>
#include <random>
#include <memory>
#include <string>
#include "utils.hpp"
#include "potentials.hpp"
#include "integrator.hpp"

namespace MD {

class Simulation {
private:
    std::vector<Particle> particles;
    double dt;
    double box_size;
    int num_particles;

    std::unique_ptr<Potentials> potentials_calc;
    std::unique_ptr<Integrator> integrator;

public:
    Simulation(int N, double dt_val, double box_s, std::unique_ptr<Potentials> pc, std::unique_ptr<Integrator> integr);

    void initialize_particles(double temperature);
    void create_lattice_positions();
    void initialize_velocities(double temperature);
    void remove_velocity_drift();

    void run(int num_steps);
    void step();

    void set_thermostat(double Q, double T_target);

    double calculate_temperature() const;
    double get_kinetic_energy() const;
    double get_potential_energy() const;
    double get_total_energy() const;

    void save_positions(const std::string& filename) const;

    const std::vector<Particle>& get_particles() const;
    std::vector<Particle>& get_particles_mutable();
    
private:
    double current_potential_energy = 0.0;
};

} // namespace MD

