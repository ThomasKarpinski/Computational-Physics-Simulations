#ifndef SYMPLECTIC_H
#define SYMPLECTIC_H

#include <vector>

struct State {
    double x, y;      // position
    double vx, vy;    // velocity
};

void symplecticIntegrate(
    double tmax,
    double dt,
    double alpha,
    State &state,
    std::vector<double> &x_out,
    std::vector<double> &y_out
);

#endif
