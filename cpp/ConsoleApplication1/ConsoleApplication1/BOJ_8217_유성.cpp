// BOJ_8217_����
/*
	1 <= N, M <= 30��
	M : "�༺ �˵�"�� M���� �������� ������ 
		1���� M���� ������� ��ȣ�� �ο�
		(�༺ �˵��� �� �˵��̹Ƿ� 1�� ������ M�� ������ ���� ����)
	N : �� ����(1~M)�� "N���� BIUȸ����"���� ���� ������ ������ ����
	�� ȸ�������� �������� �ϴ� "� ������ ��ǥġ"�� ���ߴ�.
	������ ������ �������� �� ������� "���� ���� ä�븦 �Ϸ��� �� �ִ���"
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(300000)

typedef long long ll;
int N, M, Q;
int orbit[2*NMAX+5];
ll goal[NMAX + 5];
ll tree_plus[NMAX+5], tree_minus[NMAX+5];

void update(int at, ll p, ll m) {
	while (at <= N) {
		;
	}
}

void range_update(int l, int r, ll val) {
	update(l, val, -val*(1LL*l-1));
	update(r + 1, -val, val * r);
}

void input_() {
	int tmp, l, r, a;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d", &orbit[i]);
	}
	for (int i = M + 1; i <= (M<<1); i++) orbit[i] = orbit[i-M];
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &goal[i]);
	}
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d %d %d", &l, &r, &a);
		if (l <= r) {
			range_update(l, r, 1LL*a);
		}
		else if (l > r) {
			range_update(l, r + M, 1LL*a);
		}
	}
}

void output() {
	for (int i = 1; i <= N; i++) {
		;
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	input_();
	output();
	return 0;
}
#endif