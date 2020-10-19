// [기출P-0039] 개미 굴 파기
/*
	N-1개의 굴로 연결되어 있어야 충족
	MST!!?
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(300010)

typedef pair<int, int> pii;
typedef long long ll;
int T, N;
vector<pii> edges[NMAX];
int parent[NMAX];
int result_cnt;

void init() {
	result_cnt = 0;
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		parent[i] = i;
	}
}

void input_() {
	int a, b, c;
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
		edges[b].push_back({ c, a });
	}
}

int find(int v) {
	if (parent[v] == v) return v;
	return parent[v] = find(parent[v]);
}

bool chk_union(int v1, int v2) {
	return find(v1) != find(v2);
}

void _union(int v1, int v2) {
	v1 = find(v1);
	v2 = find(v2);
	parent[v1] = v2;
}

void output(int tc) { printf("#%d %d\n", tc, result_cnt); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		output(tc);
	}
	return 0;
}
#endif