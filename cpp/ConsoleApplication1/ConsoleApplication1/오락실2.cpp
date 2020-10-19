// 2020.10.17 (��) ������2 �ڵ�
/*
	[ �� �� ]
	2
	10
	4 1 4
	6 4 10
	8 9 4
	6 7 5
	4 5 1
	2 4 3
	3 4 5
	8 6 3
	10 8 3
	10
	4 1 4
	6 4 10
	8 9 4
	6 7 5
	4 5 20
	2 4 3
	3 4 5
	8 6 3
	10 8 3

	[ �� �� ]
	#1 1 15
	#2 1 20
*/
// 1. Ʈ���� �׷��� + dfs ��ȸ
// 1-1) 2���� dfs �Լ����� ���� �ٸ� dp �迭 ���
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(20010)
#define ROOT	(1)

typedef long long ll;
typedef pair<int, int> pii;
int T, N;
vector<pii> edges[NMAX];
ll dist1[NMAX];	// 'i����� �ڽ� ���� �� i���' �Ÿ�(�ִ�)
ll dist2[NMAX];	// 'i����� �ڽ� ��尡 �ƴ� ���(�θ� ��� && �θ� ����� �ٸ� �ڽ� ���) �� i���' �Ÿ�(�ִ�)
ll dist1_second[NMAX];	// dist1�� �ִ���, dist1_second�� �� ��°�� ū �ð�
int dist1_idx[NMAX];	// dist1�� �ִ��� �ڽ� ����� ��ȣ ����

void init() {	// �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		dist1[i] = dist2[i] = dist1_second[i] = 0LL;
		dist1_idx[i] = 0;
	}
}

void input() {	// �Է�
	int a, b, c;
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
		edges[b].push_back({ c, a });
	}
}

void child_dfs(int node, int parent) {	// [�ڽ� �� �θ� ����] �Ÿ� �ִ밪
	for (pii next : edges[node]) {
		int child = next.second;
		int dist = next.first;
		if (child == parent) continue;
		child_dfs(child, node);
		ll dist_chk = dist1[child] + 1LL * dist;
		if (dist1[node] < dist_chk) {
			dist1_second[node] = dist1[node];
			dist1[node] = dist_chk;
			dist1_idx[node] = child;
		}
		else dist1_second[node] = max(dist1_second[node], dist_chk);
	}
}

void non_child_dfs(int node, int parent) {	// [no �ڽ� �� �� ���] �Ÿ� �ִ밪
	for (pii next : edges[node]) {
		int child = next.second;
		int dist = next.first;
		if (child == parent) continue;
		ll chk1 = max(dist2[node], dist1_second[node]); // dist1�� �ִ�� ���� �ڽ������� ������ ��
		ll chk2 = max(dist2[node], dist1[node]); // �� �� �ڽ������� ������ ��
		// �θ� �� �ڽ��� �� �� �� �̵��ϰ� ��! : �������� �ʿ� ���� �� ������!
		if (child == dist1_idx[node]) {
			dist2[child] += (chk1 + 1LL * dist);
		}
		else {
			dist2[child] += (chk2 + 1LL * dist);
		}
		non_child_dfs(child, node);
	}
}

void output(int tc) {	// ���
	ll dist_min = (1LL << 62);
	int dist_min_cnt = 0;
	for (int i = 1; i <= N; i++) {
		ll dist_chk = max(dist1[i], dist2[i]);
		if (dist_min > dist_chk) {
			dist_min = dist_chk;
			dist_min_cnt = 1;
		}
		else if (dist_min > dist_chk) dist_min_cnt++;
	}
	printf("#%d %d %lld\n", tc, dist_min_cnt, dist_min);
}

void print_dist() {	// [�����] dist�迭 ���
	for (int i = 1; i <= N; i++) {
		printf("[%2d] 1: %3lld / 2: %3lld\n", i, dist1[i], dist2[i]);
	}
	printf("================\n");
}

int main() {
	//freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		child_dfs(ROOT, -1);
		non_child_dfs(ROOT, -1);
		print_dist();
		output(tc);
	}
	return 0;
}
#endif


// 1-2) 2���� dfs �Լ����� ���� dp �迭 ���
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(20010)
#define ROOT	(1)		// Ʈ���� �׷���(N�� ����, N-1�� ����� ����, ������ �� ��忡�� �ٸ� ������ ���� ������ ����)�� ��� ��Ʈ�� ��Ƶ� ��� ����!
#define INF		(1LL<<62)

typedef long long ll;
typedef pair<int, int> pii;
int T, N;
vector<pii> edges[NMAX];
ll max_dist[NMAX];		// '�ڱ� ���� ��� �� �ڱ� �ڽ� ���' ������ �Ÿ� �ִ밪
ll second_dist[NMAX];	// max_dist�� �ִ���, second_dist�� �� ��°�� ū �ð�
int max_dist_idx[NMAX];	// max_dist�� �ִ��� �ڽ� ����� ��ȣ ���� (ù ��° dfs)

void init() {	// �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		max_dist[i] = second_dist[i] = 0LL;
		max_dist_idx[i] = 0;
	}
}

void input() {	// �Է�
	int a, b, c;
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
		edges[b].push_back({ c, a });
	}
}

