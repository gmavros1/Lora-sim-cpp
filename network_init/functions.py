import json
import math
import random
import matplotlib.pyplot as plt
import numpy as np


def distance_nodes(node1, node2):
    x1, y1, z1 = node1.x, node1.y, node1.height
    x2, y2, z2 = node2.x, node2.y, node2.height

    distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2 + (z2 - z1) ** 2)
    return distance


# bw 125 or 256 | coding rate (cr) = {1,2,3,4}
def toa(payload_length, sf, crc=1, header=0, de=0, n_preamble=8, bw=125, cr=1):
    # The LowDataRateOptimize is enabled fo bandwidth 125 kHz and Spreading Factor >= 11
    if bw == 125 and int(sf) >= 11:
        de = 1

    # Time of symbol (ms)
    Ts = (2 ** int(sf)) / bw
    # print(f"time of symbol {Ts}")

    # Time of payload - include header crc and low data range optimization
    num_payload_symbols = 8 + \
                          max(math.ceil((8.0 * payload_length - 4.0 * int(sf) + 28.0 + 16.0 *
                                         crc - 20.0 * header) / (4.0 * (int(sf) - 2.0 * de))) * (cr + 4), 0)
    # print(f"num of symbol {num_payload_symbols}")
    print(num_payload_symbols)
    T_payload = Ts * num_payload_symbols

    T_preamble = (n_preamble + 4.25) * Ts
    # print(f"time of preamble {T_preamble}")

    return T_preamble + T_payload


# Function to calculate the received signal power at a given distance
# Call it from node receive
def calculate_received_power(distance, transmission_power, shadowing_std_dev=6.0):
    # Constants - sensors-22-03518-v3.pdf - reference
    PLd0 = 37  # Reference path loss at the reference distance (d0)
    d0 = 1.0  # Reference distance (1 meter)
    alpha = 3.0  # Path loss exponent - (2-4) - urban enviroments ~ 3

    # Calculate the path loss without shadowing
    PL = PLd0 + 10 * alpha * math.log10(distance / d0)

    # Generate a random value for shadowing
    shadowing = shadowing_std_dev

    # Calculate the total path loss with shadowing
    PL += shadowing

    # Receive power returned in dB
    Pr = transmission_power - PL

    return Pr


# Function to calculate SNR from received signal power and noise power


def calculate_snr(signal_power, signal_noise):
    # noise_power = random.uniform(10.0, 15.0)  # Random noise power in db
    noise_power = signal_noise
    snr = signal_power - noise_power
    return snr


# Data Rate = (4 * SF) / (2^(SF/CR)) * (BW / 2^SF)


def data_rate(sf, cr, bw):
    return sf * ((4 / (4 + cr)) / (2 ** sf / bw))


# example
# print(data_rate(7, 1, 125))

# SNRlimit according to spreading factor


def snr_limit(sf):
    extra = sf - 7
    return -(7.5 + 2.5 * extra)


# example - inpu:sf
# print(snr_limit(12))

# ADR in server


def adr(last_packets, sf):
    snrLimit = snr_limit(sf)
    snr_measured = max(last_packets)
    margin_default = 10  # dB

    if snr_measured > snrLimit + margin_default:
        if sf > 7:
            return sf - 1
        else:
            return sf
    else:
        if sf < 12:
            return sf + 1
        else:
            return sf


def duty_cycle(toa):
    dutyCycle = 0.01  # 1%

    t_interval = (toa / dutyCycle) - toa

    return t_interval  # ms have to wait until the next transmission


# Make topology - place nodes
def generate_nodes(center, num_nodes, start_radius, level):
    nodes = []
    angle_increment = 2 * math.pi / num_nodes

    for l in range(int(level)):
        for i in range(num_nodes):
            angle = i * angle_increment

            x = center[0] + (start_radius + 600 * l) * math.cos(angle)
            y = center[1] + (start_radius + 600 * l) * math.sin(angle)
            nodes.append((x, y))

    return nodes


def generate_random_coordinates(center_x, center_y, min_distance, max_distance):
    # Generate a random Euclidean distance within the specified range
    euclidean_distance = np.random.uniform(min_distance, max_distance)

    # Generate a random angle (theta) between 0 and 2*pi
    theta = np.random.uniform(0, 2 * np.pi)

    # Calculate x and y coordinates using polar coordinates
    x = center_x + euclidean_distance * np.cos(theta)
    y = center_y + euclidean_distance * np.sin(theta)

    return x, y


