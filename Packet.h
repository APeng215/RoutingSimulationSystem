#pragma once
#include<vector>
#include<iostream>

#define DEBUG
using namespace std;
//Packet���ص����޷������ƣ���Router����֮�󣬷�����Router���Զ�ɾ���Լ������Packet
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
		cout << "��Ŀ������Ϊ" << target << endl;
#endif // DEBUG

		return true;
	}


};

