// [기출P-0037] 섬나라
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMMAX	(510)
#define NUMMMAX	(100010)
#define QMAX	(100010)

struct NODE { int y, x; };
int T, N, M, Q;
int map[NMMAX][NMMAX], query[QMAX];
vector<NODE> num[NUMMMAX];
int max_num;
int result[QMAX];
bool chk[NUMMMAX];

void init() {
	for (int i = 1; i <= max_num; i++) {
		num[i].clear();
		chk[i] = false;
	}
}

void input_() {
	int tmp;
	max_num = -1;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &tmp);
			max_num = max(max_num, tmp);
			num[tmp].push_back({ i, j });
			map[i][j] = tmp;
		}
	}
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d", &query[i]);
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
		input_();
		output(tc);
		init();
	}
	return 0;
}
#endif