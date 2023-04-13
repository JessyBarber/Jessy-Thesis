import matplotlib.pyplot as plt

plt.close('all')

with open('exp1_raw.log', 'r') as f:
    lines = f.read().splitlines()

x = []
y = []
z = []

line_n = len(lines) // 256

for i, line in enumerate(lines[1:], start = 1):   # Skip the first line
    # Split the line into individual variables, separated by whitespace
    values = line.split()
    x.append(float(values[0]))
    y.append(float(values[1]))
    z.append(float(values[2]))
    
fig, ax = plt.subplots()
# Plot the data on the subplot
ax.plot(x, label='X')
ax.plot(y, label='Y')
ax.plot(z, label='Z')

# Set the axis labels and legend
ax.set_xlabel('Sample')
ax.set_ylabel('Value')
ax.legend()



# # Loop through each line of the file and extract the variables
# for i, line in enumerate(lines[1:], start = 1):   # Skip the first line
#     # Split the line into individual variables, separated by whitespace
#     values = line.split()
#     x.append(float(values[0]))
#     y.append(float(values[1]))
#     z.append(float(values[2]))

#     # If we've processed 16 lines, create a new subplot and plot the data
#     if i % line_n == 0:
#         # Create a new figure and subplot
#         fig, ax = plt.subplots()

#         # Plot the data on the subplot
#         ax.plot(x, label='X')
#         ax.plot(y, label='Y')
#         ax.plot(z, label='Z')

#         # Set the axis labels and legend
#         ax.set_xlabel('Time')
#         ax.set_ylabel('Value')
#         ax.legend()

#         # Reset the data lists for the next group of 16 lines
#         x = []
#         y = []
#         z = []

# Display the plot
plt.show()