#pragma once
#include<iostream>
#include<map>
using namespace std;
typedef struct Arc {
	int index;
	Arc* next;
}Arc;

class AdList {
protected:
	map<int, Arc*> heads;
public:
	//插入a到b的邻接关系，如果关系已经存在，则返回false
	bool insert(const int a,const int b) {
		auto it = heads.find(a);
		//如果已经存在这个头节点，顺着链表寻找是否指向b
		if (it != heads.end()) {
			//point指向firstArc
			Arc* point = (*it).second;
			//寻找是否已经存在b，找到b直接返回false
			while (point != NULL){
				if (point->index == b) return false;
			}
			//如果没找到b,则需要创建

		}
	}
};

