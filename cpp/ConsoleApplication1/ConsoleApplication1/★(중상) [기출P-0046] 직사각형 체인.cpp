// (�߻�) [����P-0046] ���簢�� ü��
/*
	������ ������,
	�� ���������� ���� ���̰� 0 �̰ų� ���� ���̰� 0 �� �͵�
	Ư���� ���簢������ ���������,
	����, ���� ���̰� ��� 0 �� ����
	���簢������ ������� �ʴ´ٴ� ���̴�.

	������ ������ �Է� �޾�
	��� ������ ���簢�� ü���� ������ ����ϴ� ���α׷�

	�� ���� Ǯ�� ��
	1000 * 1000�̱� ������ ����� ��Ž���� �� �� ���� ������?
	But, �������� ����� % 10��7�� ���ִ� ������ ����
		 �Ϲ����� ��Ž���δ� �ð��ʰ��� �� ������ ����ǰ�,
		 ��û�� ����ġ�� �Ǵ� ���ٸ� Ǯ�̰� �ʿ��� ����.
	1 1 1		0(1) 1 1
	1 1 1	->	1    2 3
	1 1 1		1    3 6

	1 1 1		0(1) 1 1
	1 2 2	->	1    1 2
	1 2 1		1    2 4
	�̷��� ���� �׷����鼭 ��Ģ���� ã�ư�!

	2 3 4 5 ... (N+1)
	3 4 5 6 ... (N+2)
	4 5  . .
	5 6  .   .
	. .        .
	. .          .
	. .            .
	(N+1) (N+2)  ... (N+N)
	��
	(1,2) (2,1)				=> 1, -1
	(1,3) (2,2) (3,1)		=> 2, 0, -2
	(1,4) (2,3) (3,2) (4,1) => 3, 1, -1, -3
	...
	(1,N) . . . . . .  (N,1)=> (N-1), (N-3), ... , (1-N)
	(2,N) . . . . . .  (N,2)=> (N-2), (N-4), ... , (2-N)
	(N,N)					=> (0)
	��
	1) �׹������� �����.
	2) chain[i][j]�� ��
	  �� y��ǥ : 0 ~ chain[i][j], x��ǥ : chain[i][j] ~ 0
		 �� chain[i-y][j-x]�� �����ִ� ���� ������
		   (��, i-y �Ǵ� j-x�� < 1�� ��쿡�� X)
		   (�׸��� �Ź� %MOD�� ��������!)
	3) (N, N)���� 2)�� ����
	4) �ڿ����� chain[N][N]�� �� cnt�� ���̰� ��!
	=> (2N-2)*N^2 �ִ�� �� 2000 * 10��..!!

	���� �� ��������, �ð� ���⵵�� �ذ��ؾ� ��!!
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
	bool operator()(NODE& n1, NODE& n2) {	// ��������
		if (n1.y + n1.x < n2.y + n2.x) return true;
		if (n1.y + n1.x == n2.y + n2.x) {
			if (n1.y > n2.y) return true;
		}
		return false;
	}
};
int T, N, chain[NMAX + 5][NMAX + 5], path_cnt[NMAX + 5][NMAX + 5];
bool chk[NMAX + 5][NMAX + 5];	// 4 : �ߺ�����
//long long process_cnt;
/*
				��
	���� ����ġ�⸦ �غ�������
	for���� tc ������ �־��� ��� �� �� ���ư��� ���غ� ���,
	1��2õ���� ������ �־��̾���. (���� �־��� ���̽��� ��쿡�� �� Ŭ����..)
	for���� �� ������ ����ȭ���־�� ��!!
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
void get_path_cnt() { // ��Ʈ��ŷ(dfs)�ε� ������ �� ����!
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

// 4 :  (N, N) �� (1, 1)
void get_path_cnt() {
	priority_queue<NODE, vector<NODE>, cmp> pq;	// y+x ��������
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



// ���� : ��Ʈ��ŷ
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



// ���� : DP
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