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
#include <cmath>

double toa(int payload_length, int sf, int crc = 1, int header = 0, int de = 0, int n_preamble = 8, int bw = 125, int cr = 1) {
    if (bw == 125 && sf >= 11) {
        de = 1;
    }

    double Ts = std::pow(2, sf) / bw;
    double num_payload_symbols = 8 + std::max(static_cast<double>(std::ceil(
            (8 * payload_length - 4 * sf + 28 + 16 * crc - 20 * header) / (4 * (sf - 2 * de))) * (cr + 4)), 0.0);
    double T_payload = Ts * num_payload_symbols;
    double T_preamble = (n_preamble + 4.25) * Ts;
    return T_preamble + T_payload;
}

double duty_cycle(double toa) {
    double dutyCycle = 0.01; // 1%
    double t_interval = (toa / dutyCycle) - toa;
    return t_interval; // ms have to wait until the next transmission
}

Node::Node(int id, int x, int y, int z, int sf, int channel, int transmission_power,double packet_gen_prob) {
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
    //this->time_over_air_remained = 0;
    this->ready_for_transmission = 0;
    this->buffer = nullptr;
    this->packet_gen_prob = packet_gen_prob;
    this->state = "Sleeping";
}

void Node::generate_packet(int dst) {
    this->buffer = new Packet(this->id, dst, this->environment_time);

    // Calculate toa nd dc
    this->ready_for_transmission = this->environment_time;
    double time_over_air = toa(this->buffer->getPayload_bytes(), this->sf);
    this->duty_cycle_current = duty_cycle(time_over_air);
    this->ready_for_transmission += time_over_air + this->duty_cycle_current;

    // toa is used as seq_number of packet
    // If toa = 40, receiver should be able to decode 40 segments
    // Every time slot, when packet is in air, seq num is decreasing until 0
    int toa_seq = time_over_air;
    this->buffer->setSeqNumReversed(toa_seq);

}

Packet* Node::transmit_packet() {
    if (this->buffer != nullptr) {
        static Packet transmitted_packet = *this->buffer;
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

