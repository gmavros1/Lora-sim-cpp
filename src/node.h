//
// Created by gmavros-yoga-7 on 22/10/2023.
//

#ifndef LORA_SIM_CPP_NODE_H
#define LORA_SIM_CPP_NODE_H

#include "packet.h"
#include <vector>

struct coordinates{
    int x;
    int y;
    int z;
};

class Node {
public:
    Node(int id, int x, int y,  int z, int sf, int channel, int transmission_power);
    ~Node() = default;
    void generate_packet(int dst);
    Packet transmit_packet();
    void clock(int time);
private:
    int id;
    int channel;
    int sf;
    int bandwidth;
    int transmission_power;
    int environment_time;
    int duty_cycle_remained;
    int time_over_air_remained;
    coordinates location{};
    Packet* buffer;

};


#endif //LORA_SIM_CPP_NODE_H
