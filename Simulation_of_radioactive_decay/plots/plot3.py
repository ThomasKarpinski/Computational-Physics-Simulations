import pandas as pd
import matplotlib.pyplot as plt

df1 = pd.read_csv("../data/task3/test2.csv")
df2 = pd.read_csv("../data/task3/test3.csv")

#  N values plot for TOL2
t1 = df1["t"]
N0_1 = df1["N0"]
N1_1 = df1["N1"]
N2_1 = df1["N2"]
N0_analitical_1 = df1["N0_analytical"]
N1_analitical_1 = df1["N1_analytical"]
N2_analitical_1 = df1["N2_analytical"]

fig, ax = plt.subplots(nrows = 2, ncols = 2, figsize=(20, 15))

ax[0,0].plot(t1, N0_1, label='N0 (Simulated, TOL=1e-6)', color='blue')
ax[0,0].plot(t1, N1_1, label='N1 (Simulated, TOL=1e-6)', color='red')
ax[0,0].plot(t1, N2_1, label='N2 (Simulated, TOL=1e-6)', color='green')
ax[0,0].plot(t1, N0_analitical_1, 'o', label='N0 (Analytical, TOL=1e-6)', color='blue')
ax[0,0].plot(t1, N1_analitical_1, 'o', label='N1 (Analytical, TOL=1e-6)', color='red')
ax[0,0].plot(t1, N2_analitical_1, 'o', label='N2 (Analytical, TOL=1e-6)', color='green')
ax[0,0].set_title('TOL=1e-6')
ax[0,0].set_xlabel('Time (t)')
ax[0,0].set_xscale('log')
ax[0,0].set_xlim(1e-4, 1e3)
ax[0,0].set_ylim(0, 1)
ax[0,0].legend()

#  N values plot for TOL3
t2 = df2["t"]
N0_2 = df2["N0"]
N1_2 = df2["N1"]
N2_2 = df2["N2"]
N0_analitical_2 = df2["N0_analytical"]
N1_analitical_2 = df2["N1_analytical"]
N2_analitical_2 = df2["N2_analytical"]

ax[0,1].plot(t2, N0_2, label='N0 (Simulated, TOL=1e-3)', color='blue')
ax[0,1].plot(t2, N1_2, label='N1 (Simulated, TOL=1e-3)', color='red')
ax[0,1].plot(t2, N2_2, label='N2 (Simulated, TOL=1e-3)', color='green')
ax[0,1].plot(t2, N0_analitical_2, 'o', label='N0 (Analytical, TOL=1e-3)', color='blue')
ax[0,1].plot(t2, N1_analitical_2, 'o', label='N1 (Analytical, TOL=1e-3)', color='red')
ax[0,1].plot(t2, N2_analitical_2, 'o', label='N2 (Analytical, TOL=1e-3)', color='green')
ax[0,1].set_title('TOL=1e-3')
ax[0,1].set_xlabel('Time (t)')
ax[0,1].set_xscale('log')
ax[0,1].set_xlim(1e-4, 1e3)
ax[0,1].set_ylim(0, 1)
ax[0,1].legend()

# time step plot for TOL2
dt1 = t1.diff().dropna()
ax[1,0].plot(t1.iloc[1:], dt1, label='Time Step (dt, TOL=1e-6)', color='black', marker='o', linestyle='-')
ax[1,0].set_title('Time Step vs Time (TOL=1e-6)')
ax[1,0].set_xlabel('Time (t)')
ax[1,0].set_ylabel('Time Step (dt)')
ax[1,0].set_xscale('log')
ax[1,0].set_yscale('log')
ax[1,0].set_xlim(1e-2, 1e3)
ax[1,0].set_ylim(1e-2, 1e1)
ax[1,0].legend()

# time step plot for TOL3
dt2 = t2.diff().dropna()
ax[1,1].plot(t2.iloc[1:], dt2, label='Time Step (dt, TOL=1e-3)', color='black', marker='o', linestyle='-')
ax[1,1].set_title('Time Step vs Time (TOL=1e-3)')
ax[1,1].set_xlabel('Time (t)')
ax[1,1].set_ylabel('Time Step (dt)')
ax[1,1].set_xscale('log')
ax[1,1].set_yscale('log')
ax[1,1].set_xlim(1e-2, 1e3)
ax[1,1].set_ylim(1e-2, 1e1)
ax[1,1].legend()
plt.tight_layout()
plt.savefig("../plots/plot3.png")
plt.close()
