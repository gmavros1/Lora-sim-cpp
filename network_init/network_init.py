import random
import matplotlib.pyplot as plt
import numpy as np
from node import Node
from gateway import Gateway
from server import Server
from metrics import Metrics
from functions import *
from protocol import Multihop
from protocol import Lorawan
import json
import os


# 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
class Topology:

    def __init__(self, num_nodes, num_gateways, use_multihop, rangekm, load, life_time) -> None:

        self.server = Server()
        self.metrics = Metrics()
        self.num_nodes = num_nodes
        self.general_level = 1
        self.max_sf = 7

        def generate_random_coordinates(center_x, center_y, min_distance, max_distance):
            # Generate a random Euclidean distance within the specified range
            euclidean_distance = np.random.uniform(min_distance, max_distance)

            # Generate a random angle (theta) between 0 and 2*pi
            theta = np.random.uniform(0, 2 * np.pi)

            # Calculate x and y coordinates using polar coordinates
            x = center_x + euclidean_distance * np.cos(theta)
            y = center_y + euclidean_distance * np.sin(theta)

            return x, y

        if num_gateways > 1:
            # Range of x-coordinates for gateways
            gateway_x_range = (rangekm / 2 - 8000, rangekm / 2 + 8000)
            # Range of y-coordinates for gateways
            gateway_y_range = (rangekm / 2 - 8000, rangekm / 2 + 8000)
        else:
            # Range of x-coordinates for gateways
            gateway_x_range = (rangekm / 2 - 8000, rangekm / 2 + 8000)
            # Range of y-coordinates for gateways
            gateway_y_range = (rangekm / 2 - 8000, rangekm / 2 + 8000)

        def get_gw_coordinates(num_of_gw, which_gw, rangekm, max_distance):
            if num_of_gw == 1:
                return rangekm / 2, rangekm / 2
            if num_of_gw == 2:
                if which_gw == 0:
                    return (rangekm / 2 + (2 / 3) * max_distance), (rangekm / 2 + (2 / 3) * max_distance)
                else:
                    return (rangekm / 2 - (2 / 3) * max_distance), (rangekm / 2 - (2 / 3) * max_distance)
            if num_of_gw == 3:
                if which_gw == 0:
                    return (rangekm / 2), (rangekm / 2 + (2 / 3) * max_distance)
                elif which_gw == 1:
                    return (rangekm / 2 - (2 / 3) * max_distance), (rangekm / 2 - (2 / 3) * max_distance)
                else:
                    return (rangekm / 2 + (2 / 3) * max_distance), (rangekm / 2 - (2 / 3) * max_distance)

        node_height_range = (0, 10)
        gateway_height_range = (40, 50)
        center_x = rangekm / 2  # Example center x-coordinate
        center_y = rangekm / 2  # Example center y-coordinate

        """ratio_for_type_0 = 0.9
        # ratio_for_type_0 = 1
        # ratio_for_type_0 = 1 - ratio_for_type_1

        nodes = {}

        # For type 0 nodes
        min_distance = 6000  # Example minimum distance in meters
        max_distance = 12000  # Example maximum distance in meters
        # min_distance = 100  # Example minimum distance in meters
        # max_distance = 10000  # Example maximum distance in meters

        # Create nodes and assign positions
        for i in range(int(num_nodes * ratio_for_type_0)):
            node_id = i
            node_x, node_y = generate_random_coordinates(
                center_x, center_y, min_distance, max_distance)
            node_height = random.uniform(*node_height_range)
            nodes[node_id] = (node_x, node_y, node_height)

        # For type 1 nodes
        min_distance = 5500  # Example minimum distance in meters
        max_distance = 6000  # Example maximum distance in meters

        for i in range(int(num_nodes * ratio_for_type_0), num_nodes):
            node_id = i
            node_x, node_y = generate_random_coordinates(
                center_x, center_y, min_distance, max_distance)
            node_height = random.uniform(*node_height_range)
            nodes[node_id] = (node_x, node_y, node_height)"""

        nodes_cords = generate_nodes((center_x, center_y), 32, 5900, 9) # last arg - levels
        nodes = {}

        for i in range(len(nodes_cords)):
            node_id = i
            node_x = nodes_cords[i][0]
            node_y = nodes_cords[i][1]
            node_height = random.uniform(*node_height_range)
            nodes[node_id] = (node_x, node_y, node_height)

        # Create gateways and assign positions
        gateways = {}
        for i in range(num_gateways):
            gateway_id = i + 1
            # gateway_x = random.uniform(*gateway_x_range)
            # gateway_y = random.uniform(*gateway_y_range)
            gateway_x, gateway_y = get_gw_coordinates(num_of_gw, i, rangekm, max_distance=8000)
            gateway_height = random.uniform(*gateway_height_range)
            gateways[gateway_id] = (gateway_x, gateway_y, gateway_height)

        self.nodes = []
        for node_id, position in nodes.items():
            self.nodes.append(Node(node_id, position, self.metrics))

        self.gateways = []
        for gateway_id, position in gateways.items():
            self.gateways.append(Gateway(gateway_id, position, self.server))

        if use_multihop:
            self.multihop_join_process_inf()
            # Plot topology
            print("MULTIHOP")
        else:
            self.join_process()
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
        net_case = ''
        protocol_used = ''
        if use_multihop:
            net_case = f"Multihop {num_gateways} gateways"
            protocol_used = "Multihop"
        else:
            net_case = f"LoraWAN {num_gateways} gateways"
            protocol_used = "Aloha"

        # print(f"LEVEL: {self.general_level}")

        # Define metric related to load based to level of every node
        level_sum = 0
        for nd in nodes:
            # nd
            level_sum += int(nd["type"]) + 1
        traffic_prd = level_sum / len(nodes)
        # print(level_sum/num_nodes)
        # print(self.general_level)
        all_same = 1
        # print(f"max sf: {self.max_sf}")

        topologggy = {"nodes": nodes, "gateways": gateways, "load": load, "life_time": int(life_time), "case": net_case,
                      "level": int(self.general_level), "prt": protocol_used, "rate_prd": float(self.general_level), "max_sf": float(self.max_sf)}

        json_object = json.dumps(topologggy, indent=4)
        with open("topology/topology.json", "w") as outfile:
            outfile.write(json_object)

    def add_gateway(self, num_gateways, rangekm):

        # Range of x-coordinates for gateways
        def getrange(pos):
            gateway_x_range = (rangekm / 2, rangekm / 2)
            # Range of y-coordinates for gateways
            gateway_y_range = (rangekm / 2 + pos, rangekm / 2 + pos)

            return gateway_x_range, gateway_y_range

        pos = [-8000, +8000]

        gateway_height_range = (40, 50)

        gateways = {}
        for i in range(num_gateways):
            gateway_x_range, gateway_y_range = getrange(pos[i % 2])

            gateway_id = f"Gateway{len(self.gateways) + i + 1}"
            gateway_x = random.uniform(*gateway_x_range)
            gateway_y = random.uniform(*gateway_y_range)
            gateway_height = random.uniform(*gateway_height_range)
            gateways[gateway_id] = (gateway_x, gateway_y, gateway_height)

        for gateway_id, position in gateways.items():
            self.gateways.append(Gateway(gateway_id, position, self.server))

    def join_process(self):
        for nd in self.nodes:
            nd.type = 0

        self.max_sf = 7


    def join_process_adr(self):
        for nd in self.nodes:
            nd.type = 0

        sum_sf = 0.0

        gw = self.gateways[0]
        for nd in self.nodes:
            dist = distance_nodes(nd, gw)

            rec_power = calculate_received_power(
                dist, nd.transmission_power)

            # ADR like
            while True:
                if calculate_snr(rec_power, -(130 + 2.5)) >= snr_limit(nd.sf) + 10:
                    break
                elif nd.sf == 12:
                    # print("OUT OF RANGE")
                    break
                else:
                    nd.sf += 1

            temp_sf = nd.sf

            #plus_sf = dist // 6000
            #temp_sf = 7 + plus_sf
            # print(temp_sf)

            sum_sf += temp_sf  # If we want the mean - comment out following

            if temp_sf > self.max_sf:
                self.max_sf = temp_sf

        self.max_sf = float(sum_sf/len(self.nodes))
        ### TO ENABLE MULTIHOP ###
        #print(self.max_sf)

    def multihop_join_process_inf(self):

        # Store nodes, first index is type (0 starting from close to gw)
        # store node, rec_power, rec_id
        node_and_types = []

        # 1. Collect L0 - single hop to gw
        node_and_types.append([])
        for node in self.nodes:
            # For each node select the min distance form gw
            distance_to_gw = []
            for gw in self.gateways:
                distance_to_gw.append(distance_nodes(node, gw))
            min_distance = min(distance_to_gw)

            rec_power = calculate_received_power(
                min_distance, node.transmission_power)

            if calculate_snr(rec_power, -(130 + 2.5)) >= snr_limit(node.sf) + 10:  # rec_power >= -130:
                node.type = 0  # middle node - which is also the type index of node_and_types list
                node.state = "Listen"
                node_and_types[-1].append(
                    {"node": node, "rec_power": [rec_power], "rec_id": [-1]})  # same index - associate id - rec power

        # 2. Go for the others
        level = 1
        while True:

            node_and_types.append([])

            count_new_entries = 0
            for node in self.nodes:  # node which I want to associate with a relay node
                if node.type != -1: continue  # Only unassigned nodes

                rec_powers = []
                rec_ids = []

                for r_node in self.nodes:
                    if (r_node.type != level - 1): continue  # Only level - 1 nodes

                    # print("IN")

                    distance = distance_nodes(node, r_node)
                    # print(distance)
                    rec_power = calculate_received_power(distance, node.transmission_power)

                    if calculate_snr(rec_power, - (109 + 2.5)) >= snr_limit(node.sf) + 10:  # rec_power >= -109:
                        count_new_entries += 1  # To stop when we have no other nodes
                        rec_powers.append(rec_power)
                        rec_ids.append(r_node.id)
                        node.type = level
                        node.state = "Listen"

                if len(rec_powers) > 0:
                    node_and_types[level].append(
                        {"node": node, "rec_power": rec_powers,
                         "rec_id": rec_ids})  # same index - associate id - rec power

            if count_new_entries == 0:
                node_and_types.pop()
                break
            level += 1

        # It is minus one due to last increase
        level -= 1

        self.general_level = level

        # 3. Clustering algorithm preparation
        only_nodes = []
        for level_in_level in node_and_types:
            only_nodes.append([])
            for node in level_in_level:
                only_nodes[-1].append({"node": node["node"]})

        # 4. Build clusters
        for index_level in range(len(only_nodes) - 1):
            only_nodes[index_level + 1], only_nodes[index_level] = self.build_clusters(only_nodes[index_level + 1],
                                                                                       only_nodes[index_level])

        # 5. Define Following Nodes
        for index_level in range(len(only_nodes) - 1):
            for node_type1 in only_nodes[index_level]:
                nd1 = node_type1["node"]
                for node_type0 in only_nodes[index_level + 1]:
                    nd0 = node_type0["node"]

                    if nd1.id == nd0.assigned_node:
                        nd1.node_following = nd0.id
                        break

        # 6 See if a type 1 node has no assigned type 0 nodes make it type 0
        for node in self.nodes:  # Make them type 0
            if node.node_following is None:
                node.type = level
                node.protocol = Lorawan(None)
                node.state = "Sleep"
            else:
                node.protocol = Multihop()

        # Every node close to gw has assigned node -1
        for node in self.nodes:
            if node.type == 0:
                node.assigned_node = -1

        """for i in node_and_types:
            try:
                print(len(i))
                print()
            except:pass

        print(f"LEVEL {level}")"""

    def build_clusters(self, type0_nodes, type1_nodes):

        # print(type1_nodes)

        m = []

        # For every type 1 node
        for type1 in type1_nodes:
            node_1 = type1["node"]
            m.append([])
            for type0 in type0_nodes:
                node_0 = type0["node"]
                m[-1].append(calculate_received_power(distance_nodes(node_1,
                                                                     node_0), node_0.transmission_power))

        # c = len(m)
        # n = len(m[0])
        # opt = n/c

        def fm(i, p, m):
            return m[i].index(p)

        m_sorted = []

        for i in range(len(m)):
            m_i = m[i].copy()
            m_i.sort()
            m_sorted.append(m_i)
            m_sorted[-1] = [x for x in m_sorted[-1] if x > -109]

        f_m = []
        for i in range(len(m_sorted)):
            f_m.append([])
            for p in m_sorted[i]:
                f_m[-1].append(fm(i, p, m))

        max_priority = self.num_nodes
        already_assigned_nodes = []
        when_type_1_assigned_to_node_added = []

        def indices(mylist, value):
            return [i for i, x in enumerate(mylist) if x == value]

        for i in range(max_priority):
            priority_i = []
            for type1_list in f_m:
                try:
                    priority_i.append(type1_list[i])
                except:
                    priority_i.append(None)

            # print(priority_i)
            # Start Assigning type 0 to type 1
            type_0_to_be_assigned = list(set(priority_i))
            # print(type_0_to_be_assigned)
            # type_0_to_be_assigned = type_0_to_be_assigned.remove(None)
            # print(type_0_to_be_assigned)

            for element in type_0_to_be_assigned:
                if element in already_assigned_nodes or element is None:
                    continue
                if priority_i.count(element) == 1:
                    winner = priority_i.index(element)
                    type0_nodes[element]["node"].channel = type1_nodes[winner]["node"].channel
                    type0_nodes[element]["node"].assigned_node = type1_nodes[winner]["node"].id
                    already_assigned_nodes.append(element)
                    when_type_1_assigned_to_node_added.append(winner)
                else:
                    to_whch_types1 = indices(priority_i, element)
                    score = {}
                    for nd in to_whch_types1:
                        score[nd] = when_type_1_assigned_to_node_added.count(nd)
                    winner = min(score, key=score.get)
                    type0_nodes[element]["node"].channel = type1_nodes[winner]["node"].channel
                    type0_nodes[element]["node"].assigned_node = type1_nodes[winner]["node"].id
                    already_assigned_nodes.append(element)
                    when_type_1_assigned_to_node_added.append(winner)

        return type0_nodes, type1_nodes

    def plot_topology(self):

        def get_node_color(channel):
            # Define a dictionary to map channels to colors
            channel_colors = {
                "0": "red",
                "1": "blue",
                "2": "green",
                "3": "purple",
                "4": "orange",
                "5": "cyan",
                "6": "magenta",
                "7": "lime",
                "8": "pink",
            }

            # Default to black if channel not found
            return channel_colors.get(channel, "black")

        def plot_nodes_and_gateways(nodes, gateways):
            fig = plt.figure()
            ax = fig.add_subplot(projection='3d')
            ax.view_init(elev=90, azim=-90, roll=0)

            # Plot gateways
            for gateway in gateways:
                ax.scatter(gateway.x, gateway.y, gateway.height,
                           color='black', marker='^', s=100)

            # Plot nodes
            for node in nodes:
                ax.scatter(node.x, node.y, node.height,
                           color=get_node_color(node.channel))

            # Set labels
            ax.set_xlabel('X')
            ax.set_ylabel('Y')
            ax.set_zlabel('Z')

            plt.show()

        plot_nodes_and_gateways(self.nodes, self.gateways)


# top = Topology(50, 5)
# top.plot_topology()
# top.join_process()
import sys

if __name__ == "__main__":
    argument = sys.argv[1]
    i = float(argument)  # Convert the argument to a float
    time = sys.argv[2]
    num_nodes = int(sys.argv[4])
    protocol = sys.argv[3]
    num_of_gw = int(sys.argv[5])
    topology = Topology(num_nodes, num_of_gw, protocol == 'Multihop', 100000, i / 10, time)
    #opology = Topology(num_nodes, num_of_gw, protocol == 'Multihop', 100000, i*2+1, time)  # is nodes per level

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

    #topology.plot_topology()
