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

    //New states due to wake up transceivers
    this->states[4] = "SEND_WUR";
    this->states[5] = "RECEIVE_WUR";

    this->wur_timer = 0;

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

    if (this->current_state == states[0]) { // SLEEP
        if (wur_received){
            this->wur_timer = 8;
            this->current_state = states[5];
            return this->current_state;
        }

        if (dc_timer==0){
            // CONDITIONS TO GENERATE PACKET IN ORDER TO TRANSMIT
            if((rand() / double (RAND_MAX)) /*0.0*/ <= this->packet_gen_prob){

                generate_packet();
                if (assigned_node < 0) { // Node near gateway
                    double toa = calculate_toa();
                    double dc = duty_cycle(toa);
                    this->dc_timer = dc;
                    this->toa_timer = toa;
                    this->current_state = states[2]; // TRANSITION
                } else{ // Two hop nodes
                    this->wur_timer = 8; // Lets assume 8 ms delay
                    this->current_state = states[4]; // SEND WUR
                }
                cout << "Node " << this->id << " generate/transmit at " << this->environment_time << endl;
                return this->current_state;
            } else{ // NO EVENT TO GENERATE PACKET
                return this->current_state;
            }
        } else{ // CANNOT SEND DUE TO DC RESTRICTIONS
            dc_timer --;
            return this->current_state;
        }
    }

    if (this->current_state == states[1]) { // RECEIVE
        if (this->buffer != nullptr){
            if (assigned_node < 0) { // Node near gateway
                double toa = calculate_toa();
                double dc = duty_cycle(toa);
                this->dc_timer = dc;
                this->toa_timer = toa;
                this->current_state = states[2]; // TRANSITION
            } else{ // Two hop nodes
                this->wur_timer = 8; // Lets assume 8 ms delay
                this->current_state = states[4]; // SEND WUR
            }
            return this->current_state; // HAS A PACKET, SO TRANSMIT
        } else{
            if (receiver_timeout == 0) { // Couldn't receive, go to sleep
                this->current_state = states[0];
                return this->current_state;
            } else{
                receiver_timeout --;
                this->current_state = states[1];
                return this->current_state; // KEEP RECEIVING
            }
        }
    }

    if (this->current_state == states[2]) { // TRANSMIT
        if (this->toa_timer > 1){
            this->toa_timer--;
            return this->current_state;
        } else{
            this->current_state = states[0]; // TRANSITION GOES TO SLEEP
            cout << "Node " << this->id << " Completed transmission at " << this->environment_time << endl;
            return this->current_state;
        }
    }

    if (this->current_state == states[3]) { // LISTEN
        return this->current_state;
    }

    if (this->current_state == states[4]) { // SEND WUR
        if (this->wur_timer > 1){
            this->wur_timer--;
            return this->current_state;

        } else{
            double toa = calculate_toa();
            double dc = duty_cycle(toa);
            this->dc_timer = dc;
            this->toa_timer = toa;
            this->current_state = states[2]; // TRANSITION
            return this->current_state;
        }

    }

    if (this->current_state == states[5]) { // RECEIVE WUR
        if (this->wur_timer == 0){
            this->current_state = states[1]; // receiving
            return this->current_state;
        } else{
            this->wur_timer--;
            return this->current_state;
        }
    }

    return "BUG";
}
