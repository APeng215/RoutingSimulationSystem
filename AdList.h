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
	//����a��b���ڽӹ�ϵ�������ϵ�Ѿ����ڣ��򷵻�false
	bool insert(const int a,const int b) {
		auto it = heads.find(a);
		//����Ѿ��������ͷ�ڵ㣬˳������Ѱ���Ƿ�ָ��b
		if (it != heads.end()) {
			//pointָ��firstArc
			Arc* point = (*it).second;
			//Ѱ���Ƿ��Ѿ�����b���ҵ�bֱ�ӷ���false
			while (point != NULL){
				if (point->index == b) return false;
			}
			//���û�ҵ�b,����Ҫ����

		}
	}
};

