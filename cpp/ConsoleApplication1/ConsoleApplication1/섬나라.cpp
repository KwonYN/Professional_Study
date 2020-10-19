// [����P-0037] ������
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMMAX	(510)
#define NUMMAX	(100010)

struct NODE { int y, x; };
int T, N, M, Q;
int map[NMMAX][NMMAX], map_max;
int parent[NMMAX*NMMAX];
vector<NODE> node[NUMMAX];
int query[NUMMAX];
bool chk_query[NUMMAX];
int result[NUMMAX];
bool visited[NMMAX][NMMAX];
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };

void init() {
	for (int i = 0; i <= map_max; i++) {
		node[i].clear();
		chk_query[i] = false;	// �ʱ�ȭ
		query[i] = 0;			// �ʱ�ȭ
	}
	map_max = -1;
}

void input_() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
			map_max = max(map_max, map[i][j]);
			node[map[i][j]].push_back({ i, j });
			parent[M*i+j] = M*i+j;	// �ʱ�ȭ
			visited[i][j] = false;		// �ʱ�ȭ
		}
		map[i][0] = map[i][M + 1] = -1;
	}
	for (int j = 0; j <= M+1; j++) map[0][j] = map[N + 1][j] = -1;	// �׵θ�
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d", &query[i]);
		map_max = max(map_max, query[i]);
		if (!chk_query[query[i]]) {
			chk_query[query[i]] = true;	// �μ������� ���� ������ ��ȭ�� ���� �� ����
			for (NODE n : node[query[i]]) {	// �ı�
				map[n.y][n.x] = -1;
			}
		}
		else query[i] = 0;	// �μ��� �������� ���� ���� ��ȭ�� ���� 
	}
}

int find(int n) {
	if (parent[n] == n) return n;
	return parent[n] = find(parent[n]);
}

void ally(int n1, int n2) {
	n1 = find(n1);
	n2 = find(n2);
	parent[n1] = n2;
}

void bfs(int y, int x) {
	queue<NODE> que;
	int ny, nx;
	visited[y][x] = true;
	que.push({ y, x });
	while (!que.empty()) {
		NODE out = que.front();		que.pop();
		for (int d = 0; d < 4; d++) {
			ny = out.y + dy[d];	nx = out.x + dx[d];
			if (map[ny][nx] == -1 || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			ally(ny * M + nx, out.y * M + out.x);
			que.push({ ny, nx });
		}
	}
}

void get_first_island_cnt() {	// Q�� ° �־��� ������ �ı��� �� ���������� ���� ���� ���� �ľ�
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if(map[i][j] == -1 || visited[i][j]) continue;
			bfs(i, j);			cnt++;
		}
	}
	result[Q] = cnt;
}

void get_island_cnt() {
	int cnt, qnum;
	for (int q = Q; q > 1; q--) {
		cnt = result[q];

		qnum = query[q];
		// chk_query[q]�� �����̶�� ���⿡�� �μ��� ���� ������
		// �� �ܰ迡�� ���� ������ ��ȭ�� ���� ���̹Ƿ� �Ѿ
		if (qnum) {
			// q�� ° �־��� ���� ����� && ��� üũ
			for (NODE n : node[qnum]) {
				map[n.y][n.x] = qnum;		cnt++;
				for (int d = 0; d < 4; d++) {
					int ny = n.y + dy[d];
					int nx = n.x + dx[d];
					if (map[ny][nx] == -1) continue;
					if (find(ny * M + nx) != find(n.y * M + n.x)) {
						ally(ny * M + nx, n.y * M + n.x);
						cnt--;
					}
				}
			}
		}
		// �� ��� q�� ° �ܰ� ������ �����ִ� ���� ������ ������ ����
		result[q-1] = cnt;
	}
}

void output(int tc) {
	printf("#%d", tc);
	for (int i = 1; i <= Q; i++) {
		printf(" %d", result[i]);
	}
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		input_();
		get_first_island_cnt();
		get_island_cnt();
		output(tc);
	}
	return 0;
}
#endif