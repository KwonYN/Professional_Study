// BOJ_2517_�޸���
/*
	 �� ������ ���忡�� �ڱ⺸�� �տ� �޸��� �ִ� ������ �� 
		��� �Ƿ��� �ڱ⺸�� ���� ������ ���� �Ÿ� ���� �������� ���� 
		�Ұ����ϴ�.
	�ݴ��, ��� �Ƿ��� �ڱ⺸�� ���� ���� ������ �տ� �޸��� ������ 
		���� �Ÿ� ���� �������� ���� �����ϴ�.
	�� ������ �ڽ��� ������ ���� �� �ִ� �ּ��� ����� �� �� �ִ�. 
	�� ������ ��� �Ƿ��� ������ �־����µ� �� ū ���� �� ���� �Ƿ��� �ǹ��Ѵ�. 
	�ڴ�, ������ �������� ��� �Ƿ��� ��� �ٸ���.��
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(500010)

struct RUNNER { int ab, idx; };
int N;
RUNNER ability[NMAX];
int seg_tree[NMAX*3], leaf_node[NMAX], order[NMAX];

bool cmp(const RUNNER& r1, const RUNNER& r2) {
	return r1.ab > r2.ab;
}

void input() {
	int r;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &r);
		ability[i] = { r, i };
	}
	sort(ability+1, ability+N+1, cmp);
	// �޸��� �Ƿ� ���� �������� : ���� �Ƿ� ����!!!!
}

void tree_init(int s, int e, int idx) {
	seg_tree[idx] = 0;
	if (s == e) {
		leaf_node[s] = idx;
		return;
	}
	int m = (s + e) / 2;
	tree_init(s, m, idx<<1);
	tree_init(m+1, e, (idx<<1)|1);
}

int get_cnt(int s, int e, int l, int r, int idx) {
	if(e < l || r < s) return 0;
	if (l <= s && e <= r) return seg_tree[idx];
	int m = (s + e) / 2;
	return get_cnt(s, m, l, r, idx<<1) + get_cnt(m+1, e, l, r, (idx<<1)|1);
}

void update(int idx) {
	idx = leaf_node[idx];
	while (idx) {
		seg_tree[idx]++;
		idx >>= 1;
	}
}

void operation() {
	tree_init(1, N, 1);
	for (int i = 1; i <= N; i++) {
		RUNNER runner = ability[i];
		order[runner.idx] = min(runner.idx, get_cnt(1, N, 1, runner.idx-1, 1))+1;
		update(runner.idx);
	}
}

void output() {
	for (int i = 1; i <= N; i++) {
		printf("%d\n", order[i]);
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	input();
	operation();
	output();
	return 0;
}
#endif