import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../data/task2/test.csv")

# print(df.head())

#  N values plot
t = df["t"]
N0 = df["N0"]
N1 = df["N1"]
N2 = df["N2"]
N0_analitical = df["N0_analytical"]
N1_analitical = df["N1_analytical"]
N2_analitical = df["N2_analytical"]

plt.figure(figsize=(10, 6))
plt.plot(t, N0, label='N0 (Simulated)', color='blue')
plt.plot(t, N1, label='N1 (Simulated)', color='red')
plt.plot(t, N2, label='N2 (Simulated)', color='green')

plt.plot(t, N0_analitical, 'o', label='N0 (Analytical)', color='blue')
plt.plot(t, N1_analitical, 'o', label='N1 (Analytical)', color='red')
plt.plot(t, N2_analitical, 'o', label='N2 (Analytical)', color='green')

plt.legend()
plt.title('Comparison of Simulated and Analytical Results')
plt.xlabel('Time (t)')
plt.xscale('log')
plt.xlim(1e-2, 1e3)
plt.ylim(0, 1)

plt.savefig("../plots/plot2.png")

# time step plot
dt = t.diff().dropna()
plt.figure(figsize=(10, 6))
plt.plot(t.iloc[1:], dt, label='Time Step (dt)', color='black', marker='o', linestyle='-')
plt.legend()
plt.title('Time Step vs Time')
plt.xlabel('Time (t)')
plt.ylabel('Time Step (dt)')
plt.xscale('log')
plt.yscale('log')
plt.xlim(1e-2, 1e3)
plt.ylim(1e-2, 1e3)


plt.savefig("../plots/plot2_time.png")
