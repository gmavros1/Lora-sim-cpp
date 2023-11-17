import math
import random
import json


# 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
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
                          max(math.ceil((8 * payload_length - 4 * int(sf) + 28 + 16 *
                                         crc - 20 * header) / (4 * (int(sf) - 2 * de))) * (cr + 4), 0)
    # print(f"num of symbol {num_payload_symbols}")

    T_payload = Ts * num_payload_symbols

    T_preamble = (n_preamble + 4.25) * Ts
    # print(f"time of preamble {T_preamble}")

    return T_preamble + T_payload


# Function to calculate the received signal power at a given distance
# Call it from node receive
def calculate_received_power(distance, transmission_power, shadowing_std_dev=5.34):
    # Constants - sensors-22-03518-v3.pdf - reference
    PLd0 = 40.7  # Reference path loss at the reference distance (d0)
    d0 = 1.0  # Reference distance (1 meter)
    alpha = 2.85  # Path loss exponent - (2-4) - urban enviroments ~ 3

    # Calculate the path loss without shadowing
    PL = PLd0 + 10 * alpha * math.log10(distance / d0)

    # Generate a random value for shadowing
    shadowing = random.gauss(0, shadowing_std_dev)
    shadowing = shadowing_std_dev

    # Calculate the total path loss with shadowing
    PL += shadowing

    # Calculate the received signal power at the receiver
    # Pt = 10 ** (transmission_power / 10)  # Convert transmission power from dBm to Watts
    # Pr = Pt / (10 ** (PL / 10))

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


def debug_node(node, action=None):
    log_file = open("./logs.txt", "a")
    dictionary = {"Time": node.environment_time, "Node": node.id, "Type": node.type,
                  "state": node.state, "toa_remain": node.toa_remain,
                  "buffer_len": len(node.buffer), "Action": action, "is receving": node.current_receiving_packet}
    json_object = json.dumps(dictionary, indent=7)
    log_file.write(json_object)
    log_file.close()


def debug_gw(packet, protocol):
    log_file = open("./logs.txt", "a")
    dictionary = {"Time": protocol.environment_time, "Source": packet.src, "flag": packet.start_end_flag,
                  "sequence number": packet.seq_num, "Action": "Gw receive from node"}
    json_object = json.dumps(dictionary, indent=7)
    log_file.write(json_object)
    log_file.close()


# print(toa(15, 7))
# print(duty_cycle(toa(15, 7)))
# print(toa(15, 7)+duty_cycle(toa(15, 7)))
#print(calculate_received_power(12000, 14))
