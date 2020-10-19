// (중상) [교육P-0007] 군사 도로망
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MKMAX	(250010)

typedef long long ll;
struct BRIDGE_INFO { int s, e, c; };
int T, N, M, K;
BRIDGE_INFO destroy[MKMAX];
BRIDGE_INFO construct[MKMAX];
int parent[NMAX];
ll total_min_cost;

// 오름차순으로 정렬
bool cmp(const BRIDGE_INFO &b1, const BRIDGE_INFO &b2) {
	return b1.c < b2.c;
}

void input() {
	int a, b, c;
	total_min_cost = 0LL;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) parent[i] = i;	// init
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		destroy[i] = {a, b, c};
		// 우선 이미 있는 도로들을 파괴한다.
		total_min_cost += 1LL*c;
	}
	sort(destroy+1, destroy+M+1, cmp); // M부터 빼야
	for (int i = 1; i <= K; i++) {
		scanf("%d %d %d", &a, &b, &c);
		construct[i] = {a, b, c};
	}
	sort(construct+1, construct+K+1, cmp); // 1부터 빼야
}

int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

bool chk_union(int v1, int v2) {
	return find(v1) == find(v2);
}

void _union(int v1, int v2) {
	v1 = find(v1);
	v2 = find(v2);
	parent[v1] = v2;
}

void control_bridge() {
	int cnt = 0;
	// 파괴했던 도로들 중 제거비용이 비싼 순으로 되살림
	for (int i = M; i >= 1; i--) {
		BRIDGE_INFO tmp = destroy[i];
		if (!chk_union(tmp.s, tmp.e)) {
			_union(tmp.s, tmp.e);
			total_min_cost -= 1LL*tmp.c;
			cnt++;
		}
	}
	if (cnt >= N-1) return;
	// 도로 만드는 것이 가능한 경우에는, 만드는 비용이 적은 순으로 만듦
	for (int i = 1; i <= K; i++) {
		BRIDGE_INFO tmp = construct[i];
		if (!chk_union(tmp.s, tmp.e)) {
			_union(tmp.s, tmp.e);
			total_min_cost += 1LL*tmp.c;
			if(++cnt >= N-1) break;
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_min_cost); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		control_bridge();
		output(tc);
	}
	return 0;
}
#endif