// ode.cpp
#include "ode.h"
#include <cmath>
#include <stdexcept>

void compute_rhs(const std::vector<double>& u, double t, std::vector<double>& dudt, const Params& p) {
    if (u.size() != 2) throw std::runtime_error("state vector must have size 2");
    dudt.resize(2);
    double x = u[0];
    double v = u[1];

    // dx/dt = v
    dudt[0] = v;

    // dv/dt = -(k/m) x - (alpha/m) v + (F0/m) * sin(omega_ext * t)
    double Ft_over_m = -(p.k / p.m) * x - (p.alpha / p.m) * v + (p.F0 / p.m) * std::sin(p.omega_ext * t);
    dudt[1] = Ft_over_m;
}
