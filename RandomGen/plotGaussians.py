import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

df = pd.read_csv("samples.csv", header=None, names=["Sample"])

samples = df["Sample"].values


plt.figure(figsize=(10, 6))
df["Sample"].plot(kind='hist', bins=100, density=True, alpha=0.6, color='cornflowerblue', label="Sampled Gaussians")

x = np.linspace(-4, 4, 1000)
pdf = norm.pdf(x, loc=0, scale=1)
plt.plot(x, pdf, 'r-', lw=2, label="Standard Normal PDF")

plt.title("Sampled Gaussians vs. Standard Normal Distribution")
plt.xlabel("Value")
plt.ylabel("Density")
plt.legend()
plt.grid(True)

plt.show()