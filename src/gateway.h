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

class radio_packet; // Add a forward declaration for radio_packet
class Gateway {
private:
    int id;
    coordinates_gw location{};
    int environment_time{};

public:
    Gateway(int id, int x, int y, int z);
    void receive(vector<radio_packet> &packets_received);
    void clock(int time);
    coordinates_gw getLocation();
};


#endif //LORA_SIM_CPP_GATEWAY_H
