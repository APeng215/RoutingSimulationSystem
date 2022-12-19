#pragma once
#include"Router.h"
template <typename T>
class BroadcastDevice{
protected:
	//用于存储收到的广播包
	T recivedPacket;
	//表示邮箱中是否有未解读的广播包
	bool isIncludeRecivedPacket = false;
	void recivePacket(T packetToRecive) {
		recivedPacket = packetToRecive;
		isIncludeRecivedPacket = true;
	}
public:
	//返回邮箱中是否有未解读的广播包
	bool hasRecivedPacket() {
		return isIncludeRecivedPacket;
	}
	//返回广播包，使用前请检查
	T getRecivedPacket() {
		if (isIncludeRecivedPacket) {
			return recivedPacket;
		}
		else {
			cout << "警告:并不含有recivePacket!请在get前检查!\n";
		}
	
	}
	//发送广播包，第一个参数为目标，第二个参数为要发送的广播包
	void sendBoradcastPacket(BroadcastDevice &target,T packetToSend) {
		target.recivePacket(packetToSend);
	}
	//销毁广播包
	void deleteRecivedPacket() {
		isIncludeRecivedPacket = false;
	}
};

