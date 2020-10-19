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
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
int parent[NMAX+5], indegree[NMAX+5];
bool circul_flag;
pair<int, int> edges[NMAX+5];
vector<int> result_idx[NMAX+5];

void init() {
	circul_flag = false;
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		indegree[i] = 0;
		result_idx[i].clear();
	}
}

int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

void _ally_(int v1, int v2) { // v1(parent) -> v2(child)
							  // child가 parent 바라봄!!
	v1 = find(v1);
	v2 = find(v2);
	parent[v2] = v1;
}

void input_operation_output(int tc) {
	int s, e;
	scanf("%d", &N);
	init();
	printf("#%d ", tc);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		edges[i] = { s, e };
		if (++indegree[e] > 1) circul_flag = true;
		result_idx[e].push_back(s);
		if (find(s) != find(e)) _ally_(s, e);
		else {	// 순환 발생
			if (circul_flag) {
				int prev = -1;
				for (int idx = result_idx[e].size() - 1; idx >= 0; idx--) {
					if (indegree[result_idx[e][idx]] == 0) {
						if (prev != result_idx[e][idx]) {
							prev = result_idx[e][idx];
							continue;
						}
					}
					printf("%d %d\n", result_idx[e][idx], e);
				}
			}
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

#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
//int parent[NMAX + 5];
int indegree[NMAX + 5], outdegree[NMAX + 5];
bool circul_flag;
pair<int, int> edges[NMAX+5];
vector<int> result_idx[NMAX+5];
int tmp_idx;

void init() {
	circul_flag = false;
	for (int i = 1; i <= N; i++) {
		//parent[i] = i;
		indegree[i] = 0;
		outdegree[i] = 0;
		result_idx[i].clear();
	}
}

//int find(int v) {
//	if (v == parent[v]) return v;
//	return parent[v] = find(parent[v]);
//}
//
//void _ally_(int v1, int v2) { // v1(parent) -> v2(child)
//							  // child가 parent 바라봄!!
//	v1 = find(v1);
//	v2 = find(v2);
//	parent[v2] = v1;
//}

void input_operation() {
	int s, e;
	scanf("%d", &N);
	init();
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		edges[i] = { s, e };
		if (++indegree[e] > 1) {
			circul_flag = true;
			tmp_idx = e;
		}
		outdegree[s]++;
		result_idx[e].push_back(s);
		//if (find(s) != find(e)) _ally_(s, e);
		//else {	// 순환 발생
		//	if (circul_flag) {
		//		for (int idx = result_idx[tmp_idx].size() - 1; idx >= 0; idx--) {
		//			if (indegree[result_idx[tmp_idx][idx]] == 0
		//				&& outdegree[result_idx[tmp_idx][idx]] <= 1) {
		//				continue;
		//			}
		//			printf("%d %d\n", result_idx[tmp_idx][idx], tmp_idx);
		//			break;
		//		}
		//	}
		//	else printf("%d %d\n", edges[i].first, edges[i].second);
		//}
	}
}

void output(int tc) {
	printf("#%d ", tc);
	if (circul_flag) {
		for (int idx = result_idx[tmp_idx].size() - 1; idx >= 0; idx--) {
			if (indegree[result_idx[tmp_idx][idx]] == 0
				&& outdegree[result_idx[tmp_idx][idx]] <= 1) {
				continue;
			}
			printf("%d %d\n", result_idx[tmp_idx][idx], tmp_idx);
			break;
		}
	}
	else {
		printf("%d %d\n", edges[N-1].first, edges[N - 1].second);
	}
}

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


// ReReReRe
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
int parent[NMAX + 5], indegree[NMAX + 5], outdegree[NMAX + 5];
bool two_parent_flag;
pair<int, int> edges[NMAX + 5];
vector<int> result_idx[NMAX + 5];
int two_parent_node, cir_node;

void init() {
	two_parent_flag = false;
	two_parent_node = cir_node = 0;
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		indegree[i] = 0;
		outdegree[i] = 0;
		result_idx[i].clear();
	}
}

int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

