// BOJ_1238_파티
/*
	각각의 학생들은 파티에 참석하기 위해 
		걸어가서 다시 그들의 마을로 돌아와야 한다.
	하지만 이 학생들은 워낙 게을러서 최단 시간에 오고 가기를 원한다.
	이 도로들은 단방향이기 때문에
		아마 그들이 오고 가는 길이 다를지도 모른다.
	N명의 학생들 중 오고 가는데
		가장 많은 시간을 소비하는 학생은 누구일지 구하여라.
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(1010)
#define MMAX	(10010)
#define INF		(0x7fffffff)

typedef pair<int, int> pii;
int N, M, X;
vector<pii> edges[NMAX], reverse_edges[NMAX];
int dist1[NMAX], dist2[NMAX];

int main() {
	freopen("in.txt", "r", stdin);
	int a, b, c;
	// 1. 입력
	scanf("%d %d %d", &N, &M, &X);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		// 단방향 간선
		edges[a].push_back({ c, b });			// X에서 돌아갈 때!
		reverse_edges[b].push_back({ c, a });	// X로 갈 때
	}
	// 2. 거리 구하기
	for (int i = 1; i <= N; i++) dist1[i] = dist2 [i] = INF;	// init
	// 2-1. 각자의 집 -> X : reverse_edges
	priority_queue<pii, vector<pii>, greater<pii>> pq1;
	pq1.push({ 0, X });		dist1[X] = 0;
	while (!pq1.empty()) {
		pii cur = pq1.top();		pq1.pop();
		for (pii next : reverse_edges[cur.second]) {
			if (dist1[next.second] > dist1[cur.second] + next.first) {
				dist1[next.second] = dist1[cur.second] + next.first;
				pq1.push({ dist1[next.second], next.second });
			}
		}
	}
	// 2-2. X -> 되돌아가기 : edges
	priority_queue<pii, vector<pii>, greater<pii>> pq2;
	pq2.push({ 0, X });		dist2[X] = 0;
	while (!pq2.empty()) {
		pii cur = pq2.top();		pq2.pop();
		for (pii next : edges[cur.second]) {
			if (dist2[next.second] > dist2[cur.second] + next.first) {
				dist2[next.second] = dist2[cur.second] + next.first;
				pq2.push({ dist2[next.second], next.second });
			}
		}
	}
	// 3. 출력
	int max_stu = 0;
	for (int i = 1; i <= N; i++) {
		//printf("[%d]->[%d] : %d\n", i, X, dist1[i]);
		//printf("[%d]->[%d] : %d\n", X, i, dist2[i]);
		if (dist1[i] + dist2[i] > max_stu) max_stu = dist1[i] + dist2[i];
		//printf("%d\n", max_stu);
		//printf("=======================\n");
	}
	printf("%d\n", max_stu);
	return 0;
}
#endif