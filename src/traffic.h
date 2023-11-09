//
// Created by gmavros-yoga-7 on 27/10/2023.
//

#ifndef LORA_SIM_CPP_TRAFFIC_H
#define LORA_SIM_CPP_TRAFFIC_H

#include <vector>
#include "traffic.h"
#include "environment.h"
#include "packet.h"
#include "node.h"  // Include other necessary headers if needed
#include "gateway.h"

class Node;
class Gateway;
class Environment;
class Packet;

using namespace std;
//#include "gateway.h"
//#include "environment.h"

class Packet;
class Environment;
class Traffic {
private:
    vector<Node> nodes;
    vector<Gateway> gateways;
    Environment environment;
    double rate;
    int life_time;

public:
    void initialize();
    void run();
    void put_metrics_in_file();

};


#endif //LORA_SIM_CPP_TRAFFIC_H
