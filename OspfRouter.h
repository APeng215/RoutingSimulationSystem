#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Router.h"
#include<Windows.h>
#include"BroadcastDevice.h"
#include"LsaPacket.h"
class OspfRouter:public Router<Packet>,public BroadcastDevice<LsaPacket,Router<Packet>>{
protected:
	map<int, vector<vector<int>>> LSA;
	vector<int> contiguousRouters;

	//����LSA�������Ƿ���º��LAS�Ƿ������仯
	bool updateLSA(map<int, vector<vector<int>>> receivedLSA) {

	}
public:
	void tick() override {
		//����������
		timer = (timer + 1) % 100000;
		//����������й㲥��
		if (this->hasRecivedPacket()) {
			if(updateLSA)

			this->deleteRecivedPacket();
		}
		//�������LSA�����ڵ���
		if (timer % 10 == 0) {
			for (auto it : this->indexToPoints) {
				this->sendBoradcastPacket(*it.second,)
			}
		}
		if (isIncludePacket) {

		}
	}
};

