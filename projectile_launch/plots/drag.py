import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df1 = pd.read_csv('../task3_1/trajectory_diff_drag_a0_D0.000000.csv', header=None)
df2 = pd.read_csv('../task3_1/trajectory_diff_drag_a0_D0.000100.csv', header=None)
df3 = pd.read_csv('../task3_1/trajectory_diff_drag_a0_D0.000200.csv', header=None)
df4 = pd.read_csv('../task3_1/trajectory_diff_drag_a0_D0.000500.csv', header=None)
df5 = pd.read_csv('../task3_1/trajectory_diff_drag_a0_D0.001000.csv', header=None)

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(12, 8))

ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.set_xlim(0, 1200)
ax.plot(df1[1], df1[2], label='D=0')
ax.plot(df2[1], df2[2], label='D=0.0001')
ax.plot(df3[1], df3[2], label='D=0.0002')
ax.plot(df4[1], df4[2], label='D=0.0005')
ax.plot(df5[1], df5[2], label='D=0.0010')
ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.grid(True)
ax.set_title("Trajectories, With Drag")
ax.legend(loc='upper right', fontsize=10, shadow=True)


plt.tight_layout()
plt.savefig('drag_plot.png', dpi=300)
