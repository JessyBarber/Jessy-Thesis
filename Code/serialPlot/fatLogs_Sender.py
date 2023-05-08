import matplotlib.pyplot as plt
import serial
import time
import os

# MAC ADDRESS
PORT = '/dev/tty.usbmodem1413301'
# PC ADDERSS
# PORT = 'COM3'
BAUD_RATE = 9600
ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

raw_xAccel = []
raw_yAccel = []
raw_zAccel = [] 

fname = input("Enter the name of the log file: ")

def read_serial_data():
    data = ser.readline().decode('utf-8').strip()
    if data:
        variables = data.split(' ')
        if len(variables) == 3 and all(variables):
            try:
                var1, var2, var3 = map(float, variables)
                return var1, var2, var3
            except ValueError:
                print("ERROR: INVALID DATA RECEIVED")
    return None, None, None

print("Ctrl-C to stop logging")

try:
    while True:
        var1, var2, var3 = read_serial_data()
        if var1 is not None and var2 is not None and var3 is not None:
            raw_xAccel.append(var1) 
            raw_yAccel.append(var2)
            raw_zAccel.append(var3)
        time.sleep(0.01)

except KeyboardInterrupt:
    print("Interrupted by user.")

finally:
    # Close the serial port
    ser.close()
    print("Serial port closed.")

# Open and overwrite senderlog
dir_path = "serialPlot/logs/"
full_path = os.path.join(dir_path, fname)

f = open(full_path, "w")
for i in range(len(raw_xAccel)):
    f.writelines([str(raw_xAccel[i]), " ", str(raw_yAccel[i]), " ", str(raw_zAccel[i]), "\n"])