from packet import Packet
from protocol import Lorawan
from protocol import Multihop
from functions import *
import random
import json


class Node:

    # position --> list [x, y, z]
    def __init__(self, id, position, metrics) -> None:
        self.id = id  # Could replace mac address
        self.x = position[0]
        self.y = position[1]
        self.height = position[2]
        # self.sf = random.randint(7, 12) # By default on our approach ?
        self.sf = 7
        self.channel = str(int(id) % (8 + 1))  # 0 to 8
        self.bandwidth = 125  # Or 250
        self.transmission_power = 20  # 25 dB - default in our approach
        self.state = "Sleep"  # Sleep, Transmit, Listen, Receive (Idle Listening/Receiving)
        self.time_dc = 0
        self.environment_time = 0
        self.toa_remain = 0

        self.assigned_node = None
        self.node_following = None

        self.metrics = metrics

        self.protocol = Lorawan(None)

        self.buffer = []

        # GOING TO NULL AGAIN ONLY FROM ENVIRONMENT ************************
        self.current_transmiting_packet = None  # Null when a packet is not transmiting
        self.current_receiving_packet = None

        self.type = 0  # type 0 only send, type 1 closer to gw can receive

    def tick(self, time):
        if self.time_dc > 0:
            self.time_dc -= 1

        self.environment_time = time
        if self.toa_remain > 0:
            self.toa_remain -= 1

        # WHEN A PACKET ARRIVES FROM TYPE0 NODE. PACKET SHOULD BE SENT
        # if len(self.buffer) > 0:
        #    self.current_transmiting_packet = self.buffer[0]

        self.protocol.tick_nodes(time)
        self.protocol.states_change_node(self)
        # print(self.state)

        ##### DEBBUG ######
        # debug_node(self)
        ##### DEBBUG ######

    # If packet generated (comply with dc regulations) : return true
    def generate_data_packet(self, time, dst) -> None:

        # If type0 node, define dst
        dst = self.assigned_node

        if self.state != "Sleep":
            return

        # print("2")
        # Do not generate more than 1 packet 

        # payload_size = random.randint(1,125) # It may be constant
        payload_size = 15  # It may be constant
        payload = "data"
        generated_packet = Packet(self.id, time, payload_size, payload, dst)

        # Duty cycle does not apply in type 1 nodes
        if self.time_dc <= 1 or self.type == 1:
            self.buffer.append(generated_packet)
            self.current_transmiting_packet = self.buffer[0]
            ##### DEBBUG ######
            # print("Generating Packet")
            # debug_node(self, "generate_packet")
            ##### DEBBUG ######
            self.metrics.add_transmission()  ## Metric COUNT TRANSMISSION
            return True

        return False

    # If not type=data, then is a crontrol packet
    # Block other transmission during current transmission or duty cycle regulations
    def transmit_packet(self):
        # may time relevant processes will be added

        if self.state != "Transmit":
            return None

        transmitted_pacet = None
        toa_time = None
        if len(self.buffer) != 0:
            transmitted_pacet = self.buffer.pop(0)
            toa_time = toa(transmitted_pacet.payload_bytes, self.sf)
            self.toa_remain = toa_time
            self.metrics.add_toa(toa_time)
            self.time_dc = duty_cycle(toa_time)
            # Add transmission in generation packet

            ##### DEBBUG ######
            # debug_node(self, "transmit_packet")
            ##### DEBBUG ######

        # try:
        #    print(f"TIME: {self.environment_time} | Packet transmited from {transmitted_pacet.src} to {transmitted_pacet.dst}")
        # except:
        #    pass
        return transmitted_pacet

        # Apply duty cycle

    # packets is a list
    # received_signal power is a list. Index connected to pakcets index (each element)
    def receive_packets(self, enviroment_channel, enviroment_sf):

        if not (self.state == "Listen" or self.state == "Receive"):
            return

        # print(enviroment_channel)

        received_packets = []  # The packets - signal power reiceive of the same sf and channel of the

        # Find the inresection
        packets_in_same_channel = enviroment_channel[self.channel]
        packets_in_same_sf = enviroment_sf[str(self.sf)]
        set1 = {tuple(sorted(d.items())) for d in packets_in_same_channel}
        set2 = {tuple(sorted(d.items())) for d in packets_in_same_sf}
        intersection_set = set1 & set2
        pakets_in_receiver = [dict(item) for item in intersection_set]

        # Compute rec power
        # print(f"COMPUTE FOR NODE {self.id} | state {self.state}")
        for i in pakets_in_receiver:
            if i["node"] == self:
                print(self.state)
            i["rec_power"] = calculate_received_power(distance_nodes(i["node"], self), i["transmission_power"])

        # if len(pakets_in_receiver)>1:
        #    print(enviroment_channel)
        #    print(enviroment_sf)

        # SNR limit
        snrLimit = snr_limit(int(self.sf))

        # Define  noise in channel
        rec_power_list = [{"src": packet["packet"].src, "rec_power": packet["rec_power"]} for packet in
                          pakets_in_receiver]
        rec_power_list.sort(key=lambda x: x["rec_power"], reverse=True)
        noise = rec_power_list[:2]

        for packet in pakets_in_receiver:

            ##### DEBBUG ######
            # debug_node(self, "receive_packet")
            ##### DEBBUG ######

            # See if it can be decoded
            # Compute snr for the recived packet
            if len(noise) == 1:  # In this case we dont have snr - no noise for other signals
                if packet["rec_power"] < -137:
                    # print("OUT OF RANGE")
                    continue
            else:  # In this case we have signals interference
                snr = 1
                # Define snr for that packet
                if packet["packet"].src == noise[0]["src"]:
                    snr = calculate_snr(packet["rec_power"], noise[1]["rec_power"])
                else:
                    snr = calculate_snr(packet["rec_power"], noise[0]["rec_power"])

                # See if the segment can be decoded
                if snr < snrLimit + 10 or packet["rec_power"] < -137:
                    # ADD METRIC FOR PACKET COLLISION IN NODES
                    self.metrics.add_node_collision()
                    continue
                else:
                    pass

            """snr = 0
            if packet["rec_power"] == noise[0] and len(noise) > 1 :
                snr = calculate_snr(packet["rec_power"], noise[1])
            else:
                snr = calculate_snr(packet["rec_power"], noise[0])
            # Decoding check
            if snr < snrLimit + 10 and packet["rec_power"] < -137:
                continue
            else:
                #print(self.environment_time)
                #print(packet["rec_power"])
                pass"""

            # Last segment ignored
            if packet["remaining_time"] < 2:
                packet["packet"].timestamp_rec = self.environment_time
                packet["packet"].start_end_flag = "END"
                self.current_receiving_packet = None
            else:
                self.current_receiving_packet = 1

            received_packets.append(packet)

        self.protocol.receive_node(received_packets, self)

    # Set to Transmit when method transmit is called
    # Set to Sleep after the pass of the last ms in remaining time (from enviroement)
    # Set to Listen in protocol algorithm
    def set_state(self, state):
        self.state = state
