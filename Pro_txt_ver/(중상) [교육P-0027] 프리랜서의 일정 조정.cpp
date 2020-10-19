// (중상) [교육P-0027] 프리랜서의 일정 조정 
/*
	병환이에게 총 N개의 일이 들어왔다.
	일을 1번부터 N번까지 번호를 매겨 놓았는데,
	i번 일은 s[i]부터 e[i]까지 일을 해야하며,
		c[i]의 수익이 남는다.
	병환이의 작업 특성상 하나의 일을 맡으면 다른 일을 하지 못한다.
	일하는 것을 좋아하는 병환이는 하루도 빠짐없이 일할 수 있다.
	최고의 수익을 얻고 싶어한다.
	;
*/

// Re : Greedy... => 정렬을 통해서 + 이진 ㅠ
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)

typedef long long ll;
typedef pair<int, ll> pil;	// e, c
struct WORK { int s, e; ll c; };
int T, N;
WORK work[NMAX];
int working[NMAX];
ll working_price[NMAX];

bool cmp(const WORK &w1, const WORK &w2) {
	if(w1.e < w2.e) return true;
	/*if (w1.e == w2.e) {
		if (w1.c < w2.c) return true;
	}*/
	return false;
}

void input() {
	int a, b;
	ll c;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		work[i] = { a, b, c };
		working_price[i] = 0LL;	// init
	}
	sort(work + 1, work + N + 1, cmp);
	/*for (int i = 1; i <= N; i++) {
		printf("%d %d %lld\n", work[i].s, work[i].e, work[i].c);
	}*/
}

int bin_search(int s, int e, int target, ll c) {
	int m, idx = 0;
	while (s <= e) {
		m = (s+e)/2;
		if (working[m] < target) {
			s = m+1;
			idx = m;
		}
		else {
			e = m-1;
		}
	}
	return idx;
}

void max_income_schedule() {
	int idx;
	for (int i = 1; i <= N; i++) {
		WORK w = work[i];
		idx = bin_search(1, i - 1, w.s, w.c);
		working[i] = w.e;
		working_price[i] = max(working_price[i-1], w.c+working_price[idx]);
	}
}

void output(int tc) { printf("#%d %lld\n", tc, working_price[N]); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		max_income_schedule();
		output(tc);
	}
	return 0;
}
#endif