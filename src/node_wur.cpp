//
// Created by gmavros-yoga-7 on 4/7/2024.
//

#include "node_wur.h"

Node_wur::Node_wur(int id, int x, int y, int z, int sf, int channel, int transmissionPower, double packetGenProb,
                   int assignedNode, int following, int type) : Node(id, x, y, z, sf, channel, transmissionPower,
                                                                     packetGenProb, assignedNode, following, type) {
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
wake_up_radio *Node_wur::send_wur() {

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

    // IF NODE SLEEPS NOW
    if (this->current_state == states[0]) { // SLEEP

        // THE FIRST SEGMENT OF A WUR IN RECEIVER
        // START COUNTING THE DELAY
        // NOW THE STATE WILL BE RECEIVE_WUR
        if (wur_received) {
            return this->ctrl_receive_wur();
        }

        // NO WUR FOR THIS NODE
        // DC COUNTER IS 0, SO NODE CAN GENERATE PACKET
        if (dc_timer == 0) {
            if ((rand() / double(RAND_MAX)) <= this->packet_gen_prob) {
                generate_packet();

                // IF IT GOES FOR GW, TRANSMIT
                // SET COUNTERS AND RETURN THE STATE
                if (assigned_node < 0) {
                    return ctrl_send_packet();
                } else {
                    return ctrl_send_wur();
                }
            } else {
                // NO PACKET GENERATION
                // KEEP SLEEPING
                return this->current_state;
            }
        } else {
            // DUTY CYCLE HAS NOT FINISHED YET
            // REDUCE THE TIMER
            // KEEP SLEEPING
            dc_timer--;
            return this->current_state;
        }
    }

    // IF NODE IS RECEIVING NOW
    if (this->current_state == states[1]) {

        // THE TRANSMISSION HAS COMPLETED SUCCESSFULLY
        // THERE IS A PACKET IN BUFFER
        if (this->buffer != nullptr) {
            this->receiver_timeout = 0; // Zero timer

            // TRANSMIT BECAUSE IT'S NEAR THE GATEWAY
            if (assigned_node < 0) {
                return ctrl_send_packet();
            } else {
                // SEND WUR BECAUSE IT IS A MULTI-HOP NODE
                return ctrl_send_wur();
            }

            // IT MEANS THAT KEEP RECEIVING OR FAILED TO RECEIVE
        } else {
            // TIMED OUT -> RETURN TO SLEEP
            if (receiver_timeout <= 1) {
                this->current_state = states[0];
                return this->current_state;
            } else {
                // KEEP RECEIVING
                receiver_timeout--;
                this->current_state = states[1];
                return this->current_state;
            }
        }
    }

    // IF NODE IS TRANSMITTING NOW
    if (this->current_state == states[2]) {
        // PACKET TRANSMISSION HAS NOT COMPLETED YET
        if (this->toa_timer > 1) {
            this->toa_timer--;
            return this->current_state;
        } else {
            // TRANSMISSION COMPLETED
            this->current_state = states[0];
            return this->current_state;
        }
    }

    // IF NODE IS LISTENING
    if (this->current_state == states[3]) {
        return this->current_state;
    }

    // IF NODE IS SENDING WUR NOW
    if (this->current_state == states[4]) {
        // WUR DELAY ONGOING
        if (this->wur_timer > 1) {
            this->wur_timer--;
            return this->current_state;

            // AFTER WUR GO FOR TRANSMISSION
        } else {
            return ctrl_send_packet();
        }

    }

    // IF NODE IS RECEIVING WUR NOW
    if (this->current_state == states[5]) {

        // DONE
        // GO FOR RECEPTION
        if (this->wur_timer <= 1) {
            return ctrl_receive_packet();
            //KEEP GOING
        } else {
            this->wur_timer--;
            return this->current_state;
        }
    }

    return "BUG";
}

std::string Node_wur::ctrl_send_packet() {
    // IF IT GOES FOR GW, TRANSMIT
    // SET COUNTERS AND RETURN THE STATE
    // Node near gateway
    double toa = calculate_toa();
    double dc = duty_cycle(toa);
    this->dc_timer = dc;
    this->toa_timer = toa;
    this->current_state = states[2]; // OTHERWISE SEND WUR
    // TO WAKE UP THE NEXT NODE
    return this->current_state;
}

std::string Node_wur::ctrl_receive_packet() {
    this->current_state = states[1];
    this->wur_received = false;
    this->receiver_timeout = 1000;
    return this->current_state;
}

std::string Node_wur::ctrl_send_wur() {
    // IN ORDER TO TRANSMIT
    this->wur_timer = 8; // Lets assume 8 ms delay
    this->current_state = states[4];
    return this->current_state;
}

std::string Node_wur::ctrl_receive_wur() {
    this->wur_timer = 8;
    this->current_state = states[5];
    return this->current_state;
}