void _ally_(int v1, int v2) { // v1(parent) -> v2(child)
							  // child가 parent 바라봄!!
	v1 = find(v1);
	v2 = find(v2);
	parent[v2] = v1;
}

void input_operation() {
	int s, e;
	scanf("%d", &N);
	init();
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		edges[i] = { s, e };
		if (++indegree[e] > 1) {
			two_parent_flag = true;
			two_parent_node = e;
		}
		outdegree[s]++;
		result_idx[e].push_back(s);
		if (find(s) != find(e)) _ally_(s, e);
		else {	// 순환 발생
			cir_node = e;
			printf("||\n");
		}
	}
}

void output(int tc) {
	printf("#%d ", tc);
	if (two_parent_flag) {
		for (int idx = result_idx[two_parent_node].size() - 1; idx >= 0; idx--) {
			if (indegree[result_idx[two_parent_node][idx]] == 0
				&& outdegree[result_idx[two_parent_node][idx]] <= 1) {
				continue;
			}
			printf("%d\n", find(result_idx[two_parent_node][idx]));
			/*if (find(result_idx[two_parent_node][idx]) == two_parent_node) {
				printf("%d %d\n", result_idx[two_parent_node][idx], two_parent_node);
				break;
			}*/
		}
	}
	else {
		for (int idx = result_idx[cir_node].size() - 1; idx >= 0; idx--) {
			if (indegree[result_idx[cir_node][idx]] == 0
				&& outdegree[result_idx[cir_node][idx]] <= 1) {
				continue;
			}
			printf("%d %d\n", result_idx[cir_node][idx], cir_node);
			break;
		}
	}
}

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

