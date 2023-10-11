//
// Created by gmavros-yoga-7 on 11/10/2023.
//

#ifndef LORA_SIM_CPP_TRAFFIC_H
#define LORA_SIM_CPP_TRAFFIC_H

#include "node.h"
#include <list>

class traffic {
public:
    const list<Node> &getDataSet() const;

    void setDataSet(const list<Node> &dataSet);

private:
    std::list<Node> dataSet;

public:
    int getTime();
    void setTime(int time);

private:
    int time;

public:
    traffic(int node_number, int duration);
    ~traffic()= default;
    void run();
};


#endif //LORA_SIM_CPP_TRAFFIC_H
