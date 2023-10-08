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
        int seqnum;
        string start_end_flag;


    public:
        Packet(int src, int dst, int timestamp, int payload_bytes=15, int crc=1, int header=1);
        ~Packet(){};
        string getPacketId();
        int getDst();
        int getTimestamp_start();
        int getTimestamp_end();
        int getPayload_bytes();
        int getSeqnum();
        string getStart_end_flag();
        string calculateuniqueId();


};