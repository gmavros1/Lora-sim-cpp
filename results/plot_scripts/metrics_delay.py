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
# def plot_delay_nodes(results_df, experiment_name):
#     df = results_df.groupby(['case', 'max_sf'], as_index=False).mean()
#
#     # df['normalized_delay'] = (df['delay'] / df['decoded']) / df['max_delay']
#     df['normalized_delay'] = df['delay'] # / df['max_delay']
#
#     # Create a line plot for each case
#     cases = df['case'].unique()
#     #
#     #plt.figure(figsize=(14, 8))
#
#     for case in cases:
#         case_data = df[df['case'] == case]
#         plt.plot(case_data['max_sf'], case_data['normalized_delay'], label=f"Delay - {case}")
#
#     plt.xlabel('max_sf')
#     plt.ylabel('Delay (ms))')
#     plt.title('Delay vs Number of nodes for Different Cases')
#     plt.legend()
#     plt.grid(True)
#
#     plt.savefig(f"./plots/delay_nodes/{experiment_name}.png")
#     plt.clf()
#
# # plt.show()
#
#
#


import matplotlib.pyplot as plt
import pandas as pd

def plot_delay_nodes(
        results_df: pd.DataFrame,
        experiment_name: str
):
    """
    Plots the average end-to-end delay versus the 'max_sf' parameter for
    each distinct scenario (case) in the given DataFrame.

    This function:
      1) Groups the data by ('case', 'max_sf') and computes mean values.
      2) For each scenario, creates a line plot where the x-axis is 'max_sf'
         (which may represent an increase in node count or maximum spreading factor),
         and the y-axis is the average delay (in ms).
      3) Saves the resulting figure as a PNG file.

    Parameters
    ----------
    results_df : pd.DataFrame
        The DataFrame should contain columns:
          - 'case': scenario or experiment label
          - 'max_sf': numeric parameter (could represent number of nodes, or SF limit)
          - 'delay': measured delay (ms)
        Additional columns are allowed but not directly used by this function.
    experiment_name : str
        Filename stem for saving the figure. The plot is saved to
        ./plots/delay_nodes/<experiment_name>.png

    Returns
    -------
    None
    """
    # Group and compute mean for all columns within each (case, max_sf) pair
    agg_df = results_df.groupby(['case', 'max_sf'], as_index=False).mean()

    # In this example, we simply alias 'delay' to 'normalized_delay'
    # if you have a reason to normalize it, do so here
    agg_df['normalized_delay'] = agg_df['delay']

    # Identify the scenarios
    scenario_names = agg_df['case'].unique()

    # Create the plot
    plt.figure(figsize=(7, 4))
    plt.rc('font', size=11)

    # Plot each scenario as a line
    for scenario in scenario_names:
        scenario_data = agg_df[agg_df['case'] == scenario]
        plt.plot(
            scenario_data['max_sf'],
            scenario_data['normalized_delay'],
            marker='o',
            linewidth=2,
            label=f"Delay - {scenario}"
        )

    # Configure axes and legend
    plt.xlabel('Maximum SF Required')
    plt.ylabel('Delay (ms)')
    plt.title('Delay vs. Number of Nodes for Different Cases')
    plt.grid(True)
    plt.legend()

    # Save and clear
    out_path = f"./plots/delay_nodes/{experiment_name}.png"
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.clf()
    print(f"Plot saved to: {out_path}")

# Usage Example:
# df = pd.read_csv("metrics.txt")
# plot_delay_vs_nodes(df, "experiment_delay")
