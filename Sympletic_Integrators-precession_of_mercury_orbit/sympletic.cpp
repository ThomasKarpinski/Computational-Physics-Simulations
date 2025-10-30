#include "sympletic.h"
#include <cmath>
#include <iostream>


void symplecticIntegrate(
    double tmax,
    double dt,
    double alpha,
    State &state,
    std::vector<double> &x_out,
    std::vector<double> &y_out
) {
    const double pi = M_PI;

    // Coefficients for Neri 4th order
    const double a1 = 1.0 / (2.0 * (2.0 - std::cbrt(2.0)));
    const double a2 = (1.0 - std::cbrt(2.0)) / (2.0 * (2.0 - std::cbrt(2.0)));
    const double a3 = a2;
    const double a4 = a1;

    const double b1 = 1.0 / (2.0 - std::cbrt(2.0));
    const double b2 = -std::cbrt(2.0) / (2.0 - std::cbrt(2.0));
    const double b3 = b1;
    const double b4 = 0.0;

    const double a[4] = {a1, a2, a3, a4};
    const double b[4] = {b1, b2, b3, b4};

    double t = 0.0;
    int nsteps = static_cast<int>(tmax / dt);

    for (int i = 0; i < nsteps; ++i) {
        double x = state.x, y = state.y;
        double vx = state.vx, vy = state.vy;
        double r;
        double w;

        for (int k = 0; k < 4; ++k) {
            x = x + a[k] * vx * dt;
            y = y + a[k] * vy * dt;

            r = std::sqrt(pow(x,2) + pow(y,2));
            w = -((4 * pow(pi,2)) / pow(r,3)) * (1 + alpha / pow(r,2));

            vx = vx + b[k] * w * x * dt;
            vy = vy + b[k] * w * y * dt;


        }
        
        state.x = x;
        state.y = y;
        state.vx = vx;
        state.vy = vy;

        // saving trajectory
        x_out.push_back(state.x);
        y_out.push_back(state.y);

        t += dt;
    }
}