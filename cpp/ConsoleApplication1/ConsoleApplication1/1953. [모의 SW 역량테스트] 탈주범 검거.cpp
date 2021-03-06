// 1953. [모의 SW 역량테스트] 탈주범 검거
// BFS
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMMAX	(50)

struct NODE { int y, x, t; };
int T, N, M, R, C, L;
int pipe[8] = {0, 0xf, 0x5, 0xa, 0x9, 0xc, 0x6, 0x3};
int map[NMMAX+5][NMMAX+5];
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };
int cur[4] = { 1, 4, 2, 8 }, nex[4] = { 4, 1, 8, 2 };

void input() {
	int tmp;
	scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &tmp);
			map[i][j] = pipe[tmp];
		}
	}
}

int bfs(int y, int x) {
	queue<NODE> que;
	int cnt = 0, ny, nx, nt;
	bool visited[NMMAX + 5][NMMAX + 5] = {false};
	que.push({ y, x, 1 }); visited[y][x] = true;
	cnt++;
	while (!que.empty()) {
		NODE node = que.front();	que.pop();
		y = node.y;		x = node.x;		nt = node.t;
		for (int d = 0; d < 4; d++) {
			ny = y + dy[d];
			nx = x + dx[d];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M || visited[ny][nx]) continue;
			if (!(map[y][x] & cur[d])) continue;
			if (!(map[ny][nx] & nex[d])) continue;
			if (nt + 1 > L) return cnt;
			visited[ny][nx] = true;
			que.push({ ny, nx, nt+1 });
			cnt++;
		}
	}
	return cnt;
}

void output(int tc) { printf("#%d %d\n", tc, bfs(R, C)); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		output(tc);
	}
	return 0;
}
#endif

// DFS re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMMAX	(50)

int T, N, M, R, C, L;
int pipe[8] = { 0x0, 0xf, 0x5, 0xa, 0x9, 0xc, 0x6, 0x3 };
int map[NMMAX+5][NMMAX+5];
int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, -1, 0, 1 };// 상좌하우
int cur[4] = { 1, 2, 4, 8 }, nex[4] = { 4, 8, 1, 2 };
bool visited[NMMAX+5][NMMAX+5], result[NMMAX+5][NMMAX+5];

void input() {
	int tmp;
	scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &tmp);
			map[i][j] = pipe[tmp];
		}
	}
}

void dfs(int d, int y, int x) {
	//printf("d = %d, y = %d, x = %d\n", d, y, x);
	if (d >= L) return;
	result[y][x] = true;
	int ny, nx;
	for (int d = 0; d < 4; d++) {
		if (!(map[y][x] & cur[d])) continue;
		ny = y + dy[d];		nx = x + dx[d];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M || visited[ny][nx]) continue;
		if (!(map[ny][nx] & nex[d])) continue;
		//printf("ny = %d, nx = %d\n", ny, nx);
		visited[ny][nx] = true;
		dfs(d + 1, ny, nx);
		visited[ny][nx] = false;
	}
}

int get_result() {
	int result_cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			//printf("%d ", result[i][j]);
			if (result[i][j]) result_cnt++;
			result[i][j] = visited[i][j] = false;	// init
		}
		//printf("\n");
	}
	return result_cnt;
}

void output(int tc) { printf("#%d %d\n", tc, get_result()); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		visited[R][C] = true;
		dfs(1, R, C);
		visited[R][C] = false;	// init
		output(tc);
	}
	return 0;
}
#endif