#ifndef ODE_H
#define ODE_H

#include <vector>

struct Params {
    double k;
    double m;
    double alpha;
    double F0;
    double omega_ext;
};

void compute_rhs(const std::vector<double>& u, double t, std::vector<double>& dudt, const Params& p);

#endif  // ODE_H
