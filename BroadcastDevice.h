#pragma once
#include"Router.h"
template <typename T>
class BroadcastDevice{
protected:
	T recivedPacket;
	bool isIncludeRecivedPacket = false;
	void recivePacket(T packetToRecive) {
		recivedPacket = packetToRecive;
		isIncludeRecivedPacket = true;
	}
public:
	bool hasRecivedPacket() {
		return isIncludeRecivedPacket;
	}
	T getRecivedPacket() {
		if (isIncludeRecivedPacket) {
			return recivedPacket;
		}
		else {
			cout << "����:��������recivePacket!����getǰ���!\n";
		}
		
	}
	void sendBoradcastPacket(BroadcastDevice &target,T packetToSend) {
		target.recivePacket(packetToSend);
	}
	void deleteRecivedPacket() {
		isIncludeRecivedPacket = false;
	}
};

