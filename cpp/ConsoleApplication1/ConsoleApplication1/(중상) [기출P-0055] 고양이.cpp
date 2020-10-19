// (중상) [기출P-0055] 고양이
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(300010)
#define MOD		(1000000007)

typedef long long ll;
int T, N;
int isCat[NMAX];
vector<int> edges[NMAX]; 
ll dp[NMAX][2];

void input_() {
	int tmp1, tmp2;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &isCat[i]);
		edges[i].clear();
	}
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &tmp1, &tmp2);
		edges[tmp1].push_back(tmp2);
		edges[tmp2].push_back(tmp1);
	}
}

void dfs(int cur, int par) {
	printf("[ %d -> %d ]\n", par, cur);
	dp[cur][1] = (ll)isCat[cur];
	dp[cur][0] = -1LL*(dp[cur][1] - 1);
	printf("dp[%d][1]=%lld\n", cur, dp[cur][1]);
	printf("dp[%d][0]=%lld\n", cur, dp[cur][0]);
	for (int next : edges[cur]) {
		if (next == par) continue;
		printf("=========in!!=========\n");
		dfs(next, cur);
		dp[cur][1] = (2 * dp[cur][1] * dp[next][0] + (dp[cur][1] + dp[cur][0]) * dp[next][1]) % MOD;
		dp[cur][0] = (2 * dp[cur][0] * dp[next][0] + dp[cur][0] * dp[next][1]) % MOD;
		printf("=========out!=========\n");
		printf("dp[%d][1]=%lld\n", cur, dp[cur][1]);
		printf("dp[%d][0]=%lld\n", cur, dp[cur][0]);
	}
}

void output(int tc) { printf("#%d %lld\n", tc, (dp[1][0] + dp[1][1])%MOD); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		dfs(1, 0);
		printf("\n");
		output(tc);
	}
	return 0;
}
#endif