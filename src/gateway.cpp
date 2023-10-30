//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#include "gateway.h"
#include "environment.h"
#include "utils.h"


void Gateway::receive(vector<radio_packet> &packets_received) {

    for (size_t index = 0; index < packets_received.size(); ++index) {
        packets_received[index].receive_power = calculate_received_power(distanceGatewayNode(this->location, ))
    }

}

void Gateway::clock(int time) {
    this->environment_time = time;
}

Gateway::Gateway(int id, int x, int y, int z) {
    this->id = id;
    this->location.x = x;
    this->location.x = y;
    this->location.x = z;
}

coordinates_gw Gateway::getLocation() {
    return this->location;
}


