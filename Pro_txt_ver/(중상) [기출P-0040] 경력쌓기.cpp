// (중상) [기출P-0040] 경력쌓기
/*
	Stack : 1 Mbytes
	N개의 직장 (1 ~ N)
		철민씨는 각 직장에서 받는 월급들을 다 알고 있음.
	직장 알선 소개소 M개
		한 상담소는 i <-> j번 직장간의 이동을 소개해주는 역할을 함.			 -> 월급 바뀌어
		어떤 상담소는 같은 직장에서 부서만 바꾸어 주는 역할을 함. ( i == j ) -> 월급 안 바뀌어
		
	철민씨는 가능한 경력쌓기방법(Career Path)이 몇 가지나 되는지 알고 싶다.
					( == 월급이 계속 증가하기만 하는 2개 이상의 직장들의 순서이다. )
	한 직장에서 다른 직장으로 이동할 때는 반드시 상담소를 거쳐야 한다.
	또, 동일한 순서의 직장들인 경우라도 중간에 거치는 상담소가 다른 경우는 다른 경력인 것으로 간주한다.
	첫 직장과 마지막 직장은 아무 곳이나 가능하다.
*/

// dfs ver. => 왜 Runtime Error가 뜨는 건지..?
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(300010)
#define MOD		(1000000007LL)

typedef long long ll;
int T, N, M, salary[NMAX];
vector<int> edges[NMAX];
int indegree[NMAX];
ll child_node_cnt[NMAX];

void input() {
	int a, b;
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &salary[i]);
		// init
		edges[i].clear();
		indegree[i] = 0;
		child_node_cnt[i] = 0LL;
	}
	for(int i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		if(salary[a] > salary[b]) {
			edges[b].push_back(a);
			indegree[a]++;
		}
		else if(salary[b] > salary[a]) {
			edges[a].push_back(b);
			indegree[b]++;
		}
	}
}

void dfs(int child) {	// get child node cnt (accumulated)
	if(child_node_cnt[child]) return;
	for(int next : edges[child]) {
		dfs(next);
		child_node_cnt[child] = (child_node_cnt[child]%MOD + (child_node_cnt[next]+1LL)%MOD)%MOD;
	}
}

void get_child_cnt() {
	for(int i = 1; i <= N; i++) {
		if(!indegree[i]) dfs(i);
	}
}

void output(int tc) {
	ll cnt = 0;
	for(int i = 1; i <= N; i++) {
		cnt = (cnt%MOD + child_node_cnt[i]%MOD)%MOD;
	}
	printf("#%d %lld\n", tc, cnt);
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_child_cnt();
		output(tc);
	}
	return 0;
}
#endif



// MST ver.
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(300010)
#define MOD		(1000000007)

int T, N, M, salary[NMAX];
vector<int> edges[NMAX];
int indegree[NMAX], child_node_cnt[NMAX];

void input() {
	int a, b;
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &salary[i]);
		// init
		edges[i].clear();
		indegree[i] = child_node_cnt[i] = 0;
	}
	for(int i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		if(salary[a] < salary[b]) {
			edges[b].push_back(a);
			indegree[a]++;
		}
		else if(salary[b] < salary[a]) {
			edges[a].push_back(b);
			indegree[b]++;
		}
	}
}

void get_child_cnt() {
	queue<int> que;
	for(int i = 1; i <= N; i++) if(!indegree[i]) que.push(i);
	while(!que.empty()) {
		int cur_node = que.front();		que.pop();
		for(int next_node : edges[cur_node]) {
			if(--indegree[next_node] == 0) que.push(next_node);
			child_node_cnt[next_node] = ((child_node_cnt[next_node]%MOD) + (child_node_cnt[cur_node]+1)%MOD)%MOD;
		}
	}
}

void output(int tc) {
	int cnt = 0;
	for(int i = 1; i <= N; i++) {
		cnt = (cnt%MOD + child_node_cnt[i]%MOD)%MOD;
	}
	printf("#%d %d\n", tc, cnt);
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		get_child_cnt();
		output(tc);
	}
	return 0;
}
#endif