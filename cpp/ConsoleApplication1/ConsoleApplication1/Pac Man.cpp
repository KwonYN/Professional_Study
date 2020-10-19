// (중상) [기출P-0063] Pac Man 
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMMAX	(105)
#define INF		(0x7fffffff)

int T, N, M;
int map[NMMAX][NMMAX];
int pac_y, pac_x, ey, ex;
int cy[5], cx[5], c_cnt;
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };
int visited[NMMAX][NMMAX];
int result;

void input() {
	char tmp[NMMAX];
	c_cnt = 0;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%s", tmp + 1);
		for (int j = 1; j <= M; j++) {
			if (tmp[j] == 'S') {
				pac_y = i;	pac_x = j;
			}
			else if (tmp[j] == 'E') {
				ey = i;		ex = j;
			}
			else if (tmp[j] == 'C') {
				cy[++c_cnt] = i;		cx[c_cnt] = j;
			}
			else if (tmp[j] == '#') map[i][j] = -1;
			else map[i][j] = 0;	// 못 지나가
			visited[i][j] = INF;	// init
		}
		map[i][0] = map[i][M + 1] = -1;	// 테두리
	}
	for (int i = 1; i <= M; i++) map[0][i] = map[N + 1][i] = -1;	// 테두리
}

int get_path(int sy, int sx) {
	int ny, nx;
	queue<pair<int, int>> que;
	que.push({ sy, sx });		visited[sy][sx] = 0;
	while (!que.empty()) {
		pair<int, int> out = que.front();		que.pop();
		sy = out.first;		 sx = out.second;
		if (sy == ey && sx == ex) return visited[sy][sx];
		for (int d = 0; d < 4; d++) {
			ny = sy + dy[d];
			nx = sx + dx[d];
			if (map[ny][nx] == -1 || visited[ny][nx] <= visited[sy][sx] + 1) continue;
			visited[ny][nx] = visited[sy][sx] + 1;
			que.push({ ny, nx });
		}
	}
	return -1;
}

void print_visited() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			printf("%d ", visited[i][j]);
		}
		printf("\n");
	}
	printf("==========================\n");
}

void operation() {
	result = INF;
	for (int i = 1; i <= c_cnt; i++) {
		get_path(cy[i], cx[i]);
		print_visited();
	}
	result = get_path(pac_y, pac_x);
	print_visited();
}

void output(int tc) {
	printf("#%d %d\n", tc, result);
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif