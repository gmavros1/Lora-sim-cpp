import matplotlib.pyplot as plt

plt.figure(figsize=(8, 6))
cases = []

# Read the text file and extract load and throughput values
with open('metrics.txt', 'r') as file:
    lines = file.readlines()
    for line in lines[1:]: cases.append(line.split(",")[0])
    cases = list(set(cases))

    for case in cases:
        # Initialize lists to store data
        load_values = []
        throughput_values = []
        for line in lines[1:]:  # Skip the first line with headers
            if case == line.split(",")[0]:

                load, decoded, non_decoded, nodes_number, life_time, max_trans, gen_packs, delay, max_delay = map(float, line.split(",")[1:])
                load_values.append(load)
                throughput = ((non_decoded/nodes_number) / (gen_packs/nodes_number))
                throughput_values.append(throughput)

        plt.plot(load_values, throughput_values, marker='o', linestyle='-', label=case)

# Create a line graph
plt.legend()
plt.title('Load vs. Corrupted packets in Gateway')
plt.xlabel('Load')
plt.ylabel('Number of packets')
plt.grid(True)

# Display the plot or save it to a file
plt.show()
