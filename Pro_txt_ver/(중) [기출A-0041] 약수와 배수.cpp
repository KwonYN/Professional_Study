// (중) [기출A-0041] 약수와 배수
/*
	1. 숫자가 적혀있는 N장의 카드를 준비한다. 
	2. 카드 중 한 장을 골라 손으로 가져온다. 
	3. 나머지 카드 중 현재 고른 카드와 약수 혹은 배수 관계에 있는 카드를 손으로 가져온다. 
	4. 손으로 가져온 카드 중 다시 한 장을 골라 3번의 과정을 진행한다. 
	5. 더 이상 카드가 추가되지 않을 때까지 3,4번을 반복 한다. 
	6. 더 이상 카드가 추가되지 않으면 손으로 가져온 카드의 장수를 세어 점수를 낸다.
	
	연아는 카드게임에서 카드를 가장 많이 가져갈 수 있는 방법을 미리 연구해 놓으려 한다.
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(510)
#define MIN_NUM	(1)
#define MAX_NUM	(1000000)

int T, N, max_num;
int prime[MAX_NUM+5] = { 0 };
int prime_cnt[MAX_NUM], arr[NMAX], max_cnt;

void init() {
	for(int i = 1; i <= max_num; i++) {
		prime_cnt[i] = 0;
	}
	max_num = max_cnt = -1;
}

void input() {
	int num;
	init();
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &num);
		arr[i] = num;
		prime_cnt[prime[num]]++;
		max_num = max(max_num, prime[num]);
	}
}

void operation() {
	int cnt = 0;
	for(int i = 1; i <= N; i++) {
		cnt = 0;
		for(int j = prime[arr[i]]; j <= max_num; j++) {
			cnt += prime_cnt[j];
		}
		max_cnt = max(max_cnt, cnt);
	}
}

void output(int tc) { printf("#%d %d\n", tc, max_cnt); }

int main() {
	prime[1] = 1;
	for(int i = 2; i <= MAX_NUM; i++) {
		if( prime[i] ) continue;
		for(int j = i; j <= MAX_NUM; j += i) {
			if( !prime[j] ) prime[j] = i;	// 약수 중 가장 작은 소수 ( 1 제외 )
		}
	}
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif


#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(510)

struct CARD { int idx, check; };
int T, N, arr[NMAX], chk[NMAX][NMAX], max_cnt;

void input() {
	int num;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &num);
		arr[i] = num;
		for(int j = 1; j < i; j++) {
			int a = arr[j];	int b = arr[i];
			if(a>=b) { // i번째 수 <= j번째 수
				if((a/b > 0) && (a%b == 0)) {
					chk[i][j] = chk[j][i] = a/b;	// i번째 수 * chk[i][j] = j번째 수
					//chk[j][i] = (a/b);// j번째 수 / (chk[j][i]) = i번째 수
				}
				else chk[i][j] = chk[j][i] = 0;
			}
			else {
				if((b/a > 0) && (b%a == 0)) {	// i번째 수 > j번째 수
					chk[j][i] = chk[i][j] = b/a;		// j번째 수 * chk[j][i] = i번째 수
					//chk[i][j] = (b/a);	// i번째 수 / (chk[i][j]) = j번째 수 
				}
				else chk[i][j] = chk[j][i] = 0;
			}
			
		}
	}
}

int get_cnt(int s) {
	int cnt = 1;
	queue<CARD> que;
	bool flag[NMAX] = { false };
	que.push({ s, 0 });	flag[s] = true;
	while(!que.empty()) {
		CARD card = que.front();		que.pop();
		int node = card.idx;
		int val = card.check;
		printf("%d ", arr[node]);
		for(int i = 1; i <= N; i++) {
			if(!flag[i] && chk[node][i] != 0) {
				flag[i] = true;
				que.push({i, chk[node][i]});
				cnt++;
			}
			else if(!flag[i] && arr[i] == val) {
				flag[i] = true;
				que.push({i, chk[node][i]});
				cnt++;
			}
		}
	}
	printf("\n");
	return cnt;
}


void operation() {
	max_cnt = -1;
	for(int i = 1; i <= N; i++) {
		max_cnt = max(max_cnt, get_cnt(i));
	}
}

void output(int tc) { printf("#%d %d\n", tc, max_cnt); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif


