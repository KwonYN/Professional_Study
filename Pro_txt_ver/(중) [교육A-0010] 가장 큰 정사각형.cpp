// (중) [교육A-0010] 가장 큰 정사각형
// 제한시간 초과 코드!!!!!;;;;;;;;;;;;;;;
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMMAX	(1010)

int T, N, M, grid[NMMAX][NMMAX], result;

int get_num(int start_y, int start_x, int size) {
	return grid[start_y][start_x] + grid[start_y-size][start_x-size]
	- (grid[start_y-size][start_x] + grid[start_y][start_x-size]);
}

void input() {
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			scanf("%d", &grid[i][j]);
			grid[i][j] += grid[i][j-1];	// 누적합
		}
		for(int j = 1; j <= M; j++) {
			grid[i][j] += grid[i-1][j];
			//printf("%d ", grid[i][j]);
		}
		//printf("\n");
	}
	//printf("\n");
}

void get_cnt() {
	int size;
	result = 0;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			size = min(i, j);
			for(int k = 1; k <= size; k++) {
				if(k <= result) continue;
				int chk = get_num(i, j, k);
				if(!chk) result = max(result, k);
			}
		}
	}
}

void output(int tc) {
	printf("#%d %d\n", tc, result);
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_cnt();
		output(tc);
	}
	return 0;
}
#endif



/*
	이중 for문, 아니 사실 거의 3중에 육박하는 for문을 돌렸기 때문에 제한시간 초과되었음!!
	[Idea]
	- 점화식 -> n이 커지더라도 그 이전의 값이 보장(?)되는지 보자!!
	- 입력된 이차원 배열에서(grid)
	  ....
	  .
	  .
	      O  O
		  O  이렇게 [i-1][j-1]와 [i-1][j], [i][j-1]가 모두 0이라면 길이 2가 될 수 있음!!
		  
	  =>
	  dp 배열 기준으로
	  
	     1 1
	     1 이런 상황이 되었다는 것은,
		 
		 1(3개)의 [i-1][j-1]와 [i-1][j], [i][j-1] 방향의 grid 모두 0이라는 것!!
		 따라서 이 곳의 길이는 2가 될 수 있는 것이다!!!
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMMAX	(1010)

int T, N, M, grid[NMMAX][NMMAX], dp[NMMAX][NMMAX], result;

void input() {
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			scanf("%d", &grid[i][j]);
			dp[i][j] = 0;	// init
		}
	}
}

void get_max_len() {
	result = 0;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			if(grid[i][j]) dp[i][j] = 0;
			else {
				dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]))+1;
			}
			result = max(result, dp[i][j]);
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, result); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_max_len();
		output(tc);
	}
	return 0;
}
#endif