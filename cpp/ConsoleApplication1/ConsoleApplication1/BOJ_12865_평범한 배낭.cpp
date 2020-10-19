// BOJ_12865_평범한 배낭
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100)

int N, K;
int W[NMAX+5], V[NMAX+5];
bool chk[NMAX+5];
int max_val;

void dfs(int d, int sum_val, int sum_weight) {
	if (sum_weight > K) return;
	max_val = max(max_val, sum_val);
	if (d >= N) return;
	for (int i = 1; i <= N; i++) {
		if(chk[i]) continue;
		chk[i] = true;
		dfs(d + 1, sum_val + V[i], sum_weight + W[i]);
		chk[i] = false;
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	max_val = -1;
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &W[i], &V[i]);
		chk[i] = false;	// init
	}
	dfs(0, 0, 0);
	printf("%d\n", max_val);
	return 0;
}
#endif

#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100)

struct STUFF { int W, V; };
int N, K;
STUFF stuff[NMAX+5];
int dp[NMAX+5];
int max_val;

bool cmp(STUFF s1, STUFF s2) {
	double a = 1.0 * s1.V / s1.W;
	double b = 1.0 * s2.V / s2.W;
	if (a < b) return true;
	else if (a == b) if (s1.W < s2.W) return true;
	return false;
}

int main() {
	freopen("in.txt", "r", stdin);
	max_val = -1;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &stuff[i].W, &stuff[i].V);
	}
	sort(stuff, stuff + N, cmp);
	/*for (int i = 0; i < N; i++) {
		printf("[ %d %d ]  ", stuff[i].W, stuff[i].V);
	}
	printf("\n");*/
	int sw, sv;
	for (int i = 0; i < N; i++) {
		sw = sv = 0;
		for (int j = i; j < N; j++) {
			sw += stuff[j].W;
			sv += stuff[j].V;
			if (sw > K) {
				sw -= stuff[j].W;
				sv -= stuff[j].V;
				break;
			}
		}
		max_val = max(max_val, sv);
	}
	printf("%d\n", max_val);
	return 0;
}
#endif

// BOJ_12865_평범한 배낭
/*
	dp[i][j] : 무게 제한(K) i
			   j번째 물건을 판단
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100)
#define KMAX	(100000)

int N, K;
int W[NMAX+5], V[NMAX+5];
int dp[KMAX+5][NMAX+5];

void input() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &W[i], &V[i]);
		dp[0][i] = 0;
	}
	for (int i = 1; i <= K; i++) dp[i][0] = 0;
}

void operation() {
	for (int i = 1; i <= K; i++) {
		for (int j = 1; j <= N; j++) {
			if (i >= W[j]) dp[i][j] = max(dp[i][j-1], dp[i-W[j]][j-1] + V[j]);
			else dp[i][j] = dp[i][j-1];
		}
	}
}

void output() { printf("%d\n", dp[K][N]); }

int main() {
	//freopen("in.txt", "r", stdin);
	input();
	operation();
	output();
	return 0;
}
#endif

