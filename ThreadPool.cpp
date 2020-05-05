#include"pch.h"
#include"ThreadPool.h"

ThreadPool::ThreadPool() 
	:done(false), isEmpty(true), isFull(false) {
}

//���ó��г�ʼ�߳���
void ThreadPool::setSize(int num) {
	(*this).initnum = num;
}

//�������
void ThreadPool::addTask(const Task& f, pair<int,int>& args) {

	if (!done) {
		//����������Դ    
		unique_lock<mutex>lk(_mutex);

		//Ҫ�����������������,�͵ȴ������������
		while (isFull) {
			cond.wait(lk);
		}

		//���������������
		task.push({f,args});

		if (task.size() == initnum)
			isFull = true;

		cout << "Add a task" << endl;
		isEmpty = false;
		cond.notify_one();
	}
}

void ThreadPool::finish() {

	//�̳߳ؽ�������
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}

void ThreadPool::runTask() {

	//���ϱ�������,�ж�Ҫ��������Ļ�,��ִ��
	while (!done) {

		unique_lock<mutex>lk(_mutex);

		//����Ϊ�յĻ�,�͵ȴ�����
		while (isEmpty) {
			cond.wait(lk);
		}

		Task ta;

		auto pcb = task.front();
		//ת�ƿ��ƿ�,����ֵ����ת��Ϊ��ֵ����
		ta = move(pcb.first);
		task.pop();

		if (task.empty()) {
			isEmpty = true;
		}

		isFull = false;
		cond.notify_one();
		ta(pcb.second);
	}
}


void ThreadPool::start(int num) {

	setSize(num);

	for (int i = 0; i < num; i++) {
		threads.push_back(thread(&ThreadPool::runTask, this));
	}
}

ThreadPool::~ThreadPool() {
}
