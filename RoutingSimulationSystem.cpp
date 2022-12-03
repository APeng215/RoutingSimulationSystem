﻿#include"Packet.h"
#include"Router.h"
#include"System.h"
#include"ExampleRouter.h"
#include<iostream>
#include<fstream>
using namespace std;
void readMatrix(vector<vector<int>>& matrix)
{
    ifstream in("data.txt");
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
}
int main(){
    vector<vector<int>> matrix;
    readMatrix(matrix);
    System<ExampleRouter,Packet> system(matrix);
    Packet packet;
    system.givePacket(1, packet);
    system.tick();
}


