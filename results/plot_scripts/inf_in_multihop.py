import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display
pd.set_option('display.max_columns', None)

# Read the results from the CSV file
# results_df = pd.read_csv("metrics.txt")

# def plot_inference_reasons_load(results_df, experiment_name):
#     # Filter for case "Multihop 1 gateways"
#     df = results_df[results_df['case'] == 'Multihop 1 gateways']
#
#     # Group by 'rate' and calculate the mean for each group
#     df = df.groupby(['case', 'rate'], as_index=False).mean()
#
#     # Calculate the total generated packets
#     # df['gen_packets'] = df['non_decoded'] + df['decoded']
#
#     # Calculate the portion of missing packets due to various reasons
#     df['interference_in_gw'] = df['non_decoded'] / df['gen_packets']
#     df['interference_in_nd'] = df['interference_in_node'] / df['gen_packets']
#     df['out_of_range'] = df['out_of_range_in_ge'] / df['gen_packets']
#     df['receiver_not_rec_state'] = df['drop_p_async'] / df['gen_packets']
#     df['time_outs'] = df['time_out'] / df['gen_packets']
#
#     # Plot the data
#     """plt.figure(figsize=(14, 8))
#
#     plt.plot(df['rate'], df['interference_in_gw'], label='Interference in GW')
#     plt.plot(df['rate'], df['interference_in_nd'], label='Interference in Node')
#     plt.plot(df['rate'], df['out_of_range'], label='Out of Range')
#     plt.plot(df['rate'], df['other_reasons'], label='Other Reasons')
#
#     plt.xlabel('Load')
#     plt.ylabel('Portion of Missing Packets')
#     plt.title('Portion of Missing Packets vs Load for Multihop 1 Gateways')
#     plt.legend()
#     plt.grid(True)
#     plt.show()"""
#
#     # Plot the data as a stacked bar plot
#     bar_width = 0.09
#     r = df['rate']
#
#     # plt.figure(figsize=(14, 8))
#
#     plt.bar(r, df['interference_in_gw'], color='red', edgecolor='white', width=bar_width, label='Interference in GW')
#     plt.bar(r, df['interference_in_nd'], bottom=df['interference_in_gw'], color='blue', edgecolor='white', width=bar_width, label='Interference in Node')
#     plt.bar(r, df['out_of_range'], bottom=df['interference_in_gw'] + df['interference_in_nd'], color='green', edgecolor='white', width=bar_width, label='Out of Range')
#     plt.bar(r, df['receiver_not_rec_state'], bottom=df['interference_in_gw'] + df['interference_in_nd'] + df['out_of_range'], color='orange', edgecolor='white', width=bar_width, label='Receiver not in receiving state')
#     plt.bar(r, df['time_outs'], bottom=df['interference_in_gw'] + df['interference_in_nd'] + df['out_of_range'] + df['receiver_not_rec_state'], color='purple', edgecolor='white', width=bar_width, label='Time out')
#
#     plt.xlabel('Load')
#     plt.ylabel('Portion of Missing Packets')
#     plt.title('Portion of Missing Packets vs Load for Multihop 1 Gateways')
#     plt.legend()
#     plt.grid(True)
#
#     plt.savefig(f"./plots/inference_reasons_load/{experiment_name}.png")
#     plt.clf()

# plt.show()

import matplotlib.pyplot as plt
import pandas as pd

def plot_inference_reasons_load(
        results_df: pd.DataFrame,
        experiment_name: str,
        case_filter: str = 'Multihop 1 gateways'
):
    """
    Generates a stacked bar chart showing the portion of missing packets
    attributed to various causes as a function of load, specifically for the
    specified case in the DataFrame.

    Parameters
    ----------
    results_df : pd.DataFrame
        DataFrame containing columns such as:
         - 'case' : string identifier for the scenario
         - 'rate' : float representing the offered load
         - 'non_decoded' : int or float (missing packets due to interference in gateway)
         - 'gen_packets' : int or float (total generated packets)
         - 'interference_in_node' : int or float
         - 'out_of_range_in_ge' : int or float
         - 'drop_p_async' : int or float
         - 'time_out' : int or float
         ... plus other relevant fields used in the calculations
    experiment_name : str
        Filename stem for saving the resulting plot image.
    case_filter : str
        The scenario label (in 'case' column) for which to visualize data.

    Returns
    -------
    None
    """
    # Filter data to include only the specified case (e.g., "Multihop 1 gateways")
    df_filtered = results_df[results_df['case'] == case_filter].copy()

    # Group by 'case' and 'rate' and take the mean
    agg_df = df_filtered.groupby(['case', 'rate'], as_index=False).mean()

    # Calculate the fraction of missing packets due to various reasons
    # First, confirm total generated packets = gen_packets
    # If not present, you can compute gen_packets = decoded + non_decoded
    # For example: agg_df['gen_packets'] = agg_df['decoded'] + agg_df['non_decoded']

    agg_df['interference_in_gw_frac'] = agg_df['non_decoded'] / agg_df['gen_packets']
    agg_df['interference_in_node_frac'] = agg_df['interference_in_node'] / agg_df['gen_packets']
    agg_df['out_of_range_frac'] = agg_df['out_of_range_in_ge'] / agg_df['gen_packets']
    agg_df['receiver_not_state_frac'] = agg_df['drop_p_async'] / agg_df['gen_packets']
    agg_df['time_out_frac'] = agg_df['time_out'] / agg_df['gen_packets']

    # Prepare figure
    plt.figure(figsize=(8, 5))
    plt.rc('font', size=11)

    # X-axis
    x_vals = agg_df['rate']
    bar_width = 0.08

    # Plot stacked bars
    plt.bar(
        x_vals,
        agg_df['interference_in_gw_frac'],
        color='red',
        edgecolor='white',
        width=bar_width,
        label='Interference in GW'
    )
    plt.bar(
        x_vals,
        agg_df['interference_in_node_frac'],
        bottom=agg_df['interference_in_gw_frac'],
        color='blue',
        edgecolor='white',
        width=bar_width,
        label='Interference in Node'
    )
    plt.bar(
        x_vals,
        agg_df['out_of_range_frac'],
        bottom=agg_df['interference_in_gw_frac'] + agg_df['interference_in_node_frac'],
        color='green',
        edgecolor='white',
        width=bar_width,
        label='Out of Range'
    )
    plt.bar(
        x_vals,
        agg_df['receiver_not_state_frac'],
        bottom=agg_df['interference_in_gw_frac']
               + agg_df['interference_in_node_frac']
               + agg_df['out_of_range_frac'],
        color='orange',
        edgecolor='white',
        width=bar_width,
        label='Receiver not in receiving state'
    )
    plt.bar(
        x_vals,
        agg_df['time_out_frac'],
        bottom=agg_df['interference_in_gw_frac']
               + agg_df['interference_in_node_frac']
               + agg_df['out_of_range_frac']
               + agg_df['receiver_not_state_frac'],
        color='purple',
        edgecolor='white',
        width=bar_width,
        label='Time out'
    )

    # Formatting
    plt.xlabel('Load')
    plt.ylabel('Portion of Missing Packets')
    title_str = f'Portion of Missing Packets vs Load for {case_filter}'
    plt.title(title_str)
    plt.legend()
    plt.grid(True)

    # Save the figure
    out_path = f"./plots/inference_reasons_load/{experiment_name}.png"
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.clf()
    print(f"Plot saved to: {out_path}")

# Example usage:
# results_df = pd.read_csv("metrics.txt")
# plot_inference_reasons_load(results_df, "multihop_inference_analysis")
