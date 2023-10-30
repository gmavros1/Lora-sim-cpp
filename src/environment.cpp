//
// Created by gmavros-yoga-7 on 28/10/2023.
//

#include "environment.h"
#include "packet.h"
#include "iostream"


using namespace std;

Environment::Environment() = default;

void Environment::add_packet(Packet packet, int channel, int sf, int transmission_power, coordinates location) {
    radio_packet packet_on_air;
    packet_on_air.packet = packet;
    packet_on_air.channel = channel;
    packet_on_air.sf = sf;
    packet_on_air.transmission_power = transmission_power;
    packet_on_air.location = location;

    packets.push_back(packet_on_air);

}

vector<radio_packet > Environment::getPackets() {
    return packets;
}

void Environment::time_over_air_handling(){
    for (int index = 0; index < packets.size(); ++index) {
        if (packets[index].packet.getSeqNum() > 0) {
            packets[index].packet.decrease_seq_num();
        } else {
            packets.erase(packets.begin() + index);
        }
    }

}