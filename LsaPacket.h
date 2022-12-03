#pragma once
#include"Packet.h"
#include"Router.h"
#include"System.h"
#include"ExampleRouter.h"
#include<iostream>
#include<fstream>
class LsaPacket{
protected:
	map<int, vector<vector<int>>> LSA;
	int senterIndex;
public:
	map<int, vector<vector<int>>> getLSA() const{
		return LSA;
	}
	int getSenterIndex () const {
		return senterIndex;
	}
};

