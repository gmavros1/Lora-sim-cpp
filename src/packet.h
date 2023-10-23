#ifndef PACKET_H
#define PACKET_H

#include <string>
using namespace std;

class Packet{

    private:
        string packetId;
        int src;
        int dst;
        int timestamp_start;
        int timestamp_end;
        int payload_bytes;
        int crc;
        int header;
        string start_end_flag;
        int seq_num;

    public:
        Packet(int src, int dst, int timestamp, int payload_bytes=15, int crc=1, int header=1);
        ~Packet()= default;
        Packet* aggregated_packet{};
        string getPacketId();
        int getDst() const;
        int getTimestamp_start() const;
        int getTimestamp_end() const;
        int getPayload_bytes() const;
        int getSeqNum() const;
        string getStart_end_flag();
        string calculateUniqueId() const;


};
#endif