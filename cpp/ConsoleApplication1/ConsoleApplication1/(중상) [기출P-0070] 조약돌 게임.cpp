// (중상) [기출P-0070] 조약돌 게임
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(200010)

typedef long long ll;
struct EDGES {
	int cur_node, cur_score, next_node, next_score;
	bool flag;
};
int T, N, M, K;
EDGES edges[MMAX*2];
int edges_cnt;
vector<int> scores[NMAX];
ll result_score;

void init() {
	for (int i = 1; i <= N; i++) {
		scores[i].clear();
	}
	edges_cnt = 0;
}

void input_() {
	int a, b, p, q;
	scanf("%d %d %d", &N, &M, &K);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &a, &b, &p, &q);
		edges[++edges_cnt] = {a, p, b, q, false};
		scores[a].push_back(edges_cnt);
		edges[++edges_cnt] = {b, q, a, p, false};
		scores[b].push_back(edges_cnt);
	}
}

void output(int tc) { printf("#%d %lld %d\n", tc, result_score, ); }

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