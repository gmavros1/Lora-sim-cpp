import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

# results_df = pd.read_csv("metrics.txt")
#display(results_df)
def plot_fairness_nodes(results_df, experiment_name):

    # result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()
    df = results_df[results_df['case'] == 'Multihop 1 gateways']

    df = df.groupby(['case', 'max_sf'], as_index=False).mean()

    # df['fairness'] = (df['decoded'] / df['nodes_number']) / df['maximum_trans']

    # Create a line plot for each case
    cases = df['case'].unique()

    #plt.figure(figsize=(14, 8))

    for case in cases:
        case_data = df[df['case'] == case]
        plt.plot(case_data['max_sf'], case_data['fairness'], label=f"Fairness - {case}")
        #plt.plot(case_data['rate'], case_data['load'], label=f"Load - {case}", linestyle='--')

    plt.xlabel('Mac SF')
    plt.ylabel('Jain\'s Fairness index')
    plt.legend()
    plt.title('Fairness vs Max\' SF ')
    plt.ylim(ymin=0)
    plt.xlim(xmin=0)
    plt.ylim(ymax=1.2)
    plt.xlim(xmax=1.2)
    plt.legend()
    plt.grid(True)

    plt.savefig(f"./plots/nodes_fairness/{experiment_name}.png")
    plt.clf()

#plt.xlim(0, 1)
#plt.ylim(0, 1)

# plt.show()



