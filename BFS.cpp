
#include "pch.h"
#include "ThreadPool.h"
#include "ThreadSafeQueue.h"
#include <time.h>
#include <iostream>
#if 1

using namespace std;

const int MAX_E = 5105039+1;
const int MAX_V = 875713+1;

typedef pair<int, int> P;
//typedef pair<function<void(int x, int y)>, pair<int, int>> PCB;

namespace Diagram {
	struct node {
		int to;
		int nex = -1;
	}e[MAX_E];;
	
	int dgree[MAX_V];
	int cnt;
	int head[MAX_V];
	int d[MAX_V];
	bool vis[MAX_V];
	ThreadPool<void(P),P> p;
	ThreadSafeQueue<P>Q;
	void add(int u, int v) {
		++cnt;
		e[cnt].to = v;
		e[cnt].nex = head[u];
		head[v] = cnt;
	}

	void Step(P p) {
		for (int i = head[p.first]; ~i; i = e[i].nex) {
			if (!vis[e[i].to]) {
				Q.Push(P(e[i].to, p.second + 1));
			}
		}
	}

	void bfs(int s = 0) {
		p.start(2);
		Q.Push(P(s, 0));
		vis[s] = true;
		d[s] = 0;
		while (!Q.IsEmpty()) {
			auto u = Q.WaitAndPop();
			if (vis[u->first]) continue;
			vis[u->first] = true;
			//printf("%d\n",u.first);
			d[u->first] = u->second;
			for (int i = head[u->first]; ~i; i = e[i].nex) {
				if (!vis[e[i].to]) {
					p.addTask(Diagram::Step, P(u->first, u->second));
				}
			}
			p.finish();
			/*step(P(u->first,u->second));*/
		}
	}

};

int main()
{
	int l, r;
	freopen("C://Users//User//Documents//code//中科院//web-Google.txt","r",stdin);
	int v = 875713;
	int e = 5105039;
	

	for (int i = 0; i < e; i++) {
		scanf("%d %d", &l, &r);
		Diagram::add(l, r);
		//printf("%d\n", l);
	}
	clock_t start = clock();  
	for (int i = 0; i < MAX_V; i++) {
		Diagram::bfs(i);
	}
	clock_t end = clock();    
	printf("The process takes %d ms\n", end - start);
}
#endif
/*
The process takes 18502 ms
*/