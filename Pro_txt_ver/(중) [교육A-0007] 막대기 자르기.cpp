//  (중) [교육A-0007] 막대기 자르기
/*
	[Idea]
	- 역시나 기본 중의 기본적인 DP 문제
	- dp의 인덱스는 길이를 의미!
	  즉, dp[i]는 길이가 i인 막대기를 어떻게 잘랐든 간에 가장 가치가 높은 애임!
	  => dp[i] = max(dp[i], dp[i-j]+value[j]);
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(3010)

int T, N, value[NMAX], dp[NMAX];

void input() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &value[i]);
		dp[i] = value[i];
	}
}

void get_max_acc_value() {
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j < i; j++) {
			dp[i] = max(dp[i], dp[i-j]+value[j]);
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, dp[N]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_max_acc_value();
		output(tc);
	}
	return 0;
}
#endif

