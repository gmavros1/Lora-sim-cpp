#!/bin/bash

python3 network_init/place_nodes.py 160 range
sleep 2
python3 ./network_init/network_init.py 1 1000 Multihop 1 adr debug && python3 ./network_init/network_init.py 1 1000 LoRaWAn 1 adr debug
