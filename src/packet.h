#ifndef PACKET_H
#define PACKET_H

#include <string>

class Packet;
using namespace std;

class Packet {

private:
    string packetId;
    int src;
    int dst;
    int timestamp_start;
    int timestamp_end;
    int payload_bytes;
    int crc;
    int header;
    int seq_num_reversed;

public:
    Packet(int src, int dst, int timestamp, int payload_bytes = 15, int crc = 1, int header = 1);

    ~Packet() = default;

    Packet *aggregated_packet{};

    string getPacketId();

    int getDst() const;

    int getTimestamp_start() const;

    int getTimestamp_end() const;

    int getPayload_bytes() const;

    int getSeqNum() const;

    void setSeqNumReversed(int toa_remained);

    void decrease_seq_num();

    string calculateUniqueId() const;


};

#endif