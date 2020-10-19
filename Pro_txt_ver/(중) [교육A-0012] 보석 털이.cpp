// (중) [교육A-0012] 보석 털이 
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1010)
#define MMAX	(10010)

typedef long long ll;
int T, N, price[NMAX], weight[NMAX], M;
ll dp[2][MMAX];

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		for(int i = 1; i <= N; i++) {
			scanf("%d %d", &price[i], &weight[i]);
		}
		for(int i = 1; i <= M; i++) { dp[0][i] = dp[1][i] = 0; }
		
		// [문제 잘 읽기!!] N 종류의 보석이 있고, 각각 한 개씩 있다는 것!!
		// -> N개를 각각 선택 할까 말까? 의 조합으로 푼다면 : O(2^N)이므로 옳지 않음!
		for(int i = 1; i <= N; i++) {	// N개의 보석 각각에 대해서!
			// 보통 dp[N][M]을 선언해서 사용함
			for(int j = 1; j < weight[i]; j++) { dp[i&1][j] = dp[(i+1)&1][j]; }
			for(int j = weight[i]; j <= M; j++) {
				dp[i&1][j] = max(dp[(i+1)&1][j], dp[(i+1)&1][j-weight[i]]+price[i]);	// 홀짝홀짝... -> 01010101... 순으로
			}
		}
		printf("#%d %lld\n", tc, dp[N&1][M]);
	}
	return 0;
}
#endif


// 이전 코드s
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
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++) {
			if (i >= wei[j]) dp[i][j&1] = max(dp[i-wei[j]][(j-1)&1] + 1LL*val[j], dp[i][(j-1)&1]);
			else dp[i][j&1] = dp[i][(j-1)&1];
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, dp[M][N&1]); }

int main() {
	//freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif

#if 0
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(10000)
#define MAX(a, b)		( ( (a)  > (b) ) ? (a) : (b) )

int T, N, C[NMAX+5], W[NMAX+5], M;
long long DP[2][MMAX + 5];

void make_DP() {
	for (int i = 1; i <= N; i++) { // 모든 보석에 대해서
		for (int j = 0; j < W[i]; j++) DP[i&1][j] = DP[(i - 1)&1][j];
		for (int j = W[i]; j <= M; j++) { // 모든 무게에 대해서
			DP[i&1][j] = MAX(DP[(i - 1)&1][j - W[i]] + C[i], DP[(i - 1)&1][j]);
		}
	}
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
        for(int i = 0; i <= M; i++) DP[0][i] = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &C[i], &W[i]);
		}
		make_DP();
		printf("#%d %lld\n", tc, DP[N&1][M]);
	}
	return 0;
}
#endif