#include <iostream>
#include <vector>
#include <string>
#include "node.h"

using namespace std;

// g++ -std=c++11 -o main src/* | ./main 
int main(){

    Packet packet(-1, -1, -1, 15) ;
    cout << packet.getPacketId() ;


   Node node(1, 2, 4, 5, Packet(0, 0, 0));

    cout << "\n";
    return 0;
}