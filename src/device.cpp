//
// Created by gmavros-yoga-7 on 30/6/2024.
//


#include "device.h"

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



Device::Device(int id, int x, int y, int z, int sf, int channel, int transmission_power,double packet_gen_prob, int assigned_node, int following, int type) {
    this->id = id;
    this->location.x = x;
    this->location.y = y;
    this->location.z = z;
    this->sf = sf;
    this->channel = channel;
    this->bandwidth = 125;
    this->transmission_power = transmission_power;
    this->environment_time = 0;
    //this->duty_cycle_current = 0.0;
    //this->ready_for_transmission = 0;
    this->buffer = nullptr;
    this->packet_gen_prob = packet_gen_prob;
    //this->state = "Sleeping";

    this->assigned_node = assigned_node;
    this->following = following;
    this->type = type;

    this->generated_packets = 0;
    this->received_packets = 0;
}

void Device::generate_packet() {
    this->buffer = new Packet(this->id, this->assigned_node, this->environment_time);
    this->generated_packets ++; // Metrics
    //cout << "Node " << this->id << " generated packet" << endl;
    //this->calculate_toa();

}

// Given a saved packet in buffer after packet generation or packet reception
// Calculate the time over air
int Device::calculate_toa() {
    // Calculate toa nd dc
    //this->ready_for_transmission = this->environment_time;
    double time_over_air = toa(this->buffer->getPayload_bytes(), this->sf);
    //double duty_cycle_current = duty_cycle(time_over_air);
    //this->ready_for_transmission += time_over_air;

    // toa is used as seq_number of packet
    // If toa = 40, receiver should be able to decode 40 segments
    // Every time slot, when packet is in air, seq num is decreasing until reaches 0
    int toa_seq = time_over_air;
    this->buffer->setSeqNumReversed(toa_seq);
    //generated_packets ++;

    return toa_seq;
}

// Returns the pointer of a new generated packet or null pointer
Packet* Device::transmit_packet() {
    if (this->buffer != nullptr) {
        static Packet transmitted_packet = *new Packet( id, assigned_node, environment_time);
        transmitted_packet = *this->buffer;
        this->buffer = nullptr;

        return &transmitted_packet;
    } else{
        return nullptr;
    }
}

void Device::clock(int time) {
    this->environment_time = time;

}


coordinates Device::getLocation() {
    return this->location;
}

int Device::getId() {
    return this->id;
}

int Device::getChannel() {
    return this->channel;
}

int Device::getSf() {
    return this->sf;
}

int Device::getTrasmissionPower() {
    return this->transmission_power;
}

