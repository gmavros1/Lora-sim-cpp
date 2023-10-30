//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#include "gateway.h"
#include "environment.h"
#include "utils.h"

// Set sensitivity of Lora -149 dBm
void Gateway::receive(vector<radio_packet> &packets_received) {

    vector<radio_packet> current_packets = packets_received;

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
    //      * The sf
    //      * The channel
    //      * A vector of structs. which will contain
    //            * The rec power
    //            * The max power of the current segment packets in same channel and sf with different id



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


