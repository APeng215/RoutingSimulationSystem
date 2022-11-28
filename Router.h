#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Packet.h"
using namespace std;
class Router{
protected:
	map<int, Router*> indexToPoints;//���תָ��
	int index;//·�ɱ��
	bool ifIncludePacket = false;//flag�Ƿ��а�������ֱ�Ӳ���
	Packet packet;//���еİ�



	bool setPacket(Packet input) {//���ð�
		packet = input;
		ifIncludePacket = true;
		return true;
	}
	bool deletePacket() {//ɾ����
		packet.clear();
		ifIncludePacket = false;
		return true;
	}
public:
	Router(int index, map<int, Router*> indexToPoints) {//�ް���ʼ��
		this->index = index;
		this->indexToPoints = indexToPoints;
	}
	Router(int index, map<int, Router*> indexToPoints,Packet packet) {//�а���ʼ��
		this->index = index;
		this->indexToPoints = indexToPoints;
		this->setPacket(packet);
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
			indexToPoints[target]->setPacket(packet);
			printf("�����ݣ�%d-->%d\n", index, target);
			this->deletePacket();
			return true;
		}
		
		
		return false;
	}
	
	Packet getPacket() {//���ذ�
		if (ifIncludePacket) {
			return packet;
		}
		else {//�ް�����
			printf("����:���Ϊ%d��·�ɲ������а�!\n", index);
		}
		
	}
};

