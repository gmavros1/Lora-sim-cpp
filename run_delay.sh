#!/bin/bash

rounds="$1"
name_of_experiment="${2}_${rounds}_${3}_moving_number_of_nodes_${4}"
echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay,interference_in_node,out_of_range_in_ge,in_range_in_ge,max_sf,time_out,drop_p_async,fairness,power_consumption" > results/metrics/"${name_of_experiment}".txt
for r in {1..8};
do
  echo ""
  nodes_num=$((${2} * r))
  echo "Nodes number $nodes_num"

  for ((i=1; i <= rounds; i++))
  do

    # Num nodes - If we want more range
    python3 ./network_init/place_nodes.py "$nodes_num" range

    rate="$4"

    echo "round $i"
    echo "Running LoRaWAn Simulation with rate $rate and $nodes_num Nodes"

    # Load - Time - Protocol - num of gateways - using adr in join process

    # We make such a call to fill node_sf.json file as we want this information for multi-hop too
    python3 ./network_init/network_init.py "$rate" "$3" LoRaWAn 1 adr "$name_of_experiment"

    python3 ./network_init/network_init.py "$rate" "$3" Multihop 1 adr "$name_of_experiment"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$rate" "$3" LoRaWAn 1 adr "$name_of_experiment"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

  done
done

cd ./results || return
# python3 metrics_th.py & python3 metrics_inf_gw.py
# python3 metrics_delay.py & python3 fairness_node.py
