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
    Position position;

public:
    Node(int id, int x, int y, int z);
    Packet generatePacket(int destination, int time);
    void transmitPacket(const Packet& packet);
    void receivePacket(const Packet& packet);
};
