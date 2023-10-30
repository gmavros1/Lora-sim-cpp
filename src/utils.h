
#ifndef LORA_SIM_UTILS_CPP
#define LORA_SIM_UTILS_CPP

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include "node.h"
#include "gateway.h"

static double distanceNodes(Node node1, Node node2);

static double distanceGatewayNode(Gateway gateway, Node node);

double toa(int payload_length, int sf, int crc = 1, int header = 0, int de = 0, int n_preamble = 8, int bw = 125, int cr = 1);

static double calculate_received_power(double distance, double transmission_power, double shadowing_std_dev = 5.34);

double duty_cycle(double toa);

double calculate_snr(double signal_power, double signal_noise);

double data_rate(int sf, int cr, double bw);

double snr_limit(int sf);

int adr(const std::vector<double> &last_packets, int sf);

#endif

