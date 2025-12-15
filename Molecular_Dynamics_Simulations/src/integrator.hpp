#pragma once

#include <vector>
#include "utils.hpp"

namespace MD {

class Integrator {
public:
    virtual ~Integrator() = default;
    virtual void step1(std::vector<Particle>& particles, double dt_val, double box_size) = 0;
    virtual void step2(std::vector<Particle>& particles, double dt_val, double box_size) = 0;
};

class VelocityVerletIntegrator : public Integrator {
private:
    double xi;
    double Q;
    double target_temperature;
    int k_max;

public:
    VelocityVerletIntegrator();
    
    void set_parameters(double Q_val, double T_target, int iterations = 5);
    double get_xi() const { return xi; }

    void step1(std::vector<Particle>& particles, double dt_val, double box_size) override;
    void step2(std::vector<Particle>& particles, double dt_val, double box_size) override;
};

} // namespace MD