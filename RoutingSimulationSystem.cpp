#include"Packet.h"
#include"Router.h"
#include <iostream>
#include<fstream>
using namespace std;
int main(){
    ifstream in("data.txt");
    string str;
    in >> str;
    cout << str;
}


