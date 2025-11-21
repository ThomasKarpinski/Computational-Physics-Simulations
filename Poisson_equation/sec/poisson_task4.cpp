#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

inline int idx(int i, int j, int N) { return i * N + j; }

void solve(double A_rho, int k1, int k2, int k3, int k4, const string& pot_filename, const string& res_filename) {
    const double L = 4.0;
    const int    N = 100;
    const double Vmax = 1.0;
    const double eps  = 1.0;
    const double TOL  = 1e-8;
    const int Kmax    = 10000;
    const double omega = 1.5;

    const double dx = 2.0 * L / (N - 1);
    const double pi = acos(-1.0);

    vector<double> V(N*N, 0.0);
    vector<double> rho(N*N, 0.0);

    vector<double> x(N), y(N);
    for (int i = 0; i < N; i++) {
        x[i] = -L + i * dx;
        y[i] = -L + i * dx;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rho[idx(i, j, N)] = A_rho * x[i] * y[j] * exp(-(x[i]*x[i] + y[j]*y[j]));
        }
    }

    for (int j = 0; j < N; j++) {
        V[idx(0, j, N)]     = (k1 != 0) ? Vmax * sin(k1 * pi * (y[j] + L) / (2*L)) : 0.0;
        V[idx(N-1, j, N)]   = (k3 != 0) ? Vmax * sin(k3 * pi * (y[j] + L) / (2*L)) : 0.0;
    }
    for (int i = 0; i < N; i++) {
        V[idx(i, 0, N)]     = (k4 != 0) ? Vmax * sin(k4 * pi * (x[i] + L) / (2*L)) : 0.0;
        V[idx(i, N-1, N)]   = (k2 != 0) ? Vmax * sin(k2 * pi * (x[i] + L) / (2*L)) : 0.0;
    }

    auto compute_S = [&](const vector<double>& V) {
        double S = 0.0;
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double Ex = -(V[idx(i+1,j,N)] - V[idx(i-1,j,N)]) / (2*dx);
                double Ey = -(V[idx(i,j+1,N)] - V[idx(i,j-1,N)]) / (2*dx);
                S += (0.5 * (Ex*Ex + Ey*Ey) - V[idx(i,j,N)]*rho[idx(i,j,N)]) * dx * dx;
            }
        }
        return S;
    };

    double Sold = compute_S(V);
    bool converged = false;

    for (int k = 1; k <= Kmax; k++) {
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double rhs = (V[idx(i+1,j,N)] + V[idx(i-1,j,N)] + 
                              V[idx(i,j+1,N)] + V[idx(i,j-1,N)] + 
                              rho[idx(i,j,N)]*dx*dx/eps) * 0.25;
                V[idx(i,j,N)] = (1 - omega)*V[idx(i,j,N)] + omega*rhs;
            }
        }

        double Snew = compute_S(V);
        double delta = fabs((Snew - Sold) / Sold);

        if (delta < TOL) {
            converged = true;
            cout << "Converged for " << pot_filename << " at iteration " << k << endl;
            break;
        }
        Sold = Snew;
    }

    if (!converged) {
        cout << "Did not converge for " << pot_filename << endl;
    }

    vector<double> residual(N*N, std::numeric_limits<double>::quiet_NaN());
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            double lap =
                (V[idx(i+1,j,N)] - 2*V[idx(i,j,N)] + V[idx(i-1,j,N)])/(dx*dx) +
                (V[idx(i,j+1,N)] - 2*V[idx(i,j,N)] + V[idx(i,j-1,N)])/(dx*dx);
            residual[idx(i,j,N)] = lap + rho[idx(i,j,N)]/eps;
        }
    }

    auto write_csv = [&](string filename, const vector<double>& arr) {
        ofstream out(filename);
        out.setf(ios::scientific);
        out.precision(9);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                out << arr[idx(i,j,N)];
                if (j < N - 1) out << ",";
            }
            out << "\n";
        }
    };

    write_csv(pot_filename, V);
    write_csv(res_filename, residual);
    cout << "CSV files written: " << pot_filename << ", " << res_filename << endl;
}

int main() {
    solve(1.0, 0, 0, 0, 0, "potential_task4a.csv", "residual_task4a.csv");
    solve(1.0, 1, -1, 1, -1, "potential_task4b.csv", "residual_task4b.csv");
    return 0;
}
