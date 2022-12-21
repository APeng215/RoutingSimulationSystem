#pragma once
#include"Packet.h"
#include<vector>
class PathPacket:public Packet{
protected:
	vector<int> path;
public:
	vector<int> getPath() const {
		return path;
	}
	void setPath(vector<int> path) {
		this->path = path;
	}
	bool hasPath() const {
		return !path.empty();
	}
	int getNextTarget(int current) {
		//���
		if (!hasPath()) {
			cout << "����:PathPacket��������path,�޷������һ��Ŀ��!" << endl;
			return -1;
		}
		//��ȡ
		auto it = find(this->path.begin(), this->path.end(), current);
		return ++(*it);
	}
};

