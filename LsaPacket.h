#pragma once
#include"Packet.h"
#include"Router.h"
#include"System.h"
#include"ExampleRouter.h"
#include<iostream>
#include<fstream>
//LSA�㲥��
class LsaPacket{
protected:
	//firstΪ�ڵ��±꣬secondΪ���ڽӾ���
	map<int, vector<vector<int>>> LSA;
	//�㲥�������ߵ��±�
	int senterIndex;
public:
	//����LSA
	map<int, vector<vector<int>>> getLSA() const{
		return LSA;
	}
	//���ع㲥�������ߵ��±�
	int getSenterIndex () const {
		return senterIndex;
	}
};

