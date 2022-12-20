#pragma once
#include"Packet.h"
#include"Router.h"
#include"System.h"
#include"ExampleRouter.h"
#include<iostream>
#include<fstream>
//LSA广播包
class LsaPacket{
protected:
	//first为节点下标，second为其邻接矩阵
	map<int, vector<vector<int>>> LSA;
	//广播包发送者的下标
	int senterIndex;
public:
	//返回LSA
	map<int, vector<vector<int>>> getLSA() const{
		return LSA;
	}
	//返回广播包发送者的下标
	int getSenterIndex () const {
		return senterIndex;
	}
};

