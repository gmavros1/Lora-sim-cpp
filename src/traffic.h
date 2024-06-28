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
#include "multihopNode.h"
#include "gateway.h"

class Node;
class MultihopNode;
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
    string net_case;
    string protocol_used;
    vector<Node> nodes;
    vector<MultihopNode> middle_nodes;
    vector<Gateway> gateways;
    Environment environment;
    int level;
    int life_time;
    float rate_prd;
    double rate;
    double norm_load;
    double max_sf;
    double max_delay;

public:
    void initialize();
    void run();
    void put_metrics_in_file();

};


#endif //LORA_SIM_CPP_TRAFFIC_H
