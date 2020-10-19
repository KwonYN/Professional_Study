// BOJ_17404_RGB�Ÿ�2
/*
	N���� �� (1~N)
	���� ��/��/�� �� �ϳ��� ������ ĥ�ؾ� ��
	������ ���� ����, �ʷ�, �Ķ����� ĥ�ϴ� ����� �־����� ��, 
		�Ʒ� ��Ģ�� �����ϸ鼭 ��� ���� ĥ�ϴ� ����� 
		�ּڰ��� ���غ���.
		1) N���� �� != 1���� ��
					  1���� �� != 2���� ��
		2) N-1���� �� != N���� ��
						N���� �� != 1���� ��
		3) i-1���� �� != i���� ��
						i���� �� != i+1���� ��
	N : 2 ~ 1000
	RGB ������ �־���
	��� : 1 ~ 1000

	���� : https://neohtux.tistory.com/171
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1010)
#define INF		(NMAX*NMAX)

int N;
int cost[NMAX][3];
int dp[NMAX][3], answer;

int main() {
	freopen("in.txt", "r", stdin);
	int r, g, b;
	// input
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &r, &g, &b);
		cost[i][0] = r;
		cost[i][1] = g;
		cost[i][2] = b;
		for (int j = 0; j < 3; j++) dp[i][j] = INF;	// init
	}
	// get dp
	answer = INF;
	for (int s = 0; s < 3; s++) {	// 1�� ���� ����
		// dp[1][]
		for (int j = 0; j < 3; j++) {
			if (s == j) dp[1][j] = cost[1][j];
			else dp[1][j] = INF;
		}
		// dp[2][] ~ dp[N-1][]
		for (int i = 2; i < N; i++) {
			for (int j = 0; j < 3; j++) {
				dp[i][j] = min(dp[i-1][(j+1)%3], dp[i-1][(j+2)%3]) + cost[i][j];
			}
		}
		// dp[N][]
		for (int j = 0; j < 3; j++) {
			if (s == j) dp[N][j] = INF;
			else dp[N][j] = min(dp[N-1][(j+1)%3], dp[N-1][(j+2)%3])+cost[N][j];
			answer = min(answer, dp[N][j]);
		}
	}
	// output
	printf("%d\n", answer);
	return 0;
}
#endif