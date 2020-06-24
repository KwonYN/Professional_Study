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
#include <queue>	// 4
#include <vector>	// 4
using namespace std;
#define NMAX	(1000)
#define MOD		(1000000007)

struct NODE { int y, x; };	// 4
class cmp	// 4
{
public:
	bool operator()(NODE& n1, NODE& n2) {	// 내림차순
		if (n1.y + n1.x < n2.y + n2.x) return true;
		if (n1.y + n1.x == n2.y + n2.x) {
			if (n1.y > n2.y) return true;
		}
		return false;
	}
};
int T, N, chain[NMAX + 5][NMAX + 5], path_cnt[NMAX + 5][NMAX + 5];
bool chk[NMAX + 5][NMAX + 5];	// 4 : 중복제거
//long long process_cnt;
/*
				▼
	나름 가지치기를 해보았지만
	for문이 tc 내에서 최악의 경우 몇 번 돌아가나 구해본 결과,
	1억2천만번 정도가 최악이었음. (실제 최악의 케이스의 경우에는 더 클수도..)
	for문을 덜 돌도록 최적화해주어야 함!!
*/

void input() {
	//process_cnt = 0LL;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			path_cnt[i][j] = 0;
			chk[i][j] = false;
			scanf("%d", &chain[i][j]);

		}
	}
	//path_cnt[1][1] = 1;
	path_cnt[N][N] = 1;
}

// 1
/*
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
*/

// 2
/*
void get_path_cnt() {
	int x, dx, val, x1, y1, x2, y2;
	for (int s = 3; s <= N + 1; s++) {
		for (int y = 1; y < s; y++) {
			x = s - y;
			val = chain[y][x];
			if (x < val) {
				y1 = y - 1 - (val - x);
				x1 = 1;
			}
			else {
				y1 = y;
				x1 = x - val;
			}
			if (y < val) {
				y2 = 1;
				x2 = x - 1 - (val - y);
			}
			else {
				y2 = y - val;
				x2 = x;
			}
			for (int i = x1; i <= x2; i++) {
				//process_cnt++;
				path_cnt[y][x] = (path_cnt[y][x] + path_cnt[y + x - i - val][i])%MOD;
			}
		}
	}
	for (int s = N + 2; s <= 2 * N; s++) {
		for (int y = s - N; y <= N; y++) {
			x = s - y;
			val = chain[y][x];
			if (x < val) {
				y1 = y - 1 - (val - x);
				x1 = 1;
			}
			else {
				y1 = y;
				x1 = x - val;
			}
			if (y < val) {
				y2 = 1;
				x2 = x - 1 - (val - y);
			}
			else {
				y2 = y - val;
				x2 = x;
			}
			for (int i = x1; i <= x2; i++) {
				//process_cnt++;
				path_cnt[y][x] = (path_cnt[y][x] + path_cnt[y + x - i - val][i]) % MOD;
			}
		}
	}
}
*/

// 3
/*
void get_path_cnt(int y, int x) {
	int x1, x2, y1, y2, val;
	if (y == 1 && x == 1) {
		result++;
		result %= MOD;
		printf("result = %d\n", result);
		return;
	}
	val = chain[y][x];
	if (x < val) {
		y1 = y - 1 - (val - x);
		x1 = 1;
	}
	else {
		y1 = y;
		x1 = x - val;
	}
	if (y < val) {
		y2 = 1;
		x2 = x - 1 - (val - y);
	}
	else {
		y2 = y - val;
		x2 = x;
	}
	for (int i = x1; i <= x2; i++) {
		get_path_cnt(y + x - i - val, i);
	}
}
*/

