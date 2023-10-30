//
// Created by gmavros-yoga-7 on 27/10/2023.
//

#ifndef LORA_SIM_CPP_TRAFFIC_H
#define LORA_SIM_CPP_TRAFFIC_H

#include "node.h"
#include "gateway.h"
#include "environment.h"


class Traffic {
private:
    vector<Node> nodes;
    Environment environment;

public:
    void initialize();
    void run();

};


#endif //LORA_SIM_CPP_TRAFFIC_H
