// (중상) [교육P-0035] 이진 탐색 2
/*
	N 개의 서로 다른 정수가 오름차순으로 정렬되어 있는 수열이 있음
	이들과 값이 다른 새로운 정수 하나를 수열에 넣을 경우,
		그 새로운 값이 오름차순 정렬을 유지하면서 위치할 자리를 찾아야 할 때,
		이진 탐색을 이용하면 빠르게 답을 알아낼 수 있다.
	새로운 값은 기존 값과 같지 않으므로
		새로운 값과 기존의 값을 비교할 때의 결과는
		"새로운 값이 더 작다" 혹은 "새로운 값이 더 크다" 두 가지 경우만 존재하며,
		"같다" 라는 경우는 존재하지 않을 것이다.
		결국 새로운 값은 기존의 값들 사이, 또는 맨 앞, 또는 맨 뒤에 위치할 것이다.
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(105)

int T, N, K, compare_time[NMAX], arr[NMAX], worst_time;

void input() {
	char tmp[NMAX];
	scanf("%s", tmp);
	for (N = 0; tmp[N]; N++) {
		compare_time[N + 1] = tmp[N] - '0';
	}
	for (int i = 1; i <= N; i++) {
		arr[i] = i * 2 - 1;
	}
}

int _bin_search(int s, int e, int target) {	// 누적 비교 시간 리턴
	int m, accumulated_time = 0;
	while (s <= e) {
		m = (s + e) / 2;
		printf("%d - %d - %d\n", s, m, e);
		if (arr[m] > target) e = m - 1;
		else s = m + 1;
		accumulated_time += compare_time[m];
	}
	printf("accumulated_time = %d\n", accumulated_time);
	return accumulated_time;
}

void get_worst_compare_time() {
	worst_time = 0;
	for (int i = 0; i <= N; i++) {
		worst_time = max(worst_time, _bin_search(1, N, i * 2));
	}
}

void output(int tc) { printf("#%d %d\n", tc, worst_time); }

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		get_worst_compare_time();
		output(tc);
	}
	return 0;
}
#endif


/*
	[ Binary Search Tree ]
	가능한 모든 BST의 모양을 만들어보는 건 너무 비효율적이다.
		노드 n개가 있고 어떤 노드를 루트에 뒀을 때,
		그 노드를 제외한 나머지 n-1개의 모든 노드들은
			부모 노드의 왼쪽이나 오른쪽에 위치할 수 있으므로
			가능한 BST의 경우의 수가 2^(n-1) 개이다.
		즉. 지수 시간복잡도라는 얘기다.
	그래서 최적 BST를 빨리 찾기 위해서 또 다이나믹 프로그래밍이 등장한다.
		BST의 특성상 어떤 BST의 왼쪽, 오른쪽 서브트리가 각각 최적 BST여야
			해당 BST도 최적이다. 즉 최적의 원리가 성립한다.
		먼저 i번째 key부터 j번째 key까지로 최적 BST를 만들었을 때의 평균 검색 시간,
			즉 최적값을 A[i][j] 라고 정의하자.
		그러면 서브트리의 평균 검색 시간은
			루트노드가 k번째 key일 때 왼쪽, 오른쪽 각각 A[1][k-1], A[k+1][n] 이다.
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(105)
#define INF		(0x7fffffff)

int T, N, compare_time[NMAX], dp[NMAX][NMAX];

void input() {
	char tmp[NMAX];
	scanf("%s", tmp);
	for (N = 0; tmp[N]; N++) {
		compare_time[N + 1] = tmp[N]-'0';
	}
}

void set_dp() {	// init
	for (int i = 1; i <= N+1; i++) {
		for (int j = i - 1; j <= N; j++) {
			if (i - j == 1) dp[i][j] = 0;
			else dp[i][j] = INF;
		}
	}
}

int get_dp(int s, int e) {
	if (dp[s][e] == 0) return 0;
	if (dp[s][e] != INF) return dp[s][e];
	for (int m = s; m <= e; m++) {
		int left = get_dp(s, m-1);
		int right = get_dp(m+1, e);
		dp[s][e] = min(dp[s][e], max(dp[s][m-1], dp[m+1][e]) + compare_time[m]);
	}
	return dp[s][e];
}

void output(int tc) { printf("#%d %d\n", tc, dp[1][N]); }

void print_dp() {
	for (int i = 1; i <= N+1; i++) {
		for (int j = 0; j < i - 1; j++) printf("   ");
		for (int j = i - 1; j <= N; j++) {
			printf("%2d ", dp[i][j]);
		}
		printf("\n");
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		set_dp();
		get_dp(1, N);
		//print_dp();
		output(tc);
	}
	return 0;
}
#endif
