#include"pch.h"
#include <iostream>
#include"ThreadPool.h"

#if 0
void func(int i) {
	cout << "task finish" << "------>" << i << endl;
}


int main()
{

	ThreadPool p;
	p.start(2);
	int i = 0;

	while (1) {
		i++;
		//�����߳�֮��cpu����,����ȥ��
		//this_thread::sleep_for(chrono::seconds(1));
		auto task = bind(func, i);
		p.addTask(task);
	}

	p.finish();
	return 0;
}
#endif