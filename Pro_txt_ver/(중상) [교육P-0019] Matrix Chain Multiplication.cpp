// (중상) [교육P-0019] Matrix Chain Multiplication
/*
	행렬 곱셈  A1A2A3…An을 계산하는데 필요한 연산의 최수 횟수를 구하는 프로그램
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(510)
#define INF		(0x7fffffff)	

typedef pair<int, int> pii;
int T, N;
pii _size[NMAX];
int dp[NMAX][NMAX];

void input() {
	int a;
	scanf("%d", &N);
	for(int i = 1; i <= N+1; i++) {
		scanf("%d", &a);
		_size[i-1].second = _size[i].first = a;
	}
	_size[0].second = _size[N+1].first = 0;
	
	// init
	for(int i = 1; i < N; i++) {
		for(int j = i+1; j <= N; j++) {
			dp[i][j] = INF;
		}
	}
}

void get_operation_cnt() {
	for(int i = 1; i <= N; i++) {
		dp[i][i] = 0;
	}
	for(int i = 1; i < N; i++) {	// 두 좌표 차(열이 행보다 더 큼)
		for(int j = i+1; j <= N; j++) {	// 열
			//j-i부터 j까지!!
			int s = j-i, e = j;
			for(int m = s; m < e; m++) {
				// s~m, m+1~e
				dp[s][e] = min(dp[s][e], 
								dp[s][m] + dp[m+1][e] + _size[s].first*_size[m].second*_size[e].second);
			}
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, dp[1][N]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_operation_cnt();
		output(tc);
	}
	return 0;
}
#endif