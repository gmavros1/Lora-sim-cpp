#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay" > results/metrics.txt
for i in {1..10}; do
  echo ""
  echo "ROUND $i"

  for i in {1..10}; do
    echo "Running LoRaWAn Simulation with rate $i"

    # Load - Time - Protocol - Num of nodes - num od gateways
    python3 ./network_init/network_init.py $i 5000 Multihop 180 1
    cd cmake-build-debug
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py $i 5000 LoRaWAn 180 1
    cd cmake-build-debug
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py $i 5000 LoRaWAn 180 2
    cd cmake-build-debug
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py $i 5000 LoRaWAn 180 3
    cd cmake-build-debug
    ./Lora_sim_cpp
    cd ..

  done
done

cd ./results || return
python3 metrics.py & python3 metrics_inf.py
# & python3 metrics_delay.py
