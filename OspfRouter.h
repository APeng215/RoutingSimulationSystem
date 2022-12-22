#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"AdList.h"
#include"Router.h"
#include<Windows.h>
#include"LsaPacket.h"
#include"PathPacket.h"
#include<set>
#include<queue>
class OspfRouter:public Router<PathPacket>{
protected:
	//用于存储收到的广播包
	queue<AdList> recivedPacket;


	//本路由储存的LSA
	AdList adList;
	vector<int> contiguousRouters;

	//**********************************************************************************************************
	void recivePacket(AdList packetToRecive) override {
		recivedPacket.push(packetToRecive);
	}

	//返回邮箱中是否有未解读的广播包
	bool hasRecivedPacket() {
		return !recivedPacket.empty();
	}
	//返回广播包，使用前请检查
	AdList getRecivedPacket() {
		if (hasRecivedPacket()) {
			return recivedPacket.front();
		}
		else {
			cout << "警告:并不含有recivePacket!请在get前检查!\n";
		}

	}
	//发送广播包，第一个参数为目标，第二个参数为要发送的广播包
	void sendBoradcastPacket(Router<PathPacket>* target, AdList packetToSend) {
		target->recivePacket(packetToSend);
	}
	//销毁广播包
	void deleteRecivedPacket() {
		recivedPacket.pop();
	}
	//************************************************************************************************************
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
			this->sendBoradcastPacket(it.second, LSAtoSend);
		}
	}
	//根据自己已知的AdList，找出最短路径
	vector<int> Dijkstra(int target) {
		vector<int> path;
		//如果LAS中没有节点的数据，返回空的vec
		if (!this->adList.hasVertex(target)) return path;
		//如果有节点的数据，则用算法寻找最短路径存入path
		//set储存已经计算出最短路径的点
		set<int> sptSet;
		//dist储存点的目前最短路径
		vector<int> dist(adList.maxVertex() * adList.maxVertex()+100, INT_MAX);
		//parent储存点最短路径所需要的来自的parent
		vector<int> parent(adList.maxVertex() * adList.maxVertex()+100, -1);
		//令本节点的dist为0，因此本节点将会是第一个加入最小路径树的
		dist[index] = 0;
		parent[index] = index;
		//如果sptSet大小与adlist不一致，说明还没遍历完
		while (sptSet.size() < adList.size()) {
			//用选择查找，寻找dist中最小的还未加入生成树
			int minKey=-1;
			int minDist = INT_MAX;
			for (int i = 0; i < dist.size(); i++) {
				auto it = sptSet.find(i);
				//如果不在spt中，且其dist小,将key变成它
				if (it == sptSet.end() && dist[i] < minDist) {
					minKey = i;
					minDist = dist[i];
				}
			}
			if (minKey == -1) break;//如果没找到退出循环
			//此时找到了minKey，将其加入spt并更新其邻居点的dist
			sptSet.insert(minKey);
			//如果目标加入了最短路径树，可以直接退出搜索
			if (minKey == target) break;
			//获得其邻接点
			vector<int> nbList = adList.getNBlist(minKey);
			//遍历更新邻接点的dist和parent
			for (auto& it : nbList) {
				auto find = sptSet.find(it);
				//邻接点不在spt中且距离更小，且邻接点在adlist中，更新dist和parent
				if (adList.hasVertex(it) && find == sptSet.end() && dist[minKey] + 1 < dist[it]) {
					dist[it] = dist[minKey] + 1;
					parent[it] = minKey;
				}
			}
		}
		//根据dist和parent寻找最短路径，反向寻找
		vector<int> emptyVec;
		path.push_back(target);
		int curPoint = parent[target];
		while (curPoint != index) {
			if (curPoint == -1) return emptyVec;
			path.push_back(curPoint);
			curPoint = parent[curPoint];
		}
		path.push_back(curPoint);
		reverse(path.begin(), path.end());
		return path;
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
		for (auto &it : indexToPoints) {
			this->adList.update(this->index, it.first);
		}
	}
	void tick() override {
		//计数器增加
		timer = (timer + 1) % 100000;
		//如果邮箱中有LSA包
		while (hasRecivedPacket()) {
			//copy接收到的LSA包
			AdList recivedPacket = getRecivedPacket();
			//尝试用LSA包更新自己的包。如果更新了，要继续传递包给其有邻接关系的路由器；否则不传递。
			//如果更新了，要检查发包者是否与自己有邻接关系，如果没有且对方与自己有线路连接，回复并建立邻接关系
			if (updateLSA(recivedPacket)) {//Pass
				//遍历邻接路由表来发送
				for (auto it : contiguousRouters) {
					this->sendBoradcastPacket(indexToPoints[it], recivedPacket);
				}
				if (find(contiguousRouters.begin(), contiguousRouters.end(), recivedPacket.getSender()) 
					== contiguousRouters.end()
					&& indexToPoints.find(recivedPacket.getSender())!=indexToPoints.end()) {//**************************************
					//创建回复包
					AdList packetTosend = this->adList;
					packetTosend.setSender(this->index);
					//发送回复包
					this->sendBoradcastPacket(indexToPoints[recivedPacket.getSender()], packetTosend);
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
		//如果接收到了包，先检查包目标是否是自己，如果不是再根据包路径发送，如果包不存在路径，要自己创建再发送
		if (isIncludePacket) {
			//如果目标是自己，说明包送达
			if (this->getPacket().getTarget() == this->index) {
				//输出结果
				cout << index << ":包送达" << endl;
				//销毁包
				this->deletePacket();
			}
			//如果目标不是自己
			else {
				//copy包
				PathPacket pathPacket = this->getPacket();
				//如果包有路径，就按路径来发送
				if (pathPacket.hasPath()) {
					//获取目标
					int target = pathPacket.getNextTarget(this->index);
					//发包
					this->sendPacket(target);
				}
				//如果包没有路径，需要自己计算
				else {
					//计算出path
					vector<int> path = Dijkstra(pathPacket.getTarget());
					//如果得到path，压入包
					if (!path.empty()) {
						pathPacket.setPath(path);
						this->setPacket(pathPacket);
					}
				}
			}
			
		}
	}
};

