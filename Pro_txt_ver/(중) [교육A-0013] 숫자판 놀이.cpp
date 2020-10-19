// (중) [교육A-0013] 숫자판 놀이
/*
	숫자판의 첫 행의 임의의 칸에서 시작하여
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMMAX	(1010)
#define MINUS_INF	(-987654321)

int T, N, M, map[NMMAX][NMMAX], dp[NMMAX][NMMAX];

void input() {
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
			dp[i][j] = 0;
		}
		dp[i][0] = dp[i][M+1] = MINUS_INF;		// 테두리
	}
	//for(int i = 1; i <= M; i++) dp[0][i] = dp[N+1][i] = 0;	// 테두리
}

void get_max_move() {
	for(int j = 1; j <= M; j++) dp[1][j] = map[1][j];
	for(int i = 2; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			dp[i][j] = max(dp[i-1][j], max(dp[i-1][j-1], dp[i-1][j+1])) + map[i][j];
		}
	}
}

void output(int tc) { 
	int max_num = dp[N][1];
	for(int i = 2; i <= M; i++) max_num = max(max_num, dp[N][i]);
	printf("#%d %d\n", tc, max_num);
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_max_move();
		output(tc);
	}
	return 0;
}
#endif