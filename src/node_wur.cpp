//
// Created by gmavros-yoga-7 on 4/7/2024.
//

#include "node_wur.h"

Node_wur::Node_wur(int id, int x, int y, int z, int sf, int channel, int transmissionPower, double packetGenProb,
           int assignedNode, int following, int type) : Node(id, x, y, z, sf, channel, transmissionPower, packetGenProb, assignedNode, following, type) {
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

    this->num_of_decoded_packets_known_in_protocol = 0;
    this->num_of_ongoing_packets_in_receiver = 0;
    this->dc_timer = 0;
    this->toa_timer = 0;

}

// After generation of data, send.
wake_up_radio* Node_wur::send_wur() {

    int dst = this->buffer->getDst();
    int ch = this->channel;
    coordinates pos = this->location;

    static wake_up_radio wur_signal;
    wur_signal.location = pos;
    wur_signal.channel = ch;
    wur_signal.dst = dst;

    return &wur_signal;
}


// Every time a signal like this is on radio, a receiver (corr dst)
// is being activated
void Node_wur::receive_wur(vector<wake_up_radio> &interrupt) {

    vector<wake_up_radio> current_wurs;
    current_wurs = interrupt;

    for (int index = current_wurs.size() - 1; index >= 0; index--) {

        wake_up_radio received_wur;

        received_wur.dst = current_wurs[index].dst;
        received_wur.channel = current_wurs[index].channel;
        received_wur.location = current_wurs[index].location;

        double distance = devicesDistance(received_wur.location, current_wurs[index].location);
        if (this->id == received_wur.dst && distance <= 900.0) {
            this->wur_received = true;
        }
    }
}

std::string Node_wur::protocol() {
    return std::string();
}
