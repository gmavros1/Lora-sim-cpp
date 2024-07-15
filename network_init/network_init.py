from node import Node
from gateway import Gateway
from server import Server
from metrics import Metrics
from functions import *
import json
import sys
from join_functions import multihop_join_process_inf, join_process, join_process_adr


# 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
class Topology:

    def __init__(self, num_gateways, use_multihop, load, life_time, use_adr_on_join) -> None:

        self.server = Server()
        self.metrics = Metrics()
        self.general_level = 1  # Initial value - before multi join all nodes are level 1
        self.max_sf = 7  # If ADR is not applied all nodes have sf7

        center_x, center_y = 0, 0  # rangekm / 2  # Example center x-coordinate

        # nodes_cords = generate_nodes((center_x, center_y), 32, 5900, 9) # last arg - levels
        f = open('topology/placed_nodes.json')
        data = json.load(f)
        nodes_cords, rangeKm = data["node_cords"], data["rangeKm"]

        # Define num of nodes
        self.num_nodes = len(nodes_cords)

        # nodes_cords, rangeKm = generate_nodes_random((center_x, center_y), num_nodes, 6000)
        nodes = {}

        # Save nodes in a list
        for i in range(len(nodes_cords)):
            node_id = i
            node_x = nodes_cords[i][0]
            node_y = nodes_cords[i][1]
            node_height = 0  # random.uniform(*node_height_range)
            nodes[node_id] = (node_x, node_y, node_height)

        # Create gateways and assign positions
        gateways = {}
        for i in range(num_gateways):
            gateway_id = i + 1
            gateway_x, gateway_y = get_gw_coordinates(num_of_gw, i, rangeKm)
            gateway_height = 0  # random.uniform(*gateway_height_range)
            gateways[gateway_id] = (gateway_x, gateway_y, gateway_height)

        self.nodes = []
        for node_id, position in nodes.items():
            self.nodes.append(Node(node_id, position, self.metrics))

        self.gateways = []
        for gateway_id, position in gateways.items():
            self.gateways.append(Gateway(gateway_id, position, self.server))

        if use_multihop:
            multihop_join_process_inf(self)
            # Plot topology
            print("MULTIHOP")
        else:
            if not use_adr_on_join:
                join_process(self)
            else:
                join_process_adr(self)
            # Plot topology
            print("LORAWAN ", num_gateways, "GWs")

        # ******************** # Writing to a json file
        nodes = []

        def null_to_minus_1(value):
            if value is None:
                return -1
            else:
                return value

        for n in self.nodes:
            dictionary = {
                "id": n.id,
                "channel": int(n.channel),
                "sf": n.sf,
                "transmission_p": n.transmission_power,
                "x": int(n.x),
                "y": int(n.y),
                "z": int(n.height),
                "type": n.type,
                "assigned_node": null_to_minus_1(n.assigned_node),
                "following": null_to_minus_1(n.node_following)
            }
            nodes.append(dictionary)

        gateways = []
        for g in self.gateways:
            dictionary = {
                "id": g.id,
                "x": int(g.x),
                "y": int(g.y),
                "z": int(g.height)
            }
            gateways.append(dictionary)

            # min_Interval = toa(15, 7) + duty_cycle(toa(15, 7))

        # Which case of simulation
        if use_multihop:
            net_case = f"Multihop {num_gateways} gateways"
            protocol_used = "Multihop"
        else:
            net_case = f"LoraWAN {num_gateways} gateways"
            protocol_used = "Aloha"

        # Define metric related to load based to level of every node
        level_sum = 0
        sf_sum = 0
        for nd in nodes:
            # nd
            level_sum += int(nd["type"]) + 1
            sf_sum += float(nd["sf"])
        self.general_level = level_sum / len(nodes)
        mean_sf = sf_sum / len(nodes)

        topologggy = {"nodes": nodes, "gateways": gateways, "load": load, "life_time": int(life_time), "case": net_case,
                      "level": int(self.general_level), "prt": protocol_used, "mean_sf": float(mean_sf),
                      "max_sf": int(self.max_sf)}

        json_object = json.dumps(topologggy, indent=4)
        with open("topology/topology.json", "w") as outfile:
            outfile.write(json_object)

    # Use it when comparing throughput


if __name__ == "__main__":
    load = float(sys.argv[1])
    time = int(sys.argv[2])
    protocol = sys.argv[3]
    num_of_gw = int(sys.argv[4])
    try:
        use_adr_on_join = sys.argv[5]
    except:
        use_adr_on_join = ""
    topology = Topology(num_of_gw, protocol == 'Multihop', load / 10, time, use_adr_on_join == 'adr')

    """print("TYPE 0")
    for n in topology.nodes:
        if n.type == 0:
            print(f"NODE {n.id} || Assigned to --> {n.assigned_node}")

    print("TYPE 1")
    for n in topology.nodes:
        if n.type == 1:
            print(f"NODE {n.id} || Assigned to --> {n.assigned_node}")

    print("TYPE 2")
    for n in topology.nodes:
        if n.type == 2:
            print(f"NODE {n.id} || Assigned to --> {n.assigned_node}")

    print("TYPE 3")
    for n in topology.nodes:
        if n.type == 3:
            print(f"NODE {n.id} || Assigned to --> {n.assigned_node}")

    print("TYPE 4")
    for n in topology.nodes:
        if n.type == 4:
            print(f"NODE {n.id} || Assigned to --> {n.assigned_node}")
"""

    #  plot_topology(topology)
