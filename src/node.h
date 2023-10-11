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
public:
    int getNodeId() const;

private:
    string channel;
    int bandwidth;
    int transmission_power;
    int state;
    int duty_cycle_remain;
    int environment_time;
    int toa_remain;
    int assigned_node;
    int following_node;
    Position position;
    Packet buffered_packet;
public:

    Node(int id, int x, int y, int z);

    void tick(int time);

    void generatePacket(int destination, int time);

    Packet transmitPacket();

    void receivePacket(Packet &packet);

    void setNodeId(int nodeId);

    int getSf() const;

    void setSf(int sf);

    const string &getChannel() const;

    void setChannel(const string &channel);

    int getBandwidth() const;

    void setBandwidth(int bandwidth);

    int getTransmissionPower() const;

    void setTransmissionPower(int transmissionPower);

    int getState() const;

    void setState(int state);

    int getDutyCycleRemain() const;

    void setDutyCycleRemain(int dutyCycleRemain);

    int getEnvironmentTime() const;

    void setEnvironmentTime(int environmentTime);

    int getToaRemain() const;

    void setToaRemain(int toaRemain);

    int getAssignedNode() const;

    void setAssignedNode(int assignedNode);

    int getFollowingNode() const;

    void setFollowingNode(int followingNode);

    const Position &getPosition() const;

    void setPosition(const Position &position);

    const Packet &getBufferedPacket() const;

    void setBufferedPacket(const Packet &bufferedPacket);


};
