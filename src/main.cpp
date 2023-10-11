#include <iostream>
#include "traffic.h"
using namespace std;


// g++ -std=c++11 -o main src/* | ./main 
int main(){

    traffic network = *new traffic(2, 1000);

    cout << "\n";
    return 0;
}