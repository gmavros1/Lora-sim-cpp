//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#include "gateway.h"
#include "utils.h"


void Gateway::receive(vector<radio_packet> packets_received) {

    // First Remove packets which are out of range

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
