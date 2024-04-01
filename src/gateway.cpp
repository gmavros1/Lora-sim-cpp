//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#include "gateway.h"
#include "environment.h"
#include "utils.h"
#include "../external/json/include/nlohmann/json.hpp"
#include <fstream>

// Set sensitivity of Lora -149 dBm
void Gateway::receive(vector<radio_packet> &packets_received) {

    // Packets within Range
    vector<radio_packet> current_packets;
    current_packets = packets_received;

    // Abort packet due to range issues
    for (int index = current_packets.size() - 1; index >= 0; index--) {
        double receive_power = calculate_received_power(distanceGatewayNode(this->location,
                                                                            current_packets[index].location),
                                                        current_packets[index].transmission_power);
        if (receive_power >= -130) {
            current_packets[index].receive_power = receive_power;
            // cout << "IN" << endl;
        } else {
            current_packets.erase(current_packets.begin() + index);
            // cout << "ABORT" << endl;
        }
    }


    // Add every segment of a packet + interference information n^2 complexity
    for (auto current_packet: current_packets) {
        string packet_id = current_packet.packet.getPacketId();

        // Find max interference signal;
        double max_itf = -1000;
        for (auto current_packet_cmp: current_packets) { // packet compared (cmp)
            if (current_packet.sf == current_packet_cmp.sf &&
                current_packet.channel == current_packet_cmp.channel &&
                packet_id != current_packet_cmp.packet.getPacketId()) {
                if (current_packet_cmp.receive_power > max_itf) {
                    max_itf = current_packet_cmp.receive_power;
                }
            }
        }

        // Build interference info per packet
        rec_powers r_powers{};
        r_powers.packet_rec_power = current_packet.receive_power;
        r_powers.maximum_interference_power = max_itf; // found above
        double snr = calculate_snr(r_powers.packet_rec_power, r_powers.maximum_interference_power);
        double snr_limit_value = snr_limit(current_packet.sf);
        r_powers.able_to_decode = snr > snr_limit_value + 10; // Margin 10

        // First segment of the packet
        if (receiving_buffer.find(packet_id) == receiving_buffer.end()) {

            // Build Packet receiving information
            packets_receiving current_packet_info{};
            current_packet_info.id = packet_id;
            current_packet_info.packet = current_packet.packet;
            current_packet_info.sf = current_packet.sf;
            current_packet_info.channel = current_packet.channel;
            current_packet_info.segments_received.push_back(r_powers);

            receiving_buffer.insert({packet_id, current_packet_info});
        } else { // Next received segments

            // Add receiving segment power information
            receiving_buffer[packet_id].segments_received.push_back({r_powers});

            // If it is the last segment
            //cout << packet_id << " " << current_packet.packet.getSeqNum() << endl;
            if (current_packet.packet.getSeqNum() == 0) {
                int num_of_sccs_decod_packets_req = receiving_buffer[packet_id].packet.getNumber0fSegments();
                int num_of_sccs_decod_packets = 0;
                for (auto &s: receiving_buffer[packet_id].segments_received) {
                    if (s.able_to_decode) {
                        num_of_sccs_decod_packets++;
                    }
                }
                if (num_of_sccs_decod_packets_req == num_of_sccs_decod_packets) {
                    // cout << "eq" << endl;
                    receiving_buffer[packet_id].decoded_or_not = "Decoded";
                } else {
                    receiving_buffer[packet_id].decoded_or_not = "Non_decoded";
                }

            }

        }
    }

    // Remove decoded packets
    for (auto it = receiving_buffer.begin(); it != receiving_buffer.end();) {
        if (it->second.decoded_or_not == "Decoded") {
            //cout << "DEC" << endl;
            if (it->second.packet.aggregated_packet != nullptr){
                string agg_packet = it->second.packet.aggregated_packet->getPacketId();
                decoded_packets_statistics.push_back(agg_packet);
            }
            //cout << "Gateway received from " << it->second.packet.getSrc() <<  endl;
            decoded_packets_statistics.push_back(it->first);
            it = receiving_buffer.erase(it); // Remove the item


        } else if (it->second.decoded_or_not == "Non_decoded") {
            non_decoded_packets_statistics.push_back(it->first);
            it = receiving_buffer.erase(it);
        } else {
            ++it; // Move to the next item
        }
    }


}

void Gateway::clock(int time) {
    this->environment_time = time;
}

Gateway::Gateway(int id, int x, int y, int z) {
    this->id = id;
    this->location.x = x;
    this->location.y = y;
    this->location.z = z;
}

coordinates_gw Gateway::getLocation() {
    return this->location;
}


