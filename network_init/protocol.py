from functions import *
from packet import Packet


class Lorawan:

    def __init__(self, server) -> None:
        self.current_receiving_packets = dict()
        self.server = server
        self.environment_time = 0

    # At first, without capture effect
    def receive_gateway(self, received_packets):

        for packet in received_packets:

            # debug_gw(packet["packet"], self)

            packets_node_index = packet["packet"].packetId
            if packets_node_index not in self.current_receiving_packets:
                self.current_receiving_packets[packets_node_index] = []

            if packet["packet"].start_end_flag == "END":  # Last packet
                packet["packet"].timestamp_rec = self.environment_time
                self.current_receiving_packets[packets_node_index].append(packet["packet"])
                if self.all_fragments_received(self.current_receiving_packets[packets_node_index]):
                    self.server.receive_from_gw(packet["packet"].packetId, packet["packet"])  # Server for statistic
                    self.current_receiving_packets.pop(packets_node_index)  # Remove from gw
                    src = packet["packet"].src
                    # print(f"TIME: {self.environment_time} | Packet received from {src} to Gateway")
            else:
                self.current_receiving_packets[packets_node_index].append(packet["packet"])

    def all_fragments_received(self, packets):
        # debug_gw("\n")
        # print(str(packets[-1].seq_num))
        # debug_gw("\n")
        # print(str(len(packets)))
        if packets[-1].seq_num == len(packets) - 1:
            # debug_gw(packets[-1], self)
            return True
        else:
            # print("*** DECODING ERROR IN GATEWAY")
            return False

    def states_change_node(self, node):
        if len(node.buffer) == 1:
            node.state = "Transmit"
            return

        if node.current_transmiting_packet is None:
            node.state = "Sleep"
            return

    def tick_nodes(self, time):
        self.environment_time = time


class Multihop:

    def __init__(self) -> None:
        self.current_receiving_packets = dict()
        self.environment_time = 0

    def receive_node(self, received_packets, node):

        for packet in received_packets:

            packets_node_index = packet["packet"].packetId
            if packets_node_index not in self.current_receiving_packets:
                self.current_receiving_packets[packets_node_index] = []

            if packet["packet"].start_end_flag == "END":  # Last packet
                packet["packet"].timestamp_rec = self.environment_time
                self.current_receiving_packets[packets_node_index].append(packet["packet"])
                if self.all_fragments_received(self.current_receiving_packets[packets_node_index]):
                    if packet["packet"].dst == node.id:  # TO AVOID COLLISION IN GW
                        src = packet["packet"].src
                        dst = packet["packet"].dst
                        # node = packet["node"]
                        # print(f"TIME: {self.environment_time} | Packet received from {src} to {dst}")
                        # print(f"packets in buffer {len(node.buffer)}")
                        # CHANGE HEADER FOR TRANS FROM NODE TO GW
                        packet["packet"].seq_num = -1
                        packet["packet"].start_end_flag = "START"
                        packet["packet"].dst = None

                        # The payload after the aggrefgation will be payload + payload + 9 bytes (header and crc)
                        # Apply that if received packet from the node following
                        if node.node_following == src:
                            packet["packet"].payload_bytes += packet["packet"].payload_bytes + 9

                        node.buffer.append(packet["packet"])  # Store for multihop

                    else:
                        src = packet["packet"].src
                        # print(f"DROPED from {src} to {node.id}")
                    # node.state = "Sleep"
                    # print(self.environment_time)
                    # print(f"node {node.id}")
                    # print("Received in node")
                    # print(f"payload {len(node.buffer)}")
            else:
                self.current_receiving_packets[packets_node_index].append(packet["packet"])

    # When node goes to sleep or transmit, empty the current_receiving_packets dict
    # Seq number is encreasing from the environment
    def all_fragments_received(self, packets):
        if packets[-1].seq_num == len(packets) - 1:
            return True
        else:
            # print(f"--- DECODING ERROR IN NODE {packets[-1].src}")
            return False

    def aggregation(self, node):
        payload_sum = 0
        time_gen = 0
        for p in node.buffer:
            payload_sum += p.payload_bytes
            time_gen = p.timestamp_gen

        agg_packet = Packet(node.id, time_gen, payload_sum, "data", None)
        node.buffer = []
        node.buffer.append(agg_packet)

    def states_change_node(self, node):

        # if node.state == "Sleep" and random.random() < 0.1:
        #    node.state = "Listen"
        #    return

        # trans packet returning to None from enviroment and to packet from environment
        if len(node.buffer) == 1 and node.current_transmiting_packet != None:
            node.state = "Transmit"
            return

        if node.current_receiving_packet != None and node.current_transmiting_packet == None:
            node.state = "Receive"
            return

        if node.current_receiving_packet == None and node.current_transmiting_packet == None:
            node.state = "Listen"
            return

        # if node.current_transmiting_packet == None:
        #    node.state = "Sleep"
        #    return
        return

    def tick_nodes(self, time):
        self.environment_time = time
