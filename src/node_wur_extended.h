//
// Created by gmavros-yoga-7 on 4/7/2024.
//

#ifndef LORA_SIM_CPP_NODE_WUR_EXTENDED_H
#define LORA_SIM_CPP_NODE_WUR_EXTENDED_H

#include "node.h"

class Node_wur_extended: public Node {

public:

    struct wake_up_radio{
        int dst = 0;
        int channel = 0;
        int timestamp = 0;
        coordinates location{};
    };

    Node_wur_extended(int id, int x, int y, int z, int sf, int channel, int transmissionPower, double packetGenProb,
         int assignedNode, int following, int type);

    wake_up_radio* send_wur();
    void receive_wur(vector<wake_up_radio> &interrupt);

    std::string protocol();
    std::string get_state();

private:
    bool wur_received = false;
    int wur_timer;

    int wur_timer_block_receive;
    int wur_timer_block_transmit;

    std::string ctrl_send_packet();
    std::string ctrl_receive_packet();
    std::string ctrl_send_wur();
    std::string ctrl_receive_wur();
    std::string ctrl_block_transmit();
    std::string ctrl_block_receive();
    std::string ctrl_receive_packet_and_wur();

};


#endif //LORA_SIM_CPP_NODE_WUR_EXTENDED_H
