#pragma once
#include<vector>
#include<iostream>

#define DEBUG
using namespace std;
//Packet的特点是无法被复制，被Router发送之后，发送者Router将自动删除自己储存的Packet
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
#ifdef DEBUG
		cout << "包目标设置为" << target << endl;
#endif // DEBUG

		return true;
	}


};