def generate_random_coordinates_range(center_x, center_y, min_distance, max_distance, angle):
    # Generate a random Euclidean distance within the specified range
    euclidean_distance = np.random.uniform(min_distance, max_distance)

    # Generate a random angle (theta) between 0 and 2*pi
    # theta = np.random.uniform(0, 2 * np.pi)
    theta = angle

    # Calculate x and y coordinates using polar coordinates
    x = center_x + euclidean_distance * np.cos(theta)
    y = center_y + euclidean_distance * np.sin(theta)

    return x, y


def distance_from_center(i, center):
    return np.sqrt((i[0] - center[0]) ** 2 + (i[1] - center[1]) ** 2)


def place_out_node(center, pointi):
    """if max_distance >= max_radius:
        return"""

    # Vector
    vector = (pointi[0] - center[0], pointi[1], center[1])
    # Angle
    try:
        theta = np.arctan2(vector[1], vector[0])
    except:
        theta = np.arctan2(vector[1])

    # Random distance
    r_distance = np.random.uniform(400, 600)
    down_limit = theta - (np.pi) / 3
    upper_limit = theta + (np.pi) / 3
    r_angle = np.random.uniform(down_limit, upper_limit)

    pointj = (pointi[0] + r_distance * np.cos(r_angle), pointi[1] + r_distance * np.sin(r_angle))

    return pointj


def place_out_node_range(center, pointi):
    """if max_distance >= max_radius:
        return"""

    # Vector
    vector = (pointi[0] - center[0], pointi[1], center[1])
    # Angle
    try:
        theta = np.arctan2(vector[1], vector[0])
    except:
        theta = np.arctan2(vector[1])

    # Random distance
    r_distance = np.random.uniform(400, 600)
    down_limit = theta - (np.pi) / 5
    upper_limit = theta + (np.pi) / 5
    r_angle = np.random.uniform(down_limit, upper_limit)

    pointj = (pointi[0] + r_distance * np.cos(r_angle), pointi[1] + r_distance * np.sin(r_angle))

    return pointj


# Percentage of in-range nodes # Topology stuff
# def generate_nodes_random(center, num_nodes, start_radius):
#     nodes = []
#     max_node_distance = 0
#
#     in_range = 15 #  int(0.3 * num_nodes)
#     out_of_range = num_nodes - in_range
#
#     # Place nodes in range
#     in_nodes = []
#     for i in range(in_range):
#         node_x, node_y = generate_random_coordinates(center[0], center[1], 2000, start_radius)
#         in_nodes.append((node_x, node_y))
#
#     # Find relay nodes
#     relay_nodes = []
#     for i in in_nodes:
#         distance_temp = distance_from_center(i, center)
#         if distance_temp >= 2000:
#             relay_nodes.append(i)
#
#     for _ in range(out_of_range):
#         random_r_node = random.randint(0, len(relay_nodes) - 1)
#         relay_node_temp = relay_nodes[random_r_node]
#         new_node = place_out_node(center, relay_node_temp)
#
#         # Define range of network
#         max_node_distance += distance_from_center(new_node, center)
#
#         nodes.append(new_node)
#         relay_nodes.append(new_node)
#
#         if np.random.uniform(0, 1) < 0.9:
#             relay_nodes.pop(random_r_node)
#
#     # Add inside nodes
#     nodes += in_nodes
#
#     return nodes, (max_node_distance / num_nodes)


