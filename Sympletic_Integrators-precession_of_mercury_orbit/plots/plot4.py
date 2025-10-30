import matplotlib.pyplot as plt
import pandas as pd

df1 = pd.read_csv("../data/task4/trajectory_alpha01.csv")
df2 = pd.read_csv("../data/task4/extrema.csv")
df_extrema = pd.read_csv("../data/task4/peri_aphe.csv")

x = df1["x"]
y = df1["y"]

peri_indices = df_extrema[df_extrema["type"] == "perihelium"]["index"].astype(int).to_list()
aphe_indices = df_extrema[df_extrema["type"] == "aphelium"]["index"].astype(int).to_list()

plt.plot(x, y, label="trajectory")

for idx in peri_indices:
    plt.plot([0, x[idx]], [0, y[idx]], color='blue', linestyle='--', alpha=0.7, label="perihelium" if idx == peri_indices[0] else "")
for idx in aphe_indices:
    plt.plot([0, x[idx]], [0, y[idx]], color='red', linestyle='--', alpha=0.7, label="aphelium" if idx == aphe_indices[0] else "")

plt.xlabel("x [Au]")
plt.ylabel("y [Au]")
plt.xlim(-0.6, 0.6)
plt.ylim(-0.6, 0.6)
plt.legend()
plt.savefig("task4.png", dpi=300)