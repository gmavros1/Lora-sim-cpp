#include <string>
#include <vector>
#include "packet.h"

struct Position {
    int x;
    int y;
    int z;
};

class Node {
    private:
        int nodeId;
        int sf;
        int channel;
        int bandwidth;
        int transmission_power;
        int state;
        int duty_cycle_remain;
        int environment_time;
        int toa_remain;
        int assigned_node;
        int following_node;
        Position position;
        Packet buffer;

    public:
        Node(int id, int x, int y, int z, Packet buffer);
        void tick(int time);
        Packet generatePacket(int destination, int time) const;
        Packet transmitPacket(Packet packet);
        void receivePacket(const Packet& packet);

    Packet generatePacket(int destination, int time);
};
