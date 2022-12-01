#pragma once
#include"Router.h"
#include"BroadcastDevice.h"
#include<random>
class ExampleRouter:public Router,public BroadcastDevice<int>{
public:
	ExampleRouter(int a) :Router(a) {}
	void tick() override {
		if (this->ifIncludePacket) {
			this->sendPacket(rand() * (this->indexToPoints.size()));
		}
	}
};

