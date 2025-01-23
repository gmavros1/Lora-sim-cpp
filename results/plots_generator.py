import os
import pandas as pd
from plot_scripts.metrics_th import plot_load_th
from plot_scripts.fairness_node import plot_fairness_nodes
from plot_scripts.fairness_rate import plot_load_fairness
from plot_scripts.inf_in_multihop import plot_inference_reasons_load
from plot_scripts.metrics_delay import plot_delay_nodes
from plot_scripts.metrics_inf_gw import plot_inf_gateway

### Listing all files of metrics ###
def contains(word, file):
    if word in file: return True

metric_files =  os.listdir("./metrics/")
different_loads = [f for f in metric_files if contains("load", f)]
different_nodes = [f for f in metric_files if contains("nodes", f)]

### This section is about experiments using different traffic loads ###

# Throughput - Normalized Load
for diff in different_loads:
    plot_load_th(pd.read_csv("./metrics/"+diff), diff)

# Fairness - Normalized Load
for diff in different_loads:
    plot_load_fairness(pd.read_csv("./metrics/"+diff), diff)

# Reasons of inference - Normalized Load
for diff in different_loads:
    plot_inference_reasons_load(pd.read_csv("./metrics/"+diff), diff)

# Collisions in gateway - Normalized Load
for diff in different_loads:
    plot_inf_gateway(pd.read_csv("./metrics/"+diff), diff)

### This section is about experiments using different number of nodes ###

# Delay - Nodes Number
for diff in different_nodes:
    plot_delay_nodes(pd.read_csv("./metrics/"+diff), diff)

# Fairness - Nodes Number
for diff in different_nodes:
    plot_fairness_nodes(pd.read_csv("./metrics/"+diff), diff)

