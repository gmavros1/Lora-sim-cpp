//
// Created by gmavros-yoga-7 on 27/10/2023.
//

#include "traffic.h"
#include "iostream"
#include "../external/tqdm.cpp/include/tqdm/tqdm.h"

void Traffic::initialize() {

    // Nodes Initialization
    for (int i = 0; i < 3; ++i) {
        Node *node;
        node = new Node(i, 100, 200, 40, 7, 1, 25, 0.1);
        nodes.push_back(*node);
    }
}


void Traffic::run() {
    vector<Packet > packets;
    for (int time : tqdm::range(1000000)) {
        for (auto & node : nodes) {
            node.clock(time);
            string state = node.node_driver();

            if (state == "Packet Generation") {
                node.generate_packet(8);
            }
            if (state == "Transmitting") {
                Packet* transmitted_packet = node.transmit_packet();
                if (transmitted_packet != nullptr) {
                    environment.add_packet(*transmitted_packet, node.getChannel(), node.getSf());
                }
            }
            if (state == "Sleeping") {
            }
        }

        // Receiving
        auto packet_to_receive = environment.getPackets();


        // Decreasing time over air and remove timed out packets from radio
        environment.time_over_air_handling();

    }

}

int main() {

    Traffic traffic;
    traffic.initialize();
    traffic.run();

}