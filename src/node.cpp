#include "node.h"

Node::Node(int id, int x, int y, int z) : nodeId(id) {
    position.x = x;
    position.y = y;
    position.z = z;
}

Packet Node::generatePacket(int destination, int time) {
    return Packet(nodeId, destination, time);
}

void Node::transmitPacket(const Packet& packet) {
    // Implement transmission logic here
}

void Node::receivePacket(const Packet& packet) {
    // Implement reception logic here
}
