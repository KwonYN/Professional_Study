// BOJ_1904_01타일
/*
	각각의 타일들은 0 또는 1이 쓰여 있는 낱장의 타일들이다.
	공부를 방해하기 위해 0이 쓰여진 낱장의 타일들을 붙여서 한 쌍으로 이루어진 00 타일들을 만들었다.
		결국 현재 1 하나만으로 이루어진 타일 또는 0타일을 두 개 붙인 한 쌍의 00타일들만이 남게 되었다.
	타일로 더 이상 크기가 N인 모든 2진 수열을 만들 수 없게 되었다.
	N이 주어졌을 때 지원이가 만들 수 있는 모든 가짓수를 세는 것이다.
		단 타일들은 무한히 많은 것으로 가정하자.
	=> 00타일 또는 1타일임!

	[예시]
	N = 4
	=> 0000 0011 1001 1100 1111
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000010)
#define MOD		(15746)

int N, dp[NMAX];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &N);
	dp[0] = 0;	dp[1] = 1;	dp[2] = 2;
	for (int i = 3; i <= N; i++) {
		dp[i] = (dp[i-1] + dp[i-2])%MOD;
		//printf("%d\n", dp[i]);
	}
	printf("%d\n", dp[N]);
	return 0;
}
#endif