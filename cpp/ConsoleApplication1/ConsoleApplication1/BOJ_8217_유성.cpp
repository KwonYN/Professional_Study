// BOJ_8217_유성
/*
	1 <= N, M <= 30만
	M : "행성 궤도"를 M개의 구역으로 나누고 
		1부터 M까지 순서대로 번호를 부여
		(행성 궤도는 원 궤도이므로 1번 구역과 M번 구역은 서로 인접)
	N : 각 구역(1~M)은 "N개의 BIU회원국"들이 서로 적당히 나누어 가짐
	각 회원국들은 모으고자 하는 "운석 샘플의 목표치"를 정했다.
	유성우 예보를 바탕으로 각 나라들이 "언제 샘플 채취를 완료할 수 있는지"
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