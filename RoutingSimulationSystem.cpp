#include"Packet.h"
#include"Router.h"
#include"System.h"
#include"ExampleRouter.h"
#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ifstream in("data.txt");
    vector<vector<int>> matrix;
    int temp;
    vector<int> tempVec;
    while (in >> temp) {
        tempVec.push_back(temp);
        char c = in.get();
        if (c == '\n') {
            matrix.push_back(tempVec);
            tempVec.clear();
        }
    }
    System<ExampleRouter> system(matrix);
    Packet packet;
    system.givePacket(1, packet);
    system.tick();
}


