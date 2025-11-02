#ifndef ADAPTIVE_H
#define ADAPTIVE_H

#include "vector"

using namespace std;

vector<std::pair<double, std::array<double, 3>>> 
adaptive_solver(const std::array<double, 3>& lambda,
                std::array<double, 3> N0,
                double tmax,
                double dt0 = 1e-2,
                double TOL = 1e-6,
                double S = 0.9);


#endif