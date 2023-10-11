//
// Created by gmavros-yoga-7 on 11/10/2023.
//

#include "traffic.h"

traffic::traffic(int node_number, int duration) {
    time = duration;
    for (int i = 0; i < node_number; ++i) {
        Node node = *new Node(i, rand()%100, rand()%100, rand()%40);
        dataSet.insert(dataSet.begin(), node);
    }
}

void traffic::run() {
    for (int slot = 0; slot < getTime(); ++slot) {
        printf("ds");
    }
}

const list<Node> &traffic::getDataSet() const {
    return dataSet;
}

void traffic::setDataSet(const list<Node> &dataSet) {
    traffic::dataSet = dataSet;
}

/************************/
/* GETTERS AND SETTERS */
/************************/

int traffic::getTime(){
    return time;
}


