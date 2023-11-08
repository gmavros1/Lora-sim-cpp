#!/bin/bash

for i in {1..10}; do
  echo "Running network_init.py with argument $i"
  python3 ./network_init/network_init.py $i
  echo "Finished running network_init.py"

  echo "Running Lora_sim_cpp"
  cd cmake-build-debug
  ./Lora_sim_cpp
  echo "Finished running Lora_sim_cpp"
  cd ..
done
