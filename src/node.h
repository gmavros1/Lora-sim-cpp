#ifndef LORA_SIM_CPP_NODE_H
#define LORA_SIM_CPP_NODE_H

#include "device.h"

class Node: public Device{

protected:
    std::string states[4] = {"SLEEP", "RECEIVE", "TRANSMIT", "LISTEN"};
    std::string previous_state;
    std::string current_state;

    // USED FOR TOA DC, RX1/2 PERIODS ECT.
    // RX1 AND RX2 1 AND 2 SECONDS RESPECTIVELY
    int dc_timer;
    int toa_timer;

    // IN ORDER TO IDENTIFY SUCCESSFUL TRANSMISSION
    int num_of_decoded_packets_known_in_protocol;
    // IN ORDER TO GO FROM LISTENING TO RECEIVING
    int num_of_ongoing_packets_in_receiver;

public:
    Node(int id1, int x1, int y1, int z1, int sf, int channel, int transmissionPower, double packetGenProb,
            int assignedNode, int following, int type);

    std::string LoRaWan();
    void identify_incoming_segments(vector<radio_packet> &packets_received);
};

#endif //LORA_SIM_CPP_NODE_H