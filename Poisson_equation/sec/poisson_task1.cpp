#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

inline int idx(int i, int j, int N) { return i * N + j; }

int main() {
    const double L = 4.0;
    const int    N = 100;
    const double Vmax = 1.0;
    const double eps  = 1.0;
    const double A_rho = 0.0;
    const int k1 = 1, k2 = -1, k3 = 1, k4 = -1;
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

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            rho[idx(i, j, N)] = 0.0;

    for (int j = 0; j < N; j++) {
        V[idx(0, j, N)]     = Vmax * sin(k1 * pi * (y[j] + L) / (2*L));
        V[idx(N-1, j, N)]   = Vmax * sin(k3 * pi * (y[j] + L) / (2*L));
    }
    for (int i = 0; i < N; i++) {
        V[idx(i, 0, N)]     = Vmax * sin(k4 * pi * (x[i] + L) / (2*L));
        V[idx(i, N-1, N)]   = Vmax * sin(k2 * pi * (x[i] + L) / (2*L));
    }

    auto compute_S = [&](const vector<double>& V) {
        double S = 0.0;
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double Ex = -(V[idx(i+1,j,N)] - V[idx(i-1,j,N)]) / (2*dx);
                double Ey = -(V[idx(i,j+1,N)] - V[idx(i,j-1,N)]) / (2*dx);
                S += 0.5 * (Ex*Ex + Ey*Ey) * dx * dx;
            }
        }
        return S;
    };

    vector<double> S_hist;
    vector<double> delta_hist;

    double Sold = compute_S(V);
    S_hist.push_back(Sold);
    delta_hist.push_back(std::numeric_limits<double>::quiet_NaN());

    bool converged = false;
    int iter_conv = -1;

    for (int k = 1; k <= Kmax; k++) {

        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double rhs = (V[idx(i+1,j,N)] + V[idx(i-1,j,N)] +
                              V[idx(i,j+1,N)] + V[idx(i,j-1,N)]) * 0.25;
                V[idx(i,j,N)] = (1 - omega)*V[idx(i,j,N)] + omega*rhs;
            }
        }

        double Snew = compute_S(V);
        S_hist.push_back(Snew);

        double delta = fabs((Snew - Sold) / Sold);
        delta_hist.push_back(delta);

        if (delta < TOL) {
            converged = true;
            iter_conv = k;
            cout << "Converged at iteration " << k
                 << "  S = " << Snew
                 << "  delta = " << delta << endl;
            break;
        }

        Sold = Snew;
    }

    if (!converged)
        cout << "Did not converge within Kmax.\n";

    vector<double> residual(N*N, std::numeric_limits<double>::quiet_NaN());

    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            double lap =
                (V[idx(i+1,j,N)] - 2*V[idx(i,j,N)] + V[idx(i-1,j,N)])/(dx*dx) +
                (V[idx(i,j+1,N)] - 2*V[idx(i,j,N)] + V[idx(i,j-1,N)])/(dx*dx);
            residual[idx(i,j,N)] = lap;
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

    write_csv("potential_task1.csv", V);
    write_csv("residual_task1.csv", residual);

    {
        ofstream out("S_delta_history_task1.csv");
        out << "iter,S,delta\n";
        for (int i = 0; i < (int)S_hist.size(); i++)
            out << i << "," << S_hist[i] << "," << delta_hist[i] << "\n";
    }

    cout << "CSV files written:\n"
         << "  potential_task1.csv\n"
         << "  residual_task1.csv\n"
         << "  S_delta_history_task1.csv\n";

    return 0;
}
