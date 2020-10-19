// [����P-0020] �޸���
/*
	���� i������ �޸��� �ִ� ������ �޸��� �Ƿ��� A[i]
	���� �ڽź��� �տ��� �޸��� �����鼭(index�� �� ����)
		�ڽź��� �Ƿ��� ������(A[i]�� �� ����)
		���� ���ɼ��� �ִ�
	�ڽ��̶� �Ƿ��� ���ų� �Ƿ��� �� ���� �����(A[i]�� ���ų� �� ŭ)
		������ ���ɼ��� �ƿ� ����
	������ ������ �ִ� �� �� ������ �ñ�!!
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