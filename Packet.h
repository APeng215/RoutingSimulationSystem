#pragma once
#include<vector>
#include<iostream>
using namespace std;
class Packet{
protected:
	int target=-1;
public:
	Packet() {
		this->target = -1;
	}
	Packet(int target) {
		this->target = target;
	}
	bool clear() {
		target = -1;
		return true;
	}
	int getTarget() const {
		return target;
	}
	bool setTarget(int target) {
		this->target = target;
		return true;
	}

};

