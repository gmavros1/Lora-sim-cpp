//
// Created by gmavros-yoga-7 on 28/10/2023.
//

#ifndef LORA_SIM_CPP_ENVIRONMENT_H
#define LORA_SIM_CPP_ENVIRONMENT_H
#include <vector> // Include the vector header
//#include "packet.h" // Include the header for the Packet class
#include "node.h"
#include "gateway.h"
#include "node_wur.h"

using namespace std;

class Environment {
private:
    vector<radio_packet> packets;
    vector<wake_up_radio> wake_up_radios;
public:
    Environment();
    void add_packet(Packet packet, int channel, int sf, int transmission_power, coordinates location);
    void add_wur_signal(int dst, int channel, coordinates location);
    vector<radio_packet> getPackets();
    vector<wake_up_radio> get_wurs();
    void time_over_air_handling();

};


#endif //LORA_SIM_CPP_ENVIRONMENT_H