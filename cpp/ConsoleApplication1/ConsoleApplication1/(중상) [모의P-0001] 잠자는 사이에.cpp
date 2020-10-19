// (�߻�) [����P-0001] ���ڴ� ���̿�
/*
	���� �ִ� ����! ( �θ��� -> �ڽĳ�� )
	�μ��� Ʈ���� �ƹ� �� ������ ���
		�� ���� �մ� ���� ���� �ϳ�!!�� �׸� ����
	�� �ϳ��� ������ ����� �ٽ� Ʈ���� ���ٵ�..!?!?
	N : 1 ~ 30,000 (�� ������ 1~N �ѹ���)
	�Է� �޴� ������ ���� ������ ���� ����!!
		=> ����Ŭ ã�� ��!?!?
*/
// Union-Find�� �����غ���?
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

// indegree, �� ����������?
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
	Ʈ���� ����? : ��ȯ�� ����� ��!!!
	1) BFS/DFS
		N == 30,000�̴ϱ�
		���� �ϳ��� �����, BFS/DFS�� �����鼭 ��� �ֵ� ��ġ���� ����!
		�׷� �־��� ��� 30000^2���� �ξ� Ŭ �� �ֱ� ������ �Ұ���!!
	2) Ʈ���� �����ϱ�..?
		��Ʈ ��� �� �ϳ�!
		������ N-1
		�׷��� ����Ŭ�� ����!
	3) �ð����⵵?
		N^2�� ������
		N*logN�̳� N, ����� �ð����⵵�� ��!
		2-1) ���׸�Ʈ/�ε����� Ʈ�� -> ������ �ƴ� ���� ���ݾ�..?
		     ����Ʈ�� -> ��� ��¥ �ƴ� �� ����!!
		2-2) ���� -> �� ���� �ƴ� �� ����!!
	4) �ٽ� BFS/DFS?
		�ٽ� �ð����⵵ ����!!
		���ͽ�Ʈ�� : ElogE -> �����ҵ�..? -> 
		�������� : VE -> X
		�÷��̵���� : V^3 -> X
	5) �ᱹ ����Ŭ ã�Ƽ�
	   �� ����Ŭ�� �����ϴ� ������ ��,
	   ���� �������� �Է����� �־��� ������ ������ �ȴٴ� ��!!!
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
							  // child�� parent �ٶ�!!
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
		else {	// ��ȯ �߻�
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
//							  // child�� parent �ٶ�!!
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
		//else {	// ��ȯ �߻�
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
							  // child�� parent �ٶ�!!
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
		else {	// ��ȯ �߻�
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
	1. Ʈ���� ������ ����� ���ÿ�
	   ������ ��Ȳ���� �� �ϳ��� ������ �̿��Ͽ� Ʈ���� �������� ��,
	   � ������ Ʈ���� ���ǿ� ����Ǵ����� �����(?) ��������!
	2. Ʈ���� ����
		1) ����Ŭ ����
		2) N�� ����� Ʈ���� ������ N-1��
		3) ��Ʈ ���� �ϳ�
		4) �������� ��?
			4-1) ��ü ����Ŭ : �ϳ� �ۿ� ���� ������Ʈ -> ��Ʈ���
				=> indegree[��ü ����] == 1
			4-2) �κ� ����Ŭ : �� ��(��Ʈ ��尡 �ƴ� ���) -> �ٸ� ���
				=> indegree[node] == 2�� node �ϳ���
				   ��Ʈ���(indegree == 0),
				   �׸��� indegree == 1�� ������ ���
	3. output���� �ǵ��� ��
	=> ���� indegree[node] == 2�� ���� �ִٸ�, (�κ� ��ȯ) 
		�� node�� �θ� 2�� �� �ϳ��� ���� ��.
	=> �׷��� �ʴٸ�, ��ü N�� ��尡 ��� ��ȯ(����Ŭ) �ȿ� ���Ե� ���̹Ƿ�
		���� �������� �־��� ������ ������ָ� ��
	4. ó������ ��ü ��ȯ�� ������ ���̽��� ����� ���������� ������.
	   ������ indegree[] == 2�� ��찡 ���� ���̶�� �����ؼ�
	   �ڲ� �� ���� ���̽��� Ʋ���� ��찡 ������!
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
							  // child�� parent �ٶ�!!
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
		else {	// ��ȯ �߻�
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
// �ʿ���� �� �� �ĳ�����!
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
	if (two_parent_node) {	// 1) �θ� �� �̳� ���� ��
		for (int i = result_idx[two_parent_node].size() - 1; i >= 0; i--) { // �ִ� 2�� ��
			if (find_circulation(result_idx[two_parent_node][i], two_parent_node)) {
				end_flag = false;
				printf("%d %d\n", result_idx[two_parent_node][i], two_parent_node);
				break;
			}	// 1-1) ��ȯ�� ���� �� && �Է¹��� ������ �� ���� ������ ������ ����ؾ� �ϱ� ������ �ں��� �� ����
		}
		if (end_flag) {
			for (int i = result_idx[two_parent_node].size() - 1; i >= 0; i--) {	// �ִ� 2��
				if (indegree[result_idx[two_parent_node][i]] == 0
					&& outdegree[result_idx[two_parent_node][i]] <= 1) {
					continue;
				}
				printf("%d %d\n", result_idx[two_parent_node][i], two_parent_node);
				break;
			}	// 1-2) ��ȯ�� �̷������ �ʴ´ٸ�, ��Ʈ ��尡 �ƴϸ鼭 ������ ������ �ϳ� �ۿ� ���� �ֵ� �ƴ� �� �ƹ��� ����
		}
	}
	else {	// �θ� ��尡 �� ���� ��尡 ���ٸ�? ��ü ��ȯ!! ������ ������ �ϳ��ۿ� ��� �� �� �������� �ȵǴ� ���� ���� ������!!
		for (int i = N - 1; i >= 0; i--) { // �ִ� N��
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

