//
// Created by gmavros-yoga-7 on 28/10/2023.
//

#ifndef LORA_SIM_CPP_ENVIRONMENT_H
#define LORA_SIM_CPP_ENVIRONMENT_H

#include <vector>
#include "packet.h"

struct radio_packet{
    int transmission_power = 0;
    int receive_power = 0;
    int sf = 0;
    int channel = 0;
    Packet packet = *new Packet(-1, -1, -1, -1, -1, -1);
};

class Environment {
private:
    vector<radio_packet > packets;
public:
    Environment();
    void add_packet(Packet packet, int channel, int sf, int transmission_power);
    vector<radio_packet > getPackets();
    void time_over_air_handling();

};


#endif //LORA_SIM_CPP_ENVIRONMENT_H
