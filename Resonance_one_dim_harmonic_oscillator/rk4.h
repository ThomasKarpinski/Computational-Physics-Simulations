// rk4.h
#ifndef RK4_H
#define RK4_H

#include <vector>
#include "ode.h"

void rk4_step(std::vector<double>& u, double& t, double dt, const Params& p);

#endif // RK4_H
