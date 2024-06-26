#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans,gen_packets,delay,max_delay" > results/metrics.txt
for i in {1..10}; do
  echo "Running LoRaWAn Simulation with rate $i"

  python3 ./network_init/network_init.py $i 100000 Multihop 200 1
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  python3 ./network_init/network_init.py $i 1000000 LoRaWAn 200 1
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  python3 ./network_init/network_init.py $i 1000000 LoRaWAn 200 2
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  python3 ./network_init/network_init.py $i 1000000 LoRaWAn 200 3
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  #python3 ./network_init/network_init.py $i 2000000 LoRaWAn 500 4
  #cd cmake-build-debug
  #./Lora_sim_cpp
  #cd ..

done
cd ./results
python3 metrics.py & python3 metrics_inf.py
# & python3 metrics_delay.py
