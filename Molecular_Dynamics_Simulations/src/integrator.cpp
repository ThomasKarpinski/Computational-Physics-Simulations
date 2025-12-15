#include "integrator.hpp"
#include <iostream>

namespace MD {

VelocityVerletIntegrator::VelocityVerletIntegrator() 
    : xi(0.0), Q(1e20), target_temperature(0.0), k_max(5) {}

void VelocityVerletIntegrator::set_parameters(double Q_val, double T_target, int iterations) {
    Q = Q_val;
    target_temperature = T_target;
    k_max = iterations;
    xi = 0.0;
}

void VelocityVerletIntegrator::step1(std::vector<Particle>& particles, double dt_val, double box_size) {
    double dt_half = 0.5 * dt_val;

    for (auto& p : particles) {
        Vec2 acc = p.force / p.mass;

        p.velocity_pred = p.velocity + (acc - p.velocity * xi) * dt_half;

        p.position += p.velocity_pred * dt_val;

        p.position = wrap_position(p.position, box_size);
    }
}

void VelocityVerletIntegrator::step2(std::vector<Particle>& particles, double dt_val, double box_size) {
    (void)box_size;
    double dt_half = 0.5 * dt_val;
    int N = particles.size();

    for (auto& p : particles) {
        p.velocity = p.velocity_pred;
    }

    for (int k = 0; k < k_max; ++k) {
        double E_kin = 0.0;
        for (const auto& p : particles) {
            E_kin += 0.5 * p.mass * p.velocity.mag2();
        }
        
        
        xi += (dt_val / Q) * (E_kin - target_temperature * (N + 1));

        double factor = 1.0 / (1.0 + dt_half * xi);
        for (auto& p : particles) {
            Vec2 acc = p.force / p.mass;
            p.velocity = (p.velocity_pred + acc * dt_half) * factor;
        }
    }
}

} // namespace MD
