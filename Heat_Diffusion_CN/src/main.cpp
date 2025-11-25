#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "../include/config.h"

using namespace std;

void apply_boundary_conditions(vector<vector<double>>& T, double h, double hw) {
    // BC on west wall
    for (int j = 1; j < N - 1; ++j) {
        T[0][j] = (h * DELTA * T_OUTSIDE + D * T[1][j]) / (h * DELTA + D);
    }

    // BC on north wall
    for (int i = 1; i < N - 1; ++i) {
        T[i][N - 1] = (h * DELTA * T_OUTSIDE + D * T[i][N - 2]) / (h * DELTA + D);
    }

    // BC on east wall
    for (int j = 1; j < N - 1; ++j) {
        double h_eff = h;
        if (j * DELTA >= Y_WINDOW_MIN && j * DELTA <= Y_WINDOW_MAX) {
            h_eff = hw;
        }
        T[N - 1][j] = (h_eff * DELTA * T_OUTSIDE + D * T[N - 2][j]) / (h_eff * DELTA + D);
    }

    // BC on south wall
    for (int i = 1; i < N - 1; ++i) {
        T[i][0] = (h * DELTA * T_OUTSIDE + D * T[i][1]) / (h * DELTA + D);
    }

    // Corners
    T[0][0] = (T[1][0] + T[0][1]) / 2.0;
    T[N - 1][0] = (T[N - 2][0] + T[N - 1][1]) / 2.0;
    T[0][N - 1] = (T[1][N - 1] + T[0][N - 2]) / 2.0;
    T[N - 1][N - 1] = (T[N - 2][N - 1] + T[N - 1][N - 2]) / 2.0;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <task_name> <h> <hw> <Thigh>" << endl;
        return 1;
    }

    string task_name = argv[1];
    double h = stod(argv[2]);
    double hw = stod(argv[3]);
    double t_high = stod(argv[4]);

    string dir_name = "task_" + task_name;
    mkdir(dir_name.c_str(), 0777);

    vector<vector<double>> T(N, vector<double>(N, T_OUTSIDE));
    vector<vector<double>> R(N, vector<double>(N, 0.0));
    vector<vector<double>> S(N, vector<double>(N, 0.0));

    int heater_i_min = static_cast<int>(HEATER_X_MIN / DELTA);
    int heater_i_max = static_cast<int>(HEATER_X_MAX / DELTA);
    int heater_j_min = static_cast<int>(HEATER_Y_MIN / DELTA);
    int heater_j_max = static_cast<int>(HEATER_Y_MAX / DELTA);

    for (int i = heater_i_min; i <= heater_i_max; ++i) {
        for (int j = heater_j_min; j <= heater_j_max; ++j) {
            S[i][j] = S_MAX;
        }
    }

    int sensor_ic = static_cast<int>(SENSOR_X / DELTA);
    int sensor_jc = static_cast<int>(SENSOR_Y / DELTA);

    ofstream sensor_file(dir_name + "/sensor_temp.txt");
    ofstream map_file_1(dir_name + "/map_10.txt");
    ofstream map_file_2(dir_name + "/map_100.txt");
    ofstream map_file_3(dir_name + "/map_1000.txt");
    ofstream map_file_4(dir_name + "/map_10000.txt");
    ofstream energy_file(dir_name + "/energies.txt");

    double w = 1.0;
    double w_old = 1.0;

    for (int n = 0; n <= N_MAX; ++n) {
        double t = n * DT;

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < N - 1; ++j) {
                R[i][j] = T[i][j] + (D * DT / (2 * DELTA * DELTA)) * (T[i + 1][j] + T[i - 1][j] + T[i][j + 1] + T[i][j - 1] - 4 * T[i][j]) + (DT / 2.0) * w * S[i][j];
            }
        }

        w_old = w;
        if (T[sensor_ic][sensor_jc] < T_LOW) {
            w = 1.0;
        } else if (T[sensor_ic][sensor_jc] > t_high) {
            w = 0.0;
        }

        for (int k = 0; k < K_MAX; ++k) {
            for (int i = 1; i < N - 1; ++i) {
                for (int j = 1; j < N - 1; ++j) {
                    T[i][j] = (1.0 / (1 + 2 * D * DT / (DELTA * DELTA))) *
                              ((D * DT / (2 * DELTA * DELTA)) * (T[i + 1][j] + T[i - 1][j] + T[i][j + 1] + T[i][j - 1]) +
                               (DT / 2.0) * w * S[i][j] + R[i][j]);
                }
            }
            apply_boundary_conditions(T, h, hw);
        }

        double e_supplied = 0.0;
        for (int i = heater_i_min; i <= heater_i_max; ++i) {
            for (int j = heater_j_min; j <= heater_j_max; ++j) {
                e_supplied += (w + w_old) / 2.0 * S[i][j];
            }
        }
        e_supplied *= DELTA * DELTA * DT;
        
        double e_window = 0.0;
        int j_window_min = static_cast<int>(Y_WINDOW_MIN / DELTA);
        int j_window_max = static_cast<int>(Y_WINDOW_MAX / DELTA);
        for(int j = j_window_min; j <= j_window_max; ++j) {
            e_window += hw * (T[N-1][j] - T_OUTSIDE);
        }
        e_window *= DELTA * DT;


        energy_file << t << " " << e_supplied << " " << e_window << endl;
        sensor_file << t << " " << T[sensor_ic][sensor_jc] << endl;

        if (abs(t - 10.0) < DT / 2.0) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    map_file_1 << i * DELTA << " " << j * DELTA << " " << T[i][j] << endl;
                }
                map_file_1 << endl;
            }
        }
        if (abs(t - 100.0) < DT / 2.0) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    map_file_2 << i * DELTA << " " << j * DELTA << " " << T[i][j] << endl;
                }
                map_file_2 << endl;
            }
        }
        if (abs(t - 1000.0) < DT / 2.0) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    map_file_3 << i * DELTA << " " << j * DELTA << " " << T[i][j] << endl;
                }
                map_file_3 << endl;
            }
        }
        if (abs(t - 10000.0) < DT / 2.0) {
             for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    map_file_4 << i * DELTA << " " << j * DELTA << " " << T[i][j] << endl;
                }
                map_file_4 << endl;
            }
        }
    }

    sensor_file.close();
    map_file_1.close();
    map_file_2.close();
    map_file_3.close();
    map_file_4.close();
    energy_file.close();

    return 0;
}
