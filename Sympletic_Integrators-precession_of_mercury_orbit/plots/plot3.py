import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("../data/task3/trajectory_alpha0.csv")

x = df["x"]
y = df["y"]

plt.plot(x, y, label="trajectory")
plt.xlabel("x [Au]")
plt.xlim(-0.6, 0.6)
plt.ylim(-0.6, 0.6)
plt.ylabel("y [Au]")
plt.savefig("task3.png", dpi=300)