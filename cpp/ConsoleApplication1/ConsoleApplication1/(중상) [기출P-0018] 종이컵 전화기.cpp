// (중상) [기출P-0018] 종이컵 전화기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(220)

int T, N, M;
bool connection[NMAX][NMAX];

void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			connection[i][j] = false;
		}
	}
}

void input_() {
	int a, b;
	scanf("%d %d", &N, &M);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		connection[a][b] = connection[b][a] = true;	// 연결됨
	}
}

void get_connection_cnt() {
	;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_connection_cnt();
	}
	return 0;
}
#endif