void child_dfs(int node, int parent) {	// [�ڽ� �� �θ� ����] �Ÿ� �ִ밪
	for (pii next : edges[node]) {
		int child = next.second;
		int dist = next.first;
		if (child == parent) continue;
		child_dfs(child, node);
		ll dist_chk = max_dist[child] + 1LL * dist;
		if (max_dist[node] < dist_chk) {
			second_dist[node] = max_dist[node];
			max_dist[node] = dist_chk;
			max_dist_idx[node] = child;
		}
		else second_dist[node] = max(second_dist[node], dist_chk);
	}
}

void non_child_dfs(int node, int parent, ll acc_dist) {	// [no �ڽ� �� �� ���] �Ÿ� �ִ밪
	ll next_acc;
	for (pii next : edges[node]) {
		int child = next.second;
		int dist = next.first;
		if (child == parent) continue;
		ll chk1 = max(acc_dist, second_dist[node]); // dist1�� �ִ�� ���� �ڽ������� ������ ��
		ll chk2 = max(acc_dist, max_dist[node]); 	 // �� �� �ڽ������� ������ ��
		// �θ� �� �ڽ��� �� �� �� �̵��ϰ� ��! : �������� �ʿ� ���� �� ������!
		if (child == max_dist_idx[node]) {
			next_acc = chk1 + 1LL * dist;
			max_dist[child] = max(max_dist[child], next_acc);
		}
		else {
			next_acc = chk2 + 1LL * dist;
			max_dist[child] = max(max_dist[child], chk2 + 1LL * dist);
		}
		non_child_dfs(child, node, next_acc);
	}
}

void output(int tc) {	// ���
	ll dist_min = INF;
	int dist_min_cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (dist_min > max_dist[i]) {
			dist_min = max_dist[i];
			dist_min_cnt = 1;
		}
		else if (dist_min > max_dist[i]) dist_min_cnt++;
	}
	printf("#%d %d %lld\n", tc, dist_min_cnt, dist_min);
}

void print_dist() {	// [�����] max_dist �迭 ���
	for (int i = 1; i <= N; i++) {
		printf("[%2d] %lld\n", i, max_dist[i]);
	}
	printf("================\n");
}

int main() {
	//freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		child_dfs(ROOT, -1);
		non_child_dfs(ROOT, -1, 0LL);
		print_dist();
		output(tc);
	}
	return 0;
}
#endif




// 2. �������� : ���� �ʿ�..!!!
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(20010)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
int T, N;
vector<pii> edges[NMAX];
int indegree[NMAX], outdegree[NMAX];
ll dist[NMAX];
bool flag[NMAX];

void init() {	// �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		indegree[i] = outdegree[i] = 0;
		dist[i] = 0LL;
		flag[i] = false;
	}
}

void input() {	// �Է�
	int a, b, c;
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
		outdegree[a]++;		indegree[b]++;
		edges[b].push_back({ c, a });
		outdegree[b]++;		indegree[a]++;
	}
	/*for (int i = 1; i < N; i++) {
		printf("[%2d] indegree : %d // outdegree : %d\n", i, indegree[i], outdegree[i]);
	}*/
}

void get_dist() {	// ���� �ٱ��� �ִ� ���鿡������ ���� �߾�(?)�� �ִ� ������� �̵�
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	for (int i = 1; i <= N; i++) {
		// in / out degree�� ��� 1�̶�� ���� �� ���ɼ� X (���� �����̿� �ִ� ����)
		if (indegree[i] == 1 && outdegree[i] == 1) {
			pq.push({ 0LL, i });
		}
	}
	while (!pq.empty()) {
		pii out = pq.top();		pq.pop();
		ll acc_dist = out.first;
		int cur_node = out.second;
		if (flag[cur_node]) continue;
		flag[cur_node] = true;
		/*
		printf("================================\n");
		printf("[%2d] %lld (in : %d // out : %d)\n", cur_node, acc_dist, indegree[cur_node], outdegree[cur_node]);
		*/
		indegree[cur_node]--;		outdegree[cur_node]--;
		//printf("dist[%d] = %lld\n	��\n", cur_node, dist[cur_node]);
		for (pii next : edges[cur_node]) {
			ll nex_dist = 1LL * next.first;
			int nex_node = next.second;
			if (flag[nex_node]) continue;
			dist[nex_node] = max(dist[nex_node], acc_dist + nex_dist);
			//printf("[%2d] %lld (in : %d // out : %d)\n", nex_node, dist[nex_node], indegree[nex_node], outdegree[nex_node]);
			indegree[nex_node]--;		outdegree[nex_node]--;
			if (indegree[nex_node] == 1 && outdegree[nex_node] == 1) {	// ��Ʈ ��Ŷ ����!
				pq.push({ dist[nex_node], nex_node });
				//printf("%d push!!\n", nex_node);
			}
		}
	}
}

void output(int tc) {	// ���
	ll min_dist = 0LL;
	int min_dist_cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (min_dist < dist[i]) {
			min_dist = dist[i];
			min_dist_cnt = 1;
		}
		else if (min_dist == dist[i]) min_dist_cnt++;
	}
	printf("#%d %d %lld\n", tc, min_dist_cnt, min_dist);
}

int main() {
	//freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		get_dist();
		output(tc);
	}
	return 0;
}
#endif