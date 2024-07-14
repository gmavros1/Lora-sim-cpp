from functions import *
import json
from node import Node
import sys


def place_nodes(num_nodes, range_boost):
    center_x, center_y = 0, 0
    if range_boost:
        nodes_cords, rangeKm = generate_nodes_random_more_range((center_x, center_y), num_nodes, 5700)
    else:
        nodes_cords, rangeKm = generate_nodes_random((center_x, center_y), num_nodes, 5700)

    nodes = {"node_cords": nodes_cords, "rangeKm": rangeKm}

    json_object = json.dumps(nodes, indent=4)
    with open("topology/placed_nodes.json", "w") as outfile:
        outfile.write(json_object)


if __name__ == "__main__":
    num_nodes = int(sys.argv[1])
    try:
        range_boost = sys.argv[2]
    except:
        range_boost = None
    place_nodes(num_nodes, range_boost == "range")
