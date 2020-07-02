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
							  // chile�� parent �ٶ�!!
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

