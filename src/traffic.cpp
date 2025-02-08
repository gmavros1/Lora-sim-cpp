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
    experiment_name = j["experiment_name"];
//    cout << "Level : " << level << endl;
//    cout << "Mean sf : " << mean_sf << endl;
//    cout << "Max sf : " << max_sf << endl;
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

//           cout << "Id : " << id << " | level : " << type << " | Assign node: " << assigned_node << endl;

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

                    // SEE IF WHILE TRANSMITTING THE DST DEVICE IS TRANSMITTING TOO -- METRICS ********************
                    for (auto &node_TEST: nodes_wur_extended){
                        Packet tr_p = *transmitted_packet;
                        if (node_TEST.getId() == tr_p.getDst() && (node_TEST.get_state()=="TRANSMIT" || node_TEST.get_state()=="SLEEP" ||
                            node_TEST.get_state()=="RECEIVE_WUR" || node_TEST.get_state()=="WAITING_TRANSMITTING_PACKET") ){
                            //cout << "MALAKIA "  << tr_p.getPacketId() << endl;
                            this->packet_drop_receiver_transmitOrSleep ++;
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

    // FAIRNESS
    // DEFINE DECODED PACKETS PER LEVEL --- FOR FAIRNESS -------------------------
    double fairness = 0.0;
    if (!nodes_wur_extended.empty()) // Means it is multihop
    {// Find maximum type
            int maxType = 0;
            for (const Node &nd: nodes_wur_extended) {
                if (maxType < nd.type)
                    maxType = nd.type;
            }
            // construct dict with key as type and initialize to zero
            map<int, int> receivedPerType;
            map<int, int> generatedPerType;
            for (int i = 0; i < maxType; ++i) {
                receivedPerType[i] = 0;
                generatedPerType[i] = 0;
            }
            // +1 in receivedPerType - id is the index of the string - iterate all received packets
            regex del("_");
            for (auto p: allDecodedPackets) {
                sregex_token_iterator it(p.begin(), p.end(), del, -1);
                int node_id = stoi(*(++it)); // id
                int type_of_node = nodes_wur_extended[node_id].type;
                receivedPerType[type_of_node] += 1;
            }
            // now iterate nodes to take all generated packets per type
            for (auto n: nodes_wur_extended) {
                generatedPerType[n.type] += n.generated_packets;
            }
            // ratio (received/generated) per type
            float ratioPerType[maxType + 1];
            for (int i = 0; i <= maxType; ++i) {
                ratioPerType[i] = static_cast<float>(receivedPerType[i]) / static_cast<float>(generatedPerType[i]);
            }
            // Calculate Fairness
            float sum_of_value_squared = 0;
            float sum_of_squared_value = 0;
            for (int i = 0; i <= maxType; ++i) {
                sum_of_value_squared += ratioPerType[i];
                sum_of_squared_value += (ratioPerType[i] * ratioPerType[i]);
            }
            sum_of_value_squared *= sum_of_value_squared;
            fairness = (sum_of_value_squared) / ((static_cast<float>(maxType + 1) * sum_of_squared_value));
    }

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

    // DELAY GROUPED BY TYPE
    std::ifstream nt("../topology/node_type.json");
    json j;
    nt >> j; // nd[node] = type

    // Find max Type
    int maxType = 0;
    for (int i = 0; i < nodes.size() + nodes_wur_extended.size(); ++i) {
        if (maxType < j[std::to_string(i)])
            maxType = j[std::to_string(i)];
    }

    map<int, double> DelayType;
    map<int, int> CountPacketPerType;
    for (int i = 0; i < maxType+1; ++i) {
        DelayType[i] = 0.0;
        CountPacketPerType[i] = 0;
    }
    regex del("_");
    for (const auto &pair: lowestDelays) {
        sregex_token_iterator it(pair.first.begin(), pair.first.end(), del, -1);
        int node_id = stoi(*(++it)); // id
        int node_type = j[std::to_string(node_id)];
        DelayType[node_type] += (pair.second * 1.0);
        CountPacketPerType[node_type] += 1;
    }

    // The mean for every type
    double mean_delays_per_type[maxType];
    for (int i = 0; i < maxType+1; ++i) {
        if (DelayType[i] != 0) {
            mean_delays_per_type[i] = DelayType[i] / (1.0 * CountPacketPerType[i]);
        } else{
            maxType --; // To not consider this to the last calculation
        }
    }

    // Delay calculation
    double mean_delay = 0.0;
    for (double d: mean_delays_per_type) {
        mean_delay += d;
    }
    mean_delay /= ((maxType+1) * 1.0);
//    cout << mean_delay << endl;

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

    int async_of_nodes_packet_drop = this->packet_drop_receiver_transmitOrSleep;

    int time_out_packets = generated_packets - decoded_packets_in_gateway - non_decoded_packets_in_gw_due_to_inference - non_decoded_packet_in_retransmissions - out_of_range_trans_to_nd - out_of_range_trans_to_gw - async_of_nodes_packet_drop;

    // CONSTANT METRICS
    int maximum_trans = life_time / (toa(15, 7) + duty_cycle(toa(15, 7)));
    int maximum_delay = toa(15, 12);

    // DEBUG NEGATIVE NUMBER OF OTHER DROPPED PACKETS
    set<std::string> result;
    set_intersection(allNonDecodedPackets_retrans.begin(), allNonDecodedPackets_retrans.end(), allNonDecodedPackets.begin(),
                     allNonDecodedPackets.end(),
                     inserter(result, result.begin()));

//    cout << endl << "INTERSECTION of two sets: " << endl;
//    for (std::string i : result)
//        cout << i << endl;
//
//    // PRINT RESULT FOR TESTING
//    cout << " GENERATED PACKETS OF ALL NODES : " << generated_packets << endl;
//    cout << " DECODED PACKETS IN GWs : " << decoded_packets_in_gateway << endl;
//    cout << " INTERFERENCE IN GATEWAY : " << non_decoded_packets_in_gw_due_to_inference << endl;
//    cout << " INTERFERENCE IN RETRANSMISSIONS : " << non_decoded_packet_in_retransmissions << endl;
//    //cout << " DELAY OF RECEIVED PACKETS : " << received_packet_delays_in_gw << endl;
//    cout << " OUT OF RANGE TRANSMISSION IN GW : " << out_of_range_trans_to_gw << endl;
//    cout << " OUT OF RANGE TRANSMISSION IN ND : " << out_of_range_trans_to_nd << endl;
//    cout << " RECEIVER NOT IN RECEIVING STATE : " << async_of_nodes_packet_drop << endl;
//    cout << " TIME OUT IN RECEIVING : " << time_out_packets << endl;

    // Create a file to write the combined strings
    string metrics_path = "../results/metrics/" + experiment_name +".txt";
    std::ofstream outFile(metrics_path, std::ios::app);

    // KEEP MAX SF WHEN USING MULTIHOP
    std::ifstream sf("../topology/node_sf.json");
    json jsf;
    sf >> jsf;

    int max_sf_previous = 0;
    for (int i = 0; i < nodes_wur_extended.size() + nodes.size(); ++i) {
        if (jsf[std::to_string(i)] > max_sf_previous)
            max_sf_previous = jsf[std::to_string(i)];
    }



    // CALCULATE MEAN POWER CONSUMPTION for every node
    double mean_power_consumption_per_node = 0l;
    for (Node_wur_extended &nd: nodes_wur_extended) {
        mean_power_consumption_per_node += nd.energy_consumed;
    }
    for (Node &nd: nodes) {
        mean_power_consumption_per_node += nd.energy_consumed;
    }

    mean_power_consumption_per_node /= (nodes_wur_extended.size() + nodes.size()) ;
    mean_power_consumption_per_node *= pow(10, -6); // Joules
    cout << "ec: " << mean_power_consumption_per_node  << endl;


    outFile << net_case << "," << norm_load << "," << decoded_packets_in_gateway << "," << non_decoded_packets_in_gw_due_to_inference
    << "," << nodes_wur.size() + nodes.size() + nodes_wur_extended.size() << "," << life_time << "," << maximum_trans << "," << generated_packets
    << "," << mean_delay << "," << maximum_delay << "," << non_decoded_packet_in_retransmissions
    << "," << out_of_range_trans_to_gw << "," << in_range_trans_to_gw << "," << max_sf_previous << "," << time_out_packets << "," << async_of_nodes_packet_drop << "," << fairness << "," << mean_power_consumption_per_node <<"\n";

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