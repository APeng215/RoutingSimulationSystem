#pragma once
#include"Router.h"
template <typename T>
class BroadcastDevice{
protected:
	T recivedPacket;
	
	void recivePacket(T packetToRecive) {
		recivedPacket = packetToRecive;
	}
public:
	T getrecivedPacket() {
		return recivedPacket;
	}
	void sendBoradcastPacket(BroadcastDevice target,T packetToSend) {
		target.recivePacket(packetToSend);
	}

};

