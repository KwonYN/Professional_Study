// BOJ_1922_네트워크 연결
/*
	컴퓨터와 컴퓨터를 직접 연결하여야 한다.
	a와 b가 연결이 되어 있다는 말은 a에서 b로의 경로가 존재한다는 것을 의미한다.
	a에서 b를 연결하는 선이 있고, b와 c를 연결하는 선이 있으면 a와 c는 연결이 되어 있다.
	컴퓨터를 연결하는 비용을 최소로
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(100000)

pair<int, pair<int, int>> nw[MMAX+10];
int N, M, nw_idx, cost;
int parent[NMAX+10];
bool chk[NMAX+5];

void init() {
	nw_idx = cost = 0;
	for(int i = 1; i <= N; i++) {
		parent[i] = i;
	}
}

int find(int c) {
	if(parent[c] == c) return c;
	return parent[c] = find(parent[c]);
}

void ally(int c1, int c2) { parent[find(c1)] = find(c2); }

int main() {
	int a, b, c;
	scanf("%d", &N);
	scanf("%d", &M);
	init();
	for(int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		nw[nw_idx++] = { c, { a, b} };
	}
	sort(nw, nw+nw_idx);	// for 최소스패닝트리
	for(int i = 0; i < nw_idx; i++) {
		pair<int, pair<int, int>>tmp = nw[i];
		int c1 = tmp.second.first;
		int c2 = tmp.second.second;
		if(find(c1) != find(c2)) {
			ally(c1, c2);
			cost += tmp.first;
		}
	}
	printf("%d\n", cost);
	return 0;
}
