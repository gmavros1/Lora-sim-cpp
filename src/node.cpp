#include "node.h"

Node::Node(int id, int x, int y, int z, int sf, int channel, int transmissionPower, double packetGenProb,
                 int assignedNode, int following, int type) : Device(id, x, y, z, sf, channel, transmissionPower, packetGenProb, assignedNode, following, type) {
    this->id = id;
    this->location.x = x;
    this->location.y = y;
    this->location.z = z;

    this->sf = sf;
    this->channel = channel;
    this->transmission_power = transmissionPower;
    this->packet_gen_prob = packetGenProb;
    this->assigned_node = assignedNode;
    this->following = following;
    this->type = type;

    this->previous_state = this->states[0];
    this->current_state = this->states[0];

    this->num_of_received_packets_known_in_protocol = 0;
    this->dc_timer = 0;
    this->toa_timer = 0;
    this->rx1_timer = 0;
    this->rx1_delay_timer = 0;
    this->rx2_timer = 0;
    this->rx2_delay_timer = 0;

}

std::string Node::LoRaWan(bool acknowledge) {
    if (this->current_state == states[0]) { // SLEEP
        // CONDITIONS TO GENERATE PACKET IN ORDER TO TRANSMIT
        if ((this->previous_state != states[7] || this->previous_state != states[4]) && this->dc_timer == 0){
            if((rand() / double (RAND_MAX)) <= this->packet_gen_prob){
                // GENERATE PACKET
                this->generate_packet();
                this->toa_timer = this->calculate_toa();
                this->dc_timer = duty_cycle(this->toa_timer);



            }
        }

    }

    if (this->current_state == states[1]) { // LISTEN

    }

    if (this->current_state == states[2]) { // RECEIVE

    }

    if (this->current_state == states[3]) { // TRANSMIT

    }

    if (this->current_state == states[4]) { // RX1

    }

    if (this->current_state == states[5]) { // RX2

    }

    if (this->current_state == states[6]) { // PACKET_RECEIVED

    }

    if (this->current_state == states[7]) { // PACKET_TRANSMITTED

    }
}
