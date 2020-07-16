// (중) [기출A-0040] 석탑
/*
	【 문제 이해 】
	돌들의 무게가 다양
	쌓을 때 소모되는 중장비의 연료량도 다양
	들어올리는 높이에 비례하여 소모되는 연료량도 증가
	주어지는 수는
		각 돌의 높이 & 10cm들어올려 쌓을 때 소모되는 연료량
	N개 돌 모두 쌓아 구조물을 만들 수 있는 최소한의 연료소모량 합!?
	0 + 1000*100 + 2000*100 + ... + 99만9천*100
		= 1000*(1+2+...+999)*100
		= (1000^2 / 2 ) * 10만 > int 범위

	【 문제 풀이 】
	1. DFS
		- 1000*1000
*/

// dfs ver. : 시간초과 ㅋㅋㅋ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)

struct ELEMENT { int height, fuel; };
int T, N;
ELEMENT element[NMAX+5];
bool chk[NMAX+5];
long long result, INF = 0x7fffffffffffffff;

void init() {
	result = INF;
	for (int i = 1; i <= N; i++) chk[i] = false;
}

void input() {
	int h, f;
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &h, &f);
		element[i] = { h, f };
	}
}

void dfs(int d, int h, long long s) {
	if (result <= s) return;
	if (d >= N) {
		if (result > s) result = s;
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (chk[i]) continue;
		chk[i] = true;
		dfs(d + 1, h + element[i].height, s + 1LL * (h/10) * element[i].fuel);
		chk[i] = false;
	}
}

void output(int tc) { printf("#%d %lld\n", tc, result); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		dfs(0, 0, 0);
		output(tc);
	}
	return 0;
}
#endif

/*
	간과했던 / 계산 실수했던 것!?!?
	=> 1000개의 수 순열을 1+2+...+999+1000가 아니라
	   1*2*...*999*1000였던 것!!!

	   => N이 1000이니
	      N^2 이하로 풀 수 있을 것!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)

struct ELEMENT { int fuel, height; };
int T, N;
ELEMENT element[NMAX+5];

void input() {
	int h, f;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &h, &f);
		element[i] = { f/10, h };
	}
	sort(element, element+N);	// 오름차순 정리
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
	}
	return 0;
}
#endif

