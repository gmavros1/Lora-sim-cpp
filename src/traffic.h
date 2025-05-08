//
// Created by gmavros-yoga-7 on 27/10/2023.
//

#ifndef LORA_SIM_CPP_TRAFFIC_H
#define LORA_SIM_CPP_TRAFFIC_H

#include "node.h"
#include "gateway.h"
#include "node_wur.h"
#include "node_wur_extended.h"
#include "environment.h"

class Traffic{
public:
    void initialize();
    void run_Multihop();
    void run_Multihop_extended();
    void run_LoRaWAN();
    void metrics();
    string protocol_used;
private:
    string net_case;
    vector<Node> nodes;
    vector<Node_wur> nodes_wur;
    vector<Node_wur_extended> nodes_wur_extended;
    vector<Gateway> gateways;
    Environment environment;
    int level;
    int life_time;
    float mean_sf;
    double rate;
    double norm_load;
    int max_sf;
    double max_delay;
    string experiment_name;

    // STATISTICS
    int packet_drop_receiver_transmitOrSleep = 0;

};

#endif //LORA_SIM_CPP_TRAFFIC_H