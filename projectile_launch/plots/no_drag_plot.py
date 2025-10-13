import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df10 = pd.read_csv('../trajectory_no_drag_10.csv', header=None)
df20 = pd.read_csv('../trajectory_no_drag_20.csv', header=None)
df50 = pd.read_csv('../trajectory_no_drag_50.csv', header=None)
df100 = pd.read_csv('../trajectory_no_drag_100.csv', header=None)
df200 = pd.read_csv('../trajectory_no_drag_200.csv', header=None)
df500 = pd.read_csv('../trajectory_no_drag_500.csv', header=None)

df_error = pd.read_csv('../global_error.csv')

fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(20, 8))

ax[0].set_xlabel('x [m]')
ax[0].set_ylabel('y [m]')
ax[0].set_xlim(0, 1200)
ax[0].plot(df10[1], df10[2], label='n=10')
ax[0].plot(df20[1], df20[2], label='n=20')
ax[0].plot(df50[1], df50[2], label='n=50')
ax[0].plot(df100[1], df100[2], label='n=100')
ax[0].plot(df200[1], df200[2], label='n=200')
ax[0].plot(df500[1], df500[2], label='n=500')
ax[0].set_title("")
ax[0].set_xlabel('x [m]')
ax[0].set_ylabel('y [m]')
ax[0].grid(True)
ax[0].set_title("Trajectories, No Drag")
ax[0].legend(loc='upper right', fontsize=10, shadow=True)

ax[1].set_title("Error")
ax[1].set_xlabel('Delta t [s]')
ax[1].set_ylabel('|$\mathrm{x}_{exact} - \mathrm{x}_{num}$|')
ax[1].set_ylim(1, 1000)
ax[1].set_xlim(0.01, 10)

ax[1].set_yscale('log')
ax[1].set_xscale('log')

custom_ticks = [0.01, 0.1, 1, 10]
ax[1].set_xticks(custom_ticks)
ax[1].plot(df_error['delta_t'], df_error['E_global'], marker='o', linestyle='-')
ax[1].set_yticks([1, 10, 100, 1000])

plt.tight_layout()
plt.savefig('no_drag_plot.png', dpi=300)
