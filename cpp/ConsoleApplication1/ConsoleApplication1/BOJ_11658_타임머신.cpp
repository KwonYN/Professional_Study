// BOJ_11658_타임머신
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(510)
#define MMAX	(6010)

typedef pair<int, int> pii;
int N, M;
vector<pii> edges[MMAX];
long long dst[NMAX];
bool isCycle;
const long long INF = (0x7fffffffffffffff);

void init() {
	for (int i = 1; i <= N; i++) {
		dst[i] = INF;
		edges[i].clear();
	}
	dst[1] = 0LL;
	isCycle = false;
}

void input() {
	int a, b, c;
	scanf("%d %d", &N, &M);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
	}
}

void bellman_ford() {
	for (int i = 1; i < N; i++) {	// N-1번 수행
		for (int j = 1; j <= N; j++) {
			for (pii node : edges[j]) {
				if (dst[j] == INF) continue;
				long long chk = 1LL*dst[j] + node.first;
				if (dst[node.second] > chk) {
					dst[node.second] = chk;
				}
			}
		}
	}
	for (int j = 1; j <= N; j++) {
		for (pii node : edges[j]) {
			if (dst[j] == INF) continue;
			long long chk = 1LL*dst[j] + node.first;
			if (dst[node.second] > chk) {
				isCycle = true;
				return;
			}
		}
	}
}

void output() {
	for (int i = 2; i <= N; i++) {
		if (dst[i] == INF) printf("-1\n");
		else printf("%lld\n", dst[i]);
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	input();
	bellman_ford();
	if (isCycle) printf("-1\n");
	else output();
	return 0;
}
#endif