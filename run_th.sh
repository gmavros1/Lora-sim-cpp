#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay,interference_in_node,out_of_range_in_ge,in_range_in_ge" > results/metrics.txt
for r in {1..3}; do
  echo ""
  echo "ROUND $r"

  # Num nodes
  python3 ./network_init/place_nodes.py 50

  for i in {1..10}; do
    echo "Running LoRaWAn Simulation with rate $i"

    # Load - Time - Protocol - num of gateways - using adr in join process

    python3 ./network_init/network_init.py "$i" 500000 Multihop 1
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$i" 500000 LoRaWAn 1
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$i" 500000 LoRaWAn 2
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$i" 500000 LoRaWAn 3
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

  done
done

cd ./results || return
python3 metrics_th.py & python3 metrics_inf.py
