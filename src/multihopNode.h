//
// Created by gmavros-yoga-7 on 10/11/2023.
//

#ifndef LORA_SIM_CPP_MULTIHOPNODE_H
#define LORA_SIM_CPP_MULTIHOPNODE_H

#include "node.h"
#include "environment.h"
#include "utils.h"
#include "../external/json/include/nlohmann/json.hpp"
// Forward declaration



class MultihopNode: public Node {

private:
    map<string, packets_receiving> receiving_buffer;

public:
    MultihopNode(int id, int x, int y, int z, int sf, int channel, int transmission_power, double packet_gen_prob,
                 int assigned_node, int following, int type);
    void receive_node(vector<radio_packet> &packets_received);
    string multiNode_driver();
    vector<string> decoded_packets_statistics;
    vector<string> non_decoded_packets_statistics;
};


#endif //LORA_SIM_CPP_MULTIHOPNODE_H
