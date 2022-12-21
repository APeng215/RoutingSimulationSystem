#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

class AdList {
protected:
	map<int, vector<int>> heads;
	int sender;
public:
	//利用其他邻接表更新自己的表，如果有更新，则返回true；如果无更新，则返回false
	bool update(const AdList adList) {
		//设置标记
		bool changeFlag = false;
		//获得发送者的邻接表
		const vector<int> senderVec = adList.getHeads()[adList.getSender()];
		//更新邻接表
		for (auto& it : senderVec) {
			if(this->update(adList.getSender(),it)) changeFlag=true;
		}
		//返回标记
		return changeFlag;
	}
	//插入a到b的邻接关系，如果关系已经存在，则返回false;如果关系不存在，则增加关系，并返回ture
	bool update(const int a,const int b) {
		//利用迭代器寻找a
		auto it = heads.find(a);
		//如果已经存在这个头节点，顺着链表寻找是否指向b
		if (it != heads.end()) {
			//引用vec
			vector<int>& vec = (*it).second;
			//寻找b
			auto at = find(vec.begin(), vec.end(), b);
			//如果找到直接返回false
			if (at != vec.end()) return false;
			//如果没找到，则新增b
			vec.push_back(b);
			return true;
		}
		//如果不存在这个头节点，直接添加
		vector<int> temp(1, b);
		heads[a] = temp;
		return true;
	}
	//返回对应节点邻接点vec
	vector<int> getNBlist(int key) {
		return heads[key];
	}
	//返回adlist是否有这个节点的LSA
	bool hasVertex(int vertex) {
		auto it = heads.find(vertex);
		if (it == heads.end()) return false;
		else return true;
	}
	//返回最大的点的下标
	int maxVertex() {
		auto it = heads.rbegin();
		return (*it).first;
	}
	void setHeads(map<int, vector<int>> heads) {
		this->heads = heads;
	}
	map<int, vector<int>> getHeads() const {
		return this->heads;
	}
	void setSender(int sender) {
		this->sender = sender;
	}
	int getSender() const {
		return this->sender;
	}
	int size() {
		return heads.size();
	}
};

