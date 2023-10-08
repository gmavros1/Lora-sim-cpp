#include "packet.h"

using namespace std;

// Define the constructor for the Packet class
Packet::Packet(int src, int dst, int timestamp, int payload_bytes, int crc, int header) {
    this->src = src;
    this->dst = dst;
    this->timestamp_start = timestamp;
    this->timestamp_end = 0;
    this->payload_bytes = payload_bytes;
    this->crc = crc;
    this->header = header;

    this->start_end_flag = "START";
    this->packetId = this->calculateuniqueId();
    this->seqnum = 0;
}

// Define the member functions for the Packet class
string Packet::getPacketId() {
    return this->packetId;
}

int Packet::getDst() {
    return this->dst;
}

int Packet::getTimestamp_start() {
    return this->timestamp_start;
}

int Packet::getTimestamp_end() {
    return this->timestamp_end;
}

int Packet::getPayload_bytes() {
    return this->payload_bytes;
}

int Packet::getSeqnum() {
    return this->seqnum;
}

string Packet::getStart_end_flag() {
    return this->start_end_flag;
}

string Packet::calculateuniqueId() {
    string result;
    result = "node" + to_string(this->src) + "to" + to_string(this->dst) + "at" + to_string(this->timestamp_start);
    return result;
}
