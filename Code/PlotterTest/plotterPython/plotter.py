import serial
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import datetime as dt

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

port = serial.Serial('COM3', 9600)
time.sleep(2)

data = [] 

def animate(i, xs, ys):
    data = port.readline()
    xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
    ys.append(data)

    xs = xs[-20:]
    ys = ys[-20:]

    ax.clear()
    ax.plot(xs, ys)

    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title("tester")
    plt.ylabel("test val")

    # b = port.readline()
    # string_n = b.decode()
    # string = string_n.rstrip()
    # flt = float(string)
    # print(flt)
    # data.append(flt)
    # time.sleep(0.1)

# data = [] 
# for i in range(256):
#     b = port.readline()
#     string_n = b.decode()
#     string = string_n.rstrip()
#     flt = float(string)
#     print(flt)
#     data.append(flt)
#     time.sleep(0.1)
# port.close()

# for line in data:
#     print(line)

ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), 
                              interval=1000)
plt.show()

# plt.plot(data)
# plt.xlabel('Time (seconds)')
# plt.ylabel('Reading')
# plt.title('Accel Reading Vs')
# plt.show()