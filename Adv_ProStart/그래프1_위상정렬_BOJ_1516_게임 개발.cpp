// BOJ_1516_게임 개발
/*
	종족별 균형과 전체 게임 시간 등을 조절하는 부분만 남아 있었다.
	게임 플레이에 들어가는 시간은 상황에 따라 다를 수 있기 때문에, 모든 건물을 짓는데 걸리는 최소의 시간을 이용하여 근사하기로 하였다.
	물론, 어떤 건물을 짓기 위해서 다른 건물을 먼저 지어야 할 수도 있기 때문에 문제가 단순하지만은 않을 수도 있다.
	편의상 자원은 무한히 많이 가지고 있고, 건물을 짓는 명령을 내리기까지는 시간이 걸리지 않는다고 가정하자.
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(500)
#define MAX(a, b)	( ( (a) > (b) ) ? (a) : (b) )

int N;	// 건물 종류 수
int tm[NMAX+5]; // i번 종류 건물 짓는 시간
vector<int> edges[NMAX+5]; // i번 종류 건물 짓기 위해 먼저 지어져야 하는 건물 번호 ( 없다면 가장 처음! )
int indegree[NMAX+5];
queue< int > que;

int main()
{
	int a, b;
	int tmp[NMAX+5];

	// input
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &a);
		tm[i] = tmp[i] = a;
		while(true) {
			scanf("%d", &b);
			if(b != -1) {
				edges[b].push_back(i);
				indegree[i]++;
			}
			else break;
		}
	}
	
	// 위상정렬
	for(int i = 1; i <= N; i++) if(indegree[i] == 0) que.push(i);
	int out;
	while(!que.empty()) {
		out = que.front();	que.pop();
		for(int next : edges[out]) {
			tm[next] = MAX(tm[next], tm[out] + tmp[next]);
			if(--indegree[next] == 0) que.push(next);
		}
	}

	// 프린트
	for(int i = 1; i <= N; i++) printf("%d\n", tm[i]);
	return 0;
}
