#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay,interference_in_node,out_of_range_in_ge,in_range_in_ge" > results/metrics.txt
for r in {1..10}; do
  echo ""
  nodes_num=$((120 * r))
  echo "Nodes number $nodes_num"

  # Num nodes - If we want more range
  python3 ./network_init/place_nodes.py "$nodes_num" range

  for i in {1..1}; do

    rate=1

    echo "Running LoRaWAn Simulation with rate $rate and $nodes_num Nodes"

    # Load - Time - Protocol - num of gateways - using adr in join process

    python3 ./network_init/network_init.py "$rate" 50000 Multihop 1 "adr"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$rate" 50000 LoRaWAn 1 "adr"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

  done
done

cd ./results || return
# python3 metrics_th.py & python3 metrics_inf_gw.py
python3 metrics_delay.py
