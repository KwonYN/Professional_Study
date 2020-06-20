// BOJ_3176_도로 네트워크
/*
	N개의 도시와 그 도시를 연결하는 N-1개의 도로로 이루어진 도로 네트워크
	모든 도시의 쌍에는 그 도시를 연결하는 유일한 경로가 있고, 각 도로의 길이는 입력
	총 K개의 도시 쌍. 두 도시를 연결하는 경로 상에서 "가장 짧은 도로"(이것만 있다면 다익스트라 쌉가능..)의 길이와 "가장 긴 도로"(하지만 가장 긴 도로도 구해야 하기 때문에 "LCA"로 풀면 되지 않을까?)의 길이?
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX	(100010)
#define INF	(987654321)

int N, K;
int depth[MAX], bin[18];
vector<pair<int, int>> edges[MAX];
int parent[18][MAX], mn[18][MAX], mx[18][MAX];

void make_depth() {	// 트리이니까 1을 그냥 root로 봐줘도 무방!
	queue<int> que;
	int out;
	bool chk[MAX];

	memset(chk, false, sizeof(chk));
	depth[1] = 0;	chk[1] = true;	que.push(1);
	while(!que.empty()) {
		out = que.front();	que.pop();
		for(pair<int, int> next : edges[out]) {
			if(chk[next.first]) continue;
			parent[0][next.first] = out;
			mn[0][next.first] = mx[0][next.first] = next.second;
			depth[next.first] = depth[out] + 1;
			chk[next.first] = true;
			que.push(next.first);
		}
	}
}

void make_familyTree() {
	parent[0][1] = 1;
	for(int i = 1; i < 18; i++) {
		for(int j = 1; j <= N; j++) {
			// [i][j]는 [i-1][j]의 i-1 조상이다. 
			parent[i][j] = parent[i-1][parent[i-1][j]];
			mn[i][j] = min(mn[i-1][j], mn[i-1][parent[i-1][j]]);
			mx[i][j] = max(mx[i-1][j], mx[i-1][parent[i-1][j]]);
		}
	}
}

pair<int, int> get_LCA(int a, int b) {
	int tmp, diff, min_dist = INF, max_dist = -1;

	if(depth[a] != depth[b]) {
		if(depth[a] < depth[b]) { tmp = a; a = b; b = tmp; }
		diff = depth[a] - depth[b];
		for(int i = 17; i >= 0; i--) {
			if(diff >= bin[i]) {
				diff -= bin[i];
				min_dist = min(min_dist, mn[i][a]);
				max_dist = max(max_dist, mx[i][a]);
				a = parent[i][a];
			}
			if(diff == 0) break;
		}
	}

	// 올라온 a와 b가 같다면?
	if(a == b) return { min_dist, max_dist };
	// 올라온 a와 b의 깊이가 서로 같음!
	for(int i = 17; i >= 0; i--) {
		if(depth[a] >= bin[i]) {
			if(parent[i][a] != parent[i][b]) {
				min_dist = min(min_dist, min(mn[i][a], mn[i][b]));
				max_dist = max(max_dist, max(mx[i][a], mx[i][b]));
				a = parent[i][a];
				b = parent[i][b];
			}
		}
	}
	min_dist = min(min_dist, min(mn[0][a], mn[0][b]));
	max_dist = max(max_dist, max(mx[0][a], mx[0][b]));
	return { min_dist, max_dist };
}

int main() {
	int a, b, c;

	bin[0] = 1;
	for(int i = 1; i < 18; i++) bin[i] = (bin[i-1]<<1);
	memset(mn, INF, sizeof(mn));

	scanf("%d", &N);
	for(int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({b, c});
		edges[b].push_back({a, c});
	}
	make_depth();
	make_familyTree();
	
	pair<int, int> result;
	scanf("%d", &K);
	for(int i = 1; i <= K; i++) {
		scanf("%d %d", &a, &b);
		result = get_LCA(a, b);
		printf("%d %d\n", result.first, result.second);
	}
	return 0;
}
