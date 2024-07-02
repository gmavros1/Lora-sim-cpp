//
// Created by gmavros-yoga-7 on 27/10/2023.
//

#ifndef LORA_SIM_CPP_TRAFFIC_H
#define LORA_SIM_CPP_TRAFFIC_H

#include "node.h"
#include "gateway.h"
#include "environment.h"

class Traffic{
public:
    void initialize();
    void run();
private:
    string net_case;
    string protocol_used;
    vector<Node> nodes;
    vector<Gateway> gateways;
    Environment environment;
    int level;
    int life_time;
    float rate_prd;
    double rate;
    double norm_load;
    double max_sf;
    double max_delay;

};

#endif //LORA_SIM_CPP_TRAFFIC_H