// 4 :  (N, N) → (1, 1)
void get_path_cnt() {
	priority_queue<NODE, vector<NODE>, cmp> pq;	// y+x 내림차순
	int val, x1, x2, ny;
	pq.push({ N, N });			chk[N][N] = true;
	while (!pq.empty()) {
		NODE cur = pq.top();		pq.pop();
		//printf("(%d, %d)\n", cur.y, cur.x);
		//printf("path_cnt[%d][%d] = %d\n", cur.y, cur.x, path_cnt[cur.y][cur.x]);
		val = chain[cur.y][cur.x];
		if (cur.x < val) x1 = 1;
		else x1 = cur.x - val;
		if (cur.y < val) x2 = cur.x - 1 - (val - cur.y);
		else x2 = cur.x;
		for (int i = x1; i <= x2; i++) {
			ny = cur.y + cur.x - i - val;
			if (ny <= 0 || i <= 0) continue;
			path_cnt[ny][i] = (path_cnt[ny][i] + path_cnt[cur.y][cur.x]) % MOD;
			if (chk[ny][i]) continue;
			chk[ny][i] = true;
			pq.push({ ny, i });
		}
	}
}

void output(int tc) {
	//printf("#%d %d\n", tc, path_cnt[N][N]);
	printf("#%d %d\n", tc, path_cnt[1][1]);	// 4
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		get_path_cnt();
		output(tc);
		//printf("process_cnt = %lld\n", process_cnt);
	}
	return 0;
}
#endif



// 참고 : 백트래킹
#if 0
#include <iostream>
#include <algorithm>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int N, ans, map[1001][1001];
ll dp[1001][1001];

int getdp(int i, int j) {
	if (dp[i][j] != -1) return dp[i][j];
	if (i == 0 && j == 0) return 1;

	int sum = 0;
	for (int k = 0; k <= map[i][j]; k++) {
		if (i - k >= 0 && j - (map[i][j] - k) >= 0) sum = (sum + getdp(i - k, j - (map[i][j] - k))) % MOD;
	}
	return dp[i][j] = sum;
}

int main() {
	//ios::sync_with_stdio(false); cin.tie(0);
	int tc;
	scanf("%d", &tc);
	//cin>>tc;
	for (int t = 1; t <= tc; t++) {

		ans = 0;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				dp[i][j] = -1;
			}
		}

		dp[0][0] = 1;

		/*
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				for(int k=0; k<=map[i][j]; k++) {
					//if (i-k >= 0 && j-(map[i][j]-k) >= 0) dp[i][j] = (dp[i][j]+dp[i-k][j-(map[i][j]-k)]) % MOD;
				}
			}
		}
		*/

		getdp(N - 1, N - 1);

		/*
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				printf("%d ", dp[i][j]);
			}
		   printf("\n");
		}
		*/

		printf("#%d %d\n", t, dp[N - 1][N - 1]);
	}

	return 0;
}
#endif



// 참고 : DP
#if 0
#include <stdio.h>
#include <stdlib.h>

#define NMAX 1001
#define DIV 1000000007

int T;
int N;

int SQR[NMAX][NMAX];
int DP[NMAX][NMAX];
int VIS[NMAX][NMAX];

int DFS(int x, int y) {
	int X, Y;
	int LNTH = SQR[x][y];
	int RET = 0;

	X = x - LNTH;  Y = y;

	if (X < 0) {
		Y += X; X = 0;
	}

	if (x + y < LNTH) {
		VIS[x][y] = 1;
		return DP[x][y] = RET;
	}
	else {
		for (X = X; X <= x; X++) {

			if (X == 0 || Y == 0 || VIS[X][Y]) {
				RET += DP[X][Y];
				RET %= DIV;
				Y--;
				continue;
			}

			if (Y < 0)
				break;

			RET += DFS(X, Y) % DIV;
			RET %= DIV;

			Y--;
		}
		VIS[x][y] = 1;
		return DP[x][y] = RET % DIV;
	}
}

int main() {

	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int n1 = 0; n1 < N; n1++)
			for (int n2 = 0; n2 < N; n2++) {
				scanf("%d", &SQR[n1][n2]);
				DP[n1][n2] = 0; VIS[n1][n2] = 0;
			}
		DP[0][0] = 1;
		for (int n = 1; n < N; n++) {
			if (SQR[0][n] <= n)
				DP[0][n] += DP[0][n - SQR[0][n]];
			if (SQR[n][0] <= n)
				DP[n][0] += DP[n - SQR[n][0]][0];
		}

		printf("#%d %d\n", t, DFS(N - 1, N - 1));

	}

	return 0;
}
#endif