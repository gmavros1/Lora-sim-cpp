import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

# results_df = pd.read_csv("metrics.txt")
#display(results_df)

# result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()


### It could be converted to Delay - max sf or max type
def plot_power_nodes(results_df, experiment_name):
    df = results_df.groupby(['case', 'rate'], as_index=False).mean()

    # df['normalized_delay'] = (df['delay'] / df['decoded']) / df['max_delay']
    df['power_consumption'] = df['power_consumption'] # / df['max_delay']

    # Create a line plot for each case
    cases = df['case'].unique()

    #plt.figure(figsize=(14, 8))

    for case in cases:
        case_data = df[df['case'] == case]
        plt.plot(case_data['rate'], case_data['power_consumption'], label=f"power_consumption - {case}")

    plt.xlabel('rate')
    plt.ylabel('power_consumption (ms))')
    plt.title('power_consumption vs Number of nodes for Different Cases')
    # plt.ylim(ymin=0)
    # plt.xlim(xmin=0)
    plt.legend()
    plt.grid(True)

    plt.savefig(f"./plots/power_consumption_rate/{experiment_name}.png")
    plt.clf()

# plt.show()



