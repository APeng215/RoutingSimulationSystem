#pragma once
#include<vector>
#include<iostream>
using namespace std;
class Packet{
protected:
	int target=-1;
public:
	Packet(int target) {
		this->target = target;
	}
	bool clear() {
		target = -1;
		return true;
	}
	int getTarget() {
		return target;
	}
	bool setTarget(int target) {
		this->target = target;
		return true;
	}

};

