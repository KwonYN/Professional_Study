// (중) [교육A-0003] 폐지 줍기
/*
	[Idea]
	- 대각선 DP : 사실 너무 오버임!!
	  그냥 2차원 배열 일반적으로 돌면서 DP 기록해줘도 무방!!
	- ★각 노드(격자)에서 생각을 해본다면,
	  val의 대상은 바로 위 or 왼쪽에서 온 애를 누적시키는 것!
	  => dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + city[i][j];\
*/

// 더더 간결하게
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(210)

int T, N, dp[NMAX][NMAX];

void process() {
    int trash;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
            scanf("%d", &trash);
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + trash;
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, dp[N][N]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		process();
		output(tc);
	}
	return 0;
}
#endif


// 원래 코드보다 간결하게`
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(210)

int T, N, city[NMAX][NMAX], dp[NMAX][NMAX];

void input() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			scanf("%d", &city[i][j]);
		}
	}
}

void operation() { // 대각선 for문
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + city[i][j];
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, dp[N][N]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif


// 원래 코드
# if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(210)

int T, N, city[NMAX][NMAX], dp[NMAX][NMAX];
int result;

void input() {
	//result = 0;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			scanf("%d", &city[i][j]);
			dp[i][j] = 0;
		}
		city[0][i] = city[N+1][i] = city[i][0] = city[i][N+1] = 0;
	}
}

// dfs로 풀면 제한시간 초과!!
/*
void dfs(int y, int x, int sum) {
	if(city[y][x] < 0) return;
	sum += city[y][x];
	if(y == N && x == N) {
		result = max(result, sum);
		return;
	}
	dfs(y, x+1, sum);
	dfs(y+1, x, sum);
}
*/

void operation() { // 대각선 for문
	dp[1][1] = city[1][1];
	for(int i = 2; i <= N+1; i++) {
		for(int j = 1; j < i; j++) {
			dp[j][i-j] = max(dp[j-1][i-j], dp[j][i-j-1]) + city[j][i-j];
		}
	}
	for(int i = N+2; i <= 2*N; i++) {
		for(int j = i-N; j <= N; j++) {
			dp[j][i-j] = max(dp[j-1][i-j], dp[j][i-j-1]) + city[j][i-j];
		}
	}
	
}

//void output(int tc) { printf("#%d %d\n", tc, result); }
void output(int tc) { printf("#%d %d\n", tc, dp[N][N]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		//dfs(1, 1, 0);
		operation();
		output(tc);
	}
	return 0;
}
#endif
