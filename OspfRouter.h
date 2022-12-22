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
	//���ڴ洢�յ��Ĺ㲥��
	queue<AdList> recivedPacket;


	//��·�ɴ����LSA
	AdList adList;
	vector<int> contiguousRouters;

	//**********************************************************************************************************
	void recivePacket(AdList packetToRecive) override {
		recivedPacket.push(packetToRecive);
	}

	//�����������Ƿ���δ����Ĺ㲥��
	bool hasRecivedPacket() {
		return !recivedPacket.empty();
	}
	//���ع㲥����ʹ��ǰ����
	AdList getRecivedPacket() {
		if (hasRecivedPacket()) {
			return recivedPacket.front();
		}
		else {
			cout << "����:��������recivePacket!����getǰ���!\n";
		}

	}
	//���͹㲥������һ������ΪĿ�꣬�ڶ�������ΪҪ���͵Ĺ㲥��
	void sendBoradcastPacket(Router<PathPacket>* target, AdList packetToSend) {
		target->recivePacket(packetToSend);
	}
	//���ٹ㲥��
	void deleteRecivedPacket() {
		recivedPacket.pop();
	}
	//************************************************************************************************************
	//����LSA�������Ƿ���º��LAS�Ƿ������仯
	bool updateLSA(AdList receivedLSA) { 
		return adList.update(receivedLSA);
	}
	//���ڷ�LSA��
	void periodicTransmission() {
		//����LSA�������������ӵ��ھ�
		for (auto& it : this->indexToPoints) {
			//����Ҫ���͵İ�
			AdList LSAtoSend = this->adList;
			LSAtoSend.setSender(this->getIndex());
			//���Ͱ�
			this->sendBoradcastPacket(it.second, LSAtoSend);
		}
	}
	//�����Լ���֪��AdList���ҳ����·��
	vector<int> Dijkstra(int target) {
		vector<int> path;
		//���LAS��û�нڵ�����ݣ����ؿյ�vec
		if (!this->adList.hasVertex(target)) return path;
		//����нڵ�����ݣ������㷨Ѱ�����·������path
		//set�����Ѿ���������·���ĵ�
		set<int> sptSet;
		//dist������Ŀǰ���·��
		vector<int> dist(adList.maxVertex() * adList.maxVertex()+100, INT_MAX);
		//parent��������·������Ҫ�����Ե�parent
		vector<int> parent(adList.maxVertex() * adList.maxVertex()+100, -1);
		//��ڵ��distΪ0����˱��ڵ㽫���ǵ�һ��������С·������
		dist[index] = 0;
		parent[index] = index;
		//���sptSet��С��adlist��һ�£�˵����û������
		while (sptSet.size() < adList.size()) {
			//��ѡ����ң�Ѱ��dist����С�Ļ�δ����������
			int minKey=-1;
			int minDist = INT_MAX;
			for (int i = 0; i < dist.size(); i++) {
				auto it = sptSet.find(i);
				//�������spt�У�����distС,��key�����
				if (it == sptSet.end() && dist[i] < minDist) {
					minKey = i;
					minDist = dist[i];
				}
			}
			if (minKey == -1) break;//���û�ҵ��˳�ѭ��
			//��ʱ�ҵ���minKey���������spt���������ھӵ��dist
			sptSet.insert(minKey);
			//���Ŀ����������·����������ֱ���˳�����
			if (minKey == target) break;
			//������ڽӵ�
			vector<int> nbList = adList.getNBlist(minKey);
			//���������ڽӵ��dist��parent
			for (auto& it : nbList) {
				auto find = sptSet.find(it);
				//�ڽӵ㲻��spt���Ҿ����С�����ڽӵ���adlist�У�����dist��parent
				if (adList.hasVertex(it) && find == sptSet.end() && dist[minKey] + 1 < dist[it]) {
					dist[it] = dist[minKey] + 1;
					parent[it] = minKey;
				}
			}
		}
		//����dist��parentѰ�����·��������Ѱ��
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
		//α����趨��ʼtimer
		timer = 50 * index;
	}
	//����initConnections������initAdList
	void initAdList() {
		if (indexToPoints.empty()) {
			cout << "����:�ڳ�ʼ���ڽӱ�ǰ���ȳ�ʼ������(initConnections)!" << endl;
			return;
		}
		for (auto &it : indexToPoints) {
			this->adList.update(this->index, it.first);
		}
	}
	void tick() override {
		//����������
		timer = (timer + 1) % 100000;
		//�����������LSA��
		while (hasRecivedPacket()) {
			//copy���յ���LSA��
			AdList recivedPacket = getRecivedPacket();
			//������LSA�������Լ��İ�����������ˣ�Ҫ�������ݰ��������ڽӹ�ϵ��·���������򲻴��ݡ�
			//��������ˣ�Ҫ��鷢�����Ƿ����Լ����ڽӹ�ϵ�����û���ҶԷ����Լ�����·���ӣ��ظ��������ڽӹ�ϵ
			if (updateLSA(recivedPacket)) {//Pass
				//�����ڽ�·�ɱ�������
				for (auto it : contiguousRouters) {
					this->sendBoradcastPacket(indexToPoints[it], recivedPacket);
				}
				if (find(contiguousRouters.begin(), contiguousRouters.end(), recivedPacket.getSender()) 
					== contiguousRouters.end()
					&& indexToPoints.find(recivedPacket.getSender())!=indexToPoints.end()) {//**************************************
					//�����ظ���
					AdList packetTosend = this->adList;
					packetTosend.setSender(this->index);
					//���ͻظ���
					this->sendBoradcastPacket(indexToPoints[recivedPacket.getSender()], packetTosend);
					//�����ڽӹ�ϵ
					this->contiguousRouters.push_back(recivedPacket.getSender());
				}
			}

			deleteRecivedPacket();
		}
		//�������LSA�����ڵ���
		if (timer % 10 == 0) {
			//���ڷ�LSA��
			periodicTransmission();
		}
		//������յ��˰����ȼ���Ŀ���Ƿ����Լ�����������ٸ��ݰ�·�����ͣ������������·����Ҫ�Լ������ٷ���
		if (isIncludePacket) {
			//���Ŀ�����Լ���˵�����ʹ�
			if (this->getPacket().getTarget() == this->index) {
				//������
				cout << index << ":���ʹ�" << endl;
				//���ٰ�
				this->deletePacket();
			}
			//���Ŀ�겻���Լ�
			else {
				//copy��
				PathPacket pathPacket = this->getPacket();
				//�������·�����Ͱ�·��������
				if (pathPacket.hasPath()) {
					//��ȡĿ��
					int target = pathPacket.getNextTarget(this->index);
					//����
					this->sendPacket(target);
				}
				//�����û��·������Ҫ�Լ�����
				else {
					//�����path
					vector<int> path = Dijkstra(pathPacket.getTarget());
					//����õ�path��ѹ���
					if (!path.empty()) {
						pathPacket.setPath(path);
						this->setPacket(pathPacket);
					}
				}
			}
			
		}
	}
};

