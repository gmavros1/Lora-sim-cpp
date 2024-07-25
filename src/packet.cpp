#include "packet.h"

// Define the constructor for the Packet class
Packet::Packet(int src, int dst, int timestamp, int src_level,int payload_bytes, int crc, int header) {
    this->src = src;
    this->dst = dst;
    this->timestamp_start = timestamp;
    this->packetId = this->calculateUniqueId();
    this->timestamp_end = 0;
    this->payload_bytes = payload_bytes;
    this->crc = crc;
    this->header = header;
    this->seq_num_reversed = 0;
    this->number_of_segments = 0;
    this->aggregated_packet = nullptr;
    this->src_level = src_level;
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
    // And define also the number of segments
    this->number_of_segments = toa_remained;
}

void Packet::decrease_seq_num() {
    if (this->seq_num_reversed > 0) {
        this->seq_num_reversed -= 1;
    }
}

int Packet::getNumber0fSegments() {
    return number_of_segments;
}

int Packet::getSrc() const {
    return src;
}

void Packet::setTimestamp_end(int timestamp) {
    timestamp_end = timestamp;
}

int Packet::getSrcLevel() {
    return this->src_level;
}


