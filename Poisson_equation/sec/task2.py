import numpy as np
import matplotlib.pyplot as plt
import os

indir = "." 
pot_file   = os.path.join(indir, "potential_task2.csv")
res_file   = os.path.join(indir, "residual_task2.csv")

V = np.loadtxt(pot_file, delimiter=",")
residual = np.loadtxt(res_file, delimiter=",")

N = V.shape[0]
L = 4.0
x = np.linspace(-L, L, N)
y = np.linspace(-L, L, N)

plt.figure(figsize=(6,5))
plt.title("Potential V(x,y) - Task 2")
plt.xlabel("x")
plt.ylabel("y")
plt.imshow(V.T, origin='lower', extent=[x[0], x[-1], y[0], y[-1]])
plt.colorbar(label='V')
plt.tight_layout()
plt.savefig("potential_task2.png")
plt.close()

plt.figure(figsize=(6,5))
plt.title("Absolute residual |r(i,j)| - Task 2")
plt.xlabel("x")
plt.ylabel("y")
plt.imshow(np.abs(residual).T, origin='lower', extent=[x[0], x[-1], y[0], y[-1]])
plt.colorbar(label='|r|')
plt.tight_layout()
plt.savefig("residual_task2.png")
plt.close()

print("Plots saved as potential_task2.png and residual_task2.png")
