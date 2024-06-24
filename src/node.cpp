//
// Created by gmavros-yoga-7 on 22/10/2023.
//

/*
 * Core of the functionality is a markof chain process
 * It will be called first and according to node state
 * it will return which function should be called.
 * Name of this function is node_driver.
 * Seperated of protocol functionalities, in charge only
 * for the basic functionalities
 */


#include "node.h"
#include "packet.h"
#include "utils.h"
#include <cmath>
#include <string>


Node::Node(int id, int x, int y, int z, int sf, int channel, int transmission_power,double packet_gen_prob, int assigned_node, int following, int type) {
    this->id = id;
    this->location.x = x;
    this->location.y = y;
    this->location.z = z;
    this->sf = sf;
    this->channel = channel;
    this->bandwidth = 125;
    this->transmission_power = transmission_power;
    this->environment_time = 0;
    this->duty_cycle_current = 0.0;
    this->ready_for_transmission = 0;
    this->buffer = nullptr;
    this->packet_gen_prob = packet_gen_prob;
    this->state = "Sleeping";

    this->assigned_node = assigned_node;
    this->following = following;
    this->type = type;

    this->generated_packets = 0;
}

void Node::generate_packet() {
    this->buffer = new Packet(this->id, this->assigned_node, this->environment_time);

    this->calculate_toa();

}

void Node::calculate_toa() {
    // Calculate toa nd dc
    this->ready_for_transmission = this->environment_time;
    double time_over_air = toa(this->buffer->getPayload_bytes(), this->sf);
    this->duty_cycle_current = duty_cycle(time_over_air);
    this->ready_for_transmission += time_over_air + this->duty_cycle_current;

    // toa is used as seq_number of packet
    // If toa = 40, receiver should be able to decode 40 segments
    // Every time slot, when packet is in air, seq num is decreasing until reaches 0
    int toa_seq = time_over_air;
    this->buffer->setSeqNumReversed(toa_seq);
    generated_packets ++;
}

// Returns the pointer of a new generated packet or null pointer
Packet* Node::transmit_packet() {
    if (this->buffer != nullptr) {
        static Packet transmitted_packet = *new Packet( id, assigned_node, environment_time);
        transmitted_packet = *this->buffer;
        this->buffer = nullptr;

        return &transmitted_packet;
    } else{
        return nullptr;
    }
}

// It is executed right after clock
string Node::node_driver() {
    if (this->ready_for_transmission > this->environment_time) {
        if ((this->ready_for_transmission - this->duty_cycle_current) > this->environment_time){
            this->state = "Transmitting";
            return this->state;
        } else {
            this->state = "Sleeping";
            return this->state;
        }
    }
    else {
        if((rand() / double (RAND_MAX)) <= this->packet_gen_prob) {
            this->state = "Packet Generation";
            return this->state;
        }
        else{
            this->state = "Sleeping";
            return this->state;
        }
    }
}

void Node::clock(int time) {
    this->environment_time = time;

}


coordinates Node::getLocation() {
    return this->location;
}

int Node::getId() {
    return this->id;
}

int Node::getChannel() {
    return this->channel;
}

int Node::getSf() {
    return this->sf;
}

int Node::getTrasmissionPower() {
    return this->transmission_power;
}



