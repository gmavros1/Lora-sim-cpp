#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay" > results/metrics.txt
for r in {1..1}; do
  echo ""
  echo "ROUND $r"

  # Num nodes
  python3 ./network_init/place_nodes.py 4

  for i in {4..4}; do
    echo "Running LoRaWAn Simulation with rate $i"

    # Load - Time - Protocol - num od gateways
    python3 ./network_init/network_init.py "$i" 100000 Multihop 1
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    #python3 ./network_init/network_init.py "$i" 50000 LoRaWAn 1
    #cd cmake-build-debug || return
    #./Lora_sim_cpp
    #cd ..

    #python3 ./network_init/network_init.py "$i" 500000 LoRaWAn 2
    #cd cmake-build-debug || return
    #./Lora_sim_cpp
    #cd ..

    #python3 ./network_init/network_init.py "$i" 500000 LoRaWAn 3
    #cd cmake-build-debug || return
    #./Lora_sim_cpp
    #cd ..

  done
done

cd ./results || return
#python3 metrics.py & python3 metrics_inf.py
# & python3 metrics_delay.py
