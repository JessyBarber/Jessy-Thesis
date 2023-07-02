import matplotlib.pyplot as plt
import serial
import time
import os

# MAC ADDRESS
# PORT = '/dev/tty.usbmodem141401'
# PC ADDERSS
PORT = 'COM5'
BAUD_RATE = 9600
ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

xFreq = []
yFreq = []
zFreq = [] 

xAccel = []
yAccel = []
zAccel = []

fname = input("Enter the name of the log file: ")

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

print("Ctrl-C to stop logging")

try:
    while True:
        var1, var2, var3, var4, var5, var6 = read_serial_data()
        if var1 is not None and var2 is not None and var3 is not None\
            and var4 is not None and var5 is not None and var6 is not None:
            xFreq.append(var1) 
            yFreq.append(var2)
            zFreq.append(var3)

            xAccel.append(var4)
            yAccel.append(var5)
            zAccel.append(var6)
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
for i in range(len(xFreq)):
    f.writelines([str(xFreq[i]), " ", str(yFreq[i]), " ", str(zFreq[i]), \
                  " ", str(xAccel[i]), " ", str(yAccel[i]), \
                    " ", str(zAccel[i]), "\n"]) 