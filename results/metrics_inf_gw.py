import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

results_df = pd.read_csv("metrics.txt")
# display(results_df)

df = results_df.groupby(['case', 'rate'], as_index=False).mean()

df['inference'] = (df['non_decoded']) / (df['in_range_in_ge'])  # / df['gen_packets'] IT SHOULD BE / TRANSMISSIONS REACHED THE GW

# Create a line plot for each case
cases = df['case'].unique()

plt.figure(figsize=(14, 8))

for case in cases:
    case_data = df[df['case'] == case]
    plt.plot(case_data['rate'], case_data['inference'], label=f"Packet loss - {case}")

plt.xlabel('Load')
plt.ylabel('Packet loss')
plt.title('Packet loss vs Load')
plt.legend()
plt.grid(True)
plt.show()
