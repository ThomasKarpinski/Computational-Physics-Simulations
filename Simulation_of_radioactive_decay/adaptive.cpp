#include "trapezoid.h"
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::pair<double, std::array<double, 3>>> 
adaptive_solver(const std::array<double, 3>& lambda,
                std::array<double, 3> N0,
                double tmax,
                double dt0,
                double TOL,
                double S)
{
    std::vector<std::pair<double, std::array<double, 3>>> results;
    const int p = 2; // trapezoidal order

    double t = 0.0;
    double dt = dt0;
    std::array<double, 3> N = N0;

    results.push_back({t, N});

    while (t < tmax) {
        std::array<double, 3> N1, N2_half, N2, eps;
        double eps_max;

        do {
            N1 = trapezoid(dt, N, lambda);
            N2_half = trapezoid(dt/2, N, lambda);
            N2 = trapezoid(dt/2, N2_half, lambda);

            for (int i = 0; i < 3; i++)
                eps[i] = (N2[i] - N1[i]) / (pow(2.0, p) - 1.0);
            eps_max = std::max({fabs(eps[0]), fabs(eps[1]), fabs(eps[2])});

            double dt_new = S * dt * pow(TOL / eps_max, 1.0 / (p + 1));
            dt = dt_new;
        } while (TOL / eps_max < 1.0);

        for (int i = 0; i < 3; i++)
            N[i] = N2[i] + eps[i];

        t += dt;
        results.push_back({t, N});
    }

    return results;
}
