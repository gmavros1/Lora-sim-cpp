#include "traffic.h"
#include "../external/json/include/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

void Traffic::initialize() {

    std::ifstream i("../topology/topology.json");
    json j;
    i >> j;

    life_time = j["life_time"];
    double rate_norm = j["load"]; // Normalized [0.1 , 1]
    norm_load = j["load"];
    net_case = j["case"];
    level = j["level"];
    mean_sf = j["mean_sf"];
    max_sf = j["max_sf"];
    cout << "Level : " << level << endl;
    cout << "Mean sf : " << mean_sf << endl;
    cout << "Max sf : " << max_sf << endl;
    // rate = rate / ((toa(15, max_sf) * rate_prd) + duty_cycle((toa(15, max_sf) * rate_prd)));
    rate = rate_norm / (toa(15, 7) + duty_cycle(toa(15, 7)));
    protocol_used = j["prt"];
    auto nodes_info = j["nodes"];
    auto gateways_info = j["gateways"];

    // cout << rate << " " << rate_prd << endl;

    if (protocol_used == "Multihop") {

        // Multi-hop Nodes initialization
        // Nodes Initialization
        for (const auto &nd: nodes_info) {
            int id = nd["id"];
            int channel = nd["channel"];
            int sf = nd["sf"];
            int transmission_p = nd["transmission_p"];
            int x = nd["x"];
            int y = nd["y"];
            int z = nd["z"];
            int type = nd["type"];
            int assigned_node = nd["assigned_node"];
            int following = nd["following"];

           cout << "Id : " << id << " | level : " << type << " | Assign node: " << assigned_node << endl;

            Node_wur_extended *node;
            node = new Node_wur_extended(id, x, y, z, sf, channel, transmission_p, rate, assigned_node, following, type, level);
            nodes_wur_extended.push_back(*node);
        }
    } else {

        // Nodes Initialization
        for (const auto &nd: nodes_info) {

            int id = nd["id"];
            int channel = nd["channel"];
            int sf = nd["sf"];
            int transmission_p = nd["transmission_p"];
            int x = nd["x"];
            int y = nd["y"];
            int z = nd["z"];
            int type = nd["type"];
            int assigned_node = nd["assigned_node"];
            int following = nd["following"];

            Node *node;
            node = new Node(id, x, y, z, sf, channel, transmission_p, rate, assigned_node, following, type, level);
            nodes.push_back(*node);
        }
    }

    // Gateways initialization
    for (const auto &gw: gateways_info) {
        int id = gw["id"];
        int x = gw["x"];
        int y = gw["y"];
        int z = gw["z"];

        Gateway *gateway;
        id = -id;
        gateway = new Gateway(id, x, y, z, -1, -1, 25, -1, -1, -1, -1, -1);
        gateways.push_back(*gateway);
    }

    //cout << endl;
    //cout << "Nodes " << nodes.size() << endl;
    //cout << "Nodes wur " << nodes_wur.size() << endl;
    //cout << "Gateways " << gateways.size() << endl;
    //cout << endl;
}

/*void Traffic::run_Multihop() {
    vector<Packet> packets;

    for (int time = 0; time < life_time; time++) {

        // PACKETS ON AIR
        auto packet_to_receive = environment.getPackets();
        auto wake_up_radio_to_receive = environment.get_wurs();

        // GET STATE FOR MULTI-HOP NODES ****************************
        for (auto &node: nodes_wur){
            node.clock(time);
            string state = node.protocol();
            if (state!="SLEEP")
            cout << "Node " << node.getId() << " " << state << " at " << time << endl;
        }

        // MULTI-HOP RECEIVING STUFF ****************************
        for (auto &node: nodes_wur) {

            if (node.get_state() == "RECEIVE") {
                node.receive(packet_to_receive);
                continue;
            }

            if (node.get_state() == "RECEIVE_WUR") {
                continue;
            }
        }

        // Receiving Current Packets on air - GATEWAYS
        for (auto &gateway: gateways) {
            gateway.clock(time);
            gateway.receive(packet_to_receive);
        }

        // MULTI-HOP SENDING STUFF ****************************
        for (auto &node: nodes_wur) {

            if (node.get_state() == "SLEEP") {
                node.receive_wur(wake_up_radio_to_receive);
                continue;
            }
            if (node.get_state() == "TRANSMIT") {
                Packet *transmitted_packet = node.transmit_packet();
                if (transmitted_packet != nullptr) {
                    environment.add_packet(*transmitted_packet, node.getChannel(), node.getSf(),
                                           node.getTrasmissionPower(), node.getLocation());

                    packet_to_receive = environment.getPackets();
                }
                continue;
            }
            if (node.get_state() == "SEND_WUR") {
                Node_wur::wake_up_radio *transmitted_wur = node.send_wur();
                if (transmitted_wur != nullptr) {
                    environment.add_wur_signal(transmitted_wur->dst, transmitted_wur->channel,
                                                time,transmitted_wur->location);

                    wake_up_radio_to_receive = environment.get_wurs();
                }
                continue;
            }
        }

        // Decreasing time over air and remove timed out packets from radio
        environment.time_over_air_handling(time);

    }
}*/

