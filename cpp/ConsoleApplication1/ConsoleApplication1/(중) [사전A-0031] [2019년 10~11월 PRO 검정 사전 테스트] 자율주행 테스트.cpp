// (��) [����A-0031] [2019�� 10~11�� PRO ���� ���� �׽�Ʈ] �������� �׽�Ʈ
/*
	�� ���� ���� ��
	N���� ������ M���� ����(�����, �ӵ� o)
	���� <-> �ְ�ӵ� ���̰� �ʹ� ũ�� �ȵȴ�!
	����, �������� o
	=> �ְ�, �����ӵ� ���� ���� ���� ����� �ְ�/�����ӵ� ����?

	�� ���� Ǯ�� ��
	N : 1 ~ 1000
	M : 1 ~ 4000
	������ �ӵ� : 1 ~ 10��
	���� -> ���� ��δ� ������ ����
	=> queue�� min, max�� ���
	   �� ��忡 ���ؼ� �ִ�, �ּҼӵ��� ���̰� �ּ��� ���� ã���� ���� ������?
*/
#if 0
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(4000)
#define INF		(0x7fffffff)

typedef pair<int, int> pii;
typedef pair<int, pair<int, pii>> pq_node;
int T, N, M, dep, arr;
vector<pii> edges[NMAX+5];
int diff[NMAX+5];

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		diff[i] = INF;
	}
}

void input() {
	int s, e, w;
	scanf("%d %d", &N, &M);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &s, &e, &w);
		edges[s].push_back({ w, e });
		edges[e].push_back({ w, s });
	}
	scanf("%d %d", &dep, &arr);
}

void drive() {
	// { diff, { node, { min, max} } }
	priority_queue<pq_node, vector<pq_node>, greater<pq_node>> pq;
	pq.push({ 0, { dep, { INF, -1 } } });	diff[dep] = 0;
	while (!pq.empty()) {
		pq_node node = pq.top();	pq.pop();
		int cur_node = node.second.first;
		if (cur_node == arr) return;
		for (pii next : edges[cur_node]) {
			if(node.second.second.first > next.first) node.second.second.first = next.first;
			if(node.second.second.second < next.first) node.second.second.second = next.first;
			if (diff[next.second] > node.second.second.second - node.second.second.first) {
				diff[next.second] = node.second.second.second - node.second.second.first;
				pq.push({ diff[next.second], {next.second, { node.second.second.first, node.second.second.second }} });
			}
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, diff[arr]); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		drive();
		for (int i = 1; i <= N; i++) {
			printf("%d ", diff[i]);
		}
		printf("\n");
		output(tc);
	}
	return 0;
}
#endif

// Re
/*
	�� ���� Ǯ�� 2 ��
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(4000)
#define INF		(0x7fffffff)

typedef pair<int, int> pii;
typedef pair<int, pair<int, pii>> pipipii;
int T, N, M, S, E;
vector<pii> edges[NMAX+5];
int diff[NMAX+5];
bool visited[NMAX+5][NMAX+5];

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		diff[i] = INF;
		for (int j = 1; j <= N; j++) visited[i][j] = false;
	}
}

void input() {
	int a, b, s;
	scanf("%d %d", &N, &M);
	init();
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &s);
		edges[a].push_back({ s, b });
		edges[b].push_back({ s, a });
	}
	scanf("%d %d", &S, &E);
}

void drive() {
	queue<pipipii> que;
	que.push({ 0, { S, { 0, INF } } });		diff[S] = 0;
	while (!que.empty()) {
		pipipii node = que.front();		que.pop();
		if (node.second.first == E) continue;
		for (pii next : edges[node.second.first]) {
			int max_vel = max(node.second.second.first, next.first);
			int min_vel = min(node.second.second.second, next.first);
			int chk = max_vel - min_vel;
			if (diff[next.second] > chk) {
				visited[node.second.first][next.second] = true;
				visited[next.second][node.second.first] = true;
				diff[next.second] = chk;
				que.push({ chk, { next.second, {max_vel, min_vel} } });
			}
			else if (!visited[node.second.first][next.second]) {
				visited[node.second.first][next.second] = true;
				visited[next.second][node.second.first] = true;
				que.push({ chk, { next.second, {max_vel, min_vel} } });
			}
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, diff[E]); }

void print_diff() {
	printf("print_diff\n");
	printf("S = %d, E = %d\n", S, E);
	for (int i = 1; i <= N; i++) printf("%d ", diff[i]);
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		drive();
		//print_diff();
		output(tc);
	}
	return 0;
}
#endif

// Re
/*
	�� ���� Ǯ�� 3 ��
	���� �ּ� ~ s->e ����Ǿ��� �������� �ִ�/�ּ� ����
	�� ��° �ּ� ~ ..
	�� ��° �ּ� ~ ..
	=> M*(M+1)/2 = �� 800��
	   �ᱹ 800�� * tc = �� 2.4��
	   => ����ġ�Ⱑ �ʿ��ϴ�!!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(4000)
#define INF		(0x7fffffff)

typedef pair<int, pair<int, int>> pipii;
int T, N, M, S, E;
vector<pipii> edges;
int parent[NMAX+5];
bool flag;
int min_vel, max_vel, min_diff;

void init() {
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
	}
	min_vel = INF, max_vel = 0;
}

void input() {
	int a, b, s;
	scanf("%d %d", &N, &M);
	edges.clear();
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &s);
		edges.push_back({ s, {a, b} });
	}
	scanf("%d %d", &S, &E);
	sort(edges.begin(), edges.end()); // ��������
}

int find(int v) {
	if(parent[v] == v) return v;
	return parent[v] = find(parent[v]);
}

void _ally(int v1, int v2) {
	v1 = find(v1);
	v2 = find(v2);
	parent[v1] = v2;
}

void drive() {
	bool end_flag;
	flag = true;
	min_diff = INF;
	while (flag) {
		init();
		end_flag = false;
		for (pipii node : edges) {
			int n1 = node.second.first;
			int n2 = node.second.second;
			if (find(n1) != find(n2)) {
				_ally(n1, n2);
				min_vel = min(min_vel, node.first);
				max_vel = max(max_vel, node.first);
			}
			if (find(S) == find(E)) {
				min_diff = min(min_diff, max_vel - min_vel);
				edges.erase(edges.begin());
				end_flag = true;
				break;
			}
		}
		if (!end_flag) flag = false;
	}
}

void output(int tc) { printf("#%d %d\n", tc, min_diff); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		drive();
		output(tc);
	}
	return 0;
}
#endif