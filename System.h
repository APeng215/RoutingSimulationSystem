#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Router.h"
#include<Windows.h>

#define DEBUG
//TΪRouter�࣬PΪ����
template <typename T,typename P>
class System{
protected:
	vector<T> routers;
	//�ڽӾ���
	vector<vector<int>> matrix;
	//�ڽ�����
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
	//����ʽ
	void tick() {
		while (1) {
			for (auto &it : routers) {
				it.tick();
				//Sleep();
			}
			
		}
	}
	//tick n��
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
		cout << "�����ṩ��" << routerIndex << endl;
#endif // DEBUG

	}
	//��ӡ�ڽӾ���
	void printMatrix() const {
		if (matrix.empty()) {
			cout << "����:�ڽӾ���Ϊ��!" << endl;
			return;
		}
		cout << "�ڽӾ���:" << endl;
		for (const auto& vec : matrix) {
			for (const auto& val : vec) {
				cout << val << ' ';
			}
			cout << endl;
		}
	}
	//��ӡ�ڽ�����
	void printLinkList() const {
		if (nbLinkList.empty()) {
			cout << "����:�ڽ�����Ϊ��!" << endl;
			return;
		}
		cout << "�ڽ�����:" << endl;
		for (const auto& it : nbLinkList) {
			cout << it.first << '|';
			for (const auto& val : it.second) {
				cout << val << ' ';
			}
			cout << endl;
		}
	}
};

