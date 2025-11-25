#ifndef CONFIG_H
#define CONFIG_H

// General parameters
const double L = 10.0;
const int N = 51;
const double DELTA = L / (N - 1);
const double DT = 10.0;
const double T_MAX = 10000.0;
const int N_MAX = static_cast<int>(T_MAX / DT);
const double D = 0.1;

// Heater parameters
const double HEATER_X_MIN = 2.0;
const double HEATER_X_MAX = 4.0;
const double HEATER_Y_MIN = 8.0;
const double HEATER_Y_MAX = 8.8;
const double S_MAX = 5.0;

// Window parameters
const double Y_WINDOW_MIN = 6.0;
const double Y_WINDOW_MAX = 9.0;

// Temperature sensor
const double SENSOR_X = 2.0;
const double SENSOR_Y = 8.0;
const double T_LOW = 293.0;

// Outside temperature
const double T_OUTSIDE = 273.0;

// Gauss-Seidel relaxation
const int K_MAX = 30;
const double TOL = 1e-8;

// Task 1 specific parameters
const double H = 0.0;
const double HW = 0.0;
const double T_HIGH = 10000.0;

#endif // CONFIG_H
