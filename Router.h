#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include<cstdio>
#include"Packet.h"
#include"AdList.h"
using namespace std;
//T参数为Router所发送的包类
template <typename T>
class Router{
protected:
	map<int, Router*> indexToPoints;//编号转指针
	int index=-1;//路由编号
	bool isIncludePacket = false;//flag是否含有包。请勿直接操作
	T packet;//含有的包
	unsigned int timer = 0;//时间计数器


	
	bool deletePacket() {//删除包
		packet.clear();
		isIncludePacket = false;
		return true;
	}
	
public:
	Router(int index) {//无包初始化
		this->index = index;
	}
	Router(int index, T &packet) {//有包初始化
		this->index = index;
		this->setPacket(packet);
	}
	bool initConnections(map<int, Router*> indexToPoints) {//初始化连接
		this->indexToPoints = indexToPoints;
		return true;
	}

	bool sendPacket(int target) {//发包：将包发给目标
		//如果自身无包，则无法发送包，输出报错
		if (!this->isIncludePacket) {
			printf("错误：编号为%d的路由并不含有包，无法发包！\n", index);
			return false;
		}
		//如果自身有包，要确认目标是否存在，再发包
		auto result = indexToPoints.find(target);
		if (result != indexToPoints.end()) {
			(*result).second->setPacket(packet);
			printf("包传递：%d-->%d\n", index, target);
			this->deletePacket();
			return true;
		}
		
		
		return false;
	}
	
	T getPacket() const{//返回包
		if (isIncludePacket) {
			return packet;
		}
		else {//无包报错
			printf("警告:编号为%d的路由并不含有包!\n", index);
		}
		
	}
	//返回本路由器的下标
	int getIndex() {
		return index;
	}
	bool setPacket(T input) {//设置包
		packet = input;
		isIncludePacket = true;
		return true;
	}
	
	virtual void tick(void){}

	virtual void recivePacket(AdList packetToRecive) {}

	
};

