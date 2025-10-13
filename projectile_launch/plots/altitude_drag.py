import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df1 = pd.read_csv('../task4/trajectory_D0.001000_a0.000000_alpha35.csv', header=None)
df2 = pd.read_csv('../task4/trajectory_D0.001000_a0.000000_alpha45.csv', header=None)
df3 = pd.read_csv('../task4/trajectory_D0.001000_a0.006500_alpha35.csv', header=None)
df4 = pd.read_csv('../task4/trajectory_D0.001000_a0.006500_alpha45.csv', header=None)

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(12, 8))

ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.plot(df1[1], df1[2], label='a=0, alpha=35$^{0}$', color='black', linestyle='-')
ax.plot(df2[1], df2[2], label='a=0, alpha=45$^{0}$', color='red', linestyle='-')
ax.plot(df3[1], df3[2], label='a>0, alpha=35$^{0}$', color='black', linestyle='--')
ax.plot(df4[1], df4[2], label='a>0, alpha=45$^{0}$', color='red', linestyle='--')
ax.grid(True)
ax.set_title("drag force + altitude correction")
ax.legend(loc='upper right', fontsize=10, shadow=True)


plt.tight_layout()
plt.savefig('altitude_drag.png', dpi=300)