void Traffic::run_Multihop_extended() {
    vector<Packet> packets;

    for (int time = 0; time < life_time; time++) {

        //cout << endl;

        // PACKETS ON AIR
        auto packet_to_receive = environment.getPackets();
        auto wake_up_radio_to_receive = environment.get_wurs();

        // GET STATE FOR MULTI-HOP NODES ****************************
        for (auto &node: nodes_wur_extended){
            node.clock(time);
            string state = node.protocol();

//            if (node.getId() == 4 && time >= 33800 && time <= 34200){
//                cout << "Node " << node.getId() << " " << state << " at " << time << " HAS "
//                     << node.receiving_buffer.size() << " SEGMENTS" << endl;
//            }

        }

        // MULTI-HOP RECEIVING STUFF ****************************
        for (auto &node: nodes_wur_extended) {

            if (node.get_state() == "RECEIVE") {
                node.receive(packet_to_receive);
                continue;
            }

            if (node.get_state() == "RECEIVING_PACKET_AND_TRANSMITTING_WUR") {
                node.receive(packet_to_receive);

                Node_wur_extended::wake_up_radio *transmitted_wur = node.send_wur();
                if (transmitted_wur != nullptr) {
                    environment.add_wur_signal(transmitted_wur->dst, transmitted_wur->channel,
                                               time,transmitted_wur->location);

                    wake_up_radio_to_receive = environment.get_wurs();
                }

                continue;
            }

            if (node.get_state() == "WAITING_RECEIVING_PACKET") {
                node.receive(packet_to_receive);
                continue;
            }


            if (node.get_state() == "RECEIVE_WUR") {
                continue;
            }
        }

        // Receiving Current Packets on air - GATEWAYS
        for (auto &gateway: gateways) {
            gateway.clock(time);
            gateway.receive(packet_to_receive);
        }

        // MULTI-HOP SENDING STUFF ****************************
        for (auto &node: nodes_wur_extended) {

            if (node.get_state() == "SLEEP") {

                node.receive_wur(wake_up_radio_to_receive);
                continue;
            }

            if (node.get_state() == "TRANSMIT") {
                Packet *transmitted_packet = node.transmit_packet();
                if (transmitted_packet != nullptr) {
                    environment.add_packet(*transmitted_packet, node.getChannel(), node.getSf(),
                                           node.getTrasmissionPower(), node.getLocation());

                    packet_to_receive = environment.getPackets();

                    // SEE IF WHILE TRANSMITTING THE DST DEVICE IS TRANSMITTING TOO
                    for (auto &node_TEST: nodes_wur_extended){
                        Packet tr_p = *transmitted_packet;
                        if (node_TEST.getId() == tr_p.getDst() && (node_TEST.get_state()=="TRANSMIT" || node_TEST.get_state()=="SLEEP") ){
                            cout << "MALAKIA "  << tr_p.getPacketId() << endl;
                        }
                    }

                }

                continue;
            }

            if (node.get_state() == "SEND_WUR") {
                Node_wur_extended::wake_up_radio *transmitted_wur = node.send_wur();
                if (transmitted_wur != nullptr) {
                    environment.add_wur_signal(transmitted_wur->dst, transmitted_wur->channel,
                                               time,transmitted_wur->location);

                    wake_up_radio_to_receive = environment.get_wurs();
                }
                continue;
            }

            if (node.get_state() == "WAITING_TRANSMITTING_PACKET") {

                // DEBUGGING
//                if (node.wur_timer_block_transmit <= 1){
//                    if (nodes_wur_extended[node.assigned_node].get_state() != "WAITING_RECEIVING_PACKET" && nodes_wur_extended[node.assigned_node].get_state() != "RECEIVING" && nodes_wur_extended[node.assigned_node].get_state() != "RECEIVING_PACKET_AND_TRANSMITTING_WUR"){
//                        cout << "BLOCKED : " << nodes_wur_extended[node.assigned_node].get_state() << endl;
//                        cout << nodes_wur_extended[node.assigned_node].wur_timer << endl;
//                        this->other_reasons ++;
//                    }
//                }

                continue;
            }

        }

        // Decreasing time over air and remove timed out packets from radio
        environment.time_over_air_handling(time);

    }
}


