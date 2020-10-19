// BOJ_1854_K번째 최단경로 찾기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(1010)
#define MMAX	(2000010)
#define KMAX	(110)

typedef pair<int, int> pii;
int N, M, K;	// 도시 개수, 도로 수
vector<pii> edges[NMAX];
priority_queue<int, vector<int>, less<int>> dijk[NMAX];

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		while (!dijk[i].empty()) dijk[i].pop();
	}
}

void input() {
	int a, b, c;
	scanf("%d %d %d", &N, &M, &K);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
	}
}

void dijkstra() {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({ 0, 1 });		dijk[1].push(0);
	while (!pq.empty()) {
		pii out = pq.top();		pq.pop();
		for (pii node : edges[out.second]) {
			int chk = out.first + node.first;
			if (dijk[node.second].size() < K) {
				dijk[node.second].push(chk);
				pq.push({chk, node.second});
			}
			else {
				if (dijk[node.second].top() > chk) {
					dijk[node.second].pop();
					dijk[node.second].push(chk);
					pq.push({chk, node.second});
				}
			}
		}
	}
}

void output() {
	for (int i = 1; i <= N; i++) {
		if (dijk[i].size() == K) printf("%d\n", dijk[i].top());
		else printf("-1\n");
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	input();
	dijkstra();
	output();
	return 0;
}
#endif