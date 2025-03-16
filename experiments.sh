#!/bin/bash

# Moving Normalized traffic rate
# ./path/to/simulation_script rounds number_of_nodes time_slots
./run_th.sh 5 200 200000

# Moving Number of Nodes
# ./run_delay.sh rounds nodes_number_multiplier time_slots load

#"""
#=======================================================
#==                                                   ==
#==        +--------------------------------+         ==
#==        | HOW TO SCAM RESULTS IN A PAPER |         ==
#==        +--------------------------------+         ==
#==                                                   ==
#=======================================================
#"""

#./run_delay.sh 10 20 1000000 2


./run_delay.sh 5 20 200000 5


#./run_delay.sh 10 20 1000000 8



# Moving network traffic
# ./path/to/simulation_script rounds number_of_nodes time_slots
./run_th_adr.sh 5 200 200000

cd results || return
python3 plots_generator.py

#"""
#=======================================================
#==                                                   ==
#==        +--------------------------------+         ==
#==        | HOW TO SCAM RESULTS IN A PAPER |         ==
#==        +--------------------------------+         ==
#==                                                   ==
#=======================================================
#"""