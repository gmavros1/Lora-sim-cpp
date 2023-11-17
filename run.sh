#!/bin/bash

echo "case,rate,decoded,non_decoded,nodes_number,life_time,maximum_trans" > results/metrics.txt
for i in {1..10}; do
  echo "Running LoRaWAn Simulation with rate $i"
  python3 ./network_init/network_init.py $i 100000 Multihop 50 1
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  python3 ./network_init/network_init.py $i 100000 LoRaWAn 50 1
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  python3 ./network_init/network_init.py $i 100000 LoRaWAn 50 2
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

  python3 ./network_init/network_init.py $i 100000 LoRaWAn 50 3
  cd cmake-build-debug
  ./Lora_sim_cpp
  cd ..

done
cd ./results
python3 metrics.py
