// BOJ_1753_최단경로
/*
	방향그래프
	시작 -> 다른 모든 정점으로의 최단경로?
	모든 간선의 가중치는 10 이하
	서로 다른 두 정점 사이에 여러 간선이 존재할 수 있음
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define VMAX	(20000)
#define INF	(0x7fffffff)
typedef pair<int, int> pii;

int V, E;
vector<pii> edges[VMAX+10];
int dijk[VMAX+10];

int main()
{
	int s, u, v, w;
	scanf("%d %d", &V, &E);
	for(int i = 1; i <= V; i++) dijk[i] = INF;
	scanf("%d", &s);
	for(int i = 1; i <= E; i++) {
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back({w, v});	// u -(w)-> v
	}

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, s});		dijk[s] = 0;
	while(!pq.empty()) {
		pii cur = pq.top();	pq.pop();
		for(pii next : edges[cur.second]) {
			if(dijk[next.second] > dijk[cur.second] + next.first) {
				dijk[next.second] = dijk[cur.second] + next.first;
				pq.push({dijk[next.second], next.second});
			}
		}
	}

	for(int i = 1; i <= V; i++) {
		if(dijk[i] == INF) printf("INF\n");
		else printf("%d\n", dijk[i]);
	}
	return 0;
}
#endif
