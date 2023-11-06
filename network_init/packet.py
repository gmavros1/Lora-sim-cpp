import hashlib

class Packet:
    
    # if dst none, for any gw which may hear
    def __init__(self, src, timestamp, payload_bytes, payload, dst, crc=1, header=0) -> None:
        self.dst = dst
        self.src = src
        self.timestamp_gen = timestamp
        self.timestamp_rec = None
        self.payload_bytes = payload_bytes # Will be used in ToA calculation!
        self.data = payload
        self.crc = crc
        self.header = header
        inputHah = f"{timestamp}{src}"
        self.packetId = hashlib.md5(inputHah.encode())
        self.seq_num = 0          # To check if all packets are arrived
        self.start_end_flag = "START"   # The first received fragmend and the last