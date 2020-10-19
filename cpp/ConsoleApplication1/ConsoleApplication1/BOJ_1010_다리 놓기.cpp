// BOJ_1010_다리 놓기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMMAX	(31)

typedef long long ll;
int T, N, M;
ll dp[NMMAX][NMMAX];	// [N][M] : N <= M

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	// get dp
	for (int i = 0; i <= 30; i++) dp[0][i] = 0LL;
	for (int i = 1; i <= 30; i++) dp[1][i] = 1LL*i;
	for (int i = 2; i <= 30; i++) {	// M
		dp[i][i] = 1LL;
		for (int j = i+1; j < NMMAX; j++) {	// N : N <= M
			dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
		}
	}
	// test case
	for (int tc = 1; tc <= T; tc++) {
		// input
		scanf("%d %d", &N, &M);	
		// output
		printf("%lld\n", dp[N][M]);
	}
	return 0;
}
#endif