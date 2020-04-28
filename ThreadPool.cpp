#include"pch.h"
#include"ThreadPool.h"
template<class T,class T1>
ThreadPool<T, T1>::ThreadPool() 
	:done(false), isEmpty(true), isFull(false) {
}

//���ó��г�ʼ�߳���
template<class T, class T1>
void ThreadPool<T,T1>::setSize(int num) {
	(*this).initnum = num;
}

//�������
template<class T, class T1>
void ThreadPool<T, T1>::addTask(const Task&f,T1 args) {

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

template<class T, class T1>
void ThreadPool<T, T1>::finish() {

	//�̳߳ؽ�������
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}

template<class T, class T1>
void ThreadPool<T, T1>::runTask() {

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

template<class T, class T1>
void ThreadPool<T, T1>::start(int num) {

	setSize(num);

	for (int i = 0; i < num; i++) {
		threads.push_back(thread(&ThreadPool::runTask, this));
	}
}

template<class T, class T1>
ThreadPool<T, T1>::~ThreadPool() {
}
