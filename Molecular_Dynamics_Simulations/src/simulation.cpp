#include "simulation.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>

namespace MD {

Simulation::Simulation(int N, double dt_val, double box_s, std::unique_ptr<Potentials> pc, std::unique_ptr<Integrator> integr)
    : particles(),
      dt(dt_val),
      box_size(box_s),
      num_particles(N),
      potentials_calc(std::move(pc)),
      integrator(std::move(integr)) {
    particles.reserve(num_particles);
}

void Simulation::initialize_particles(double temperature) {
    create_lattice_positions();
    initialize_velocities(temperature);
    
    double temp_before = calculate_temperature();
    std::cout << "Temperature before drift removal: " << temp_before << std::endl;

    remove_velocity_drift();
    
    double temp_after = calculate_temperature();
    std::cout << "Temperature after drift removal: " << temp_after << std::endl;

    if (potentials_calc) {
        current_potential_energy = potentials_calc->calculate_forces_and_energy(particles, box_size);
    }
}

void Simulation::create_lattice_positions() {
    particles.clear();
    double k = std::ceil(std::sqrt(num_particles));
    double delta = box_size / k;

    for (int i = 0; i < num_particles; ++i) {
        double x = delta * 0.5 + (i % (int)k) * delta;
        double y = delta * 0.5 + std::floor(i / k) * delta;
        
        
        particles.emplace_back(i, Vec2(x,y), Vec2(0.0,0.0), 1.0);
    }
}

void Simulation::initialize_velocities(double temperature) {
    double sigma = std::sqrt(temperature);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    for (auto& p : particles) {
        double sx = dist(gen);
        double sy = dist(gen);
        p.velocity.x = sigma * sx;
        p.velocity.y = sigma * sy;
    }
}

void Simulation::remove_velocity_drift() {
    Vec2 v_cm(0.0, 0.0);
    for (const auto& p : particles) {
        v_cm += p.velocity;
    }
    v_cm /= static_cast<double>(num_particles);

    for (auto& p : particles) {
        p.velocity -= v_cm;
    }
}

double Simulation::calculate_temperature() const {
    double kinetic_energy = 0.0;
    for (const auto& p : particles) {
        kinetic_energy += 0.5 * p.velocity.mag2();
    }
    return kinetic_energy / num_particles;
}

void Simulation::save_positions(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }
    out << "# id x y vx vy" << std::endl;
    for (const auto& p : particles) {
        out << p.id << " " << p.position.x << " " << p.position.y << " "
            << p.velocity.x << " " << p.velocity.y << std::endl;
    }
}

void Simulation::run(int num_steps) {
    for (int step_i = 0; step_i < num_steps; ++step_i) {
        step();
    }
}

void Simulation::step() {
    integrator->step1(particles, dt, box_size);
    if (potentials_calc) {
        current_potential_energy = potentials_calc->calculate_forces_and_energy(particles, box_size);
    }
    integrator->step2(particles, dt, box_size);
}

void Simulation::set_thermostat(double Q, double T_target) {
    auto vv_integrator = dynamic_cast<VelocityVerletIntegrator*>(integrator.get());
    if (vv_integrator) {
        vv_integrator->set_parameters(Q, T_target);
    }
}

double Simulation::get_kinetic_energy() const {
    double kinetic_energy = 0.0;
    for (const auto& p : particles) {
        kinetic_energy += 0.5 * p.mass * p.velocity.mag2();
    }
    return kinetic_energy;
}

double Simulation::get_potential_energy() const {
    return current_potential_energy;
}

double Simulation::get_total_energy() const {
    return get_kinetic_energy() + get_potential_energy();
}

const std::vector<Particle>& Simulation::get_particles() const {
    return particles;
}

std::vector<Particle>& Simulation::get_particles_mutable() {
    return particles;
}

}
