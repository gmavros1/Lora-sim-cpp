//
// Created by gmavrosi on 30/10/2023.
//

#include "utils.h"

using namespace std;

double devicesDistance(coordinates device1, coordinates device2) {
    double x1 = device1.x;
    double y1 = device1.y;
    double z1 = device1.z;

    double x2 = device2.x;
    double y2 = device2.y;
    double z2 = device2.z;

    double distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
    return distance;
}

double toa(int payload_length, int sf, int crc, int header, int de, int n_preamble, int bw, int cr) {
    if (bw == 125 && sf >= 11) {
        de = 1;
    }

    double Ts = std::pow(2, sf) / bw;

    double num_payload_symbols = 8.0 + std::max(static_cast<double>(std::ceil(
            (8.0 * payload_length - 4.0 * sf + 28.0 + 16.0 * crc - 20.0 * header) / (4.0 * (sf - 2.0 * de))) *
                                                                    (cr + 4.0)), 0.0);

    //cout << num_payload_symbols << endl;
    double T_payload = Ts * num_payload_symbols;
    double T_preamble = (n_preamble + 4.25) * Ts;
    return T_preamble + T_payload;
}


double calculate_received_power(double distance, double transmission_power, double shadowing_std_dev) {
    // Constants - sensors-22-03518-v3.pdf - reference
    double PLd0 = 37;  // Reference path loss at the reference distance (d0)
    double d0 = 1.0;     // Reference distance (1 meter)
    double alpha = 2.85; // Path loss exponent - (2-4) - urban environments ~ 3

    // Calculate the path loss without shadowing
    double PL = PLd0 + 10 * alpha * log10(distance / d0);

    // Generate a random value for shadowing
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, shadowing_std_dev);
    //double shadowing = distribution(generator);
    double shadowing = 5.34;

    // Calculate the total path loss with shadowing
    PL += shadowing;

    double Pr = transmission_power - PL;

    return Pr;
}


double duty_cycle(double toa) {
    double dutyCycle = 0.01; // 1%
    double t_interval = (toa / dutyCycle) - toa;
    return t_interval; // ms have to wait until the next transmission
}


double calculate_snr(double signal_power, double signal_noise) {
    // You can use a specific noise value or generate a random value like in Python
    // double noise_power = (double) rand() / RAND_MAX * (15.0 - 10.0) + 10.0;  // Random noise power between 10.0 and 15.0 dB
    double noise_power = signal_noise;

    double snr = signal_power - noise_power;
    return snr;
}


double data_rate(int sf, int cr, double bw) {
    return sf * ((4.0 / (4.0 + cr)) / (pow(2.0, sf) / bw));
}


double snr_limit(int sf) {
    int extra = sf - 7;
    return -(7.5 + 2.5 * extra);
}


int adr(const std::vector<double> &last_packets, int sf) {
    double snrLimit = snr_limit(sf);
    double snr_measured = *std::max_element(last_packets.begin(), last_packets.end());
    double margin_default = 10.0; // dB

    if (snr_measured > snrLimit + margin_default) {
        if (sf > 7) {
            return sf - 1;
        } else {
            return sf;
        }
    } else {
        if (sf < 12) {
            return sf + 1;
        } else {
            return sf;
        }
    }
}


/*int main() {

    int sf = 9;
    int distance = 9000;
    int transmission_p = 20;
    double receive_power = calculate_received_power(distance, transmission_p);
    cout << "received power : " << receive_power << endl;
    cout << "calculated snr :  " << calculate_snr(receive_power, -(130.0+2.5)) << endl;
    cout << "snr Limit : " << snr_limit(sf) + 10 << endl;
    cout << "If positive, could be decoded : " << calculate_snr(receive_power, -(130.0+2.5)) - (snr_limit(sf) + 10) << endl;
}*/