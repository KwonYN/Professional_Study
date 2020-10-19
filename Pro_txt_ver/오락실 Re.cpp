// 오락실 Re
/*
	N개의 집은 N-1개의 양방향 도로를 통해 연결되어 있으며, 
		서로의 집에 갈 수 없는 경우는 존재하지 않는다.
		▶ 양방향 그래프로 주어지지만, "TREE 형태"라는 것!
			→ 이미 트리이기 때문에, MST 알고리즘으로 풀 수 있지 않을까? 하는 헛된 의심하지 말자!!

	각 도로는 통과할 때마다 발생하는 특정 비용이 발생한다.
	친구들은 한 명의 친구네 집을 오락실로 만들어 그곳에 모여 다같이 놀고자 한다.
	하지만 어느 집을 오락실로 만드느냐에 따라 친구들이 그 오락실까지 오는 비용은 다 달라진다.
		▶ 최소비용 / 최소시간 / 최단거리 하면, Dijkstra가 떠오를 것이다.
		   하지만 TREE 형태라는 점, 
				즉 순환하지 않기 때문에 더 최적의 값으로 같은 노드를 재방문할 일 없고,
		   모든 노드에서 돌려야 하는데, ----------------------------> 다익 시간복잡도 최악 O(E * log E)
				그렇게 되면 2만 개인 N의 제곱까지 갈 수 있기 때문에 불가능!!
	
	최소비용을 만들 수 있는 오락실의 위치 수와 
		그때의 최소 비용을 출력하라.
		
	=> TREE 형태, 즉 dfs를 돌렸을 때 루트 노드(보통 1이라고 가정, 어디서 시작해도 상관 없음!!)부터 시작하여
		리프 노드를 찍고 다시 돌아오면서 자식의 정보들을 부모에 더해줄 수 있음!!!
*/
#if 01
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
int child_cnt[NMAX];	// N - child_cnt[i] - 1(자기 자신)은 자식이 아닌 나머지 노드 개수
ll min_cost1[NMAX], min_cost2[NMAX];

void init() {
	for(int i = 1; i <= N; i++) {
		edges[i].clear();
		child_cnt[i] = 0;
		min_cost1[i] = min_cost2[i] = 0LL;
	}
}

void input() {
	int a, b, c;
	scanf("%d", &N);
	init();
	for(int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({c, b});
		edges[b].push_back({c, a});
	}
}

void dfs_get_child_cnt(int node, int parent) {
	for(pii child_info : edges[node]) {
		int child = child_info.second;
		int cst = child_info.first;
		if(child == parent) continue;
		dfs_get_child_cnt(child, node);
		// 자식노드는 자기의 자식 개수에 자기 자신을 포함하여 부모에게 넘겨줌
		child_cnt[node] += (child_cnt[child] + 1);
		// 자식노드는 자기의 자식들이 자기한테 오기까지의 모든 비용에
		// 자기를 포함한 child_cnt[child] + 1개의 노드가 부모로 가는 비용까지 더해주어야 함!
		min_cost1[node] += min_cost1[child] + 1LL*cst*(child_cnt[child]+1);
													// 부모는 여러 자식과 연결되어 있을 수 있다.
	}
}

void reverse_dfs(int node, int parent) {
	for(pii child_info : edges[node]) {
		int child = child_info.second;
		int cst = child_info.first;
		if(child == parent) continue;
		// 우선 child 입장에서 자기 자식과 자기 자신을 제외한 노드개 만큼
		// cst(마지막 간선)을 방문하게 될 것
		min_cost2[child] += 1LL*cst*(N-child_cnt[child]-1);
		// 부모 노드에 저장되어 있는 min_cost2[node]를 더해주고
		// 그 부모의 다른 자식들에서부터 child로 가는 길까지!
		// (child 노드까지 저장되어 있는 min_cost1[child])
		min_cost2[child] += (min_cost2[node] + min_cost1[node] - min_cost1[child] - 1LL*cst*(child_cnt[child]+1));
		reverse_dfs(child, node);
	}
}

void output(int tc) {
	ll chk = (1LL<<62);
	int cnt = 0;
	for(int i = 1; i <= N; i++) {
		printf("min_cost1[%d]:%lld + min_cost2[%d]:%lld => %lld\n", i, min_cost1[i], i, min_cost2[i], min_cost1[i] + min_cost2[i]);
		printf("(children no.:%d // non_children no.:%d)\n\n", child_cnt[i], parent_cnt[i]);
		if(chk > min_cost1[i] + min_cost2[i]) {
			chk = min_cost1[i] + min_cost2[i];
			cnt = 1;
		}
		else if(chk == min_cost1[i] + min_cost2[i]) cnt++;
	}
	printf("#%d %d %lld\n", tc, cnt, chk);
}

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		dfs_get_child_cnt(ROOT, -1);
		reverse_dfs(ROOT, -1);
		output(tc);
	}
	return 0;
}
#endif