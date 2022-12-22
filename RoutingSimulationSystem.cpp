#include"Packet.h"
#include"Router.h"
#include"System.h"
#include"ExampleRouter.h"
#include"AdList.h"
#include<iostream>
#include<fstream>
#include"OspfRouter.h"
#include"PathPacket.h"
#define DEBUG
using namespace std;
void readMatrix(vector<vector<int>>& matrix)
{
#ifdef DEBUG
    cout << "从data.txt读取邻接矩阵...";
#endif // DEBUG

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
#ifdef DEBUG
    cout << endl;
#endif // DEBUG

}
int main(){
    
    vector<vector<int>> matrix;
    readMatrix(matrix);
    System<OspfRouter, PathPacket> system(matrix);
    system.printMatrix();
    system.printLinkList();
    PathPacket packet;
    packet.setTarget(3);
    system.givePacket(0, packet);
    system.tick();



}


