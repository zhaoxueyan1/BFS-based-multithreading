#include "pch.h"
#include "ThreadPool.h"
#include "ThreadSafeQueue.h"
#include <time.h>
#include <iostream>
#if 0

using namespace std;

const int MAX_E = 5105039+1;
const int MAX_V = 875713+1;

typedef pair<int, int> P;
//typedef pair<function<void(int x, int y)>, pair<int, int>> PCB;

namespace Diagram {

	struct node {
		int to;
		int nex;
	}e[MAX_E];
	struct state {
		int to, cost;
	};
	int dgree[MAX_V];
	int cnt;
	int head[MAX_V];
	int d[MAX_V];
	bool vis[MAX_V];
	ThreadPool p;
	ThreadSafeQueue<state>Q;
	void init() {
		memset(head, -1, sizeof(head));
		cnt = 0;
		memset(vis, 0, sizeof(vis));
	}
	void add(int u, int v) {
		e[cnt].to = v;
		e[cnt].nex = head[u];
		head[u] = cnt++;
		//cout << e[cnt - 1].nex<<endl;
		if (e[cnt-1].nex > MAX_E) {
			printf("error!!!!!");
		}
	}

	void Step(state p) {
		for (int i = head[p.to]; ~i; i = e[i].nex) {
			if (!vis[e[i].to]) {
				//printf("%d\n", e[i].to);
				if (e[i].to > 1e7 )
				{
					printf("%d %d %d", p.to, e[i].to, p.cost);
				}
				Q.Push({ e[i].to, p.cost + 1 });
			}
		}
	}

	void bfs(int s = 0) {
		//p.start(4);
		Q.Push({s,0});
		//vis[s] = true;
		d[s] = 0;
		while (!Q.IsEmpty()) {
			state u = Q.WaitAndPop();
			if (u.to > 1e7) {
				printf("%d\n",u.to);
			}
			if (vis[u.to]) continue;
			vis[u.to] = true;
			d[u.to] = u.cost;
			Step({u.to,u.cost});
			//p.finish();
		}
	}

};

int main()
{
	int l, r;
	freopen("C://Users//User//Documents//code//中科院//web-Google.txt","r",stdin);
	int v = 875713;
	int e = 5105039;
	Diagram::init();

	for (int i = 0; i < e; i++) {
		scanf("%d %d", &l, &r);
		Diagram::add(l, r);
		//printf("%d\n", l);
	}
	clock_t start = clock();
	Diagram::bfs(0);
	clock_t end = clock();
	printf("The process takes %d ms\n", end - start);
}
#endif
/*
The process takes 18502 ms
*/	