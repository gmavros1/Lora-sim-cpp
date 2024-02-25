//
// Created by gmavros-yoga-7 on 27/10/2023.
//

#include "traffic.h"
#include "node.h"
#include "gateway.h"
#include "environment.h"
#include "packet.h"
#include "../external/json/include/nlohmann/json.hpp"
#include <fstream>
#include "iostream"
#include "../external/tqdm.cpp/include/tqdm/tqdm.h"
#include "utils.h"

using json = nlohmann::json;

void Traffic::initialize() {

    std::ifstream i("../topology/topology.json");
    json j;
    i >> j;

    life_time = j["life_time"];
    rate = j["load"];
    net_case = j["case"];
    rate = rate / (toa(15, 7) + duty_cycle(toa(15, 7)));
    auto nodes_info = j["nodes"];
    auto gateways_info = j["gateways"];

    // Nodes Initialization
    for (const auto& nd : nodes_info) {
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

        if (type == 0) {
            Node *node;
            node = new Node(id, x, y, z, sf, channel, transmission_p, rate, assigned_node, following, type);
            nodes.push_back(*node);
        } else {
            MultihopNode *middle_node;
            middle_node = new MultihopNode(id, x, y, z, sf, channel, transmission_p, rate, assigned_node, following, type);
            middle_nodes.push_back(*middle_node);
        }

    }

    // Gateways initialization
    for (const auto& gw : gateways_info) {
        int id = gw["id"];
        int x = gw["x"];
        int y = gw["y"];
        int z = gw["z"];

        // cout << "id" << id << "x" << x << "y" << y << "z" << z << endl;

        Gateway *gateway;
        gateway = new Gateway(id, x, y, z);
        gateways.push_back(*gateway);
    }

}

void Traffic::put_metrics_in_file() {
    std::set<std::string> allDecodedPackets;
    for (const Gateway& gateway : gateways) {
        for (auto packet: gateway.decoded_packets_statistics){
            allDecodedPackets.insert(packet);
        }
    }
    int num_decoded = allDecodedPackets.size();

    std::set<std::string> allNonDecodedPackets;
    for (const Gateway& gateway : gateways) {
        for (auto packet: gateway.non_decoded_packets_statistics){
            allNonDecodedPackets.insert(packet);
        }
    }
    int num_non_decoded = allNonDecodedPackets.size();

    // Create a file to write the combined strings
    std::ofstream outFile("../results/metrics.txt", std::ios::app);

    double normalized_rate = rate * (toa(15, 7), duty_cycle(toa(15, 7)));

    double maximum_tr;
    maximum_tr = life_time / (toa(15, 7) + duty_cycle(toa(15, 7)));

    int nodes_number;
    nodes_number = nodes.size();

    outFile << net_case << "," << normalized_rate << "," << num_decoded << "," << num_non_decoded << "," << nodes_number << "," << life_time << "," << maximum_tr <<"\n";

    // Close the file
    outFile.close();
}


void Traffic::run() {
    vector<Packet > packets;
    for (int time=0; time < life_time; time ++) {

        // Receiving Current Packets on air
        auto packet_to_receive = environment.getPackets();
        for (auto & gateway: gateways) {
            gateway.clock(time);
            gateway.receive(packet_to_receive);
        }

        // Receiving Sleeping Transmitting
        for (auto & node : middle_nodes) {
            node.clock(time);
            string state = node.multiNode_driver();
            if (state == "Transmitting") {
                Packet* transmitted_packet = node.transmit_packet();
                if (transmitted_packet != nullptr) {
                    environment.add_packet(*transmitted_packet, node.getChannel(), node.getSf(), node.getTrasmissionPower(), node.getLocation());
                }
            }
            // Wake up receivers, so it listen always
            if (state == "Sleeping") {
                node.receive_node(packet_to_receive);
            }
        }

        // Transmitting - Sleeping
        for (auto & node : nodes) {
            node.clock(time);
            string state = node.node_driver();

            if (state == "Packet Generation") {
                node.generate_packet();
            }
            if (state == "Transmitting") {
                Packet* transmitted_packet = node.transmit_packet();
                if (transmitted_packet != nullptr) {
                    environment.add_packet(*transmitted_packet, node.getChannel(), node.getSf(), node.getTrasmissionPower(), node.getLocation());
                }
            }
            if (state == "Sleeping") {
            }
        }

        // Decreasing time over air and remove timed out packets from radio
        environment.time_over_air_handling();

    }

    // Push metrics in file
    put_metrics_in_file();

}

int main() {

    Traffic traffic;
    traffic.initialize();
    traffic.run();

}