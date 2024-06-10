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
        delay_values = []
        for line in lines[1:]:  # Skip the first line with headers
            if case == line.split(",")[0]:
                load, decoded, non_decoded, nodes_number, life_time, max_trans, gen_packs, delay, max_delay = map(float,
                                                                                                       line.split(",")[
                                                                                                       1:])
                load_values.append(load * 10)
                load_values = [8, 9, 10, 11, 12]
                delay_temp = (delay / decoded) / max_delay
                delay_values.append(delay_temp)

        plt.plot(load_values, delay_values, marker='o', linestyle='-', label=case)

# Create a line graph
plt.legend()
plt.title('Load vs. Delay per Node per Transmission')
plt.xlabel('max sf')
plt.ylabel('Delay')
plt.grid(True)

# Display the plot or save it to a file
plt.show()
