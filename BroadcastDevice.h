#pragma once
#include"Router.h"
template <typename T>
class BroadcastDevice{
protected:
	//���ڴ洢�յ��Ĺ㲥��
	T recivedPacket;
	//��ʾ�������Ƿ���δ����Ĺ㲥��
	bool isIncludeRecivedPacket = false;
	void recivePacket(T packetToRecive) {
		recivedPacket = packetToRecive;
		isIncludeRecivedPacket = true;
	}
public:
	//�����������Ƿ���δ����Ĺ㲥��
	bool hasRecivedPacket() {
		return isIncludeRecivedPacket;
	}
	//���ع㲥����ʹ��ǰ����
	T getRecivedPacket() {
		if (isIncludeRecivedPacket) {
			return recivedPacket;
		}
		else {
			cout << "����:��������recivePacket!����getǰ���!\n";
		}
	
	}
	//���͹㲥������һ������ΪĿ�꣬�ڶ�������ΪҪ���͵Ĺ㲥��
	void sendBoradcastPacket(BroadcastDevice &target,T packetToSend) {
		target.recivePacket(packetToSend);
	}
	//���ٹ㲥��
	void deleteRecivedPacket() {
		isIncludeRecivedPacket = false;
	}
};

