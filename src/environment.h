//
// Created by gmavros-yoga-7 on 28/10/2023.
//

#ifndef LORA_SIM_CPP_ENVIRONMENT_H
#define LORA_SIM_CPP_ENVIRONMENT_H
#include <vector> // Include the vector header
#include "packet.h" // Include the header for the Packet class
#include "node.h"

using namespace std;

struct radio_packet{
    int transmission_power = 0;
    double receive_power = 0;
    int sf = 0;
    int channel = 0;
    coordinates location;
    Packet packet = *new Packet(-1, -1, -1, -1, -1, -1);
};


class Environment {
private:
    vector<radio_packet > packets;
public:
    Environment();
    void add_packet(Packet packet, int channel, int sf, int transmission_power, coordinates location);
    vector<radio_packet > getPackets();
    void time_over_air_handling();

};


#endif //LORA_SIM_CPP_ENVIRONMENT_H
