# import matplotlib.pyplot as plt
# import pandas as pd
# from IPython.display import display
# pd.set_option('display.max_columns', None)
#
# # results_df = pd.read_csv("metrics.txt")
# #display(results_df)
#
# # result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()
#
# def plot_load_th(results_df, experiment_name):
#
#     df = results_df.groupby(['case', 'rate'], as_index=False).mean()
#
#     df['throughput'] = (df['decoded'] / df['nodes_number']) / df['maximum_trans']
#
#     # Create a line plot for each case
#     cases = df['case'].unique()
#
#     #plt.figure(figsize=(14, 8))
#
#     for case in cases:
#         case_data = df[df['case'] == case]
#         plt.plot(case_data['rate'], case_data['throughput'], label=f"Throughput - {case}")
#         #plt.plot(case_data['rate'], case_data['load'], label=f"Load - {case}", linestyle='--')
#
#     plt.xlabel('Normalized Load')
#     plt.ylabel('Normalized Throughout')
#     plt.title('Throughput vs Load for each Network Topologies')
#     plt.legend()
#     plt.grid(True)
#
#     plt.savefig(f"./plots/load_throughput/{experiment_name}.png")
#     plt.clf()

#plt.xlim(0, 1)
#plt.ylim(0, 1)

# plt.show()

import matplotlib.pyplot as plt
import pandas as pd

def plot_load_th(
        results_df: pd.DataFrame,
        experiment_name: str,
        x_col: str = 'rate',
        y_col: str = 'decoded',
        group_col: str = 'case',
        node_count_col: str = 'nodes_number',
        max_trans_col: str = 'maximum_trans'
):
    """
    Creates a line plot showing normalized throughput vs. normalized load
    for each distinct 'case' in the results DataFrame.

    Parameters
    ----------
    results_df : pd.DataFrame
        Data containing columns:
         - 'case'  (str): identifies each network scenario
         - 'rate'  (float): the offered/normalized load
         - 'decoded' (int): number of successfully decoded packets
         - 'nodes_number' (int): number of nodes in the simulation
         - 'maximum_trans' (int or float): scaling factor for maximum transmissions
    experiment_name : str
        Output filename stem (no extension) for the saved plot.
    x_col : str
        Column name in results_df representing the x-axis (default 'rate').
    y_col : str
        Column name in results_df representing successful transmissions (default 'decoded').
    group_col : str
        Column name used to group scenarios (default 'case').
    node_count_col : str
        Column name for number of nodes (default 'nodes_number').
    max_trans_col : str
        Column name for maximum transmissions factor (default 'maximum_trans').

    Returns
    -------
    None
    """
    # Compute average over any repeated trials
    agg_df = results_df.groupby([group_col, x_col], as_index=False).mean()

    # Calculate normalized throughput
    # throughput = (# decoded / # nodes) / maximum_trans
    agg_df['throughput'] = (agg_df[y_col] / agg_df[node_count_col]) / agg_df[max_trans_col]

    # Identify each scenario (case)
    scenario_names = agg_df[group_col].unique()

    # Prepare figure
    plt.figure(figsize=(8, 5))
    plt.rc('font', size=11)  # slightly larger font

    # Plot each scenario
    for scenario in scenario_names:
        scenario_data = agg_df[agg_df[group_col] == scenario]
        plt.plot(
            scenario_data[x_col],
            scenario_data['throughput'],
            marker='o',
            linewidth=2,
            label=f"Throughput - {scenario}"
        )

    # Labeling and formatting
    plt.xlabel('Normalized Load')
    plt.ylabel('Normalized Throughput')
    plt.title('Throughput vs. Load for Each Network Topology')
    plt.legend()
    plt.grid(True)

    # Optionally set x or y limits, e.g.:
    # plt.xlim(0, 1)
    # plt.ylim(0, 1)

    # Save the figure to file
    out_path = f"./plots/load_throughput/{experiment_name}.png"
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.clf()
    print(f"Plot saved to: {out_path}")


# Example usage:
# ---------------------------------------------------------
# import pandas as pd
#
# # Suppose we have a CSV with columns: ['case','rate','decoded','nodes_number','maximum_trans']
# results_df = pd.read_csv("metrics.txt")
# plot_load_vs_throughput(results_df, "my_experiment")
# ---------------------------------------------------------



