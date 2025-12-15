#pragma once

#include <vector>
#include "utils.hpp"

namespace MD {

class Potentials {
public:
    virtual ~Potentials() = default;
    virtual double calculate_forces_and_energy(std::vector<Particle>& particles, double box_size) = 0;
};

class LennardJonesPotentials : public Potentials {
private:
    double epsilon;
    double sigma;
    double rcut_sq;
    double force_cutoff;
    double energy_cutoff;

public:
    LennardJonesPotentials(double eps, double sig, double r_cut);
    double calculate_forces_and_energy(std::vector<Particle>& particles, double box_size) override;
};

} // namespace MD
