import matplotlib.pyplot as plt
import serial
import time
import os

plt.close('all')

xFreq = []
yFreq = []
zFreq = [] 

xAccel = []
yAccel = []
zAccel = []

def read_log_data():
    xVar = []
    yVar = []
    zVar = [] 

    xAccel = []
    yAccel = []
    zAccel = []

    with open(full_path, "r") as f:
        for line in f:
            var1, var2, var3, var4, var5, var6 = map(float, line.split())
            xVar.append(var1)
            yVar.append(var2)
            zVar.append(var3)

            xAccel.append(var4)
            yAccel.append(var5)
            zAccel.append(var6)

    return xVar, yVar, zVar, xAccel, yAccel, zAccel

# Open and overwrite senderlog
fname = input("Enter the name of the log file: ")
fname2 = input("Enter the name of the FFT plot file (with file extension): ")
fname3 = input("Enter the name of the accleration plot file (with file extension): ")

dir_path = "serialPlot/logs/"
full_path = os.path.join(dir_path, fname)

dir_path2 = "serialPlot/plots/"
full_path2 = os.path.join(dir_path2, fname2)

dir_path3 = "serialPlot/plots/"
full_path3 = os.path.join(dir_path3, fname3)

xVar, yVar, zVar, xAccel, yAccel, zAccel = read_log_data()

plotType = input("FFT or Disp?: ")

if (plotType == "FFT"):
    print("Plotting FFT and Maximum Acceleration")

    # Create the plot
    plt.plot(xVar, label="x_axis")
    plt.plot(yVar, label="y_axis")
    plt.plot(zVar, label="z_axis")

    # Set plot labels and legend
    plt.title("FFT")
    plt.xlabel("N's")
    plt.ylabel("Frequency (Hz)")
    plt.legend()

    # Save the figure as a high-resolution PNG file
    plt.savefig(full_path2, dpi=300)

    # Display the plot
    plt.show()

    plt.figure()  # Create a new figure for the second plot
    plt.plot(xAccel, label="x_axis")
    plt.plot(yAccel, label="y_axis")
    plt.plot(zAccel, label="z_axis")

    # Set plot labels and legend
    plt.title("Maximum Acceleration")
    plt.xlabel("N's")
    plt.ylabel("Max Acceleration (m/s/s)")
    plt.legend()

    # Save the second figure as a high-resolution PNG files
    plt.savefig(full_path3, dpi=300)

    # Display the second plot
    plt.show()

elif (plotType == "Disp"):
    print("Maximum Displacement and Maximum Acceleration")

    # Create the plot
    plt.plot(xVar, label="x_axis")
    plt.plot(yVar, label="y_axis")
    plt.plot(zVar, label="z_axis")

    # Set plot labels and legend
    plt.title("Maximum Displacement")
    plt.xlabel("N's")
    plt.ylabel("Frequency (m)")
    plt.legend()

    # Save the figure as a high-resolution PNG file
    plt.savefig(full_path2, dpi=300)

    # Display the plot
    plt.show()

    plt.figure()  # Create a new figure for the second plot
    plt.plot(xAccel, label="x_axis")
    plt.plot(yAccel, label="y_axis")
    plt.plot(zAccel, label="z_axis")

    # Set plot labels and legend
    plt.title("Maximum Acceleration")
    plt.xlabel("N's")
    plt.ylabel("Max Acceleration (m/s/s)")
    plt.legend()

    # Save the second figure as a high-resolution PNG files
    plt.savefig(full_path3, dpi=300)

    # Display the second plot
    plt.show()