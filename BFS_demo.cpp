#include "pch.h"
#include "ThreadPool.h"
#include "ThreadSafeQueue.h"
#include <time.h>
#include <iostream>
#include <set>
#include <bitset>
#include <assert.h>
#if 1

using namespace std;

const int MAX_E = 5105039 + 1;
const int MAX_V = 875713 + 1;

int v = 875713;
int e = 5105039;
typedef pair<int, int> P;
//typedef pair<function<void(int x, int y)>, pair<int, int>> PCB;

struct node {
	int to;
	int nex;
};
typedef std::bitset<MAX_V> vec;

int pre[MAX_V];

namespace Diagram {
	int head[MAX_V];
	int rev_head[MAX_V];
	node e[MAX_E];
	node rev_e[MAX_E];
	bool vis[MAX_V];
	int cnt;

	void init() {
		cnt = 0;
		memset(head, -1, sizeof(head));
		memset(rev_head, -1, sizeof(rev_head));
		memset(vis, 0, sizeof(vis));
	}

	void add(int u, int v) {
		e[cnt].to = v;
		e[cnt].nex = head[u];
		rev_e[cnt].to = v;
		rev_e[cnt].nex = rev_head[u];
		rev_head[u] = cnt;
		head[u] = cnt++;
		assert(e[cnt - 1].nex <= MAX_E);
	}

	std::bitset<MAX_V>&& get_rol_vector(int i) {
		std::bitset<MAX_V> res;
		for (int j = Diagram::head[i]; ~j; j = Diagram::e[j].nex) {
			res.set(e[j].to);
		}
		return std::move(res);
	}
	
	std::bitset<MAX_V>&& get_col_vector(int i) {
		std::bitset<MAX_V> res;
		for (int j = Diagram::rev_head[i]; ~j; j = Diagram::rev_e[j].nex) {
			res.set(rev_e[j].to);
		}
		return std::move(res);
	}

};

struct state {
	int to, cost;
};

ThreadPool p;
vec&& Maper(vec& t,vector<int>&S) {
	vec res;
	for (int i = 0; i < S.size(); i++) {
		vec&& col = Diagram::get_col_vector(S[i]);
		vec&& rol = Diagram::get_rol_vector(S[i]);
		vec tmp = col & t;
		pre[S[i]] = __builtin_ctz(tmp);
		res |= rol;
	}
	return std::move(res);
}

vec&& Reducer(vector<vec>&& t) {
	vec res;
	for (vec& i : t)
		res |= i;
	return std::move(res);
}

void bfs(int s = 0) {
	//p.start(4);
	//sparse diagram use vector, bitset is better if not.
	vector<int> S;//
	vec Vis;
	//vis[s] = true;
	S.push_back(0);
	pre[s] = -1;
	while (Vis.count() != v) {
		vec t;
		std::for_each(S.begin(), S.end(), [&](int tt) {t.set(tt);});
		vec&& res = Maper(t,S);
		res &= ~Vis;
		Vis |= res;
		S.clear();
		S = res;
	}
}

int main()
{
	int l, r;
	freopen("C://Users//User//Documents//code//ÖÐ¿ÆÔº//web-Google.txt", "r", stdin);

	Diagram::init();

	for (int i = 0; i < e; i++) {
		scanf("%d %d", &l, &r);
		Diagram::add(l, r);
		//printf("%d\n", l);
	}
	clock_t start = clock();
	bfs(0);
	clock_t end = clock();
	printf("The process takes %d ms\n", end - start);
}
#endif
/*
The process takes 18502 ms
*/