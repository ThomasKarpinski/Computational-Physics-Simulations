import matplotlib.pyplot as plt
import pandas as pd

df1 = pd.read_csv('../results/task3/alpha_0.00.csv')
df2 = pd.read_csv('../results/task3/alpha_0.10.csv')
df3 = pd.read_csv('../results/task3/alpha_0.50.csv')
df4 = pd.read_csv('../results/task3/alpha_1.95.csv')

plt.figure()
plt.plot(df1['t'], df1['x'], label="alpha=10^-4")
plt.plot(df2['t'], df2['x'], label="0.1")
plt.plot(df3['t'], df3['x'], label="0.5")
plt.plot(df4['t'], df4['x'], label="1.95")
plt.xlabel("x")
plt.ylabel("t")
plt.legend()
plt.grid(True)

out_png = "../results/task3/plot3.png"
plt.savefig(out_png, dpi=300)
