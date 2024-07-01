#include "gateway.h"

Gateway::Gateway(int id, int x, int y, int z, int sf, int channel, int transmissionPower, double packetGenProb,
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

}