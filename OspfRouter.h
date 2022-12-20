#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"AdList.h"
#include"Router.h"
#include<Windows.h>
#include"BroadcastDevice.h"
#include"LsaPacket.h"
class OspfRouter:public Router<Packet>,public BroadcastDevice<AdList,Router<Packet>>{
protected:
	//本路由储存的LSA
	AdList adList;
	vector<int> contiguousRouters;

	//更新LSA，返回是否更新后的LAS是否有所变化
	bool updateLSA(AdList receivedLSA) {
		return adList.update(receivedLSA);
	}
	//周期发LSA包
	void periodicTransmission() {
		//发送LSA包给其所有连接的邻居
		for (auto& it : this->indexToPoints) {
			//创建要发送的包
			AdList LSAtoSend = this->adList;
			LSAtoSend.setSender(this->getIndex());
			//发送包
			this->sendBoradcastPacket(*it.second, LSAtoSend);
		}
	}
	
public:
	OspfRouter(int index) :Router(index) {
		//伪随机设定起始timer
		timer = 50 * index;
	}
	//请在initConnections后马上initAdList
	void initAdList() {
		if (indexToPoints.empty()) {
			cout << "错误:在初始化邻接表前请先初始化连接(initConnections)!" << endl;
			return;
		}
		for (auto it : indexToPoints) {
			this->adList.update(this->index, it.first);
		}
	}
	void tick() override {
		//计数器增加
		timer = (timer + 1) % 100000;
		//如果邮箱中有LSA包
		if (hasRecivedPacket()) {
			//copy接收到的LSA包
			AdList recivedPacket = getRecivedPacket();
			//尝试用LSA包更新自己的包。如果更新了，要继续传递包给其有邻接关系的路由器；否则不传递。
			//如果更新了，要检查发包者是否与自己有邻接关系，如果没有且对方与自己有线路连接，回复并建立邻接关系
			if (updateLSA(recivedPacket)) {//Pass
				//遍历邻接路由表来发送
				for (auto it : contiguousRouters) {
					this->sendBoradcastPacket(*indexToPoints[it], recivedPacket);
				}
				if (find(contiguousRouters.begin(), contiguousRouters.end(), recivedPacket.getSender()) 
					== contiguousRouters.end()
					&& find(indexToPoints.begin(),indexToPoints.end(),recivedPacket.getSender())!=indexToPoints.end()) {
					//创建回复包
					AdList packetTosend = this->adList;
					packetTosend.setSender(this->index);
					//发送回复包
					this->sendBoradcastPacket(*indexToPoints[recivedPacket.getSender()], packetTosend);
					//建立邻接关系
					this->contiguousRouters.push_back(recivedPacket.getSender());
				}
			}

			deleteRecivedPacket();
		}
		//如果发送LSA的周期到了
		if (timer % 10 == 0) {
			//周期发LSA包
			periodicTransmission();
		}
		if (isIncludePacket) {

		}
	}
};

