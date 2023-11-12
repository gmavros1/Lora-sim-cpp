//
// Created by gmavros-yoga-7 on 22/10/2023.
//

#ifndef LORA_SIM_CPP_NODE_H
#define LORA_SIM_CPP_NODE_H

#include "node.h"
#include <string> // Include the string header


class Packet;  // Forward declaration
std::string node_driver();

struct coordinates {
    int x;
    int y;
    int z;
};

class Node {
public:
    Node(int id, int x, int y, int z, int sf, int channel, int transmission_power, double packet_gen_prob, int assigned_node, int following, int type);

    void generate_packet(int dst);

    Packet* transmit_packet();

    void clock(int time);

    coordinates getLocation();

    int getId();

    std::string node_driver();

    int getChannel();

    int getSf();

    int getTrasmissionPower();

protected:
    int id;
    int channel;
    int sf;
    int bandwidth;
    int transmission_power;
    int environment_time;
    double duty_cycle_current;
    //int time_over_air_remained;
    double ready_for_transmission;
    coordinates location{};
    Packet *buffer;
    double packet_gen_prob;
    std::string state;

    int type;
    int assigned_node;
    int following;

};


#endif //LORA_SIM_CPP_NODE_H