// ReReReReRe
/*
	1. 트리의 조건을 물어봄과 동시에
	   문제의 상황에서 단 하나의 간선을 이용하여 트리가 망가졌을 때,
	   어떤 식으로 트리의 조건에 위배되는지를 물어보는(?) 문제였음!
	2. 트리의 조건
		1) 사이클 없음
		2) N개 노드의 트리의 간선은 N-1개
		3) 루트 노드는 하나
		4) 망가졌을 때?
			4-1) 전체 사이클 : 하나 밖에 없는 리프노트 -> 루트노드
				=> indegree[전체 노드들] == 1
			4-2) 부분 사이클 : 그 외(루트 노드가 아닌 노드) -> 다른 노드
				=> indegree[node] == 2인 node 하나와
				   루트노드(indegree == 0),
				   그리고 indegree == 1인 나머지 노드
	3. output에서 의도한 바
	=> 만약 indegree[node] == 2인 점이 있다면, (부분 순환) 
		그 node의 부모 2개 중 하나가 답일 것.
	=> 그렇지 않다면, 전체 N개 노드가 모두 순환(사이클) 안에 포함된 것이므로
		가장 마지막에 주어진 간선을 출력해주면 됨
	4. 처음에는 전체 순환이 가능한 케이스를 제대로 생각해주지 못했음.
	   무조건 indegree[] == 2인 경우가 나올 것이라고 생각해서
	   자꾸 몇 개의 케이스만 틀리는 경우가 생겼음!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
int parent[NMAX + 5], indegree[NMAX + 5], outdegree[NMAX + 5];
pair<int, int> edges[NMAX + 5];
vector<int> result_idx[NMAX + 5];
int two_parent_node, cir_node_idx;

void init() {
	two_parent_node = cir_node_idx = 0;
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		indegree[i] = 0;
		outdegree[i] = 0;
		result_idx[i].clear();
	}
}

int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

void _ally_(int v1, int v2) { // v1(parent) -> v2(child)
							  // child가 parent 바라봄!!
	v1 = find(v1);
	v2 = find(v2);
	parent[v2] = v1;
}

void input_operation() {
	int s, e;
	scanf("%d", &N);
	init();
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		edges[i] = { s, e };
		if (++indegree[e] > 1) {
			two_parent_node = e;
		}
		outdegree[s]++;
		result_idx[e].push_back(s);
		if (find(s) != find(e)) _ally_(s, e);
		else {	// 순환 발생
			cir_node_idx = i;
		}
	}
}

bool find_circulation(int start_node, int cir_node) {
	queue<int> que;
	que.push(start_node);
	while (!que.empty()) {
		int node = que.front();		que.pop();
		for (int next : result_idx[node]) {
			if (next == cir_node) return true;
			que.push(next);
		}
	}
	return false;
}

void output(int tc) {
	bool end_flag = true;
	printf("#%d ", tc);
	if (two_parent_node) {
		for (int idx = result_idx[two_parent_node].size() - 1; idx >= 0; idx--) {
			if (find_circulation(result_idx[two_parent_node][idx], two_parent_node)) {
				end_flag = false;
				printf("%d %d\n", result_idx[two_parent_node][idx], two_parent_node);
				break;
			}
		}
		if (end_flag) {
			for (int idx = result_idx[two_parent_node].size() - 1; idx >= 0; idx--) {
				if (indegree[result_idx[two_parent_node][idx]] == 0
					&& outdegree[result_idx[two_parent_node][idx]] <= 1) {
					continue;
				}
				printf("%d %d\n", result_idx[two_parent_node][idx], two_parent_node);
				break;
			}
		}
	}
	else {
		printf("%d %d\n", edges[cir_node_idx].first, edges[cir_node_idx].second);
	}
}

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
// 필요없는 것 다 쳐내보자!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(30000)

int T, N;
int indegree[NMAX + 5], outdegree[NMAX + 5];
int two_parent_node;
pair<int, int> edges[NMAX + 5];
vector<int> result_idx[NMAX + 5];

void init() {
	two_parent_node = 0;
	for (int i = 1; i <= N; i++) {
		indegree[i] = 0;
		outdegree[i] = 0;
		result_idx[i].clear();
	}
}

void input_operation() {
	int s, e;
	scanf("%d", &N);
	init();
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &s, &e);
		edges[i] = { s, e };
		if (++indegree[e] > 1) {
			two_parent_node = e;
		}
		outdegree[s]++;
		result_idx[e].push_back(s);
	}
}

bool find_circulation(int start_node, int cir_node) {
	queue<int> que;
	que.push(start_node);
	while (!que.empty()) {
		int node = que.front();		que.pop();
		for (int next : result_idx[node]) {
			if (next == cir_node) return true;
			que.push(next);
		}
	}
	return false;
}

void output(int tc) {
	bool end_flag = true;
	printf("#%d ", tc);
	if (two_parent_node) {	// 1) 부모가 둘 이나 있을 때
		for (int i = result_idx[two_parent_node].size() - 1; i >= 0; i--) { // 최대 2번 돔
			if (find_circulation(result_idx[two_parent_node][i], two_parent_node)) {
				end_flag = false;
				printf("%d %d\n", result_idx[two_parent_node][i], two_parent_node);
				break;
			}	// 1-1) 순환이 있을 때 && 입력받은 정보들 중 가장 마지막 간선을 출력해야 하기 때문에 뒤부터 돈 것임
		}
		if (end_flag) {
			for (int i = result_idx[two_parent_node].size() - 1; i >= 0; i--) {	// 최대 2번
				if (indegree[result_idx[two_parent_node][i]] == 0
					&& outdegree[result_idx[two_parent_node][i]] <= 1) {
					continue;
				}
				printf("%d %d\n", result_idx[two_parent_node][i], two_parent_node);
				break;
			}	// 1-2) 순환이 이루어지지 않는다면, 루트 노드가 아니면서 나가는 간선이 하나 밖에 없는 애들 아닌 애 아무나 지워
		}
	}
	else {	// 부모 노드가 두 개인 노드가 없다면? 전체 순환!! 나가는 간선이 하나밖에 없어서 그 선 지워지면 안되는 간선 빼고 지우자!!
		for (int i = N - 1; i >= 0; i--) { // 최대 N번
			if (outdegree[edges[i].first] >= 1) {
				printf("%d %d\n", edges[i].first, edges[i].second);
				break;
			}
		}
	}
}

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

