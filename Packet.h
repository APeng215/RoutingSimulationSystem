#pragma once
#include<vector>
#include<iostream>
using namespace std;
class Packet{
public:
	int infor=-1;
	bool clear() {
		infor = -1;
		return true;
	}
};

