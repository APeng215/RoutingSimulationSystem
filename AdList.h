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
	//���������ڽӱ�����Լ��ı�����и��£��򷵻�true������޸��£��򷵻�false
	bool update(const AdList adList) {
		//���ñ��
		bool changeFlag = false;
		//��÷����ߵ��ڽӱ�
		const vector<int> senderVec = adList.getHeads()[adList.getSender()];
		//�����ڽӱ�
		for (auto& it : senderVec) {
			if(this->update(adList.getSender(),it)) changeFlag=true;
		}
		//���ر��
		return changeFlag;
	}
	//����a��b���ڽӹ�ϵ�������ϵ�Ѿ����ڣ��򷵻�false;�����ϵ�����ڣ������ӹ�ϵ��������ture
	bool update(const int a,const int b) {
		//���õ�����Ѱ��a
		auto it = heads.find(a);
		//����Ѿ��������ͷ�ڵ㣬˳������Ѱ���Ƿ�ָ��b
		if (it != heads.end()) {
			//����vec
			vector<int>& vec = (*it).second;
			//Ѱ��b
			auto at = find(vec.begin(), vec.end(), b);
			//����ҵ�ֱ�ӷ���false
			if (at != vec.end()) return false;
			//���û�ҵ���������b
			vec.push_back(b);
			return true;
		}
		//������������ͷ�ڵ㣬ֱ�����
		vector<int> temp(1, b);
		heads[a] = temp;
		return true;
	}
	//���ض�Ӧ�ڵ��ڽӵ�vec
	vector<int> getNBlist(int key) {
		return heads[key];
	}
	//����adlist�Ƿ�������ڵ��LSA
	bool hasVertex(int vertex) {
		auto it = heads.find(vertex);
		if (it == heads.end()) return false;
		else return true;
	}
	//�������ĵ���±�
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

