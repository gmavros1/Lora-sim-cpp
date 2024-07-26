//
// Created by gmavros-yoga-7 on 30/6/2024.
//

#ifndef LORA_SIM_CPP_DEVICE_H
#define LORA_SIM_CPP_DEVICE_H

#include "utils.h"
#include "packet.h"
#include <bits/stdc++.h>
#include <vector>

struct rec_powers{
        double packet_rec_power;
        double maximum_interference_power;
        bool able_to_decode;
};

struct packets_receiving{
    string id;
    Packet packet = *new Packet(-1, -1, -1, -1, -1, -1, -1);
    int sf;
    int channel;
    vector<rec_powers> segments_received;
    string decoded_or_not;
};

struct radio_packet{
        int transmission_power = 0;
        double receive_power = 0;
        int sf = 0;
        int channel = 0;
        coordinates location;
        Packet packet = *new Packet(-1, -1, -1, -1, -1, -1, -1);
};

class Device {

public:
    Device(int id, int x, int y, int z, int sf, int channel, int transmission_power, double packet_gen_prob, int assigned_node, int following, int type);

    void generate_packet();
    Packet* transmit_packet();
    void receive(vector<radio_packet> &packets_received);

    void clock(int time);
    coordinates getLocation();

    int getId();
    int getChannel();
    int getSf();

    int getTrasmissionPower();

    int generated_packets; // Statistics
    int received_packets;
    vector<string> decoded_packets_statistics; // Just metrics
    vector<string> non_decoded_packets_statistics;
    vector<string> out_of_range_to_gw;
    vector<string> transmissions_to_gw;
    unordered_map<std::string, int> packetDelays;

    int calculate_toa();

protected:
    int id;
    int channel; // -1 if gateway
    int sf; // -1 if gateway
    int transmission_power;
    int environment_time;
    int bandwidth;
    coordinates location{};
    Packet *buffer;
    double packet_gen_prob;
    //std::string state;

public:
    int type;
    int assigned_node;
    int following;

public:
    map<string, packets_receiving> receiving_buffer;

};


#endif //LORA_SIM_CPP_DEVICE_H
