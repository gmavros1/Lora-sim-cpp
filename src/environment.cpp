//
// Created by gmavros-yoga-7 on 28/10/2023.
//

#include "environment.h"
//#include "packet.h"
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

vector<radio_packet> Environment::getPackets() {
    return packets;
}

void Environment::time_over_air_handling() {
    for (int index = packets.size() - 1; index >= 0; --index) {
        if (packets[index].packet.getSeqNum() > 0) {
            packets[index].packet.decrease_seq_num();
        } else {
            packets.erase(packets.begin() + index);
        }
    }

    // In fact they will remain at least for 8 ms.
    // But we handle that (simulate) with timer inside the node
    // If node catch the first segments of wur its ok
    for (int index = wake_up_radios.size() - 1; index >= 0; --index) {
        wake_up_radios.erase(wake_up_radios.begin() + index);
    }

}

void Environment::add_wur_signal(int dst, int channel, coordinates location) {
    static wake_up_radio inserted_radio;

    inserted_radio.dst = dst;
    inserted_radio.channel = channel;
    inserted_radio.location = location;

    wake_up_radios.push_back(inserted_radio);

}

vector<wake_up_radio> Environment::get_wurs() {
    return wake_up_radios;
}
