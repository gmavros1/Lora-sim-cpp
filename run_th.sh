#!/bin/bash

rounds="$1"
name_of_experiment="${2}_${rounds}_${3}_moving_load"
echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay,interference_in_node,out_of_range_in_ge,in_range_in_ge,max_sf,time_out,drop_p_async,fairness" > results/metrics/"${name_of_experiment}".txt

for ((r=1; r <= rounds; r++))
do
  echo ""
  echo "ROUND $r"

  # Num nodes
  python3 ./network_init/place_nodes.py "$2" range

  for i in {1..10}; do
    echo "Running LoRaWAn Simulation with rate $i"

    # Load Time_slots Protocol num_of_gateways using_adr_in_join_process number_of_gateways name_of_experiment

    python3 ./network_init/network_init.py "$i" "$3" Multihop 1 no_adr  "$name_of_experiment"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$i" "$3" LoRaWAn 1 no_adr  "$name_of_experiment"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$i" "$3" LoRaWAn 2 no_adr  "$name_of_experiment"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

    python3 ./network_init/network_init.py "$i" "$3" LoRaWAn 3 no_adr "$name_of_experiment"
    cd cmake-build-debug || return
    ./Lora_sim_cpp
    cd ..

  done
done

cd ./results || return
# python3 metrics_th.py & python3 metrics_inf_gw.py & python3 inf_in_multihop.py & python3 fairness_rate.py
