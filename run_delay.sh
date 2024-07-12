#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay" > results/metrics.txt
for r in {1..10}; do
  echo ""
  echo "ROUND $r"

  # Num nodes
  python3 ./network_init/place_nodes.py $((40 * r))

  for i in {1..3}; do

    rate=5

    echo "Running LoRaWAn Simulation with rate $rate"

    # Load - Time - Protocol - num od gateways
    python3 ./network_init/network_init.py "$rate" 1000000 Multihop 1 "adr"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$rate" 1000000 LoRaWAn 1 "adr"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$rate" 1000000 LoRaWAn 2 "adr"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$rate" 1000000 LoRaWAn 3 "adr"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

  done
done

cd ./results || return
# python3 metrics.py & python3 metrics_inf.py
python3 metrics_delay.py
