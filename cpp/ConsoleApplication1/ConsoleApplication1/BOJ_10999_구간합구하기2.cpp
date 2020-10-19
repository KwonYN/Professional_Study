// BOJ_10999_구간합구하기2 : Lazy Propagation
/*
	중간에 수의 변경이 빈번히 일어나고,
		그 중간에 어떤 부분의 합을 구하려..!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000000)

typedef long long ll;
int N, M, K, arr[NMAX+5];
struct NODE { ll val, lazy; };
NODE tree[NMAX*3];	// 세그먼트 트리

ll tree_init(int s, int e, int idx) {
	tree[idx].lazy = 0LL;	// 첨에 초기화
	if (s == e) {
		return tree[idx].val = 1LL*arr[s];
	}
	int m = (s + e) / 2;
	return tree[idx].val = tree_init(s, m, idx<<1) 
						 + tree_init(m+1, e, (idx<<1)|1);
}

void range_update(int s, int e, int l, int r, int idx, ll val) {
	// 갱신해줄 때, lazy가 남아있는 노드를 방문하면 lazy를 갱신해주고,
	// (그 자식 노드들에 이 부모 노드의 lazy가 반영되지 않았을테니) 반영해줌
	if (tree[idx].lazy != 0) {
		tree[idx].val += tree[idx].lazy * (1LL * e - s + 1);	// lazy 갱신
		if (s != e) {
			tree[idx<<1].lazy += tree[idx].lazy;
			tree[(idx<<1) | 1].lazy += tree[idx].lazy;
		}
		tree[idx].lazy = 0LL;
	}
	if (e < l || r < s) return;	// 갱신이 필요한 범위 X
	if (l <= s && e <= r) {		// 갱신이 필요한 범위!!
		tree[idx].val += val*(1LL*e-s+1);	// 구간 갱신
		if (s != e) {	// leaf node일 경우에는 자손 X임!!
			tree[idx<<1].lazy += val;
			tree[(idx<<1)|1].lazy += val;
		}
		return;
	}
	int m = (s + e) / 2;
	range_update(s, m, l, r, idx<<1, val);
	range_update(m+1, e, l, r, (idx<<1)|1, val);
	// 자식 노드들뿐만 아니라 그 위의(root 방향) 노드들도 lazy 반영 필요!!
	tree[idx].val = tree[idx << 1].val + tree[(idx << 1) | 1].val;
}

ll range_sum(int s, int e, int l, int r, int idx) {
	// 혹시 range_sum 상황에서도 lazy가 갱신되지 않은 노드 만난다면 갱신
	if (tree[idx].lazy != 0) {
		tree[idx].val += tree[idx].lazy * (1LL * e - s + 1);	// lazy 갱신
		if (s != e) {
			tree[idx<<1].lazy += tree[idx].lazy;
			tree[(idx<<1)|1].lazy += tree[idx].lazy;
		}
		tree[idx].lazy = 0LL;
	}
	if (e < l || r < s) return 0LL; // 구간합 범위 X
	if (l <= s && e <= r) {			// 구간합 범위!!
		return tree[idx].val;
	}
	int m = (s + e) / 2;
	return range_sum(s, m, l, r, idx<<1) 
		 + range_sum(m + 1, e, l, r, (idx<<1)|1);
}

void input_() {
	int a, b, c;
	ll d;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
	tree_init(1, N, 1);
	for (int i = 1; i <= M + K; i++) {
		scanf("%d", &a);
		if (a == 1) {	// 더하기
			scanf("%d %d %lld", &b, &c, &d);
			range_update(1, N, b, c, 1, d);
		}
		else {			// 출력
			scanf("%d %d", &b, &c);
			printf("%lld\n", range_sum(1, N, b, c, 1));
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	input_();
	return 0;
}
#endif