from packet import Packet
from protocol import Lorawan
import random
from functions import *


class Gateway:

    def __init__(self, id, position, server) -> None:
        self.server = server
        self.id = id  # Could replace mac address
        self.x = position[0]
        self.y = position[1]
        self.height = position[2]
        self.sf = 7  # By default on our approach ?
        self.transmission_power = 25  # dB - default in our approach

        self.protocol = Lorawan(server)
        self.environment_time = 0

        self.buffer = []

    def tick(self, time):
        self.environment_time = time
        self.protocol.environment_time = time

    # Only control packets are generated
    # A list with control packet should be defined
    def generate_packet(self, time, type, dst) -> None:
        # payload = random.randint(1, 125) # It will be changed according to the control packet
        # generated_packet = Packet(self.id, time, payload, dst, type)

        generated_packet = self.protocol.gen_packets_for_gw(
            time)  # Should be implemented

        self.buffer.append(generated_packet)

    # Transmit the control Packet
    def transmit_packet(self):
        return self.buffer.pop(0)

    # received_signal power is a list. Index connected to pakcets index (each element)

    def receive_packets(self, enviroment_channel, enviroment_sf):

        

        received_packets = []
        possible_conflicts = []

        for _, channel in enviroment_channel.items():
            for _, sf in enviroment_sf.items():
                set1 = {tuple(sorted(d.items())) for d in channel}
                set2 = {tuple(sorted(d.items())) for d in sf}
                intersection_set = set1 & set2
                pakets_in_receiver = [dict(item) for item in intersection_set]
                possible_conflicts.append(pakets_in_receiver)

        for pakets_in_receiver in possible_conflicts:
            for i in pakets_in_receiver:
                i["rec_power"] = calculate_received_power(
                    distance_nodes(i["node"], self), i["transmission_power"])

            # All the packets in the loop have the same sf - Lets take the first
            
            if len(pakets_in_receiver) == 0:
                continue

            #print(enviroment_channel)

            snrLimit = snr_limit(int(pakets_in_receiver[0]["node"].sf))
            
            # Collect all the powers of different nodes.
            rec_power_list = [{"src": packet["packet"].src, "rec_power": packet["rec_power"]} for packet in pakets_in_receiver]
            rec_power_list.sort(key=lambda x: x["rec_power"], reverse=True)
            noise = rec_power_list[:2]

            for packet in pakets_in_receiver:

                # See if it can be decoded
                # Compute snr for the recived packet
                if len(noise) == 1: # In this case we dont have snr - no noise for other signals
                    if packet["rec_power"] < -137:
                        continue
                else: # In this case we have signals inteference
                    snr = 1
                    # Define snr for that packet
                    if packet["packet"].src == noise[0]["src"]:
                        snr = calculate_snr(packet["rec_power"], noise[1]["rec_power"])    
                    else:
                        snr = calculate_snr(packet["rec_power"], noise[0]["rec_power"])

                    # See if the segment can be decoded
                    if snr < snrLimit + 10 or packet["rec_power"] < -137:
                        continue

                    else:
                        pass

                #print("REceived segment in GW from ", packet["packet"].src)

                # The next segment is the last (ignored)
                if packet["remaining_time"] < 2:
                    packet["packet"].timestamp_rec = self.environment_time
                    packet["packet"].start_end_flag = "END"

                received_packets.append(packet)

        self.protocol.receive_gateway(received_packets)

        """# aggregation
        pairs = []  # For every pair channel - sf
        for key_ch, value_ch in enviroment_channel.items():
            for key_sf, value_sf in enviroment_sf.items():
                pair = {"channel": key_ch,
                        "spreading_factor": key_sf, "packets": []}

                for item1 in value_ch:
                    for item2 in value_sf:
                        if item1["node"] == item2["node"]:  # and \
                            # item1["packet"] == item2["packet"] and \
                            # item1["remaining_time"] == item2["remaining_time"] and \
                            # item1["transmission_power"] == item2["transmission_power"]:

                            # Define rec time before receive the packet in last ms
                            if item1["remaining_time"] < 1:
                                item1["packet"].timestamp_rec = self.environment_time

                            # if item1["node"].type == 1: # FOR MULTIHOP

                            pair["packets"].append({"node": item1["node"],
                                                    "packet": item1["packet"],
                                                    "remaining_time": item1["remaining_time"],
                                                    "rec_power": calculate_received_power(distance_nodes(item1["node"], self),
                                                                                          item1["transmission_power"])})

                pairs.append(pair)

        packets = pairs  # Groupping of segment of packets of the same channel and sf
        # if str(self.id) == "Gateway3":
        #    print(f"Time: {self.environment_time}")
        #    print(f"Gateway:{self.id}")
        #    print(packets)
        self.protocol.receive_gateway(packets)"""
