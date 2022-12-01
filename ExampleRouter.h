#pragma once
#include"Router.h"
#include"BroadcastDevice.h"
#include<random>
class ExampleRouter:public Router,public BroadcastDevice<int>{
public:
	ExampleRouter(int a) :Router(a) {}
	void tick() override {
		if (this->ifIncludePacket) {
			int randNum = rand() % (this->indexToPoints.size()+1);
			this->sendPacket(randNum);
		}
	}
};

