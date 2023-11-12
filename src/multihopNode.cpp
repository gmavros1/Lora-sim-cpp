//
// Created by gmavros-yoga-7 on 10/11/2023.
//

#include "multihopNode.h"


// Set sensitivity of Lora -149 dBm
void MultihopNode::receive_node(vector<radio_packet> &packets_received) {

    // Packets within Range
    vector<radio_packet> current_packets;
    current_packets = packets_received;


    // Abort packet due to RANGE issues And different CHANNEL (receiver in one channel)
    for (int index = current_packets.size() - 1; index >= 0; index--) {
        double receive_power = calculate_received_power(distanceNodes(this->location,
                                                                            current_packets[index].location),
                                                        current_packets[index].transmission_power);
        if ((receive_power >= -149) & (current_packets[index].channel == this->channel)) {
            current_packets[index].receive_power = receive_power;
        } else {
            current_packets.erase(current_packets.begin() + index);
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
                    receiving_buffer[packet_id].decoded_or_not = "Decoded";
                } else {
                    receiving_buffer[packet_id].decoded_or_not = "Non_decoded";
                }

            }

        }
    }

    // Remove first decoded, drop others
    bool a_packet_has_decoded = false;
    for (auto it = receiving_buffer.begin(); it != receiving_buffer.end();) {
        if (it->second.decoded_or_not == "Decoded") {
            if (!a_packet_has_decoded){
                // Packet from reguler Node
                // Just forward
                if (it->second.packet.getSrc() != this->following) {
                    Packet temp_pack = it->second.packet;
                    this->buffer = new Packet(temp_pack.getSrc(), -1,
                                              temp_pack.getTimestamp_start()); // pass the arguments
                    a_packet_has_decoded = true;
                }
                // Packet from Follower
                else{
                    this->generate_packet(-1);
                    Packet temp_pack = it->second.packet;
                    this->buffer->aggregated_packet =new Packet(temp_pack.getSrc(), -1,
                                                                temp_pack.getTimestamp_start()); // pass the arguments
                    a_packet_has_decoded = true;
                }
            }
            decoded_packets_statistics.push_back(it->first);
            it = receiving_buffer.erase(it); // Remove the item
        } else if (it->second.decoded_or_not == "Non_decoded") {
            non_decoded_packets_statistics.push_back(it->first);
            it = receiving_buffer.erase(it);
        } else {
            ++it; // Move to the next item
        }
    }

    // All packets remove if one hash decoded now
    for (auto it = receiving_buffer.begin(); it != receiving_buffer.end();){
        if(a_packet_has_decoded){
            it = receiving_buffer.erase(it);
        }
    }


}

MultihopNode::MultihopNode(int id, int x, int y, int z, int sf, int channel, int transmission_power,
                           double packet_gen_prob, int assigned_node, int following, int type) : Node(id, x, y, z, sf,
                                          channel, transmission_power, packet_gen_prob, assigned_node, following, type){}

