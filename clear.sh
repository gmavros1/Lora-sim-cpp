#!/bin/bash

find results/plots -name '*.png' -exec rm -f {} +
find results/metrics -name '*.txt' -exec rm -f {} +