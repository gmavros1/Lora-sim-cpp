//
// Created by gmavros-yoga-7 on 29/10/2023.
//

#ifndef LORA_SIM_CPP_GATEWAY_H
#define LORA_SIM_CPP_GATEWAY_H
#include <vector>

class radio_packet;  // Forward declaration
using namespace std;

struct coordinates_gw {
    int x;
    int y;
    int z;
};

//#include "utils.h"
//class Environment;
class radio_packet; // Add a forward declaration for radio_packet
//class Node;
class Gateway {
private:
    int id;
    coordinates_gw location{};
    int environment_time{};

public:
    Gateway(int id, int x, int y, int z);
    void receive(vector<radio_packet> packets_received);
    void clock(int time);
};


#endif //LORA_SIM_CPP_GATEWAY_H
