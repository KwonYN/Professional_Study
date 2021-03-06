// (중상) [연습P-0022] LIS 2 
/*
	【 문제 이해 】
	부분수열 : 순서를 유지하되, 일부 항만을 선택하여 만들 수 있는 수열
	최장증가부분수열(LIS) : 각 항이 이전 항에 비해 증가하는 부분수열
	그 길이를 알아내자!

	【 문제 풀이 】
	1) N^2으로는 어떻게 풀어야할지 알겠음
		- for(int i = 1; i <= N; i++) {
			if(dp[i] == 0) dp[i] = 1;
			for(int j = 1; j < i; j++) {
				if(arr[i] > arr[j]) {
					if(dp[i] < dp[j] + 1) dp[i] = dp[j] + 1;
				}
			}
		  }
		  : dp[i]는 i번째 수를 마지막 원소로 가지는 최장증가수열의 길이
		
		- 하지만 N == 300,000이기 때문에 N^2으로는 해결 불가! (시간복잡도)
	
	2) N * log(N)의 방법? : 이진탐색? 인덱스드/세그먼트 트리?
		- 
	
	3) N의 방법? : 스택...? 
		- 
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(300000)
#define MINUS_INF	(0x80000000)

int T, N, arr[NMAX+5];
int max_lis, arr_len;

void init() {
	arr[0] = MINUS_INF;
	for (int i = 1; i <= N; i++) arr[i] = dp[i] = 0;
}

int bin_search(int s, int e, int target) {	// index(수열길이)가 리턴됨
	int m;
	while (s <= e) {
		m = (s + e) / 2;
		if (arr[m] == target) return m;
		if (arr[m] > target) e = m - 1;
		else s = m + 1;
	}
	return s;
}

void input_operation() {
	int tmp, idx;
	max_lis = arr_len = 0;		// 결과값, arr 길이 초기화
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N; i++) {
		scanf("%d", &tmp);
		if (arr[arr_len] < tmp) {
			arr[++arr_len] = tmp;
			max_lis = max(max_lis, arr_len);
		}
		else {
			idx = bin_search(1, arr_len, tmp);
			arr[idx] = tmp;
			max_lis = max(max_lis, idx);
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, max_lis); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_operation();
		output(tc);
	}
	return 0;
}
#endif

// 이전 코드
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(300000)

int T, N;
int A[NMAX + 5], D[NMAX + 5], P[NMAX + 5];
int BIN[NMAX + 5];
int len;

int bin_search(int s, int e, int target) {
	int m = (s + e) / 2;

	while (s <= e) {
		m = (s + e) / 2;
		if (BIN[m] == target) return m;
		if (BIN[m] > target) e = m - 1;
		else s = m + 1;
	}
	return s;
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		int max = 0;
		BIN[0] = 0x80000000;
		len = 0;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &A[i]);

			// 1) O(N^2)의 방법!
			/*
			D[i] = 1;	P[i] = -1;
			for (int j = i - 1; j >= 1; j--) {
				if (A[j] < A[i]) {
					if (D[i] < D[j] + 1) {
						D[i] = D[j] + 1;
						P[i] = j;
						if(max < D[i]) max = D[i];
					}
				}
			}
			*/

			int idx;
			// 2) N logN의 방법! : 또 다른 배열 + 바이너리 서치 필요
			if (BIN[len] < A[i]) {
				BIN[++len] = A[i];
				D[i] = len;
			}
			else {
				idx = bin_search(1, len, A[i]);
				D[i] = idx;
				BIN[idx] = A[i];
			}
		}
		printf("#%d %d\n", tc, len);
	}
	return 0;
}
#endif