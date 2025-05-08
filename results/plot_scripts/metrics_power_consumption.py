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
#
# ### It could be converted to Delay - max sf or max type
# def plot_power_nodes(results_df, experiment_name):
#     df = results_df.groupby(['case', 'rate'], as_index=False).mean()
#
#     # df['normalized_delay'] = (df['delay'] / df['decoded']) / df['max_delay']
#     df['power_consumption'] = df['power_consumption'] # / df['max_delay']
#
#     # Create a line plot for each case
#     cases = df['case'].unique()
#
#     #plt.figure(figsize=(14, 8))
#
#     for case in cases:
#         case_data = df[df['case'] == case]
#         plt.plot(case_data['rate'], case_data['power_consumption'], label=f"power_consumption - {case}")
#
#     plt.xlabel('rate')
#     plt.ylabel('power_consumption (ms))')
#     plt.title('power_consumption vs Number of nodes for Different Cases')
#     # plt.ylim(ymin=0)
#     # plt.xlim(xmin=0)
#     plt.legend()
#     plt.grid(True)
#
#     plt.savefig(f"./plots/power_consumption_rate/{experiment_name}.png")
#     plt.clf()
#
# # plt.show()
#
#
#


import matplotlib.pyplot as plt
import pandas as pd

def plot_power_nodes(
        results_df: pd.DataFrame,
        experiment_name: str
):
    """
    Generates a line plot comparing power consumption at different load levels
    for each scenario (case) in the provided DataFrame. The DataFrame is first
    grouped by (case, rate), and mean values are computed. The resulting plot
    shows 'rate' on the x-axis and 'power_consumption' on the y-axis.

    Parameters
    ----------
    results_df : pd.DataFrame
        Must contain at least the following columns:
          - 'case': scenario identifier (e.g., "LoRaWAN 1 gateways")
          - 'rate': numeric load level
          - 'power_consumption': numeric measure of power usage (e.g., in mJ, mW, etc.)
    experiment_name : str
        File name stem for saving the figure to disk.

    Returns
    -------
    None
    """
    # Group by case and rate, then compute the average for all numeric columns
    agg_df = results_df.groupby(['case', 'rate'], as_index=False).mean()

    # Identify the distinct scenarios
    scenario_names = agg_df['case'].unique()

    # Create the figure and axis
    plt.figure(figsize=(7, 4))
    plt.rc('font', size=11)

    # Plot each scenario on the same axes
    for scenario in scenario_names:
        scenario_data = agg_df[agg_df['case'] == scenario]
        plt.plot(
            scenario_data['rate'],
            scenario_data['power_consumption'],
            marker='o',
            linewidth=2,
            label=f"Power Consumption - {scenario}"
        )

    # Axis labels, title, and legend
    plt.xlabel('Normalized Load (rate)')
    plt.ylabel('Power Consumption (mJ)')
    plt.title('Power Consumption vs. Load for Different Scenarios')
    plt.grid(True)
    plt.legend()

    # Save to file
    out_path = f"./plots/power_consumption_rate/{experiment_name}.png"
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.clf()
    print(f"Plot saved to: {out_path}")

# Example usage:
# df = pd.read_csv("metrics.txt")
# plot_power_consumption_vs_load(df, "multihop_vs_lorawan_power")
