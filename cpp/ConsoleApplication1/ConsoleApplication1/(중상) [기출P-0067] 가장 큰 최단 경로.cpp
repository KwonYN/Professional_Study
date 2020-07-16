// (중상) [기출P-0067] 가장 큰 최단 경로
/*
	간선(E)의 총 개수는? : (N-1)*N/2 < 13000 < 2^14 
	다익스트라? : E*logE = 약 N^2

	흠....
	출발점도 도착점도 정해져있지 않다는 것은 모든 케이스를 생각해주어야 하는 것인데
	모든 출발-도착점 쌍 사이의 최단거리를 구해주는 알고리즘은
		바로 플로이드-워셜 알고리즘..!!
	하지만 시간복잡도가 N^3인 것을 감안한다면,
		N의 크기가 500이고, 테케가 총 20개 있으니
		최악의 경우 1.25억 * 20 == 25억 == 25초...
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(500)	// N^3 == 1.25억;;

typedef long long ll;
int T, N;
int deleted[NMAX+5];
ll pre_edges[NMAX+5][NMAX+5], edges[NMAX+5][NMAX+5];
const ll INF = 0x7fffffffffffffffLL;

void input() {
	long long w;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &deleted[i]);	// 결국 모든 점/간선이 지워질 것
	}
	for (int i = 1; i < N; i++) {
		for (int j = i + 1; j <= N; j++) {
			scanf("%lld", &w);
			if (w == 0LL) w = INF;
			pre_edges[i][j] = pre_edges[j][i] = w;
		}
	}
}

void pre_process(int start) {
	int s, e;
	for (int i = start; i <= N; i++) {
		s = deleted[i];
		for (int j = start; j <= N; j++) {
			e = deleted[j];
			edges[i][j] = pre_edges[s][e];
			//printf("%lld ", edges[i][j]);
		}
		//printf("\n");
	}
}

void print_edges(int start) {
	printf("\ndeleted : %d\n", deleted[start]);
	printf("print_edges\n");
	for (int i = start; i <= N; i++) {
		for (int j = start; j <= N; j++) {
			printf("%lld ", edges[i][j]);
		}
		printf("\n");
	}
	printf("▶ ");
}

void floyd_warshall(int tc) {
	ll max_min_path;
	printf("#%d", tc);
	for (int k = 1; k <= N; k++) {
		// 초기화
		pre_process(k);
		// 플로이드 워셜 : 모든 쌍 최단거리 구하기
		for (int i = k; i <= N; i++) {
			if (edges[i][k] == INF) continue;
			for (int j = k; j <= N; j++) {
				if (edges[k][j] == INF) continue;
				if (i == j) continue;
				edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
			}
		}
		print_edges(k);
		// 가장 큰 최단경로 구하기
		max_min_path = -1;
		for (int i = k; i <= N; i++) {
			for (int j = k; j <= N; j++) {
				if (edges[i][j] == INF) continue;
				max_min_path = max(max_min_path, edges[i][j]);
			}
		}
		printf(" %lld", max_min_path);
	}
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		floyd_warshall(tc);
	}
	return 0;
}
#endif


#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(500)	// N^3 == 1.25억;;

typedef long long ll;
int T, N;
int deleted[NMAX+5];
ll pre_edges[NMAX+5][NMAX+5], edges[NMAX+5][NMAX+5];
const ll INF = 0x7fffffffffffffffLL;
ll max_min_path[NMAX+5];

void input() {
	long long w;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &deleted[i]);	// 결국 모든 점/간선이 지워질 것
	}
	for (int i = 1; i < N; i++) {
		for (int j = i + 1; j <= N; j++) {
			scanf("%lld", &w);
			if (w == 0LL) w = INF;
			pre_edges[i][j] = pre_edges[j][i] = w;
		}
	}
}

void pre_process() {
	int s, e;
	for (int i = 1; i <= N; i++) {
		s = deleted[N+1-i];
		for (int j = 1; j <= N; j++) {
			e = deleted[N+1-j];
			edges[i][j] = pre_edges[s][e];
		}
		max_min_path[i] = -1LL;	// 초기화
	}
}

void floyd_warshall() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			if (edges[i][k] == INF) continue;
			for (int j = 1; j <= N; j++) {
				if (edges[k][j] == INF) continue;
				if (i == j) continue;
				edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
			}
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= k; j++) {
				if (edges[i][j] == INF) continue;
				max_min_path[k] = max(max_min_path[k], edges[i][j]);
			}
		}
	}
}

void output(int tc) { 
	printf("#%d", tc);
	for (int i = N; i >= 1; i--) {
		printf(" %lld", max_min_path[i]);
	}
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		pre_process();
		floyd_warshall();
		output(tc);
	}
	return 0;
}
#endif


