import numpy as np
import matplotlib.pyplot as plt

# Read the data from the file (assuming it's in the form of space-separated coordinates)
data = np.loadtxt('Data.txt')

# Extract x and y coordinates
x = data[:, 0]
y = data[:, 1]

# Create a plot
plt.figure()
plt.grid(True)

# Plot the vectors as a series of points
plt.plot(x, y, marker='.', color='green')

# Plot arrows between consecutive points to represent direction
for i in range(len(x)):
    i = i % len(x) - 1
    plt.arrow(x[i], y[i], x[i+1] - x[i], y[i+1] - y[i], head_width=0.1, color='green')

# Set limits for better visualization
plt.xlim(min(x)-1, max(x)+1)
plt.ylim(min(y)-1, max(y)+1)

# Show the plot
plt.show()
