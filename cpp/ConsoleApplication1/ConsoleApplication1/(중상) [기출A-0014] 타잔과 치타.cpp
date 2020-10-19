// (중상) [기출A-0014] 타잔과 치타
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(5010)
#define CMAX	(5)

int T, N, K, C, L[NMAX];
int dp[CMAX][NMAX], n_max;

void get_DP() {
	;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &K, &C);
		n_max = -1;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &L[i]);
			for (int j = 0; j <= C; j++) {	// init
				dp[j][i] = 0;
			}
		}
		get_DP();
		printf("#%d %d\n", tc, n_max);
	}
	return 0;
}
#endif