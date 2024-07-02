#include "traffic.h"
#include "../external/json/include/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

void Traffic::initialize() {

    std::ifstream i("../topology/topology.json");
    json j;
    i >> j;

    life_time = j["life_time"];
    rate = j["load"];
    norm_load = j["load"];
    net_case = j["case"];
    level = j["level"];
    rate_prd = j["rate_prd"];
    max_sf = j["max_sf"];
    rate = rate / ((toa(15, max_sf) * rate_prd) + duty_cycle((toa(15, max_sf) * rate_prd)));
    protocol_used = j["prt"];
    auto nodes_info = j["nodes"];
    auto gateways_info = j["gateways"];

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
        node = new Node(id, x, y, z, sf, channel, transmission_p, rate, assigned_node, following, type);
        nodes.push_back(*node);
    }

    // Gateways initialization
    for (const auto &gw: gateways_info) {
        int id = gw["id"];
        int x = gw["x"];
        int y = gw["y"];
        int z = gw["z"];

        Gateway *gateway;
        gateway = new Gateway(id, x, y, z, -1, -1, 25, -1, -1, -1, -1);
        gateways.push_back(*gateway);
    }
}

void Traffic::run() {
    vector<Packet> packets;

    for (int time = 0; time < life_time; time++) {

        // PACKETS ON AIR
        auto packet_to_receive = environment.getPackets();

        // Transmitting - Sleeping - LoRaWAN nodes
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
            if (state == "SLEEP") {
            }
        }

        // Receiving Current Packets on air - Gateways
        for (auto &gateway: gateways) {
            gateway.clock(time);
            gateway.receive(packet_to_receive);
        }

        // Decreasing time over air and remove timed out packets from radio
        environment.time_over_air_handling();

    }
}


int main() {

    /*int sf = 9;
    int distance = 9000;
    int transmission_p = 20;
    double receive_power = calculate_received_power(distance, transmission_p);
    cout << "received power : " << receive_power << endl;
    cout << "calculated snr :  " << calculate_snr(receive_power, -(130.0+2.5)) << endl;
    cout << "snr Limit : " << snr_limit(sf) + 10 << endl;
    cout << "If positive, could be decoded : " << calculate_snr(receive_power, -(130.0+2.5)) - (snr_limit(sf) + 10) << endl; */
    Traffic traffic;
    traffic.initialize();
    traffic.run();
}