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

	//更新LSA，返回是否更新后的LAS是否有所变化
	bool updateLSA(map<int, vector<vector<int>>> receivedLSA) {

	}
public:
	void tick() override {
		//计数器增加
		timer = (timer + 1) % 100000;
		//如果邮箱中有广播包
		if (this->hasRecivedPacket()) {
			if(updateLSA)

			this->deleteRecivedPacket();
		}
		//如果发送LSA的周期到了
		if (timer % 10 == 0) {
			for (auto it : this->indexToPoints) {
				this->sendBoradcastPacket(*it.second,)
			}
		}
		if (isIncludePacket) {

		}
	}
};

