import sys
import matplotlib.pyplot as plt

filename = sys.argv[1]

# Read data from the file
data = []
with open(filename, 'r') as file:
    for line in file:
        values = list(map(float, line.split()))
        data.append(values)

# Extracting the columns
original_y = [item[0] for item in data]
interpolated_y = [item[1] for item in data]
smoothed_y_0 = [item[2] for item in data]
smoothed_y_4 = [item[3] for item in data]
smoothed_y_8 = [item[4] for item in data]
smoothed_y_99 = [item[5] for item in data]

# Scatter plot of the different values
plt.figure(figsize=(10, 6))

plt.scatter(range(len(original_y)), original_y, color='blue', label='Original Y', alpha=0.6, marker='o', s=200)
plt.scatter(range(len(interpolated_y)), interpolated_y, color='red', label='Interpolated Y', alpha=0.6, marker='s', s=80)
plt.scatter(range(len(smoothed_y_0)), smoothed_y_0, color='green', label='Smoothed p=0', alpha=0.6, marker='^', s=100)
plt.scatter(range(len(smoothed_y_4)), smoothed_y_4, color='orange', label='Smoothed p=0.4', alpha=0.6, marker='v', s=120)
plt.scatter(range(len(smoothed_y_8)), smoothed_y_8, color='purple', label='Smoothed p=0.8', alpha=0.6, marker='x', s=140)
plt.scatter(range(len(smoothed_y_99)), smoothed_y_99, color='brown', label='Smoothed p=0.99', alpha=0.6, marker='D', s=80)

# Add labels and title
plt.title('Comparison of Original, Interpolated, and Smoothed Values')
plt.xlabel('Index')
plt.ylabel('Y values')
plt.legend()
plt.grid(True)
# Show the 
plt.show()