#!/bin/bash

# Moving Normalized traffic rate
# ./path/to/simulation_script rounds number_of_nodes time_slots
./run_th.sh 3 50 10000
./run_th.sh 2 40 10000

# Moving Number of Nodes
# ./run_delay.sh rounds nodes_number_multiplier time_slots load
./run_delay.sh 2 20 10000 5
./run_delay.sh 2 30 10000 5

cd results || return
python3 plots_generator.py