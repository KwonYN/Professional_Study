// BOJ_2522_줄 세우기
// 위상정렬! : 여기에서 indegree배열이 어떻게 ++되고, 어떻게 --되며, 이 의미가 무엇인지 되새길 것!!
//            작은 학생 -> 큰 학생이므로, 큰 학생의 idx인 indegree[idx]++;로 올라갈 것!
//            더 이상 들어오지 않는, 즉 위상(?)이 0이라서 앞으로 나갈 일만 있는(?) 번호의 학생이 que.push();될 것이고,
//            이 학생은 정확한 순서는 몰라도 적어도 지금 정도의 키 순위일 것!

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(32000)

int N, M;
vector<int> edges[NMAX+10];
int indegree[NMAX+10];
queue<int> que;

void init() {
	for(int i = 1; i <= N; i++) {
		edges[i].clear();
		indegree[i] = 0;
	}
}

void make_order() {
	queue<int>que;
	for(int i = 1; i <= N; i++) if(!indegree[i]) que.push(i);
	while(!que.empty()) {
		int out = que.front();	que.pop();
		printf("%d ", out);
		for(int next : edges[out]) {
			if(--indegree[next] == 0) que.push(next);
		}
	}
	printf("\n");
}

int main() {
	int A, B;
	scanf("%d %d", &N, &M);
	init();
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		edges[A].push_back(B);	// A < B == A -> B
		indegree[B]++;
	}
	make_order();
	return 0;
}
