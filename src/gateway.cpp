//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#include "gateway.h"
#include "environment.h"
#include "utils.h"

// Set sensitivity of Lora -149 dBm
void Gateway::receive(vector<radio_packet> &packets_received) {

    // Packets within Range
    vector<radio_packet> current_packets;
    current_packets = packets_received;

    // Abort packet due to range issues
    for (int index = current_packets.size() - 1 ; index >= 0; index--) {
        double receive_power = calculate_received_power(distanceGatewayNode(this->location,
                                                                            current_packets[index].location),
                                                        current_packets[index].transmission_power);
        if (receive_power >= -149){
            current_packets[index].receive_power = receive_power;
        } else{
            current_packets.erase(current_packets.begin() + index);
        }
    }

    // Add a vector of structs. Its struct will contain:
    //      * The id of the packet
    //      * The actual packet
    //      * The sf
    //      * The channel
    //      * A vector of structs. which will contain
    //            * The rec power
    //            * The max power of the current segment packets in same channel and sf with different id

    // Add every segment of a packet + interference information n^2 complexity
    for (auto current_packet: current_packets) {
        string packet_id = current_packet.packet.getPacketId();

        // Find max interference signal;
        double max_itf = -200;
        for (auto current_packet_cmp: current_packets){ // packet compared (cmp)
            if (current_packet.sf == current_packet_cmp.sf &&
                current_packet.channel == current_packet_cmp.channel &&
                packet_id != current_packet_cmp.packet.getPacketId()){
                if (current_packet_cmp.receive_power > max_itf){
                    max_itf = current_packet_cmp.receive_power;
                }
            }
        }

        // Build interference info per packet
        rec_powers r_powers{};
        r_powers.packet_rec_power = current_packet.receive_power;
        cout << endl << r_powers.packet_rec_power << endl;
        r_powers.maximum_interference_power = max_itf; // found above
        cout << r_powers.maximum_interference_power << endl;

        // First segment of the packet
        if (receiving_buffer.find(packet_id) == receiving_buffer.end()){

            // Build Packet receiving information
            packets_receiving current_packet_info{};
            current_packet_info.id = packet_id;
            current_packet_info.packet = current_packet.packet;
            current_packet_info.sf = current_packet.sf;
            current_packet_info.channel = current_packet.channel;
            current_packet_info.segments_received.push_back(r_powers);

            receiving_buffer.insert({packet_id, current_packet_info});
        }
        else{

            // Add receiving segment power information
            auto received_segment = receiving_buffer[packet_id];
            received_segment.segments_received.push_back({r_powers});

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


