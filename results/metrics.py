import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

results_df = pd.read_csv("metrics.txt")
display(results_df)

# result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()

df = results_df.groupby(['case', 'rate'], as_index=False).mean()

df['throughput'] = (df['decoded'] / df['nodes_number']) / df['maximum_trans']

# Create a line plot for each case
cases = df['case'].unique()

#plt.figure(figsize=(14, 8))

for case in cases:
    case_data = df[df['case'] == case]
    plt.plot(case_data['rate'], case_data['throughput'], label=f"Throughput - {case}")
    #plt.plot(case_data['rate'], case_data['load'], label=f"Load - {case}", linestyle='--')

plt.xlabel('Rate')
plt.ylabel('Throughput / Load')
plt.title('Throughput and Load vs Rate for Different Cases')
plt.legend()
plt.grid(True)


#plt.xlim(0, 1)
#plt.ylim(0, 1)

plt.show()



