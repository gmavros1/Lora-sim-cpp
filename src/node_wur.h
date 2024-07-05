//
// Created by gmavros-yoga-7 on 4/7/2024.
//

#ifndef LORA_SIM_CPP_NODE_WUR_H
#define LORA_SIM_CPP_NODE_WUR_H

#include "node.h"

struct wake_up_radio{
    int dst = 0;
    int channel = 0;
    coordinates location{};
    };

class Node_wur: public Node {

public:
    Node_wur(int id, int x, int y, int z, int sf, int channel, int transmissionPower, double packetGenProb,
         int assignedNode, int following, int type);

    wake_up_radio* send_wur();
    void receive_wur(vector<wake_up_radio> &interrupt);

    std::string protocol();

private:
    bool wur_received = false;

};


#endif //LORA_SIM_CPP_NODE_WUR_H
