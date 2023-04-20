import matplotlib.pyplot as plt
import serial
import time
from matplotlib.animation import FuncAnimation

plt.close('all')
#Change to serial name -> MAC is /tty.modem etc 
#Check with ls /dev/tty*
PORT = 'COM5'
BAUD_RATE = 9600
# ITERATIONS = 5
ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

data_var1 = []
data_var2 = []
data_var3 = [] 
data_var4 = []
data_var5 = []
data_var6 = []

def read_serial_data():
    data = ser.readline().decode('utf-8').strip()
    if data:
        variables = data.split(' ')
        if len(variables) == 6 and all(variables):
            try:
                var1, var2, var3, var4, var5, var6 = map(float, variables)
                return var1, var2, var3, var4, var5, var6
            except ValueError:
                print("ERROR: INVALID DATA RECEIVED")
    return None, None, None, None, None, None

try:
    while True:
        var1, var2, var3, var4, var5, var6 = read_serial_data()
        if var1 is not None and var2 is not None and var3 is not None and \
            var4 is not None and var5 is not None and var6 is not None:
            data_var1.append(var1)
            data_var2.append(var2)
            data_var3.append(var3)
            data_var4.append(var4)
            data_var5.append(var5)
            data_var6.append(var6)
        time.sleep(0.01)

except KeyboardInterrupt:
    print("Interrupted by user.")

finally:
    # Close the serial port
    ser.close()
    print("Serial port closed.")

# Create the plot
plt.plot(data_var1, label="x_axis")
plt.plot(data_var2, label="y_axis")
plt.plot(data_var3, label="z_axis")

# Set plot labels and legend
plt.title("Maximum Frequency")
plt.xlabel("N's")
plt.ylabel("Max Frequency (Hz)")
plt.legend()

# Save the figure as a high-resolution PNG file
plt.savefig("FFT.png", dpi=300)

# Display the plot
plt.show()

plt.figure()  # Create a new figure for the second plot
plt.plot(data_var4, label="x_axis")
plt.plot(data_var5, label="y_axis")
plt.plot(data_var6, label="z_axis")

# Set plot labels and legend
plt.title("Maximum Acceleration")
plt.xlabel("N's")
plt.ylabel("Max Acceleration (m/s/s)")
plt.legend()

# Save the second figure as a high-resolution PNG file
plt.savefig("Accel.png", dpi=300)

# Display the second plot
plt.show()