// Receive packet segments and decode the packet if everything came
void Device::receive(vector<radio_packet> &packets_received) {
    // Packets within Range
    vector<radio_packet> current_packets;
    current_packets = packets_received;

    // Keep only sf and channel where device can tune to
    if (this->id >=0){
        for (int index = current_packets.size() - 1; index >= 0; index--){
            if (current_packets[index].sf != this->sf || current_packets[index].channel != this->channel){
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
            // IF GATEWAY, CHECK FOR RECEPTIONS OF IN RANGE SIGNALS
            if (this->id < 0 && current_packets[index].packet.getDst() < 0){
                this->transmissions_to_gw.push_back(current_packets[index].packet.getPacketId());
            }
        } else {
            // IF GATEWAY, CHECK FOR RECEPTIONS OF OUT OF RANGE SIGNALS
            if (this->id < 0 && current_packets[index].packet.getDst() < 0){
                this->out_of_range_to_gw.push_back(current_packets[index].packet.getPacketId());
            }
            current_packets.erase(current_packets.begin() + index);

        }
    }


    // Add every segment of a packet + interference information n^2 complexity
    for (auto current_packet: current_packets) {
        string packet_id = current_packet.packet.getPacketId();

        // Find max interference signal;
        double max_itf = -(130 + 2.5);
        for (auto current_packet_cmp: current_packets) { // packet compared (cmp)
            if (current_packet.sf == current_packet_cmp.sf &&
                current_packet.channel == current_packet_cmp.channel &&
                packet_id != current_packet_cmp.packet.getPacketId()) {
                if (current_packet_cmp.receive_power > max_itf) {
                    max_itf = current_packet_cmp.receive_power;
                }
            }
        }

        // Build interference info per packet
        rec_powers r_powers{};
        r_powers.packet_rec_power = current_packet.receive_power;
        r_powers.maximum_interference_power = max_itf; // found above
        double snr = calculate_snr(r_powers.packet_rec_power, r_powers.maximum_interference_power);
        double snr_limit_value = snr_limit(current_packet.sf);
        r_powers.able_to_decode = snr > snr_limit_value + 10; // Margin 10

        // First segment of the packet
        if (receiving_buffer.find(packet_id) == receiving_buffer.end()) {

            // Build Packet receiving information
            packets_receiving current_packet_info{};
            current_packet_info.id = packet_id;
            current_packet_info.packet = current_packet.packet;
            current_packet_info.sf = current_packet.sf;
            current_packet_info.channel = current_packet.channel;
            current_packet_info.segments_received.push_back(r_powers);

            receiving_buffer.insert({packet_id, current_packet_info});
        } else { // Next received segments

            // Add receiving segment power information
            receiving_buffer[packet_id].segments_received.push_back({r_powers});

            // If it is the last segment
            //cout << packet_id << " " << current_packet.packet.getSeqNum() << endl;

            if (current_packet.packet.getSeqNum() == 0) {
                int num_of_sccs_decod_packets_req = receiving_buffer[packet_id].packet.getNumber0fSegments();
                int num_of_sccs_decod_packets = 0; // Check if all decoded packets are in place
                for (auto &s: receiving_buffer[packet_id].segments_received) {
                    if (s.able_to_decode) {
                        num_of_sccs_decod_packets++;
                    }
                }
                if (num_of_sccs_decod_packets_req == num_of_sccs_decod_packets) {
                    // cout << "eq" << endl;
                    receiving_buffer[packet_id].decoded_or_not = "Decoded";
                    //cout << "Gateway received packet " << receiving_buffer[packet_id].id <<" at " <<  this->environment_time << endl << endl;
                    //cout << " RECEIVED " << num_of_sccs_decod_packets << endl;
                    //cout << " REQUIRED " << num_of_sccs_decod_packets_req << endl;
                } else {
                    receiving_buffer[packet_id].decoded_or_not = "Non_decoded";
                    //cout << " RECEIVED " << num_of_sccs_decod_packets << endl;
                    //cout << " REQUIRED " << num_of_sccs_decod_packets_req << endl;
                }

            }

        }
    }

    // Remove decoded packets
    for (auto it = receiving_buffer.begin(); it != receiving_buffer.end();) {
        if (it->second.decoded_or_not == "Decoded") {

            // IT IS A NODE STO SAVE IN BUFFER FOR RETRANSMISSION
            if (this->sf != -1 && this->channel!=-1){
                Packet temp_pack = it->second.packet;
                this->buffer = new Packet(temp_pack.getSrc(), this->assigned_node,
                                          temp_pack.getTimestamp_start());
            }

            // THIS IS FOR GATEWAYS
            decoded_packets_statistics.push_back(it->first);
            packetDelays[it->first] = (environment_time - it->second.packet.getTimestamp_start()); // Delay stuff

            // THIS IS MAINLY FOR NODES
            // TRANSMISSIONS ARE UNICAST
            this->received_packets ++;

            /*if (it->second.packet.aggregated_packet != nullptr){
                string agg_packet = it->second.packet.aggregated_packet->getPacketId();
                //decoded_packets_statistics.push_back(agg_packet);
            }*/

            it = receiving_buffer.erase(it); // Remove the item

        } else if (it->second.decoded_or_not == "Non_decoded") {

            // PACKET LOSS DUE TO INTERFERENCE
            non_decoded_packets_statistics.push_back(it->first);

            it = receiving_buffer.erase(it);
        } else {
            ++it; // Move to the next item
        }
    }
}


