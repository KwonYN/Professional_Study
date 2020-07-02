// (중상) [모의P-0001] 잠자는 사이에
/*
	방향 있는 간선! ( 부모노드 -> 자식노드 )
	민수가 트리의 아무 두 정점을 골라
		그 둘을 잇는 방향 간선 하나!!를 그림 ㅋㅋ
	단 하나의 간선만 지우면 다시 트리가 될텐데..!?!?
	N : 1 ~ 30,000 (각 정점은 1~N 넘버링)
	입력 받는 간선의 수는 정점의 수와 같음!!
		=> 사이클 찾는 것!?!?
*/
// Union-Find로 접근해볼까?
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
vector<int> edges[NMAX+5];
int parent[NMAX+5];
bool flag;

int find(int v) {
	if (parent[v] == v) return v;
	return parent[v] = find(parent[v]);
}

void _ally(int v1, int v2) {
	v1 = find(v1);
	v2 = find(v2);
	parent[v1] = v2;
}

void init() {
	flag = false;
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		parent[i] = i;
	}
}

void input() {
	int s, e;
	scanf("%d", &N);
	init();
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		if (flag) continue;//
		//
		if (find(s) != find(e)) {
			_ally(s, e);
		}
		else {
			printf("%d %d\n", s, e);
			flag = true;
		}
		//
		edges[s].push_back(e);
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
	}
	return 0;
}
#endif

// indegree, 즉 위상정렬은?
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
int indegree[NMAX+5];
bool flag;

void init() {
	flag = false;
	for (int i = 1; i <= N; i++) {
		indegree[i] = 0;
	}
}

void input() {
	int s, e;
	scanf("%d", &N);
	init();
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		if (flag) continue;
		indegree[e]++;
		if (indegree[e] > 1) {
			printf("%d %d\n", s, e);
			flag = true;
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
	}
	return 0;
}
#endif

/*
	트리의 조건? : 순환이 없어야 함!!!
	1) BFS/DFS
		N == 30,000이니까
		간선 하나를 지우고, BFS/DFS를 돌리면서 모든 애들 거치는지 보기!
		그럼 최악의 경우 30000^2보다 훨씬 클 수 있기 때문에 불가능!!
	2) 트리란 무엇일까..?
		루트 노드 단 하나!
		간선이 N-1
		그래서 사이클이 없어!
	3) 시간복잡도?
		N^2은 터지니
		N*logN이나 N, 상수의 시간복잡도일 것!
		2-1) 세그먼트/인덱스드 트리 -> 이진이 아닐 수도 있잖아..?
		     이진트리 -> 얘는 진짜 아닐 것 같음!!
		2-2) 스택 -> 얘 또한 아닐 것 같음!!
	4) 다시 BFS/DFS?
		다시 시간복잡도 측면!!
		다익스트라 : ElogE -> 가능할듯..? -> 
		벨만포드 : VE -> X
		플로이드워셜 : V^3 -> X
	5) 결국 사이클 찾아서
	   이 사이클을 구성하는 간선들 중,
	   가장 마지막에 입력으로 주어진 간선을 뽑으면 된다는 것!!!
	   => DFS
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
int parent[NMAX+5], indegree[NMAX+5];
bool flag;
pair<int, int> edges[NMAX+5];
int result_idx;

void init() {
	flag = false;
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		indegree[i] = 0;
	}
}

int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

void _ally_(int v1, int v2) { // v1(parent) -> v2(child)
							  // chile가 parent 바라봄!!
	v1 = find(v1);
	v2 = find(v2);
	parent[v2] = v1;
}

void input_operation_output(int tc) {
	int s, e;
	bool continue_flag = false;
	scanf("%d", &N);
	init();
	printf("#%d ", tc);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		if (continue_flag) continue;
		edges[i] = { s, e };
		if (++indegree[e] > 1) {
			flag = true;
			result_idx = i;
		}
		if (find(s) != find(e)) _ally_(s, e);
		else {
			continue_flag = true;
			if (flag) printf("%d %d\n", edges[result_idx].first, edges[result_idx].second);
			else printf("%d %d\n", edges[i].first, edges[i].second);
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_operation_output(tc);
	}
	return 0;
}
#endif

