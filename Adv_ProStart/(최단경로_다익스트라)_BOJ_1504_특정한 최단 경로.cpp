// BOJ_1504_특정한 최단 경로
/*
	방향성 없는 그래프!
	1 -> N 최단 거리로 이동!
	  1) 임의로 주어진 두 정점은 반드시 통과해야
	  2) 한 번 이동했던 정점은 물론, 한 번 이동했던 간선도 다시 이동 가능
	  3) 단, 반드시 최단 경로로 이동해야 함
*/
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX	(800)
#define INF	(0x7fffffff)

typedef pair<int, int> pii;
int N, E;
vector<pii> edges[MAX+10];
int dijk[MAX+10];
bool chk;

int dijkstra(int s, int e) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for(int i = 1; i <= N; i++) dijk[i] = INF;
	pq.push({0, s});	dijk[s] = 0;
	while(!pq.empty()) {
		pii cur = pq.top();		pq.pop();
		if(cur.second == e) break;
		for(pii next : edges[cur.second]) {
			if(dijk[next.second] > dijk[cur.second] + next.first) {
				dijk[next.second] = dijk[cur.second] + next.first;
				pq.push({dijk[next.second], next.second});
			}
		}
	}
	return dijk[e];
}

int main() {
	int a, b, c, s, e;
	scanf("%d %d", &N, &E);
	for(int i = 1; i <= E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({c, b});
		edges[b].push_back({c, a}); // a <--(c)--> b
	}
	scanf("%d %d", &s, &e);

	int _1s = dijkstra(1, s);
	int _1e = dijkstra(1, e);
	int se = dijkstra(s, e);
	int sn = dijkstra(s, N);
	int en = dijkstra(e, N);
	int result1 = INF, result2 = INF;
	chk = false;
	if(_1s != INF && se != INF && en != INF) { chk = true; result1 = _1s + se + en; }
	if(_1e != INF && se != INF && sn != INF) { chk = true; result2 = _1e + se + sn; }
	if(chk) printf("%d\n", ( (result1 > result2) ? result2 : result1 ));
	else printf("%d\n", -1);
	return 0;
}
