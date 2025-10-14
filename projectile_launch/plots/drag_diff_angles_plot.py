import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df1 = pd.read_csv('../task3_2/range_vs_angle_D0.000000.csv', header=None)
df2 = pd.read_csv('../task3_2/range_vs_angle_D0.001000.csv', header=None)
df3 = pd.read_csv('../task3_2/range_vs_angle_D0.002000.csv', header=None)

fig, ax = plt.subplots(nrows=1, ncols=3, figsize=(20, 8))

ax[0].set_xlabel('alpha')
ax[0].set_ylabel('${x}_{max}$')
ax[0].set_xlim(15, 65)
ax[0].plot(df1[0], df1[1], label='D=0', color='blue')
ax[0].grid(True)
ax[0].set_title("Trajectories, With Drag Force")
ax[0].legend(loc='upper right', fontsize=10, shadow=True)

ax[1].set_xlabel('alpha')
ax[1].set_ylabel('${x}_{max}$')
ax[1].set_xlim(15, 65)
ax[1].plot(df2[0], df2[1], label='D=0.001', color='orange')
ax[1].grid(True)
ax[1].set_title("Trajectories, With Drag Force")
ax[1].legend(loc='upper right', fontsize=10, shadow=True)

ax[2].set_xlabel('alpha')
ax[2].set_ylabel('${x}_{max}$')
ax[2].set_xlim(15, 65)
ax[2].plot(df3[0], df3[1], label='D=0.002', color='green')
ax[2].grid(True)
ax[2].set_title("Trajectories, With Drag Force")
ax[2].legend(loc='upper right', fontsize=10, shadow=True)


plt.tight_layout()
plt.savefig('drag_diff_angles_plot.png', dpi=300)


best_path_and_range_1 = df1.iloc[df1[1].idxmax()]
print(best_path_and_range_1)
best_path_and_range_2 = df2.iloc[df2[1].idxmax()]
print(best_path_and_range_2)
best_path_and_range_3 = df3.iloc[df3[1].idxmax()]
print(best_path_and_range_3)