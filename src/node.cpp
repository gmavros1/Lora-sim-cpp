#include "node.h"

Node::Node(int id, int x, int y, int z, Packet buffer) : nodeId(id), buffer(buffer) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->buffer = buffer;
}

Packet Node::generatePacket(int destination, int time){
    return Packet(nodeId, destination, time);
}

Packet Node::transmitPacket(Packet packet) {
    if (buffer.getPacketId() != "node-1to-1at-1"){
        return buffer;
    }

}

void Node::receivePacket(const Packet& packet) {
    // Implement reception logic here
}

void Node::tick(int time) {

}
