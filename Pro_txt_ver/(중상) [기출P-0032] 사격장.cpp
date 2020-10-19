// (중상) [기출P-0032] 사격장 
/*
	N개의 과녁 (1~N 순서대로 일렬)
	M명의 손님 (차례대로 사격장 방문하여 총으로 과녁 맞힘. N개 중 일부 구간 정하여 전부.)
	과녁을 맞히면 점수를 얻음. But, 이전 손님이 맞혔던 과녁의 점수는 얻지 못함. 이미 얻었기 때문.
	실제 손님들이 얻는 점수는 각각 몇 점?
		→ 홀수 손님은 +, 짝수 손님은 -하여 모두 더한 값을 출력
		   ( 각 1점이니까, 최소 -10만, 최대 10만 )
		
	[조건]
	N : 1 ~ 100,000
	M : 1 ~ 100,000
	A, B : 1 ~ 100,000 (A <= B)
*/
// Union-Find
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(100010)

int T, N, M;
int parent[NMAX], score[MMAX];
bool chk_score[NMAX];

void init() {
	for(int i = 1; i <= N; i++) {
		parent[i] = i;
		chk_score[i] = false;
	}
}

int find(int v) {
	if(v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

void _union(int v1, int v2) {
	v1 = find(v1);
	v2 = find(v2);
	if(v1 > v2) parent[v2] = v1;
	else parent[v1] = v2;
}

bool chk_parent(int v1, int v2) {
	return (find(v1) == find(v2));
}

int shoot(int s, int e) {
	int shoot_score = 0;
	while(true) {
		s = parent[s];		// 일단 s와 연결되어 있는 가장 큰 값으로! 없다면 자기 자신!
		if(!chk_score[s]) {// 현 위치(과녁)을 전 사람이 쏘지 않았다면(false) 점수 가산
							// 만약 쏘았다면 이미 _union되었을 것!
							// ( 가장 오른쪽 끝 대표값이라도 이미 false가 되어있을 것! )
			chk_score[s] = true;
			shoot_score++;
		}
		if(chk_parent(s, e)) break;	// 오른쪽 끝(e)까지 도달했다면 다음 사람 차례!
		if(!chk_parent(s, s+1)) {		// 끝까지 도달하지 않았다면 다음 과녁 맞추러 ㄱㄱ
			_union(s, s+1);
		}
	}
	return shoot_score;
}

void process() {
	int A, B;
	// input
	scanf("%d %d", &N, &M);
	init();
	for(int i = 1; i <= M; i++) {	// 각 손님(M명)이 과녁 쏴서 맞힘
		scanf("%d %d", &A, &B);
		// update
		score[i] = shoot(A, B);
	}
}

void output(int tc) {
	int sum_result = 0;
	for(int i = 1; i <= M; i++) {
		if(i&1) sum_result += score[i];
		else sum_result -= score[i];
	}
	printf("#%d %d\n", tc, sum_result);
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		process();
		output(tc);
	}
	return 0;
}
#endif

// Tree
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(100010)

int T, N, M;

void input() {
	int A, B;
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= M; i++) {
		scanf("%d %d", &A, &B);
		;
	}
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
	}
	return 0;
}
#endif