#include "node.h"

Node::Node(int id, int x, int y, int z) : buffered_packet(Packet(-1, -1, -1)) {
    this->nodeId = id;
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->bandwidth = 125;
    this->channel = to_string(id % (8 + 1));
    this->sf = 7;
    this->transmission_power = 25;
}

void Node::generatePacket(int destination, int time) {
    buffered_packet = Packet(nodeId, destination, time);
}

Packet Node::transmitPacket() {
    if (buffered_packet.getPacketId() != "node-1to-1at-1") {
        Packet packet_to_send = buffered_packet;
        buffered_packet = Packet(-1, -1, -1);
        return packet_to_send;
    }

}

void Node::receivePacket(Packet &packet) {
    // Implement reception logic here
}

void Node::tick(int time) {
    environment_time += 1;
}


/************************/
/* GETTERS AND SETTERS */
/************************/


int Node::getNodeId() const {
    return nodeId;
}

void Node::setNodeId(int nodeId) {
    Node::nodeId = nodeId;
}

int Node::getSf() const {
    return sf;
}

void Node::setSf(int sf) {
    Node::sf = sf;
}

const string &Node::getChannel() const {
    return channel;
}

void Node::setChannel(const string &channel) {
    Node::channel = channel;
}

int Node::getBandwidth() const {
    return bandwidth;
}

void Node::setBandwidth(int bandwidth) {
    Node::bandwidth = bandwidth;
}

int Node::getTransmissionPower() const {
    return transmission_power;
}

void Node::setTransmissionPower(int transmissionPower) {
    transmission_power = transmissionPower;
}

int Node::getState() const {
    return state;
}

void Node::setState(int state) {
    Node::state = state;
}

int Node::getDutyCycleRemain() const {
    return duty_cycle_remain;
}

void Node::setDutyCycleRemain(int dutyCycleRemain) {
    duty_cycle_remain = dutyCycleRemain;
}

int Node::getEnvironmentTime() const {
    return environment_time;
}

void Node::setEnvironmentTime(int environmentTime) {
    environment_time = environmentTime;
}

int Node::getToaRemain() const {
    return toa_remain;
}

void Node::setToaRemain(int toaRemain) {
    toa_remain = toaRemain;
}

int Node::getAssignedNode() const {
    return assigned_node;
}

void Node::setAssignedNode(int assignedNode) {
    assigned_node = assignedNode;
}

int Node::getFollowingNode() const {
    return following_node;
}

void Node::setFollowingNode(int followingNode) {
    following_node = followingNode;
}

const Position &Node::getPosition() const {
    return position;
}

void Node::setPosition(const Position &position) {
    Node::position = position;
}

const Packet &Node::getBufferedPacket() const {
    return buffered_packet;
}

void Node::setBufferedPacket(const Packet &bufferedPacket) {
    buffered_packet = bufferedPacket;
}
