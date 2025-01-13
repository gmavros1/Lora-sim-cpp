# Get the argument for i from the command line
i=$1

# Check if the argument is provided
if [ -z "$i" ]; then
    echo "Usage: $0 <i>"
    exit 1
fi

# Define your cases in an array
declare -a cases=(
    "python3 ./network_init/network_init.py \"$i\" 100000 Multihop 1 && cd cmake-build-debug || return && ./Lora_sim_cpp && cd .."
    "python3 ./network_init/network_init.py \"$i\" 100000 LoRaWAn 1 && cd cmake-build-debug || return && ./Lora_sim_cpp && cd .."
    "python3 ./network_init/network_init.py \"$i\" 100000 LoRaWAn 2 && cd cmake-build-debug || return && ./Lora_sim_cpp && cd .."
    "python3 ./network_init/network_init.py \"$i\" 100000 LoRaWAn 3 && cd cmake-build-debug || return && ./Lora_sim_cpp && cd .."
)

# Run all cases in parallel
for case in "${cases[@]}"; do
    eval "$case" &
    sleep 1  # Add a 1-second delay between each case
done

# Wait for all background processes to finish
wait