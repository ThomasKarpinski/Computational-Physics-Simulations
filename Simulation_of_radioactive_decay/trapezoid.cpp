#include "trapezoid.h"
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;
std::array<double, 3> trapezoid(double dt, array<double, 3>& N, const array<double, 3>& lambda) {
    const double tolerance = 1e-10;
    int it = 0;
    array<double, 3> Nnew = N;
    const int ITmax = 50;
    double eps_max;
    do
    {
        it++;
        eps_max = 0.0;

        double F0 = Nnew[0] - N[0] - 0.5 * dt * ((-lambda[0]*N[0]) + (-lambda[0]*Nnew[0]));
        double F1 = Nnew[1] - N[1] - 0.5 * dt * ((lambda[0]*N[0] - lambda[1]*N[1]) + (lambda[0]*Nnew[0] - lambda[1]*Nnew[1]));
        double F2 = Nnew[2] - N[2] - 0.5 * dt * ((lambda[1]*N[1] - lambda[2]*N[2]) + (lambda[1]*Nnew[1] - lambda[2]*Nnew[2]));

        // matrix G elements
        double g00 = 1 + 0.5*dt*lambda[0];
        double g01 = 0.0;
        double g02 = 0.0;
        double g10 = -0.5 * dt * lambda[0];
        double g11 = 1 + 0.5*dt*lambda[1];
        double g12 = 0;
        double g20 = 0;
        double g22 = 1 + 0.5*dt*lambda[2];
        double g21 = -0.5*dt*lambda[1];

        double detG = g00*g11*g22 - g00*g12*g21 - g01*g10*g22 + g01*g12*g20 + g02*g10*g21 - g02*g11*g20;

        double dN0 = (-F0*g11*g22 + F0*g12*g21 + F1*g01*g22 - F1*g02*g21 - F2*g01*g12 + F2*g02*g11) / detG;
        double dN1 = (F0*g10*g22 - F0*g12*g20 - F1*g00*g22 + F1*g02*g20 + F2*g00*g12 - F2*g02*g10) / detG;
        double dN2 = (-F0*g10*g21 + F0*g11*g20 + F1*g00*g21 - F1*g01*g20 - F2*g00*g11 + F2*g01*g10) / detG;
        array<double, 3> dN = {dN0, dN1, dN2};

        for (int i = 0; i < 3; i++)
            Nnew[i] += dN[i];
        eps_max = max({fabs(dN0), fabs(dN1), fabs(dN2)});


    } while (eps_max > tolerance && it < ITmax);

    return Nnew;

}