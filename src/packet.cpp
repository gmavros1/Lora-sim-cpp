#include "packet.h"
#include <iostream>


// Define the constructor for the Packet class
Packet::Packet(int src, int dst, int timestamp, int payload_bytes, int crc, int header) {
    this->src = src;
    this->dst = dst;
    this->timestamp_start = timestamp;
    this->packetId = this->calculateUniqueId();
    this->timestamp_end = 0;
    this->payload_bytes = payload_bytes;
    this->crc = crc;
    this->header = header;
    this->seq_num_reversed = 0;
    this->aggregated_packet = nullptr;
}

// Define the member functions for the Packet class
string Packet::getPacketId() {
    return this->packetId;
}

int Packet::getDst() const {
    return this->dst;
}

int Packet::getTimestamp_start() const {
    return this->timestamp_start;
}

int Packet::getTimestamp_end() const {
    return this->timestamp_end;
}

int Packet::getPayload_bytes() const {
    return this->payload_bytes;
}

int Packet::getSeqNum() const {
    return this->seq_num_reversed;
}

string Packet::calculateUniqueId() const {
    string result;
    result = "node" + to_string(this->src) + "to" + to_string(this->dst) + "at" + to_string(this->timestamp_start);
    return result;
}

void Packet::setSeqNumReversed(int toa_remained) {
    this->seq_num_reversed = toa_remained;
}

void Packet::decrease_seq_num() {
    if (this->seq_num_reversed > 0) {
        this->seq_num_reversed -= 1;
    }
}

/*int main() {

    Packet packet(1, 4, 6);
    cout << packet.getPacketId() << endl;
    return 0;
}*/