// BOJ_10999_�����ձ��ϱ�2 : Lazy Propagation
/*
	�߰��� ���� ������ ����� �Ͼ��,
		�� �߰��� � �κ��� ���� ���Ϸ�..!!
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
NODE tree[NMAX*3];	// ���׸�Ʈ Ʈ��

ll tree_init(int s, int e, int idx) {
	tree[idx].lazy = 0LL;	// ÷�� �ʱ�ȭ
	if (s == e) {
		return tree[idx].val = 1LL*arr[s];
	}
	int m = (s + e) / 2;
	return tree[idx].val = tree_init(s, m, idx<<1) 
						 + tree_init(m+1, e, (idx<<1)|1);
}

void range_update(int s, int e, int l, int r, int idx, ll val) {
	// �������� ��, lazy�� �����ִ� ��带 �湮�ϸ� lazy�� �������ְ�,
	// (�� �ڽ� ���鿡 �� �θ� ����� lazy�� �ݿ����� �ʾ����״�) �ݿ�����
	if (tree[idx].lazy != 0) {
		tree[idx].val += tree[idx].lazy * (1LL * e - s + 1);	// lazy ����
		if (s != e) {
			tree[idx<<1].lazy += tree[idx].lazy;
			tree[(idx<<1) | 1].lazy += tree[idx].lazy;
		}
		tree[idx].lazy = 0LL;
	}
	if (e < l || r < s) return;	// ������ �ʿ��� ���� X
	if (l <= s && e <= r) {		// ������ �ʿ��� ����!!
		tree[idx].val += val*(1LL*e-s+1);	// ���� ����
		if (s != e) {	// leaf node�� ��쿡�� �ڼ� X��!!
			tree[idx<<1].lazy += val;
			tree[(idx<<1)|1].lazy += val;
		}
		return;
	}
	int m = (s + e) / 2;
	range_update(s, m, l, r, idx<<1, val);
	range_update(m+1, e, l, r, (idx<<1)|1, val);
	// �ڽ� ����Ӹ� �ƴ϶� �� ����(root ����) ���鵵 lazy �ݿ� �ʿ�!!
	tree[idx].val = tree[idx << 1].val + tree[(idx << 1) | 1].val;
}

ll range_sum(int s, int e, int l, int r, int idx) {
	// Ȥ�� range_sum ��Ȳ������ lazy�� ���ŵ��� ���� ��� �����ٸ� ����
	if (tree[idx].lazy != 0) {
		tree[idx].val += tree[idx].lazy * (1LL * e - s + 1);	// lazy ����
		if (s != e) {
			tree[idx<<1].lazy += tree[idx].lazy;
			tree[(idx<<1)|1].lazy += tree[idx].lazy;
		}
		tree[idx].lazy = 0LL;
	}
	if (e < l || r < s) return 0LL; // ������ ���� X
	if (l <= s && e <= r) {			// ������ ����!!
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
		if (a == 1) {	// ���ϱ�
			scanf("%d %d %lld", &b, &c, &d);
			range_update(1, N, b, c, 1, d);
		}
		else {			// ���
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