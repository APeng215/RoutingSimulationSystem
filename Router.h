#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include<cstdio>
#include"Packet.h"
#include"AdList.h"
using namespace std;
//T����ΪRouter�����͵İ���
template <typename T>
class Router{
protected:
	map<int, Router*> indexToPoints;//���תָ��
	int index=-1;//·�ɱ��
	bool isIncludePacket = false;//flag�Ƿ��а�������ֱ�Ӳ���
	T packet;//���еİ�
	unsigned int timer = 0;//ʱ�������


	
	bool deletePacket() {//ɾ����
		packet.clear();
		isIncludePacket = false;
		return true;
	}
	
public:
	Router(int index) {//�ް���ʼ��
		this->index = index;
	}
	Router(int index, T &packet) {//�а���ʼ��
		this->index = index;
		this->setPacket(packet);
	}
	bool initConnections(map<int, Router*> indexToPoints) {//��ʼ������
		this->indexToPoints = indexToPoints;
		return true;
	}

	bool sendPacket(int target) {//��������������Ŀ��
		//��������ް������޷����Ͱ����������
		if (!this->isIncludePacket) {
			printf("���󣺱��Ϊ%d��·�ɲ������а����޷�������\n", index);
			return false;
		}
		//��������а���Ҫȷ��Ŀ���Ƿ���ڣ��ٷ���
		auto result = indexToPoints.find(target);
		if (result != indexToPoints.end()) {
			(*result).second->setPacket(packet);
			printf("�����ݣ�%d-->%d\n", index, target);
			this->deletePacket();
			return true;
		}
		
		
		return false;
	}
	
	T getPacket() const{//���ذ�
		if (isIncludePacket) {
			return packet;
		}
		else {//�ް�����
			printf("����:���Ϊ%d��·�ɲ������а�!\n", index);
		}
		
	}
	//���ر�·�������±�
	int getIndex() {
		return index;
	}
	bool setPacket(T input) {//���ð�
		packet = input;
		isIncludePacket = true;
		return true;
	}
	
	virtual void tick(void){}

	virtual void recivePacket(AdList packetToRecive) {}

	
};

