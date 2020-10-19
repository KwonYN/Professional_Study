// [교육P-0020] 달리기
/*
	현재 i등으로 달리고 있는 선수의 달리기 실력은 A[i]
	현재 자신보다 앞에서 달리고 있으면서(index가 더 작음)
		자신보다 실력이 낮으면(A[i]가 더 작음)
		역전 가능성이 있다
	자신이랑 실력이 같거나 실력이 더 좋은 사람을(A[i]가 같거나 더 큼)
		역전할 가능성은 아예 없다
	앞으로 역전이 최대 몇 번 나올지 궁금!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)

struct RUNNER { int idx, ability; };
int T, N;
RUNNER A[NMAX];
int fenwick_tree[NMAX], cnt;

void init() {
	for (int i = 1; i <= N; i++) fenwick_tree[i] = 0;
}

bool cmp(RUNNER r1, RUNNER r2) {
	if (r1.ability < r2.ability) return true;
	if (r1.ability == r2.ability) {
		if (r1.idx > r2.idx) return true;
	}
	return false;
}

void input_() {
	int tmp;
	cnt = 0;
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N; i++) {
		scanf("%d", &tmp);
		A[i] = { i, tmp };
	}
	sort(A+1, A+N+1, cmp);
}

void update(int idx, int val) {
	while (idx <= N) {
		fenwick_tree[idx] += val;
		idx += idx & -idx;
	}
}

int get_sum(int idx) {
	int result = 0;
	while (idx) {
		result += fenwick_tree[idx];
		idx -= idx & -idx;
	}
	return result;
}

void get_cnt() {
	for (int i = 1; i <= N; i++) {
		cnt += get_sum(A[i].idx);
		update(A[i].idx, 1);
	}
}

void output(int tc) { printf("#%d %d\n", tc, cnt); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_cnt();
		output(tc);
	}
	return 0;
}
#endif