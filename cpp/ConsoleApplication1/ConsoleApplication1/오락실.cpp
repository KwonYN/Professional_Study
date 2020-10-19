// 오락실
/*
	N : N명의 집(각각 친구)
		- 5 <= N <= 2만
	N개의 집들은 N-1개의 양방향 도로를 통해 연결됨
	그리고 서로가 서로의 집에 갈 수 없는 일은 존재하지 않음
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(20020)
#define START	(1)

typedef pair<int, int> pii;
typedef long long ll;
int T, N;
vector<pii> edges[NMAX];
const ll INF = (10010LL*20020LL);
ll min_cost;
int child_node_cnt[NMAX];
ll each_down_cost[NMAX], each_up_cost[NMAX]; // up == not down
ll ans[NMAX];

void init() {
	min_cost = INF;
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		child_node_cnt[i] = 0;
		each_down_cost[i] = each_up_cost[i] = ans[i] = 0LL;
	}
}

void input_() {
	int a, b, c;
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ c, b });
		edges[b].push_back({ c, a });
	}
}

void dfs_down(int child, int parent) {	// dfs 움직임(?)을 생각해보자!! 백트레킹
	for (pii node : edges[child]) {
		if (node.second != parent) {
			dfs_down(node.second, child);
			child_node_cnt[child] += child_node_cnt[node.second];
			each_down_cost[child] += (((ll)node.first) * child_node_cnt[node.second] + each_down_cost[node.second]);
		}
	}
	child_node_cnt[child]++;	// 백트래킹 시, 자기 자신의 개수를 위해 ++해주고 되돌아감
}

void dfs_up(int child, int parent) {
	for (pii node : edges[child]) {
		if (node.second != parent) {
			each_up_cost[node.second] += (each_down_cost[child] - each_down_cost[node.second]) - (ll)child_node_cnt[node.second]*node.first
									  + each_up_cost[child] + ((ll)child_node_cnt[START] - child_node_cnt[node.second])*node.first;
			dfs_up(node.second, child);
		}
	}
}

void output(int tc) {
	int cnt = 0;
	ll chk;
	for (int i = 1; i <= N; i++) {
		chk = each_down_cost[i] + each_up_cost[i];
		if (min_cost > chk) {
			min_cost = chk;
			cnt = 1;
		}
		else if (min_cost == chk) cnt++;
	}
	printf("#%d %d %lld\n", tc, cnt, min_cost);
}

// for Debugging : 함수명 "print_~"
void print_child() {
	printf("print_child\n");
	for (int i = 1; i <= N; i++) {
		printf("[%d] %d\n", i, child_node_cnt[i]);
	}
	printf("\n");
}

void print_down_cost() {
	printf("print_down_cost\n");
	for (int i = 1; i <= N; i++) {
		printf("[%d] %lld\n", i, each_down_cost[i]);
	}
	printf("\n");
}

void print_up_cost() {
	printf("print_up_cost\n");
	for (int i = 1; i <= N; i++) {
		printf("[%d] %lld\n", i, each_up_cost[i]);
	}
	printf("\n");
}
// 여기까지 for 디버깅

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		dfs_down(START, 0);
		//print_down_cost();
		dfs_up(START, 0);
		//print_child();
		//print_up_cost();
		output(tc);
	}
	return 0;
}
#endif