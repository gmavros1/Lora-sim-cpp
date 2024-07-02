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

    this->num_of_decoded_packets_known_in_protocol = 0;
    this->num_of_ongoing_packets_in_receiver = 0;
    this->dc_timer = 0;
    this->toa_timer = 0;

}

std::string Node::LoRaWan() {
    if (this->current_state == states[0]) { // SLEEP
        if (dc_timer==0){
            // CONDITIONS TO GENERATE PACKET IN ORDER TO TRANSMIT
            if((rand() / double (RAND_MAX)) <= this->packet_gen_prob){
                generate_packet();
                double toa = calculate_toa();
                double dc = duty_cycle(toa);
                this->dc_timer = dc;
                this->toa_timer = toa;
                this->current_state = states[2]; // TRANSITION
                cout << "Node " << this->id << " generate/transmit at " << this->environment_time << endl;
                return states[2];
            } else{ // NO EVENT TO GENERATE PACKET
                return states[0];
            }
        } else{ // CANNOT SEND DUE TO DC RESTRICTIONS
            dc_timer --;
            return states[0];
        }
    }

    if (this->current_state == states[1]) { // RECEIVE
        return states[0];
    }

    if (this->current_state == states[2]) { // TRANSMIT
        if (this->toa_timer > 1){
            this->toa_timer--;
            return states[2];
        } else{
            this->current_state = states[0]; // TRANSITION
            cout << "Node " << this->id << " Completed transmission at " << this->environment_time << endl;
            return states[0];
        }
    }

    if (this->current_state == states[3]) { // LISTEN
        return states[0];
    }

    return "BUG";
}

void Node::identify_incoming_segments(vector<radio_packet> &packets_received) {
    // Packets within Range
    vector<radio_packet> current_packets;
    current_packets = packets_received;

    // Keep only sf and channel where device can tune to
    if (this->sf != -1 && this->channel!=-1){
        for (int index = current_packets.size() - 1; index >= 0; index--){
            if (current_packets[index].sf == this->sf && current_packets[index].channel == this->channel){
                current_packets.erase(current_packets.begin() + index);
            }
        }
    }

    // Abort packet due to range issues
    for (int index = current_packets.size() - 1; index >= 0; index--) {
        double receive_power = calculate_received_power(devicesDistance(this->location,
                                                                        current_packets[index].location),
                                                        current_packets[index].transmission_power);
        if (calculate_snr(receive_power, -(130.0+2.5)) >= snr_limit(current_packets[index].sf) + 10 ) { // receive_power >= -130
            current_packets[index].receive_power = receive_power;
            // cout << "IN" << endl;
        } else {
            current_packets.erase(current_packets.begin() + index);
            // cout << "ABORT" << endl;
        }
    }

    this->num_of_ongoing_packets_in_receiver = current_packets.size();
}
