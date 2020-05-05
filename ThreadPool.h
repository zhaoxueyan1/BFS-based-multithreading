#pragma once

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>

#define N 10

using namespace std;
class ThreadPool {
public:
	//�Զ���void()�ĺ�������
	typedef function<void(pair<int,int>)>Task;

	ThreadPool();
	~ThreadPool();
	
public:

	size_t initnum;
	//�߳�����
	vector<thread>threads;

	//�������
	queue<pair<Task,pair<int,int>>>task;

	//��������������
	mutex _mutex;
	condition_variable cond;

	//�̳߳ع�������ʱΪ��
	bool done;

	//�����Ƿ�Ϊ��
	bool isEmpty;
	//�����Ƿ�Ϊ��
	bool isFull;

public:
	void addTask(const Task& f,pair<int,int>& args);
	void start(int num);
	void setSize(int num);
	void runTask();
	void finish();
};
