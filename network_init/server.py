# deduplication

class Server:

    def __init__(self) -> None:
        self.packets_received = set()
        self.aggregated_packet_received = 0

        self.packets_delay = dict()
        self.packets_payload = dict()

        self.packets_collided = set()


    def receive_from_gw(self, packet_id, packet):
        self.packets_received.add(packet_id)

        self.packets_delay[packet_id] = packet.timestamp_rec - packet.timestamp_gen

        # Has one aggregated packet
        if packet.payload_bytes > 15:
            self.packets_payload[packet_id] = packet.payload_bytes - 9
            self.aggregated_packet_received += 1
        else:
            self.packets_payload[packet_id] = packet.payload_bytes
        # print(packet.payload_bytes)

        # print(self.packets_delay)

    def num_of_packets(self):
        return len(self.packets_received) + self.aggregated_packet_received

    # Should be changed
    def sum_delay(self):
        return sum(self.packets_delay.values())

    def sum_payload(self):
        return sum(self.packets_payload.values())
