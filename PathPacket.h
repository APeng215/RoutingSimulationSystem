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
		//检查
		if (!hasPath()) {
			cout << "警告:PathPacket包不具有path,无法获得下一个目标!" << endl;
			return -1;
		}
		//获取
		auto it = find(this->path.begin(), this->path.end(), current);
		return ++(*it);
	}
};

