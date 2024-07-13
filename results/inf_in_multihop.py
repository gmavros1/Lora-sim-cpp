import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

# Read the results from the CSV file
results_df = pd.read_csv("metrics.txt")

# Filter for case "Multihop 1 gateways"
df = results_df[results_df['case'] == 'Multihop 1 gateways']

# Group by 'rate' and calculate the mean for each group
df = df.groupby(['case', 'rate'], as_index=False).mean()

# Calculate the total generated packets
# df['gen_packets'] = df['non_decoded'] + df['decoded']

# Calculate the portion of missing packets due to various reasons
df['interference_in_gw'] = df['non_decoded'] / df['gen_packets']
df['interference_in_nd'] = df['interference_in_node'] / df['gen_packets']
df['out_of_range'] = df['out_of_range_in_ge'] / df['gen_packets']
df['other_reasons'] = (df['gen_packets'] - df['decoded'] - df['non_decoded'] - df['interference_in_node'] - df['out_of_range_in_ge']) / df['gen_packets']

# Plot the data
"""plt.figure(figsize=(14, 8))

plt.plot(df['rate'], df['interference_in_gw'], label='Interference in GW')
plt.plot(df['rate'], df['interference_in_nd'], label='Interference in Node')
plt.plot(df['rate'], df['out_of_range'], label='Out of Range')
plt.plot(df['rate'], df['other_reasons'], label='Other Reasons')

plt.xlabel('Load')
plt.ylabel('Portion of Missing Packets')
plt.title('Portion of Missing Packets vs Load for Multihop 1 Gateways')
plt.legend()
plt.grid(True)
plt.show()"""

# Plot the data as a stacked bar plot
bar_width = 0.09
r = df['rate']

plt.figure(figsize=(14, 8))

plt.bar(r, df['interference_in_gw'], color='red', edgecolor='white', width=bar_width, label='Interference in GW')
plt.bar(r, df['interference_in_nd'], bottom=df['interference_in_gw'], color='blue', edgecolor='white', width=bar_width, label='Interference in Node')
plt.bar(r, df['out_of_range'], bottom=df['interference_in_gw'] + df['interference_in_nd'], color='green', edgecolor='white', width=bar_width, label='Out of Range')
plt.bar(r, df['other_reasons'], bottom=df['interference_in_gw'] + df['interference_in_nd'] + df['out_of_range'], color='orange', edgecolor='white', width=bar_width, label='Other Reasons')

plt.xlabel('Load')
plt.ylabel('Portion of Missing Packets')
plt.title('Portion of Missing Packets vs Load for Multihop 1 Gateways')
plt.legend()
plt.grid(True)
plt.show()