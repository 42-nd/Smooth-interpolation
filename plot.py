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
size = 35
plt.scatter(range(len(original_y)), original_y, color='green', label='Original Y', alpha=0.9, marker='o', s=size+20)
plt.scatter(range(len(interpolated_y)), interpolated_y, color='orange', label='Interpolated Y', alpha=0.9, marker='x', s=size)
plt.scatter(range(len(smoothed_y_0)), smoothed_y_0, color='black', label='Smoothed p=0', alpha=0.7, marker='+', s=size+40)
plt.scatter(range(len(smoothed_y_4)), smoothed_y_4, color='red', label='Smoothed p=0.4', alpha=0.7, marker='^', s=size)
plt.scatter(range(len(smoothed_y_8)), smoothed_y_8, color='darkblue', label='Smoothed p=0.8', alpha=0.7, marker='D', s=size)
plt.scatter(range(len(smoothed_y_99)), smoothed_y_99, color='brown', label='Smoothed p=0.99', alpha=0.7, marker='8', s=size)

# Add labels and title
plt.title('Comparison of Original, Interpolated, and Smoothed Values')
plt.xlabel('Index')
plt.ylabel('Y values')
plt.legend()
plt.grid(True)
# Show the 
plt.show()