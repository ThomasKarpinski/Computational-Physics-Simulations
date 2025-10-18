#include "rk4.h"
#include "ode.h"
#include <vector>

void rk4_step(std::vector<double>& u, double& t, double dt, const Params& p) {
    const size_t n = 2;
    std::vector<double> k1(n), k2(n), k3(n), k4(n), w(n);

    // k1 = f(t, u)
    compute_rhs(u, t, k1, p);

    // k2 = f(t + dt/2, u + dt/2 * k1)
    for (size_t i = 0; i < n; ++i) w[i] = u[i] + 0.5 * dt * k1[i];
    compute_rhs(w, t + 0.5 * dt, k2, p);

    // k3 = f(t + dt/2, u + dt/2 * k2)
    for (size_t i = 0; i < n; ++i) w[i] = u[i] + 0.5 * dt * k2[i];
    compute_rhs(w, t + 0.5 * dt, k3, p);

    // k4 = f(t + dt, u + dt * k3)
    for (size_t i = 0; i < n; ++i) w[i] = u[i] + dt * k3[i];
    compute_rhs(w, t + dt, k4, p);

    // u <- u + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
    for (size_t i = 0; i < n; ++i) {
        u[i] += dt * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]) / 6.0;
    }

    t += dt;
}
