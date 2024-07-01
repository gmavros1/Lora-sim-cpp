#ifndef LORA_SIM_CPP_NODE_H
#define LORA_SIM_CPP_NODE_H

#include "device.h"

class Node: public Device{

protected:
    std::string states[8] = {"SLEEP", "LISTEN", "RECEIVE", "TRANSMIT", "RX1", "RX2",
                             "RECEPTION_COMPLETED", "TRANSMISSION_COMPLETED"};
    std::string previous_state;
    std::string current_state;

    // USED FOR TOA DC, RX1/2 PERIODS ECT.
    // RX1 AND RX2 1 AND 2 SECONDS RESPECTIVELY
    int dc_timer;
    int toa_timer;
    int rx1_timer;
    int rx1_delay_timer;
    int rx2_timer;
    int rx2_delay_timer;

    // IN ORDER TO IDENTIFY SUCCESSFUL TRANSMISSION
    int num_of_received_packets_known_in_protocol;

public:
    Node(int id1, int x1, int y1, int z1, int sf, int channel, int transmissionPower, double packetGenProb,
            int assignedNode, int following, int type);

    std::string LoRaWan(bool acknowledge);
};

#endif //LORA_SIM_CPP_NODE_H