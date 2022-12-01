#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include<cstdio>
#include"Packet.h"
using namespace std;
class Router{
protected:
	map<int, Router*> indexToPoints;//���תָ��
	int index=-1;//·�ɱ��
	bool ifIncludePacket = false;//flag�Ƿ��а�������ֱ�Ӳ���
	Packet packet;//���еİ�



	
	bool deletePacket() {//ɾ����
		packet.clear();
		ifIncludePacket = false;
		return true;
	}
	
public:
	Router(int index) {//�ް���ʼ��
		this->index = index;
	}
	Router(int index,Packet packet) {//�а���ʼ��
		this->index = index;
		this->setPacket(packet);
	}
	bool initConnections(map<int, Router*> indexToPoints) {//��ʼ������
		this->indexToPoints = indexToPoints;
		return true;
	}

	bool sendPacket(int target) {//��������������Ŀ��
		//��������ް������޷����Ͱ����������
		if (!this->ifIncludePacket) {
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
	
	Packet getPacket() const{//���ذ�
		if (ifIncludePacket) {
			return packet;
		}
		else {//�ް�����
			printf("����:���Ϊ%d��·�ɲ������а�!\n", index);
		}
		
	}
	int getIndex() {
		return index;
	}
	bool setPacket(Packet input) {//���ð�
		packet = input;
		ifIncludePacket = true;
		return true;
	}
	
	virtual void tick(void){}

	

	
};

