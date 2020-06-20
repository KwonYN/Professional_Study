// BOJ_12869_뮤탈리스크
// DP + DFS
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
int scv[4];
int damage[7][4] = { {0, 0, 0, 0}, {0, 1, 3, 9}, {0, 1, 9, 3}, 
{0, 3, 1, 9}, {0, 3, 9, 1}, {0, 9, 1, 3}, {0, 9, 3, 1} };
int dp[61][61][61];

int get_min_cnt(int a, int b, int c) {
	if(a < 0) a = 0;
	if(b < 0) b = 0;
	if(c < 0) c = 0;
	
	for(int i = 1; i <= 6; i++) {
		if(a <= damage[i][1] && b <= damage[i][2] && c <= damage[i][3]) dp[a][b][c] = 1;
	}
	if(dp[a][b][c] != -1) return dp[a][b][c];

	dp[a][b][c] = 987654321;
	for(int j = 1; j <= 6; j++) {
		dp[a][b][c] = min(dp[a][b][c], get_min_cnt(a-damage[j][1], b-damage[j][2], c-damage[j][3])+1);
	}
	return dp[a][b][c];
}

int main()
{	
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) scanf("%d", &scv[i]);
	memset(dp, -1, sizeof(dp));
	dp[0][0][0] = 0;
	printf("%d\n", get_min_cnt(scv[1], scv[2], scv[3]));
	return 0;
}
#endif

// 처음에 푼 방법
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int hp[4];
int min_attack;

void mutalisk(int s1, int s2, int s3, int cnt) {
	if(cnt >= min_attack) return;
	if(s1 <= 0 && s2 <= 0 && s3 <= 0) {
		if(min_attack > cnt) min_attack = cnt;
		return;
	}
	if(s1 >= s2 && s1 >= s3) {
		mutalisk(s1-9, s2-3, s3-1, cnt+1);
		mutalisk(s1-9, s2-1, s3-3, cnt+1);
	}
	if(s2 >= s1 && s2 >= s3) {
		mutalisk(s1-3, s2-9, s3-1, cnt+1);
		mutalisk(s1-1, s2-9, s3-3, cnt+1);
	}
	if(s3 >= s1 && s3 >= s2) {	
		mutalisk(s1-1, s2-3, s3-9, cnt+1);
		mutalisk(s1-3, s2-1, s3-9, cnt+1);
	}
}

int main()
{
	min_attack = 0x7fffffff;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &hp[i]);
	mutalisk(hp[1], hp[2], hp[3], 0);
	printf("%d\n", min_attack);
	return 0;
}
#endif
