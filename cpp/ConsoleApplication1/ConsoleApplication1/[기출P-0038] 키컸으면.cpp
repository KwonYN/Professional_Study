// [기출P-0038] 키컸으면
/*
	N명이 일렬로 줄 서있음
	철수는 구간에서 키가 x보다 큰 사람이 몇 명인지 물어봄
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX		(300030)

struct HUMAN { int height, idx; };
struct QUERY { int height, l, r, idx; };
int T, N, Q;
HUMAN human[MAX];
QUERY query[MAX];
int tree[MAX];	// 펜윅트리
int ans[MAX];
	
bool cmp1(const HUMAN &h1, const HUMAN &h2) {
	return h1.height > h2.height;
}

bool cmp2(const QUERY &q1, const QUERY &q2) {
	return q1.height > q2.height;
}

void input_() {
	int a, b, x;
	scanf("%d %d", &N, &Q);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &x);
		human[i] = { x, i };
		tree[i] = 0;	// init
	}
	sort(human + 1, human + N + 1, cmp1);	// 키 기준 내림차순
	for (int q = 1; q <= Q; q++) {
		scanf("%d %d %d", &a, &b, &x);
		query[q] = { x, a, b, q };
	}
	sort(query + 1, query + Q + 1, cmp2);	// 키 기준 내림차순
}

void update(int idx, int val) {
	while (idx <= N) {
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

int get_sum(int idx) {
	int sum = 0;
	while (idx) {
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void get_tree() {
	int h = 1;
	for (int q = 1; q <= Q; q++) {
		while (h <= N && query[q].height < human[h].height) {
			update(human[h++].idx, 1);
		}
		ans[query[q].idx] = get_sum(query[q].r) - get_sum(query[q].l - 1);
	}
}

void output(int tc) {
	printf("#%d", tc);
	for (int i = 1; i <= Q; i++) {
		printf(" %d", ans[i]);
	}
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_tree();
		output(tc);
	}
	return 0;
}
#endif