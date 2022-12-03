#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Router.h"
#include<Windows.h>
#include"BroadcastDevice.h"
#include"LsaPacket.h"
class OspfRouter:public Router<Packet>,public BroadcastDevice<LsaPacket>{
protected:
	map<int, vector<vector<int>>> LSA;
	vector<int> contiguousRouters;
public:
	void tick() override {
		timer = (timer + 1) % 100000;
		if (this->hasRecivedPacket()) {
			

			this->deleteRecivedPacket();
		}
		if (timer % 10 == 0) {
			
		}
		if (isIncludePacket) {

		}
	}
};

