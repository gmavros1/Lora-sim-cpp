import matplotlib.pyplot as plt

# Initialize lists to store data
load_values = []
throughput_values = []

# Read the text file and extract load and throughput values
with open('metrics.txt', 'r') as file:
    lines = file.readlines()
    for line in lines[1:]:  # Skip the first line with headers
        load, decoded, non_decoded, nodes_number, life_time, max_trans = map(float, line.split(","))
        load_values.append(load)
        throughput = (decoded / nodes_number) / (max_trans)
        throughput_values.append(throughput)

# Create a line graph
plt.figure(figsize=(8, 6))
plt.plot(load_values, throughput_values, marker='o', linestyle='-')
plt.title('Load vs. Throughput')
plt.xlabel('Load')
plt.ylabel('Throughput')
plt.grid(True)

# Display the plot or save it to a file
plt.show()