void Traffic::run_LoRaWAN() {
    vector<Packet> packets;

    for (int time = 0; time < life_time; time++) {

        // PACKETS ON AIR
        auto packet_to_receive = environment.getPackets();
        auto wake_up_radio_to_receive = environment.get_wurs();

        // Transmitting - Sleeping - LoRaWAN NODES ****************************
        for (auto &node: nodes) {
            node.clock(time);
            string state = node.LoRaWan();

            if (state == "TRANSMIT") {
                Packet *transmitted_packet = node.transmit_packet();
                if (transmitted_packet != nullptr) {
                    environment.add_packet(*transmitted_packet, node.getChannel(), node.getSf(),
                                           node.getTrasmissionPower(), node.getLocation());
                }
            }
        }
        // Transmitting - Sleeping - LoRaWAN NODES ****************************        // Transmitting - Sleeping - LoRaWAN NODES ****************************




        // Receiving Current Packets on air - GATEWAYS
        for (auto &gateway: gateways) {
            gateway.clock(time);
            gateway.receive(packet_to_receive);
        }

        // Decreasing time over air and remove timed out packets from radio
        environment.time_over_air_handling(time);

    }
}

void Traffic::metrics() {
    unsigned long generated_packets, decoded_packets_in_gateway, non_decoded_packets_in_gw_due_to_inference,
    non_decoded_packet_in_retransmissions, received_packet_delays_in_gw, out_of_range_trans_to_gw, in_range_trans_to_gw,
    out_of_range_trans_to_nd;

    // GENERATED PACKETS OF ALL NODES
    generated_packets = 0;
    for (const Node &nd: nodes) {
        generated_packets += nd.generated_packets;
    }
    for (const Node &nd: nodes_wur) {
        generated_packets += nd.generated_packets;
    }

    for (const Node &nd: nodes_wur_extended) {
        generated_packets += nd.generated_packets;
    }

    // DECODED PACKETS IN GWs
    std::set<std::string> allDecodedPackets;
    for (const Gateway &gateway: gateways) {
        for (auto packet: gateway.decoded_packets_statistics) {
            allDecodedPackets.insert(packet);
        }
    }
    decoded_packets_in_gateway = allDecodedPackets.size();

    // INTERFERENCE IN GATEWAY
    std::set<std::string> allNonDecodedPackets;
    for (const Gateway &gateway: gateways) {
        for (auto packet: gateway.non_decoded_packets_statistics) {
            allNonDecodedPackets.insert(packet);
        }
    }
    non_decoded_packets_in_gw_due_to_inference = allNonDecodedPackets.size();

    // INTERFERENCE IN RETRANSMISSIONS
    std::set<std::string> allNonDecodedPackets_retrans;
    for (const Node_wur &nd_wr: nodes_wur) {
        for (auto packet: nd_wr.non_decoded_packets_statistics) {
            allNonDecodedPackets_retrans.insert(packet);
        }
    }
    for (const Node_wur_extended &nd_wr_extended: nodes_wur_extended) {
        for (auto packet: nd_wr_extended.non_decoded_packets_statistics) {
            allNonDecodedPackets_retrans.insert(packet);
        }
    }

    non_decoded_packet_in_retransmissions = allNonDecodedPackets_retrans.size();


    // DELAY OF RECEIVED PACKETS
    unordered_map<std::string, int> lowestDelays;
    for (const auto &gateway: gateways) {
        // Iterate over each packet delay in the gateway
        for (const auto &packetDelay: gateway.packetDelays) {
            const std::string &packetId = packetDelay.first;
            int delay = packetDelay.second;

            // Check if this packet ID has been encountered before
            auto search = lowestDelays.find(packetId);
            if (search != lowestDelays.end()) {
                // If the current delay is lower, update it in the map
                if (delay < search->second) {
                    search->second = delay;
                }
            } else {
                // If this packet ID has not been encountered, add it to the map
                lowestDelays[packetId] = delay;
            }
        }
    }
    received_packet_delays_in_gw = 0;
    for (const auto &pair: lowestDelays) {
        received_packet_delays_in_gw += pair.second;
    }

    // OUT OF RANGE TRANSMISSIONS IN GATEWAY
    std::set<std::string> allOutOfRangePackets;
    for (const Gateway &gateway: gateways) {
        for (auto packet: gateway.out_of_range_to_gw) {
            allOutOfRangePackets.insert(packet);
        }
    }
    out_of_range_trans_to_gw = allOutOfRangePackets.size();

    // OUT OF RANGE TRANSMISSIONS IN NODES
    std::set<std::string> allOutOfRangePackets_nd;
    for (const Node_wur_extended &nd_wr_extended: nodes_wur_extended) {
        for (auto packet: nd_wr_extended.out_of_range_to_nd) {
            allOutOfRangePackets_nd.insert(packet);
        }
    }
    out_of_range_trans_to_nd = allOutOfRangePackets_nd.size();

    // IN RANGE TRANSMISSIONS TO GATEWAY
    std::set<std::string> allINRangePackets;
    for (const Gateway &gateway: gateways) {
        for (auto packet: gateway.transmissions_to_gw) {
            allINRangePackets.insert(packet);
        }
    }
    in_range_trans_to_gw = allINRangePackets.size();

    // CONSTANT METRICS
    int maximum_trans = life_time / (toa(15, 7) + duty_cycle(toa(15, 7)));
    int maximum_delay = toa(15, 12);

    // NUMBER OF PACKETS DROPPED FROM OTHER REASONS
    int other_reasons = generated_packets - decoded_packets_in_gateway - non_decoded_packets_in_gw_due_to_inference - non_decoded_packet_in_retransmissions - out_of_range_trans_to_nd - out_of_range_trans_to_gw;
    //    if (other_reasons  < 0){
    //        other_reasons = 0;
    //    }

    // DEBUG NEGATIVE NUMBER OF OTHER DROPPED PACKETS
    set<std::string> result;
    set_intersection(allNonDecodedPackets_retrans.begin(), allNonDecodedPackets_retrans.end(), allNonDecodedPackets.begin(),
                     allNonDecodedPackets.end(),
                     inserter(result, result.begin()));

    cout << endl << "INTERSECTION of two sets: " << endl;
    for (std::string i : result)
        cout << i << endl;

    // PRINT RESULT FOR TESTING
    cout << " GENERATED PACKETS OF ALL NODES : " << generated_packets << endl;
    cout << " DECODED PACKETS IN GWs : " << decoded_packets_in_gateway << endl;
    cout << " INTERFERENCE IN GATEWAY : " << non_decoded_packets_in_gw_due_to_inference << endl;
    cout << " INTERFERENCE IN RETRANSMISSIONS : " << non_decoded_packet_in_retransmissions << endl;
    //cout << " DELAY OF RECEIVED PACKETS : " << received_packet_delays_in_gw << endl;
    cout << " OUT OF RANGE TRANSMISSION IN GW : " << out_of_range_trans_to_gw << endl;
    cout << " OUT OF RANGE TRANSMISSION IN ND : " << out_of_range_trans_to_nd << endl;
    cout << " OTHER REASONS : " << other_reasons << endl;

    // Create a file to write the combined strings
    std::ofstream outFile("../results/metrics.txt", std::ios::app);

    outFile << net_case << "," << norm_load << "," << decoded_packets_in_gateway << "," << non_decoded_packets_in_gw_due_to_inference
    << "," << nodes_wur.size() + nodes.size() + nodes_wur_extended.size() << "," << life_time << "," << maximum_trans << "," << generated_packets
    << "," << received_packet_delays_in_gw << "," << maximum_delay << "," << non_decoded_packet_in_retransmissions
    << "," << out_of_range_trans_to_gw << "," << in_range_trans_to_gw << "," << int(max_sf) << "," << other_reasons <<"\n";

}


int main() {

    Traffic traffic;
    traffic.initialize();

    if (traffic.protocol_used == "Multihop"){
        traffic.run_Multihop_extended();
    } else{
        traffic.run_LoRaWAN();
    }

    traffic.metrics();
}