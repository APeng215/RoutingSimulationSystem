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
#include"PathPacket.h"
class OspfRouter:public Router<PathPacket>,public BroadcastDevice<AdList,Router<PathPacket>>{
protected:
	//��·�ɴ����LSA
	AdList adList;
	vector<int> contiguousRouters;

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
			this->sendBoradcastPacket(*it.second, LSAtoSend);
		}
	}
	//�����Լ���֪��AdList���ҳ����·��
	vector<int> Dijkstra(int target) {
		//TODO
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
		if (hasRecivedPacket()) {
			//copy���յ���LSA��
			AdList recivedPacket = getRecivedPacket();
			//������LSA�������Լ��İ�����������ˣ�Ҫ�������ݰ��������ڽӹ�ϵ��·���������򲻴��ݡ�
			//��������ˣ�Ҫ��鷢�����Ƿ����Լ����ڽӹ�ϵ�����û���ҶԷ����Լ�����·���ӣ��ظ��������ڽӹ�ϵ
			if (updateLSA(recivedPacket)) {//Pass
				//�����ڽ�·�ɱ�������
				for (auto it : contiguousRouters) {
					this->sendBoradcastPacket(*indexToPoints[it], recivedPacket);
				}
				if (find(contiguousRouters.begin(), contiguousRouters.end(), recivedPacket.getSender()) 
					== contiguousRouters.end()
					&& find(indexToPoints.begin(),indexToPoints.end(),recivedPacket.getSender())!=indexToPoints.end()) {
					//�����ظ���
					AdList packetTosend = this->adList;
					packetTosend.setSender(this->index);
					//���ͻظ���
					this->sendBoradcastPacket(*indexToPoints[recivedPacket.getSender()], packetTosend);
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

