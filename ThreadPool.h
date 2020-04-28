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
template<class T,class T1>
class ThreadPool {
public:
	//�Զ���void()�ĺ�������
	typedef function<T>Task;

	ThreadPool();
	~ThreadPool();
	
public:

	size_t initnum;
	//�߳�����
	vector<thread>threads;

	//�������
	queue<pair<Task,T1>>task;

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
	void addTask(const Task& f,T1 args);
	void start(int num);
	void setSize(int num);
	void runTask();
	void finish();
};
