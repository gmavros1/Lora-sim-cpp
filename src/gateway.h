//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#ifndef LORA_SIM_CPP_GATEWAY_H
#define LORA_SIM_CPP_GATEWAY_H

#include "utils.h"
class Environment;
class radio_packet; // Add a forward declaration for radio_packet
class Gateway {
private:
    int id;
    coordinates location{};
    int environment_time{};

public:
    Gateway(int id, int x, int y, int z);
    void receive(vector<radio_packet> packets_received);
    void clock(int time);
};


#endif //LORA_SIM_CPP_GATEWAY_H
