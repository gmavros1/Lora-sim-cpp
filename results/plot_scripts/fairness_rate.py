# import matplotlib.pyplot as plt
# import pandas as pd
# from IPython.display import display
# pd.set_option('display.max_columns', None)
#
# # results_df = pd.read_csv("metrics.txt")
# #display(results_df)
#
# def plot_load_fairness(results_df, experiment_name):
#     # result_df = results_df.groupby(['case', 'rate'], as_index=False).mean()
#     df = results_df[results_df['case'] == 'Multihop 1 gateways']
#
#     df = df.groupby(['case', 'rate'], as_index=False).mean()
#
#     # df['fairness'] = (df['decoded'] / df['nodes_number']) / df['maximum_trans']
#
#     # Create a line plot for each case
#     cases = df['case'].unique()
#
#     #plt.figure(figsize=(14, 8))
#
#     for case in cases:
#         case_data = df[df['case'] == case]
#         plt.plot(case_data['rate'], case_data['fairness'], label=f"Fairness - {case}")
#         #plt.plot(case_data['rate'], case_data['load'], label=f"Load - {case}", linestyle='--')
#
#     plt.xlabel('Normalized Load')
#     plt.ylabel('Jain\'s Fairness index')
#     plt.legend()
#     plt.title('Fairness vs Load ')
#     plt.ylim(ymin=0)
#     plt.xlim(xmin=0)
#     plt.ylim(ymax=1.2)
#     plt.xlim(xmax=1.2)
#     plt.legend()
#     plt.grid(True)
#
#     plt.savefig(f"./plots/load_fairness/{experiment_name}.png")
#     plt.clf()
#
# #plt.xlim(0, 1)
# #plt.ylim(0, 1)
#
# # plt.show()
#
#
#


import matplotlib.pyplot as plt
import pandas as pd

def plot_load_fairness(
        results_df: pd.DataFrame,
        experiment_name: str,
        case_filter: str = 'Multihop 1 gateways'
):
    """
    Plots Jain's Fairness Index vs. normalized load for the specified case.
    Each data point on the line plot is labeled with its fairness value.

    Parameters
    ----------
    results_df : pd.DataFrame
        Data containing at least:
          - 'case'  (str): scenario name
          - 'rate'  (float): normalized load
          - 'fairness' (float): Jain's Fairness Index
        Possibly grouped or aggregated already, or we can do so as needed.
    experiment_name : str
        Filename stem for saving the resulting plot.
    case_filter : str
        Name of the case (column 'case') we want to visualize, default is 'Multihop 1 gateways'.

    Returns
    -------
    None
    """
    # Filter the DataFrame to the specific case
    df_filtered = results_df[results_df['case'] == case_filter].copy()

    # Group by case, rate, then mean if we want to average any repeated trials
    agg_df = df_filtered.groupby(['case', 'rate'], as_index=False).mean()

    # Prepare figure
    plt.figure(figsize=(7, 4))
    plt.rc('font', size=11)

    # Plot the line for the specified case
    x_vals = agg_df['rate']
    y_vals = agg_df['fairness']

    plt.plot(
        x_vals,
        y_vals,
        marker='o',
        linewidth=2,
        label=f"Fairness - {case_filter}"
    )

    # Label each point with the fairness value
    for x, y in zip(x_vals, y_vals):
        plt.text(
            x,
            y + 0.01,              # Small vertical offset so text is above the point
            f"{y:.2f}",
            ha='center',
            va='bottom',
            fontsize=9
        )

    # Axes labels, limits, and legend
    plt.xlabel('Normalized Load')
    plt.ylabel("Jain's Fairness Index")
    plt.title('Fairness vs. Load')
    plt.ylim(0, 1.2)
    plt.xlim(0, 1.2)
    plt.grid(True)
    plt.legend()

    # Save figure
    out_path = f"./plots/load_fairness/{experiment_name}.png"
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.clf()
    print(f"Plot saved to: {out_path}")

# Example usage:
# ----------------------------------
# df = pd.read_csv("metrics.txt")
# plot_load_fairness(df, "my_fairness_experiment")
# ----------------------------------
