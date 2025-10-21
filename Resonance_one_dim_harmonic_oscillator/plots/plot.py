import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('../results/task2a/output.csv')
# print(df1.head(5))
t = df["t"]
x = df["x"]
v = df["v"]
Ekin = df["Ekin"]
Epot = df["Epot"]
Etot = df["Etot"]

fig, ax = plt.subplots(nrows = 2, ncols = 2, figsize=(12,8))

ax[0,0].set_xlabel('t')
ax[0,0].set_xlim(0, 50)
ax[0,0].set_ylim(0, 0.5)
ax[0,0].set_ylabel('E')
ax[0,0].plot(t, Ekin)
ax[0,0].plot(t, Epot)
ax[0,0].plot(t, Etot)

ax[0,1].set_xlabel('t')
ax[0,1].set_xlim(0, 50)
ax[0,1].set_ylim(-1, 1)
ax[0,1].set_ylabel('x')
ax[0,1].plot(t, x)

ax[1,0].set_xlabel('t')
ax[1,0].set_xlim(0, 50)
ax[1,0].set_ylim(-1, 1)
ax[1,0].set_ylabel('v')
ax[1,0].plot(t, v)

ax[1,1].set_xlabel('x')
ax[1,1].set_ylabel('v')
ax[1,1].plot(x, v)



plt.tight_layout()
out_png = "../results/task2a/plot2a.png"
plt.savefig(out_png, dpi=300)
