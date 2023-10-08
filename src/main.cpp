#include <iostream>
#include <vector>
#include <string>
#include "node.h"

using namespace std;

// g++ -std=c++11 -o main src/* | ./main 
int main(){

    Packet packet(5, 7, 1240, 15) ;
    cout << packet.getPacketId() ;


   Node node(1, 2, 4, 5);

    cout << "\n";
    return 0;
}