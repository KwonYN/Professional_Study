/*
	[핵심] : 한 사람보다 큰 사람 + 작은 사람 수가 전체 - 1(자기 자신 제외)라면, 나의 키 순위를 알 수 있음!!	
*/

// 다시 풀어보자!
// in/out-degree => 즉, DAG로 풀어보자! (ToDo) - 순서에 상관없이 어떻게...??ㅠㅠ
#if 0

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define NMAX	(500)

int T, N, M;
bool howTall[NMAX + 2][NMAX + 2];
vector<int> note[NMAX+2];
int inandout[2][NMAX+2]; // 0 : in, 1 : out
int cnt;

void make_inandout(int s, int prev) { // dfs
	
	for (int next : note[prev]) {
		if (howTall[prev][next]) {
			howTall[s][next] = true;
			inandout[1][prev]++;
			inandout[0][next]++;
			make_inandout(s, next);
		}
	}

	//for (int i = 1; i <= N; i++) { // a
	//	for (int j = 1; j <= N; j++) {
	//		for (int k = 1; k <= N; k++) { // b
	//			if ( (howTall[i][j]) && (howTall[j][k]) ) howTall[i][k] = true;
	//		}
	//	}
	//}
}

void get_cnt() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (howTall[i][j]) {
				inandout[1][i]++;
				inandout[0][j]++;
			}
		}
	}
}

void init() {
	for (int i = 1; i <= N; i++) {
		note[i].clear();
		for (int j = 1; j <= N; j++) howTall[i][j] = false;
		for (int j = 0; j < 2; j++) inandout[j][i] = 0;
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	int a, b;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		cnt = 0;
		scanf("%d", &N);
		scanf("%d", &M);
		for (int i = 1; i <= M; i++) {
			scanf("%d %d", &a, &b);	// a < b
			howTall[a][b] = true;
			note[a].push_back(b);
			inandout[1][a]++;
			inandout[0][b]++;
		}
		for (int i = 1; i <= N; i++) {
			for (int j : note[i]) {
				make_inandout(i, j);
			}
		}
		get_cnt();
		for (int i = 1; i <= N; i++) if (inandout[0][i] + inandout[1][i] + 1 == N) cnt++;
		//for (int i = 1; i <= N; i++) printf("[%d] out = %d, in = %d\n", i, inandout[1][i], inandout[0][i]);
		//printf("\n");
		printf("#%d %d\n", tc, cnt);
		init();
	}

	return 0;
}

#endif




// 참고 코드
#include <iostream>
#include <cstring>

using namespace std;

int N, M;
bool D[501][501];

bool check(int n) { // main에서 a와 b의 관계를 통해 찾을 수 있는 모든 관계를 찾음(a < b < c라면 a < c에도 체크를 해줌!!)
		    // 이를 통해 n번이라는 사람보다 큰, 작은 사람들을 모두 알 수 있다면, true 리턴 (main에서 += true하면 += 1과 똑같!!)
	for (int i = 1; i <= N; i++) {
		if (i == n)
			continue;
		if (!D[i][n] && !D[n][i])
			return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		D[a][b] = true;
	}
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (D[i][k] && D[k][j])
					D[i][j] = true;
			}
		}
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++)
		cnt += check(i);
	cout << cnt << '\n';

	return 0;
}

// BOJ_2458_키 순서
#include <cstdio>
#include <queue>
using namespace std;
#define MMAX	(500)

int N, M;
int howTall[MMAX+2][MMAX+2];
int cnt;
int tall, shrt;

int bfs1(int s) {
	queue<int> que;
	int chk[MMAX+2] = { 0 };
	int out, lv_cnt = 0;

	que.push(s);	chk[s] = 1;
	while(!que.empty()) {
		out = que.front();	que.pop();
		for(int i = 1; i <= N; i++) {
			if(howTall[out][i] && !chk[i]) {	// 더 작음
				que.push(i);
				chk[i] = 1;
				lv_cnt++;
			}
		}
	}
	return lv_cnt;
}

int bfs2(int s) {
	queue<int> que;
	int chk[MMAX+2] = { 0 };
	int out, lv_cnt = 0;

	que.push(s);	chk[s] = 1;
	while(!que.empty()) {
		out = que.front();	que.pop();
		for(int i = 1; i <= N; i++) {
			if(howTall[i][out] && !chk[i]) {	// 더 큼
				que.push(i);
				chk[i] = 1;
				lv_cnt++;
			}
		}
	}
	return lv_cnt;
}

int main() {
	int a, b;
	cnt = 0;
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		howTall[b][a] = 1; // b > a
	}
	for(int i = 1; i <= N; i++) {
		shrt = bfs1(i);		tall = bfs2(i);
		if(tall + shrt == N-1) cnt++;
	}
	printf("%d\n", cnt);

	return 0;
}
