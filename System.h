#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Router.h"
#include<Windows.h>

#define DEBUG
//T为Router类，P为包类
template <typename T,typename P>
class System{
protected:
	vector<T> routers;
	//邻接矩阵
	vector<vector<int>> matrix;
	//邻接链表
	map<int, vector<int>> nbLinkList;
	int n;

	void initRouters() {
		for (int i = 0; i < n; i++) {
			T temp(i);
			routers.push_back(temp);
		}
	}
	void initConnections(vector<vector<int>>& matrix)
	{
		for (int i = 0; i < n; i++) {
			vector<int> row = matrix[i];
			map<int, Router<P>*> tempMap;
			for (int j = 0; j < n; j++) {
				if (row[j] != 0) {
					tempMap[j] = &routers[j];
				}
			}
			routers[i].initConnections(tempMap);
		}
	}
	void initAdList() {
		for (auto& it : routers) {
			it.initAdList();
		}
	}
	void initNbLinkList(){
		for (int i = 0; i < matrix.size(); i++) {
			vector<int> tempVec;
			for (int j = 0; j < matrix.size(); j++) {
				if (matrix[i][j] != 0) tempVec.push_back(j);
			}
			nbLinkList[i] = tempVec;
		}
	}
public:
	System(vector<vector<int>> matrix) {
		this->n = matrix.size();
		this->matrix = matrix;
		initRouters();
		initConnections(matrix);
		initAdList();
		initNbLinkList();
	}
	//阻塞式
	void tick() {
		while (1) {
			for (auto &it : routers) {
				it.tick();
				//Sleep();
			}
			
		}
	}
	//tick n次
	void tick(int n) {
		while (n--) {
			for (auto& it : routers) {
				it.tick();
				//Sleep();
			}
		}
	}
	void givePacket(int routerIndex, P packet) {
		routers[routerIndex].setPacket(packet);
#ifdef DEBUG
		cout << "将包提供给" << routerIndex << endl;
#endif // DEBUG

	}
	//打印邻接矩阵
	void printMatrix() const {
		if (matrix.empty()) {
			cout << "错误:邻接矩阵为空!" << endl;
			return;
		}
		cout << "邻接矩阵:" << endl;
		for (const auto& vec : matrix) {
			for (const auto& val : vec) {
				cout << val << ' ';
			}
			cout << endl;
		}
	}
	//打印邻接链表
	void printLinkList() const {
		if (nbLinkList.empty()) {
			cout << "错误:邻接链表为空!" << endl;
			return;
		}
		cout << "邻接链表:" << endl;
		for (const auto& it : nbLinkList) {
			cout << it.first << '|';
			for (const auto& val : it.second) {
				cout << val << ' ';
			}
			cout << endl;
		}
	}
};

