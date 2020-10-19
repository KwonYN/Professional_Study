// [기출P-0058] 탱크
/*
				|
				|	S보다 작은 점수 가진 모든 탱크들의 점수 합
				|
	------------S--------------
				|
	더 큰 점수	|
				|

	=> 모든 탱크를 공격함 -> 이 때 총 점수들의 합
*/
// 이 코드는 잘못된 코드 ㅋ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)

typedef long long ll;
struct NODE { int x, y; };
typedef pair<NODE, int> pni;
int T, N;
pni tank[NMAX];
ll fenwick_tree[NMAX];
ll total_score;

void init() {
	total_score = 0LL;
	for (int i = 1; i <= N; i++) {
		fenwick_tree[i] = 0LL;
	}
}

bool cmp(pni n1, pni n2) {
	if (n1.first.x > n2.first.x) return true;
	if (n1.first.x == n2.first.x) {
		if (n1.first.y > n2.first.y) return true;
	}
	return false;
}

void input_() {
	int x, y, s;
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &x, &y, &s);	// 우선 x를 인덱스로
		tank[i] = { {x, y}, s };
	}
	sort(tank + 1, tank + N + 1, cmp);	// x 오름차순, 같으면 y 오름차순
}

void update(int idx, int val) {
	while (idx <= N) {
		fenwick_tree[idx] += (1LL*val);
		idx += idx & -idx;
	}
}

ll get_sum(int idx, int val) {
	ll sum = 0LL;
	while (idx) {
		sum += fenwick_tree[idx];
		idx -= idx & -idx;

	}
	return sum;
}

void get_tank_score() {
	int prev;
	for (int i = 1; i <= N; i++) {
		;
		prev = tank[i].first.x;
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_score); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_tank_score();
		output(tc);
	}
	return 0;
}
#endif