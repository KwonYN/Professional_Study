// (중) [교육A-0012] 보석 털이
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(10000)

typedef long long ll;
int T, N, val[NMAX+5], wei[NMAX+5], M;
ll dp[MMAX+5][2]; // [무게 i][j번 보석]

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &val[i], &wei[i]);
	}
	for (int i = 0; i <= M; i++) {
		dp[i][0] = dp[i][1] = 0;
	}
}

void operation() {
	//for (int i = 1; i <= M; i++) {
	//	for (int j = 1; j <= N; j++) {
	//		if (i >= wei[j]) dp[i][j&1] = max(dp[i-wei[j]][(j-1)&1] + 1LL*val[j], dp[i][(j-1)&1]);
	//		else dp[i][j&1] = dp[i][(j-1)&1];
	//		printf("%lld ", dp[i][j & 1]);
	//	}
	//	printf("\n");
	//}
	//for (int i = 0; i <= M; i++) {
	//	dp[i][0] = dp[i][1] = 0;
	//}
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++) {
			if (i >= wei[j]) dp[i][j & 1] = max(dp[i - wei[j]][(j - 1) & 1] + 1LL * val[j], dp[i][(j - 1) & 1]);
			else dp[i][j & 1] = dp[i][(j - 1) & 1];
			//printf("%lld ", dp[i][j & 1]);
		}
		//printf("\n");
	}
}

void output(int tc) { printf("#%d %lld\n", tc, dp[M][(N&1)]); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif