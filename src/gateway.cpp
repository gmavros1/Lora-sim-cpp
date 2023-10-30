//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#include "gateway.h"
#include "environment.h"
#include "utils.h"

// Set sensitivity of Lora -149 dBm
void Gateway::receive(vector<radio_packet> &packets_received) {

    vector<radio_packet> current_packets = packets_received;
    for (size_t index = 0; index < current_packets.size(); ++index) {
        double receive_power = calculate_received_power(distanceGatewayNode(this->location, current_packets[index].location), current_packets[index].transmission_power);

        if (receive_power >= -149){
            cout << "KEPT" << endl;
            current_packets[index].receive_power = receive_power;
        } else{
            cout << "ABORT" << endl;
            current_packets.erase(current_packets.begin() + index);
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


