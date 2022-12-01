#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include"Router.h"
#include<Windows.h>
template <typename T>
class System{
protected:
	vector<Router*> routers;
	vector<vector<int>> matrix;
	int n;

	void initRouters() {
		for (int i = 0; i < n; i++) {
			T temp(i);
			routers.push_back(&temp);
		}
	}
	void initConnections(vector<vector<int>>& matrix)
	{
		for (int i = 0; i < n; i++) {
			vector<int> row = matrix[i];
			map<int, T*> tempMap;
			for (int j = 0; j < n; j++) {
				if (row[j] != 0) {
					tempMap[j] = routers[j];
				}
			}
			routers[i]->initConnections(tempMap);
		}
	}
	
public:
	System(vector<vector<int>> matrix) {
		this->n = matrix.size();
		this->matrix = matrix;
		initRouters();
		initConnections(matrix);
		
	}
	void tick() {
		while (1) {
			for (auto it : routers) {
				it->tick();
			}
			Sleep(1000);
		}
	}
};

