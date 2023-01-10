import numpy as np
import matplotlib.pyplot as plt

with open("features.csv", "r") as f:
    lines = f.readlines()


for line in lines:
    line = line.split(",")
    mean = list(map(float, line[:512]))
    std = list(map(float, line[512:-2]))
    label = line[-2]
    filename = line[-1]
    t = range(len(mean))
    fig, axs = plt.subplots(2)
    fig.suptitle(f"Features for {filename}")
    axs[0].plot(t, mean)
    axs[1].plot(t, std)
    plt.show()
