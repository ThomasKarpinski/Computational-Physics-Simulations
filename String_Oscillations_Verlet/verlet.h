#ifndef VERLET_H
#define VERLET_H

#include <vector>
#include <string>

enum BoundaryCondition {
    FIXED,
    OPEN
};

struct VerletParams {
    double L = 1.0;
    int N = 301; 
    double Q = 1.0; 
    double T = 100.0;
    double alpha = 0.5;
    double gamma = 0.0;
    double Fext = 0.0;
    double Omega = 0.0; 
    int ip = 0; 
    double uinit = 0.01;
    double xA = 0.5;     
    double vinit = 0.0;  
    double sigma = 1.0/20.0;  
    int Nt = 2000;       
    int Kmodes = 0;
    BoundaryCondition bc = FIXED;
    bool nonhomogeneous = false;
    std::string task_name = "task1";


    double dx = 0.0;
    double dt = 0.0;
};

class Verlet {
public:
    Verlet(const VerletParams &p);

    void run(const std::string &energy_out = "energies.csv",
             const std::string &u_snapshot_prefix = "u_snap",
             const std::string &spectral_out = "");

private:
    VerletParams params;

    int N;
    double L, dx, dt;
    std::vector<double> rho;
    std::vector<double> c;
    std::vector<double> u; 
    std::vector<double> v; 
    std::vector<double> a;
    std::vector<double> vhalf; 

    void initialize_mesh();
    void set_initial_conditions();
    void apply_boundary_conditions(std::vector<double> &uvec);
    void compute_acceleration(const std::vector<double> &uvec,
                              const std::vector<double> &vvec,
                              std::vector<double> &avec,
                              double t);
    double compute_Ekin() const; 
    double compute_Epot() const;  
    void compute_spectral(int step, std::vector<double> &bk, std::vector<double> &dk, std::vector<double> &ek) const;
    double omega_k(int k) const;

    void write_energies_header(std::ofstream &ofs) const;
    void write_energies_line(std::ofstream &ofs, double t, double Ekin, double Epot) const;
};

#endif // VERLET_H