// (중) [교육A-0006] Assembly Line Scheduling 
/*
	[Idea]
	- 사실 그리 어렵지 않았던 DP 문제!! 아주 기본 중의 기본이었음!!
	- ★어떤 라인(x)에서의 y번째 공정 입장에서 생각을 해본다면,
	  같은 라인(x) 전 공정(y-1)에서 끝나서 바로 다음 공정으로 왔거나
	  다른 라인((x+1)&1) 전 공정(y1)에서 끝나서 생산라인 바꾼 후 현재로 온 경우!!
	  이 두 경우 밖에 없음!!
	  => dp[i][j] = min(dp[i][j-1], dp[(i+1)&1][j-1]+T[(i+1)&1][j-1]) + S[i][j];
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(300010)

int TC, N, e1, e2, x1, x2;
int S[2][NMAX], T[2][NMAX], dp[2][NMAX];

void input() {
	scanf("%d %d %d %d %d", &N, &e1, &e2, &x1, &x2);
	dp[0][0] = dp[1][0] = 0;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &S[0][i]);
		dp[0][i] = dp[1][i] = 0;
	}
	for(int i = 1; i <= N; i++) {
		scanf("%d", &S[1][i]);
	}
	for(int i = 1; i < N; i++) {
		scanf("%d", &T[0][i]);
	}
	for(int i = 1; i < N; i++) {
		scanf("%d", &T[1][i]);
	}
}

void get_dp() {
	dp[0][1] = S[0][1]+e1;
	dp[1][1] = S[1][1]+e2;
	for(int i = 2; i <= N; i++) {
		for(int j = 0; j <= 1; j++) {
			int idx = (j+1)&1;
			dp[j][i] = min(dp[idx][i-1]+T[idx][i-1], dp[j][i-1])+S[j][i];
		}
	}
}

void output(int tc) {
	printf("#%d %d\n", tc, min(dp[0][N]+x1, dp[1][N]+x2));
}

int main() {
	scanf("%d", &TC);
	for(int tc = 1; tc <= TC; tc++) {
		input();
		get_dp();
		output(tc);
	}
	return 0;
}
#endif