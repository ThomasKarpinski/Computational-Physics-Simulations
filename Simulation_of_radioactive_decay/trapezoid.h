#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <array>

std::array<double, 3> trapezoid(
    double dt,
    std::array<double, 3>& N,
    const std::array<double, 3>& lambda);

#endif