def generate_nodes_random_more_range(center, num_nodes, start_radius):
    nodes = []
    max_node_distance = 0

    in_range =  10 # int(0.2 * num_nodes)
    out_of_range = num_nodes - in_range

    # Place nodes in range
    in_nodes = []
    for i in range(in_range):
        angle = ((2 * np.pi) / in_range) * i
        node_x, node_y = generate_random_coordinates_range(center[0], center[1], 2000, start_radius, angle)
        in_nodes.append((node_x, node_y))

    # Find relay nodes
    relay_nodes = []
    for i in in_nodes:
        distance_temp = distance_from_center(i, center)
        if distance_temp >= 2000:
            relay_nodes.append(i)

    # hits = {k: 0 for k in range(num_nodes)}
    # print(hits)

    for _ in range((out_of_range*2)//(3*3)):
        # random_r_node = random.randint(0, len(relay_nodes) - 1)
        # relay_node_temp = relay_nodes[random_r_node]
        relay_node_temp = min(relay_nodes, key=lambda rn: distance_from_center(rn, center))
        new_node = place_out_node_range(center, relay_node_temp)

        # Define range of network
        max_node_distance += distance_from_center(new_node, center)

        nodes.append(new_node)
        relay_nodes.append(new_node)

        #if np.random.uniform(0, 1) < 0.9:
        relay_nodes.pop(relay_nodes.index(relay_node_temp))

    relay_nodes = nodes + in_nodes
    for _ in range((out_of_range*3)//(3*3)):
        random_r_node = random.randint(0, len(relay_nodes) - 1)
        relay_node_temp = relay_nodes[random_r_node]
        # relay_node_temp = min(relay_nodes, key=lambda rn: distance_from_center(rn, center))
        new_node = place_out_node_range(center, relay_node_temp)

        # Define range of network
        max_node_distance += distance_from_center(new_node, center)

        nodes.append(new_node)
        relay_nodes.append(new_node)

        #if np.random.uniform(0, 1) < 0.9:
        relay_nodes.pop(relay_nodes.index(relay_node_temp))


    relay_nodes = nodes + in_nodes
    for _ in range((out_of_range*4)//(3*3)):
        random_r_node = random.randint(0, len(relay_nodes) - 1)
        relay_node_temp = relay_nodes[random_r_node]
        # relay_node_temp = min(relay_nodes, key=lambda rn: distance_from_center(rn, center))
        new_node = place_out_node_range(center, relay_node_temp)

        # Define range of network
        max_node_distance += distance_from_center(new_node, center)

        nodes.append(new_node)
        relay_nodes.append(new_node)

        #if np.random.uniform(0, 1) < 0.9:
        relay_nodes.pop(relay_nodes.index(relay_node_temp))

    # Add inside nodes
    nodes += in_nodes
    print(len(nodes))

    return nodes, (max_node_distance / num_nodes)


def get_gw_coordinates(num_of_gw, which_gw, rangeKm):
    if num_of_gw == 1:
        return 0, 0  # At the center of the topology
    if num_of_gw == 2:
        if which_gw == 0:
            return rangeKm * np.cos(np.pi / 2), rangeKm * np.sin(np.pi / 2)
        else:
            return rangeKm * np.cos(3 * (np.pi / 2)), rangeKm * np.sin(3 * (np.pi / 2))
    if num_of_gw == 3:
        if which_gw == 0:
            return rangeKm * np.cos((2 * np.pi) / 8), rangeKm * np.sin((2 * np.pi) / 8)
        elif which_gw == 1:
            return rangeKm * np.cos(3 * ((2 * np.pi) / 8)), rangeKm * np.sin(3 * ((2 * np.pi) / 8))
        else:
            return rangeKm * np.cos(6 * ((2 * np.pi) / 8)), rangeKm * np.sin(6 * ((2 * np.pi) / 8))


# def plot_topology(self):
#     def get_node_color(channel):
#         # Define a dictionary to map channels to colors
#         channel_colors = {
#             "0": "red",
#             "1": "blue",
#             "2": "green",
#             "3": "purple",
#             "4": "orange",
#             "5": "cyan",
#             "6": "magenta",
#             "7": "lime",
#             "8": "pink",
#         }
#
#         # Default to black if channel not found
#         return channel_colors.get(channel, "black")
#
#     def plot_nodes_and_gateways(nodes, gateways):
#         fig = plt.figure()
#         ax = fig.add_subplot()
#         ax.set_aspect('equal', adjustable='box')
#
#         # Plot gateways
#         for gateway in gateways:
#             ax.scatter(gateway.x, gateway.y,
#                        color='black', marker='^', s=100)
#
#         # Plot nodes
#         for node in nodes:
#             ax.scatter(node.x, node.y,
#                        color=get_node_color(node.channel))
#
#         # Set labels
#         ax.set_xlabel('X')
#         ax.set_ylabel('Y')
#         plt.show()
#
#     plot_nodes_and_gateways(self.nodes, self.gateways)


# def plot_topology(self):
#     def get_node_color(channel):
#         # Define a dictionary to map channels to colors
#         channel_colors = {
#             "0": "red",
#             "1": "blue",
#             "2": "green",
#             "3": "purple",
#             "4": "orange",
#             "5": "cyan",
#             "6": "magenta",
#             "7": "lime",
#             "8": "pink",
#         }
#         # Default to black if channel not found
#         return channel_colors.get(channel, "black")
#
#     def plot_nodes_and_gateways(nodes, gateways):
#         fig = plt.figure()
#         ax = fig.add_subplot()
#         ax.set_aspect('equal', adjustable='box')
#
#         # Plot gateways
#         for gateway in gateways:
#             ax.scatter(gateway.x, gateway.y,
#                        color='black', marker='^', s=100)
#
#         # Plot nodes
#         for node in nodes:
#             ax.scatter(node.x, node.y,
#                        color=get_node_color(node.channel))
#
#         # Create a dictionary mapping from node id to node object
#         node_dict = {node.id: node for node in nodes}
#
#         # Draw edges between nodes and their assigned nodes
#         for node in nodes:
#             # Check if the node has a valid assigned_node id
#             if node.assigned_node != -1 and node.assigned_node in node_dict:
#                 assigned_node = node_dict[node.assigned_node]
#                 # Draw a line between the node and its assigned node
#                 ax.plot([node.x, assigned_node.x],
#                         [node.y, assigned_node.y],
#                         color='gray', linestyle='-', linewidth=1)
#
#         # Set labels
#         ax.set_xlabel('X')
#         ax.set_ylabel('Y')
#         plt.show()
#
#     plot_nodes_and_gateways(self.nodes, self.gateways)

def plot_topology(self):
    import matplotlib.pyplot as plt
    from collections import defaultdict

    def get_node_color(channel):
        # Define a dictionary to map channels to colors.
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
        # Default to black if channel not found.
        return channel_colors.get(channel, "black")

    # Predefined list of marker shapes. (This list will be cycled through if there are more types than markers.)
    marker_shapes = ['o', 's', 'D', '^', 'v', 'p', 'h', '8', 'x', '*', 'H']

    def get_marker_for_type(ntype):
        # Returns a marker shape based on the node type.
        # Uses modulo in case ntype >= len(marker_shapes).
        return marker_shapes[ntype % len(marker_shapes)]

    def get_marker_size(ntype):
        # Compute marker size such that nodes with a higher type appear larger.
        # Here we use a simple linear formula: base size plus an increment per type.
        base_size = 50
        size_increment = 10
        return base_size + size_increment * ntype

    def plot_nodes_and_gateways(nodes, gateways):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.set_aspect('equal', adjustable='box')

        # Plot gateways (using a fixed marker and color).
        for gateway in gateways:
            ax.scatter(gateway.x, gateway.y,
                       color='black', marker='^', s=100, label='Gateway')

        # Group nodes by their type.
        nodes_by_type = defaultdict(list)
        for node in nodes:
            nodes_by_type[node.type].append(node)

        # Plot nodes for each type.
        for ntype, nodelist in nodes_by_type.items():
            xs = [node.x for node in nodelist]
            ys = [node.y for node in nodelist]
            # Use the existing channel-to-color mapping for node colors.
            colors = [get_node_color(node.channel) for node in nodelist]
            marker = get_marker_for_type(ntype)
            size = get_marker_size(ntype)
            ax.scatter(xs, ys, color=colors, marker=marker, s=size, label=f"Type {ntype}")

        # Build a lookup dictionary for nodes by their id.
        node_dict = {node.id: node for node in nodes}
        # Draw edges between nodes and their assigned nodes (if assigned_node is not -1).
        for node in nodes:
            if node.assigned_node != -1 and node.assigned_node in node_dict:
                assigned_node = node_dict[node.assigned_node]
                ax.plot([node.x, assigned_node.x],
                        [node.y, assigned_node.y],
                        color='gray', linestyle='-', linewidth=1)

        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        # ax.legend()
        plt.show()

    plot_nodes_and_gateways(self.nodes, self.gateways)


def save_node_type_of_previous_topology(nodes):
    dict_n_t = {}
    for node in nodes:
        dict_n_t[node.id] = node.type

    json_object = json.dumps(dict_n_t, indent=4)
    with open("topology/node_type.json", "w") as outfile:
        outfile.write(json_object)


def save_node_sf_of_previous_topology(nodes):
    dict_n_sf = {}
    for node in nodes:
        dict_n_sf[node.id] = node.sf

    json_object = json.dumps(dict_n_sf, indent=4)
    with open("topology/node_sf.json", "w") as outfile:
        outfile.write(json_object)


# sf = 7
# distance = 600
# transmission_p = 15
# received_power = calculate_received_power(distance, transmission_p)
# print(received_power)
# print(calculate_snr(received_power, -(109.0+2.5)))
# print(calculate_snr(received_power, -(109.0+2.5)) - (snr_limit(sf) + 10))
