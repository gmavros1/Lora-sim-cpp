//
// Created by gmavros-yoga-7 on 22/10/2023.
//

#include "node.h"

Node::Node(int id, int x, int y, int z, int sf, int channel, int transmission_power) {
    this->id = id;
    this->location.x = x;
    this->location.y = y;
    this->location.z = z;
    this->sf = sf;
    this->channel = channel;
    this->bandwidth = 125;
    this->transmission_power = transmission_power;
    this->environment_time = 0;
    this->duty_cycle_remained = 0;
    this->time_over_air_remained = 0;
    this->buffer = nullptr;
}

void Node::generate_packet(int dst) {
    this->buffer = new Packet(this->id, dst, this->environment_time);
}

Packet Node::transmit_packet() {
    Packet transmited_packet = *this->buffer;
    this->buffer = nullptr;
    return transmited_packet;
}

void Node::clock(int time) {
    this->environment_time = time;
}

coordinates Node::getLocation() {
    return this->location;
}
