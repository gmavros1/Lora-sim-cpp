import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

results_df = pd.read_csv("metrics.txt")
#display(results_df)

# result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()

df = results_df.groupby(['case', 'nodes_number'], as_index=False).mean()

df['normalized_delay'] = (df['delay'] / df['decoded']) # / df['max_delay']

# Create a line plot for each case
cases = df['case'].unique()

#plt.figure(figsize=(14, 8))

for case in cases:
    case_data = df[df['case'] == case]
    plt.plot(case_data['nodes_number'], case_data['normalized_delay'], label=f"Delay - {case}")

plt.xlabel('Rate')
plt.ylabel('Delay (ms))')
plt.title('Delay vs Number of nodes for Different Cases')
plt.legend()
plt.grid(True)


plt.show()



