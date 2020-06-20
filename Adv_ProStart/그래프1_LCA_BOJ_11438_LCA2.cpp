// BOJ_11438_LCA 2
/*
	N(2 ≤ N ≤ 100,000)개의 정점으로 이루어진 트리. 트리의 각 정점은 1번부터 N번까지 번호가 매겨져 있으며, 루트는 1번.
	두 노드의 쌍 M(1 ≤ M ≤ 100,000)개가 주어졌을 때, 두 노드의 가장 가까운 공통 조상이 몇 번인지 출력.
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100000)

int N, M;
vector<int> edges[NMAX+10];
int depth[NMAX+10];
int familyTree[18][NMAX+10];
int bin[18];

void make_depth() {
	queue<int> que;
	int out;

	depth[1] = 0;	que.push(1);
	while(!que.empty()) {
		out = que.front();	que.pop();
		for(int next : edges[out]) {
			if(familyTree[0][next]) continue;
			familyTree[0][next] = out;
			depth[next] = depth[out] + 1;
			que.push(next);
		}
	}
}

void print_depth() {
	printf("print_depth\n");
	for(int i = 1; i <= N; i++) printf("%d ", depth[i]);
	printf("\n");
}

void make_familyTree() {
	familyTree[0][1] = 1;
	for(int i = 1; i < 18; i++) { // 어차피 input에서부터 한 정점의 부모는 주어짐!
		for(int j = 1; j <= N; j++) {
			familyTree[i][j] = familyTree[i-1][familyTree[i-1][j]];
		}
	}
}

int get_LCA(int a, int b) {
	int tmp, diff;

	if(depth[a] != depth[b]) {
		if(depth[a] < depth[b]) { tmp = a; a = b; b = tmp; }
		diff = depth[a] - depth[b];
		for(int i = 17; i >= 0; i--) {
			if(diff >= bin[i]) {
				diff -= bin[i];
				a = familyTree[i][a];
			}
			if(!diff) break;
		}
	}

	if(a == b) return a;
	for(int i = 17; i >= 0; i--) {
		if(depth[a] >= bin[i]) {
			if(familyTree[i][a] != familyTree[i][b]) {
				a = familyTree[i][a];
				b = familyTree[i][b];
			}
		}
	}
	return familyTree[0][a];
}

int main()
{
	int a, b;

	bin[0] = 1;
	for(int i = 1; i < 18; i++) bin[i] = (bin[i-1]<<1);

	scanf("%d", &N);
	for(int i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	make_depth();
	make_familyTree();
	//print_depth();

	scanf("%d", &M);
	for(int i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", get_LCA(a, b));
	}
	return 0;
}
