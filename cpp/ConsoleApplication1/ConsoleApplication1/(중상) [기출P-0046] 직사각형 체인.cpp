// (중상) [기출P-0046] 직사각형 체인
/*
	유의할 사항은,
	본 문제에서는 가로 길이가 0 이거나 세로 길이가 0 인 것도
	특별히 직사각형으로 허용하지만,
	가로, 세로 길이가 모두 0 인 것은
	직사각형으로 허용하지 않는다는 것이다.

	격자의 정보를 입력 받아
	모든 가능한 직사각형 체인의 개수를 출력하는 프로그램

	【 문제 풀이 】
	1000 * 1000이기 때문에 충분히 완탐으로 할 수 있지 않을까?
	But, 문제에서 결과값 % 10억7을 해주는 것으로 보아
		 일반적인 완탐으로는 시간초과가 날 것으로 예상되고,
		 엄청난 가지치기 또는 색다른 풀이가 필요해 보임.
	1 1 1		0(1) 1 1
	1 1 1	->	1    2 3
	1 1 1		1    3 6

	1 1 1		0(1) 1 1
	1 2 2	->	1    1 2
	1 2 1		1    2 4
	이렇게 직접 그려보면서 규칙성을 찾아감!

	2 3 4 5 ... (N+1)
	3 4 5 6 ... (N+2)
	4 5  . .
	5 6  .   .
	. .        .
	. .          .
	. .            .
	(N+1) (N+2)  ... (N+N)
	▼
	(1,2) (2,1)				=> 1, -1
	(1,3) (2,2) (3,1)		=> 2, 0, -2
	(1,4) (2,3) (3,2) (4,1) => 3, 1, -1, -3
	...
	(1,N) . . . . . .  (N,1)=> (N-1), (N-3), ... , (1-N)
	(2,N) . . . . . .  (N,2)=> (N-2), (N-4), ... , (2-N)
	(N,N)					=> (0)
	▼
	1) ↙방향으로 진행됨.
	2) chain[i][j]를 봄
	  ▶ y좌표 : 0 ~ chain[i][j], x좌표 : chain[i][j] ~ 0
	     → chain[i-y][j-x]에 쓰여있는 수를 더해줌
		   (단, i-y 또는 j-x가 < 1인 경우에는 X)
		   (그리고 매번 %MOD를 진행해줌!)
	3) (N, N)까지 2)를 진행
	4) 자연스레 chain[N][N]에 총 cnt가 쌓이게 됨!
	=> (2N-2)*N^2 최대는 약 2000 * 10만..!!

	답은 잘 나오지만, 시간 복잡도를 해결해야 함!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MOD		(1000000007)

int T, N, chain[NMAX+5][NMAX+5], path_cnt[NMAX+5][NMAX+5];

void input() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &chain[i][j]);
			path_cnt[i][j] = 0;
		}
	}
	path_cnt[1][1] = 1;
}

void get_path_cnt() { // 백트레킹(dfs)로도 가능할 것 같음!
	int x, dx;
	for (int s = 3; s <= N+1; s++) {
		for (int y = 1; y < s; y++) {
			x = s - y;
			//printf("(%d,%d) ", y, x);
			for (int dy = 0; dy <= chain[y][x]; dy++) {
				dx = chain[y][x] - dy;
				if (y - dy < 1 || x - dx < 1) continue;
				path_cnt[y][x] = (path_cnt[y][x] + path_cnt[y-dy][x-dx])%MOD;
			}
		}
		//printf("\n");
	}
	for (int s = N + 2; s <= 2 * N; s++) {
		for (int y = s - N; y <= N; y++) {
			x = s - y;
			//printf("(%d,%d) ", y, x);
			for (int dy = 0; dy <= chain[y][x]; dy++) {
				dx = chain[y][x] - dy;
				if (y - dy < 1 || x - dx < 1) continue;
				path_cnt[y][x] = (path_cnt[y][x] + path_cnt[y - dy][x - dx]) % MOD;
			}
		}
		//printf("\n");
	}
}

void output(int tc) { printf("#%d %d\n", tc, path_cnt[N][N]); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		get_path_cnt();
		output(tc);
	}
	return 0;
}
#endif