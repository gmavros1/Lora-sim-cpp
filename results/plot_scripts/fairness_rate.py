import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

# results_df = pd.read_csv("metrics.txt")
#display(results_df)

def plot_load_fairness(results_df, experiment_name):
    # result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()
    df = results_df[results_df['case'] == 'Multihop 1 gateways']

    df = df.groupby(['case', 'rate'], as_index=False).mean()

    # df['fairness'] = (df['decoded'] / df['nodes_number']) / df['maximum_trans']

    # Create a line plot for each case
    cases = df['case'].unique()

    #plt.figure(figsize=(14, 8))

    for case in cases:
        case_data = df[df['case'] == case]
        plt.plot(case_data['rate'], case_data['fairness'], label=f"Fairness - {case}")
        #plt.plot(case_data['rate'], case_data['load'], label=f"Load - {case}", linestyle='--')

    plt.xlabel('Normalized Load')
    plt.ylabel('Jain\'s Fairness index')
    plt.legend()
    plt.title('Fairness vs Load ')
    plt.legend()
    plt.grid(True)

    plt.savefig(f"./plots/load_fairness/{experiment_name}.png")
    plt.clf()

#plt.xlim(0, 1)
#plt.ylim(0, 1)

# plt.show()



