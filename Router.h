#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Packet.h"
using namespace std;
class Router{
protected:
	map<int, Router*> indexToPoints;//编号转指针
	int index;//路由编号
	bool ifIncludePacket = false;//flag是否含有包。请勿直接操作
	Packet packet;//含有的包



	bool setPacket(Packet input) {//设置包
		packet = input;
		ifIncludePacket = true;
		return true;
	}
	bool deletePacket() {//删除包
		packet.clear();
		ifIncludePacket = false;
		return true;
	}
public:
	Router(int index) {//无包初始化
		this->index = index;
		this->indexToPoints = indexToPoints;
	}
	Router(int index,Packet packet) {//有包初始化
		this->index = index;
		this->indexToPoints = indexToPoints;
		this->setPacket(packet);
	}
	bool initConnections(map<int, Router*> indexToPoints) {//初始化连接
		this->indexToPoints = indexToPoints;
		return true;
	}

	bool sendPacket(int target) {//发包：将包发给目标
		//如果自身无包，则无法发送包，输出报错
		if (!this->ifIncludePacket) {
			printf("错误：编号为%d的路由并不含有包，无法发包！\n", index);
			return false;
		}
		//如果自身有包，要确认目标是否存在，再发包
		auto result = indexToPoints.find(target);
		if (result != indexToPoints.end()) {
			indexToPoints[target]->setPacket(packet);
			printf("包传递：%d-->%d\n", index, target);
			this->deletePacket();
			return true;
		}
		
		
		return false;
	}
	
	Packet getPacket() {//返回包
		if (ifIncludePacket) {
			return packet;
		}
		else {//无包报错
			printf("警告:编号为%d的路由并不含有包!\n", index);
		}
		
	}
};

