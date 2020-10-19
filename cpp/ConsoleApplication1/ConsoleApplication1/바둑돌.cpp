// ¹ÙµÏµ¹
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMMAX	(5050)
#define MOD		(1000000007)

int T, n, m, N;
int nCr[NMMAX][NMMAX];
int nCr_fenwick[NMMAX][NMMAX];
int result_cnt;

void update(int row, int idx, int val) {
	while (idx <= row) {
		nCr_fenwick[row][idx] = (nCr_fenwick[row][idx] + val)%MOD;
		if (!idx) idx++;
		else idx += idx & -idx;
	}
}

int get_sum(int row, int idx) {
	int result = 0;
	if (!idx) result++;
	while (idx) {
		result = (result + nCr_fenwick[row][idx])%MOD;
		idx -= idx & -idx;
	}
	return result;
}

void init() {
	nCr[0][0] = 1;
	nCr_fenwick[0][0] = 1;
	nCr[1][0] = nCr[1][1] = 1;
	nCr_fenwick[1][0] = 1;		nCr_fenwick[1][1] = 2;
	for (int i = 2; i <= 5000; i++) {
		for (int j = 1; j < i; j++) {
			nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j])%MOD;
			update(i, j, nCr[i][j]);
		}
		nCr[i][0] = nCr[i][i] = nCr_fenwick[i][0] = 1;
		update(i, 1, 1);
		update(i, i, 1);
	}
}

void input_() {
	result_cnt = 0;
	scanf("%d %d", &n, &m);
	N = n + m;
}

void get_count() {
	int right, left;
	for (int i = 0; i <= N; i++) {
		right = ((n >= i) ? i : n);
		left = right - (m-(i-right));
		result_cnt += (get_sum(i, right) + get_sum(i, left - 1))%MOD;
	}
}

void output(int tc) { printf("#%d %d\n", tc, result_cnt); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	init();
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_count();
		output(tc);
	}
	return 0;
}
#endif