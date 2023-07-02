import matplotlib.pyplot as plt
import time
import os

plt.close('all')

def read_log_data():
    raw_xAccel = []
    raw_yAccel = []
    raw_zAccel = []

    with open(full_path, "r") as f:
        for line in f:
            var1, var2, var3 = map(float, line.split())
            raw_xAccel.append(var1)
            raw_yAccel.append(var2)
            raw_zAccel.append(var3)
    return raw_xAccel, raw_yAccel, raw_zAccel

fname = input("Enter the name of the log file: ")
fname2 = input("Enter the name of the raw acceleration \
               plot file (with file extension): ")

dir_path = "serialPlot/logs/"
full_path = os.path.join(dir_path, fname)

dir_path2 = "serialPlot/plots/"
full_path2 = os.path.join(dir_path2, fname2)

raw_xAccel, raw_yAccel, raw_zAccel = read_log_data()

# Create the plot
plt.plot(raw_xAccel, label="x_axis")
plt.plot(raw_yAccel, label="y_axis")
plt.plot(raw_zAccel, label="z_axis")

# Set plot labels and legend
plt.title("Raw Acceleration")
plt.xlabel("Samples")
plt.ylabel("Acceleration (m/s/s)")
plt.legend()

# Save the figure as a high-resolution PNG file
plt.savefig(full_path2, dpi=300)

# Display the plot
plt.show()