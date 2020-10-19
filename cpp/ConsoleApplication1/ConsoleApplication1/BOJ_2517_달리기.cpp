// BOJ_2517_달리기
/*
	 각 선수의 입장에서 자기보다 앞에 달리고 있는 선수들 중 
		평소 실력이 자기보다 좋은 선수를 남은 거리 동안 앞지르는 것은 
		불가능하다.
	반대로, 평소 실력이 자기보다 좋지 않은 선수가 앞에 달리고 있으면 
		남은 거리 동안 앞지르는 것이 가능하다.
	각 선수는 자신이 앞으로 얻을 수 있는 최선의 등수를 알 수 있다. 
	각 선수의 평소 실력은 정수로 주어지는데 더 큰 값이 더 좋은 실력을 의미한다. 
	★단, 참가한 선수들의 평소 실력은 모두 다르다.★
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
	// 달리기 실력 기준 내림차순 : 같은 실력 없음!!!!
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