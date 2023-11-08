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

    def __init__(self, num_nodes, num_gateways, use_multihop, rangekm, rate) -> None:

        self.server = Server()
        self.metrics = Metrics()
        self.num_nodes = num_nodes

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
            gateway_x_range = (rangekm / 2 - 5000, rangekm / 2 + 5000)
            # Range of y-coordinates for gateways
            gateway_y_range = (rangekm / 2 - 5000, rangekm / 2 + 5000)
        else:
            # Range of x-coordinates for gateways
            gateway_x_range = (rangekm / 2 - 100, rangekm / 2 + 100)
            # Range of y-coordinates for gateways
            gateway_y_range = (rangekm / 2 - 100, rangekm / 2 + 100)
        node_height_range = (100, 150)
        gateway_height_range = (40, 50)
        center_x = rangekm / 2  # Example center x-coordinate
        center_y = rangekm / 2  # Example center y-coordinate

        # For type 0 nodes
        min_distance = 20000  # Example minimum distance in meters
        max_distance = 30000  # Example maximum distance in meters

        ratio_for_type_1 = 0.8
        #ratio_for_type_0 = 1 - ratio_for_type_1

        # Create nodes and assign positions
        nodes = {}
        for i in range(int(num_nodes * ratio_for_type_1)):
            node_id = i
            node_x, node_y = generate_random_coordinates(
                center_x, center_y, min_distance, max_distance)
            node_height = random.uniform(*node_height_range)
            nodes[node_id] = (node_x, node_y, node_height)

        # For type 1 nodes
        min_distance = 10000  # Example minimum distance in meters
        max_distance = 20000  # Example maximum distance in meters

        for i in range(int(num_nodes * ratio_for_type_1), num_nodes):
            node_id = i
            node_x, node_y = generate_random_coordinates(
                center_x, center_y, min_distance, max_distance)
            node_height = random.uniform(*node_height_range)
            nodes[node_id] = (node_x, node_y, node_height)

        # Create gateways and assign positions
        gateways = {}
        for i in range(num_gateways):
            gateway_id = i + 1
            gateway_x = random.uniform(*gateway_x_range)
            gateway_y = random.uniform(*gateway_y_range)
            gateway_height = random.uniform(*gateway_height_range)
            gateways[gateway_id] = (gateway_x, gateway_y, gateway_height)

        self.nodes = []
        for node_id, position in nodes.items():
            self.nodes.append(Node(node_id, position, self.metrics))

        self.gateways = []
        for gateway_id, position in gateways.items():
            self.gateways.append(Gateway(gateway_id, position, self.server))

        if use_multihop:
            self.multihop_join_process()
            # Plot topology
            print("MULTIHOP")
        else:
            self.join_process()
            # Plot topology
            print("LORAWAN ", num_gateways, "GWs")

        # ******************** # Writing to a json file
        nodes = []
        for n in self.nodes:
            def null_to_minus_1(value):
                if value is None:
                    return -1
                else:
                    return value

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

        topologggy = {"nodes": nodes, "gateways": gateways, "rate": rate}

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
        pass

        ### TO ENABLE MULTIHOP ###

    def multihop_join_process(self):

        type_1_nodes = []
        type_0_nodes = []

        # 1. Collect type 1 nodes (and type 0)
        for node in self.nodes:
            # For each node select the min distance form gw
            distance_to_gw = []
            for gw in self.gateways:
                distance_to_gw.append(distance_nodes(node, gw))
            min_distance = min(distance_to_gw)  # For this distance define SF
            # print(min_distance)

            rec_power = calculate_received_power(
                min_distance, node.transmission_power)

            print(rec_power)
            if rec_power <= -149:
                node.type = 0
                type_0_nodes.append({"node": node, "rec_power": rec_power})
            else:
                node.state = "Listen"
                node.type = 1  # middle node
                node.protocol = Multihop()
                type_1_nodes.append({"node": node, "rec_power": rec_power})

        # 2. Assign channels to first 9 type 1 nodes
        for i in range(9):
            try:
                type_1_nodes[i]["node"].channel = str(i)
            except:
                break  # less than 9 type 1 nodes

        # 3. Assing channel to remaining type 1 nodes if exist
        # Try to find channel-node pairs with max rec power diff (when gw receiving)
        available_channels = ["0", "1", "2", "3", "4", "5", "6", "7", "8"]
        if len(type_1_nodes) > 9:
            for i in range(9, len(type_1_nodes)):  # remaining nodes
                if len(available_channels) == 0:
                    available_channels = ["0", "1", "2",
                                          "3", "4", "5", "6", "7", "8"]
                max_diff = 0
                for j in range(9):
                    diff = abs(
                        type_1_nodes[i]["rec_power"] - type_1_nodes[j]["rec_power"])
                    if diff > max_diff and type_1_nodes[j]["node"].channel in available_channels:
                        max_diff = diff
                        type_1_nodes[i]["node"].channel = type_1_nodes[j]["node"].channel
                available_channels.remove(type_1_nodes[i]["node"].channel)


        ##### HERE TRY THE BALANCED CLUSTER METHOD AND DISCARD THE ABOVE ######
        type_0_nodes, type_1_nodes = self.build_clusters(type_0_nodes, type_1_nodes)

        # 5. Define Following Nodes
        for node_type1 in type_1_nodes:
            nd1 = node_type1["node"]
            for node_type0 in type_0_nodes:
                nd0 = node_type0["node"]

                if nd1.id == nd0.assigned_node:
                    nd1.node_following = nd0.id
                    break

        # 6 See if a type 1 node has no assigned type 0 nodes make it type 0
        for node in self.nodes:  # Make them type 0
            if node.node_following is None:
                node.type = 0
                node.protocol = Lorawan(None)
                node.state = "Sleep"



    def build_clusters(self, type0_nodes, type1_nodes):
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
            m_sorted[-1] = [x for x in m_sorted[-1] if x > -137]

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
            ax.view_init(elev=70, azim=-90, roll=0)

            # Plot nodes
            for node in nodes:
                ax.scatter(node.x, node.y, node.height,
                           color=get_node_color(node.channel))

            # Plot gateways
            for gateway in gateways:
                ax.scatter(gateway.x, gateway.y, gateway.height,
                           color='black', marker='^', s=100)

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
    topology = Topology(100, 1, False, 100000, i/10)

