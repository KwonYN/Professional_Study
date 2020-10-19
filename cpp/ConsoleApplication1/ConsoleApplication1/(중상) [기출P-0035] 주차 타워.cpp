// (중상) [기출P-0035] 주차 타워
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000010)

typedef long long ll;
int T, N;
int park[NMAX];
ll dp1[NMAX], dp2[NMAX];

void input_() {
	int car_no;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &car_no);
		park[car_no] = i;	// car_no번째 차는 i번째 주차공간에 있음
		// ★원형이기 때문에 정방향, 역방향 모두 움직일 수 있음!
	}
}

ll rotate(int cur, int target) {
	int mx = max(cur, target), mn = min(cur, target);
	ll diff = 1LL * mx - mn;
	return min(diff, 1LL*N - diff);	// 정/역방향 중 작은 비용
}

void get_min_cost() {
	dp1[1] = rotate(1, park[1]);
	for (int i = 2; i <= N; i++) {
		dp1[i] = dp1[i-1] + rotate(park[i-1], park[i]);
	}	// 정순서대로

	ll dp1N = dp1[N];
	dp2[1] = dp1N - rotate(1, park[1]) - rotate(park[2], park[3])
				  + rotate(1, park[2]) + rotate(park[1], park[3]);
	dp2[N-1] = dp1N - rotate(park[N-1], park[N-2]) + rotate(park[N], park[N-2]);
	for (int i = 2; i < N-1; i++) {
		dp2[i] = dp1N - rotate(park[i-1], park[i]) - rotate(park[i+1], park[i+2])
					  + rotate(park[i-1], park[i+1]) + rotate(park[i], park[i+2]);
	}
}

void output(int tc) {
	ll mn = dp1[N];
	for (int i = 1; i < N; i++) {
		mn = min(mn, dp2[i]);
	}
	printf("#%d %lld\n", tc, mn);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_min_cost();
		output(tc);
	}
	return 0;
}
#endif

// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000010)

typedef long long ll;
int T, N;
int park[NMAX];

void input_() {
	int car_no;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &car_no);
		park[car_no] = i;	// car_no번째 차는 i번째 주차공간에 있음
		// ★원형이기 때문에 정방향, 역방향 모두 움직일 수 있음!
	}
}

ll rotate(int cur, int target) {
	int mx = max(cur, target), mn = min(cur, target);
	ll diff = 1LL * mx - mn;
	return min(diff, 1LL*N - diff);	// 정/역방향 중 작은 비용
}

void get_min_cost() {
	;
}

void output(int tc) {
	printf("#%d \n", tc);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		get_min_cost();
		output(tc);
	}
	return 0;
}
#endif


