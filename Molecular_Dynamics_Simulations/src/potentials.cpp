#include "potentials.hpp"
#include <cmath>
#include <iostream>

namespace MD {

LennardJonesPotentials::LennardJonesPotentials(double eps, double sig, double r_cut)
    : epsilon(eps), sigma(sig), force_cutoff(0.0), energy_cutoff(0.0) {
    if (r_cut > 0) {
        rcut_sq = r_cut * r_cut;
        double r = r_cut;
        double r2 = r * r;
        double r6 = r2 * r2 * r2;
        double r12 = r6 * r6;
        double r7 = r6 * r;
        double r13 = r6 * r6 * r;
        
        double s6 = sigma * sigma * sigma * sigma * sigma * sigma;
        double s12 = s6 * s6;

        force_cutoff = 4.0 * epsilon * (-12.0 * s12 / r13 + 6.0 * s6 / r7);
        
        energy_cutoff = 4.0 * epsilon * (s12 / r12 - s6 / r6);
    } else {
        rcut_sq = -1.0;
    }
}

double LennardJonesPotentials::calculate_forces_and_energy(std::vector<Particle>& particles, double box_size) {
    for (auto& p : particles) {
        p.force = Vec2(0.0, 0.0);
    }

    double total_potential_energy = 0.0;
    double sigma6 = sigma * sigma * sigma * sigma * sigma * sigma;
    double sigma12 = sigma6 * sigma6;

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Vec2 rij_vec = particles[i].position - particles[j].position;

            if (box_size > 0) {
                if (rij_vec.x > box_size / 2.0) rij_vec.x -= box_size;
                if (rij_vec.x < -box_size / 2.0) rij_vec.x += box_size;
                if (rij_vec.y > box_size / 2.0) rij_vec.y -= box_size;
                if (rij_vec.y < -box_size / 2.0) rij_vec.y += box_size;
            }

            double r_sq = rij_vec.mag2();

            if (rcut_sq > 0 && r_sq > rcut_sq) {
                continue;
            }

            if (r_sq < 1e-10) {
                continue;
            }

            double r = std::sqrt(r_sq);
            double r2 = r_sq;
            double r6 = r2 * r2 * r2;
            double r12 = r6 * r6;
            double r7 = r6 * r;
            double r13 = r6 * r6 * r;

            double du_dr = 4.0 * epsilon * (-12.0 * sigma12 / r13 + 6.0 * sigma6 / r7);
            double force_scalar = -(du_dr - force_cutoff) / r;
            Vec2 force_ij = rij_vec * force_scalar;

            particles[i].force += force_ij;
            particles[j].force -= force_ij;

            double u_lj = 4.0 * epsilon * (sigma12 / r12 - sigma6 / r6);
            double u_shift = u_lj - energy_cutoff - force_cutoff * (r - std::sqrt(rcut_sq));
            
            total_potential_energy += u_shift;
        }
    }
    return total_potential_energy;
}

} // namespace MD
