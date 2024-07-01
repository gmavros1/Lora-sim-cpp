#ifndef LORA_SIM_CPP_NODE_H
#define LORA_SIM_CPP_NODE_H

#include "device.h"

class Node: public Device{

public:
    Node(int id1, int x1, int y1, int z1, int sf, int channel, int transmissionPower, double packetGenProb,
            int assignedNode, int following, int type);
};

#endif //LORA_SIM_CPP_NODE_H