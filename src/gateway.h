#ifndef LORA_SIM_CPP_GATEWAY_H
#define LORA_SIM_CPP_GATEWAY_H

#include "device.h"

class Gateway: public Device{

public:
    Gateway(int id1, int x1, int y1, int z1, int sf, int channel, int transmissionPower, double packetGenProb,
            int assignedNode, int following, int type);
};

#endif //LORA_SIM_CPP_GATEWAY_H