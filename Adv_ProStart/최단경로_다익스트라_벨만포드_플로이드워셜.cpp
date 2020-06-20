/************************/
/* [ 2020.02.18 day 7 ] */
/************************/

// (중상) [연습P-0017] 재밌는 게임 
#if 01

#include <cstdio>
#include <algorithm>
using namespace std;

int T, N, M;

int main()
{

	return 0;
}

#endif




// (중) [기출A-0037] 핵심도시1 
// 정점은 도시를 뜻하고, 간선은 두 도시간의 양방향 도로를 뜻한다.
// 핵심도시의 총 수와 목록 출력 -  밑에 선배님 코드로 다시..
#if 01
#pragma warning(disable: 4996)

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define VMAX	(100000)
#define EMAX	(300000)

int T, V, E; // V : 3 ~ 10만, E : V-1 ~ 30만
vector<int> edges[EMAX+2];
bool visited[VMAX + 2];
int city[VMAX+2], od[VMAX+2], chd[VMAX + 2], low[VMAX+2];
int order, cnt;

void dfs(int prev, int s) {
	if (order > V) return;

	od[s] = low[s] = ++order;
	for (int next : edges[s]) {
		if (visited[next]) continue;
		visited[next] = true;
		chd[s]++;
		//printf("%d의 자식 추가 : %d\n", s, next);
		dfs(s, next);

		for (int nn : edges[s]) {
			if (visited[nn] && od[s] < od[nn]) {
				low[s] = min(low[s], od[nn]);
			}
		}
		if (s != 1) if (od[s] <= low[next]) city[cnt++] = s;
	}
	if (s == 1) {
		if (chd[s] <= 2) city[cnt++] = s;
	}
}

void init() {
	for (int i = 1; i <= V; i++) {
		edges[i].clear();
		visited[i] = false;
		chd[i] = od[i] = low[i] = 0;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int A, B;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		printf("#%d", tc);
		scanf("%d %d", &V, &E);
		cnt = order = 0;
		init();
		for (int i = 0; i < E; i++) {
			scanf("%d %d", &A, &B);
			edges[A].push_back(B);
			edges[B].push_back(A);
		}
		visited[1] = true;
		dfs(0, 1);
		visited[1] = false;

		sort(city, city + cnt);
		printf(" %d", cnt);
		for (int i = 0; i < cnt; i++) {
			printf(" %d", city[i]);
			city[i] = 0;
		}
		printf("\n");
	}

	return 0;
}
/*
1
9 10
1 2
2 3
4 1
5 1
2 7
3 7
8 4
8 5
7 6
8 9
*/

#endif

// 선배님 코드 : Need to Retry!!
#if 01

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define VMAX	(100000)
#define EMAX	(300000)

int T, V, E; // V : 3 ~ 10만, E : V-1 ~ 30만
vector<int> edges[EMAX + 2];
int od[VMAX + 2], order, cnt;;
bool isCutVertex[VMAX + 2];

int dfs(int s) {
	int childlow, childcnt = 0;
	od[s] = ++order;
	int low = order;

	for (int next : edges[s]) {
		if (od[next] == -1) {	// 아직 방문해보지 않은 정점
			childlow = dfs(next);
			if (childlow >= od[s] && s != 1 && !isCutVertex[s]) {
				isCutVertex[s] = true;	cnt++;
			}
			childcnt++;
			low = min(low, childlow);
		}
		else {
			low = min(od[next], low);
		}
	}
	if (s == 1 && childcnt >= 2 && !isCutVertex[s]) {
		isCutVertex[s] = true;	cnt++;
	}
	return low;
}

void init() {
	order = cnt = 0;
	for (int i = 1; i <= V; i++) {
		edges[i].clear();
		isCutVertex[i] = false;
		od[i] = -1;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int A, B;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		// 입력 및 초기화
		scanf("%d %d", &V, &E);
		init();
		for (int i = 0; i < E; i++) {
			scanf("%d %d", &A, &B);
			edges[A].push_back(B);
			edges[B].push_back(A);
		}
		// dfs를 통해 단절점 찾기
		dfs(1);
		// 출력 부분
		printf("#%d %d", tc, cnt);
		for (int i = 1; i <= V; i++) {
			if (isCutVertex[i]) printf(" %d", i);
		}
		printf("\n");
	}
	return 0;
}

#endif




// 다익스트라
// (중상) [교육P-0009] 최단 경로 
#if 01

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100000)
#define MMAX	(300000)
#define INF		(1<<31)

typedef struct { int dest, tm; }HEAP;

int T, N, M;
vector<pair<int, int>> edges[NMAX+10]; // 도로에서 걸리는 시간
int time_spent;
int maldan;
HEAP heap_min[NMAX*4];	// 힙
int D[NMAX+10];			// 기록해주는 배열
int visited[NMAX+10];	// 체크 배열

void init() {
	time_spent = -1;
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
	}

	for (maldan = 1; maldan < N; maldan *= 2);
	heap_min[1] = { 0, 0 };	// 시작점은 1
	for (int i = 2; i < 2 * maldan; i++) heap_min[i] = { INF, INF };
}

void update(HEAP &h) {
	int i = 1, l, r;
	HEAP tmp;
	if (heap_min[0].tm <= h.tm) {
		tmp = heap_min[0];
		heap_min[0] = h;
		h = tmp;
	}
	heap_min[1] = h;
	while (i < N) {
		l = i*2, r = 2*i+1;
		if (l > N) break;
		if (heap_min[i].tm < min(heap_min[l].tm, heap_min[r].tm)) break;
		else if (heap_min[i].tm > heap_min[l].tm && heap_min[l].tm <= heap_min[r].tm) {
			HEAP tmp = heap_min[i];
			heap_min[i] = heap_min[l];
			heap_min[l] = tmp;
			i = l;
		}
		else if (heap_min[i].tm > heap_min[r].tm && heap_min[l].tm > heap_min[r].tm) {
			HEAP tmp = heap_min[i];
			heap_min[i] = heap_min[r];
			heap_min[r] = tmp;
			i = r;
		}
	}
}

HEAP *get_time() { return &(heap_min[1]); }

int van_dijk(int s1, int s2) {
	HEAP* out;
	int e = 1;

	while (e != N) {
		out = get_time();	visited[out->dest] = 1;
		time_spent += out->tm;
		for (pair<int, int> next : edges[out->dest]) {
			HEAP tmp = { next.first, next.second };
			update(tmp);
		}
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b, c;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		init();
		for (int i = 0; i <= M; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back({ b, c });
			edges[b].push_back({ a, c });
		}
		van_dijk(1, 0);
		printf("#%d %d\n", tc, time_spent);
	}

	return 0;
}

#endif

// 선배님 코드 : priority_queue<가중치, 정점(edges[idx]), compare함수>
// greater<자료형>을 넣으면 작은 놈부터 나옴!!
#if 01

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define INF		(0x7fffffff)
#define NMAX	(100000)

int T, N, M;
vector<pair<int, int>> edges[NMAX+2];
int d[NMAX+2];

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		d[i] = INF;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b, c;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		init();
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back({ b, c });
			edges[b].push_back({ a, c });
		}

		priority_queue < pair<int, int>, vector<pair<int, int>>, 
			greater<pair<int, int>> > pq; // 최소힙
		pq.push({ 0, 1 });	d[1] = 0;
		while (!pq.empty()) {
			pair<int, int> cur = pq.top();	pq.pop();
			if (cur.first > d[cur.second]) continue;
			d[cur.second] = cur.first;
			if (cur.second == N) break;
			// 앞 가중치, 뒤 정점 - 우선순위큐와 edges에 넣은 순서가 다르니 헷갈리지 말 것!!
			for (pair<int, int> child : edges[cur.second]) {
				if ( d[child.first] > d[cur.second] + child.second ) {
					pq.push({ d[cur.second] + child.second, child.first});
				}
			}
		}
		if (d[N] == INF) d[N] = -1;
		printf("#%d %d\n", tc, d[N]);
	}
	return 0;
}

#endif





// 다익스트라 : Need to Retry!!
// (중상) [교육P-0032] 패닉룸 2 
#if 01

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX		(500)
#define INF		(0x7fffffff)

typedef pair<int, pair<int, int>> pipii;

int T, N, M;
int panic[MAX+5][MAX+5];
int van_dijk[MAX+5][MAX+5];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };	// 상하좌우
int min_panic;

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &panic[i][j]);
			van_dijk[i][j] = INF;
		}
	}
}

int get_panic() {
	priority_queue < pipii,
					 vector<pipii>,
					 greater<pipii> > pq; // 최소힙
	pq.push({ 0, {1, 1} });	van_dijk[1][1] = 0;
	while (!pq.empty()) {
		pipii cur = pq.top();	pq.pop();
		int f = cur.second.first, s = cur.second.second;
		if (cur.first > van_dijk[f][s]) continue;
		van_dijk[f][s] = cur.first;
		if (f == N && s == M) break;
		for (int i = 0; i < 4; i++) {
			int ny = f + dy[i];
			int nx = s + dx[i];
			if (ny < 1 || ny > N || nx < 1 || nx > M) continue;
			if (van_dijk[ny][nx] > van_dijk[f][s] + panic[f][s]) {
				van_dijk[ny][nx] = van_dijk[f][s] + panic[f][s];
				pq.push({ van_dijk[ny][nx] , { ny, nx } });
			}
		}
	}
	return van_dijk[N][M] + panic[N][M];
}

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		min_panic = get_panic();
		printf("#%d %d\n", tc, min_panic);
	}
	return 0;
}

#endif





// 벨만 포드 알고리즘 : Need to Retry!!
// 참고 : https://victorydntmd.tistory.com/104
// (중상) [연습P-0008] 웜홀
#if 01

#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(500)
#define INF		(0x7fffffff)

typedef pair<int, int> pii;

int T, N, M, W;
vector<pii> edges[NMAX + 5];
int d[NMAX+5];
char * result[2] = { "NO", "YES" };
int flag;

void init() {
	flag = 0;
	for (int i = 1; i <= N; i++) {
		d[i] = INF;
		edges[i].clear();
	}
}

void time_travel(int s) {
	priority_queue < pii, vector<pii>, greater<pii> > pq;

	pq.push({ 0, s });		d[1] = 0;
	while (!pq.empty()) {
		pii cur = pq.top();		pq.pop();
		int nt = cur.first, ns = cur.second;
		if (nt);

		for (pii next : edges[ns]) {
			int w = next.first;
			int e = next.second;
			if (w >= 0) {
				if (d[e] > d[ns] + w) {
					d[e] = d[ns] + w
						pq.push
				}
			}
			else {

			}
		}

	}
}

int main() {
	freopen("in.txt", "r", stdin);
	int s, e, t;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &M, &W);
		init();
		for (int i = 1; i <= M; i++) {
			scanf("%d %d %d", &s, &e, &t);
			edges[s].push_back({ t, e });
			edges[e].push_back({ t, s }); // 양방향
		}
		for (int i = 1; i <= W; i++) {
			scanf("%d %d %d", &s, &e, &t);
			edges[s].push_back({ t*(-1), e }); // 단방향
		}
		for (int i = 1; i <= N; i++) time_travel(i);
		printf("#%d %s\n", tc, result[flag]);
	}
	return 0;
}

#endif

// 선배님 코드 : Need to Retry!!
#if 01

#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(500)
#define MMAX	(2500)
#define WMAX	(200)
#define INF		(0x7fffffff)

typedef pair<int, pair<int, int>> pipii;

int T, N, M, W;
pipii edges[MMAX*2 + WMAX + 5];
int d[NMAX + 5];

void init() {
	for (int i = 1; i <= N; i++) {
		d[i] = INF;
	}
	d[1] = 0;
}

int main() {
	freopen("in.txt", "r", stdin);
	int s, e, t;
	scanf("%d", &T); 
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &M, &W);
		init();
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &s, &e, &t);
			edges[i * 2] = { t, {s, e} };
			edges[i * 2 + 1] = { t, {e, s} };
		}
		for (int i = 2 * M; i < 2 * M + W; i++) {
			scanf("%d %d %d", &s, &e, &t);
			edges[i] = { -t, {s, e} };
		}


		int a, b, c;
		bool minusCycle = false;
		for (int i = 1; i < N; i++) {	// 모든 정점에 대하여
			for (int j = 0; j < 2 * M + W; j++) {
				a = edges[j].second.first;	// s
				b = edges[j].second.second;	// e
				c = edges[j].first;			// t
				if (d[a] != INF) d[b] = min(d[b], d[a] + c);
			}
		}
		for (int j = 0; j < 2 * M + W; j++) { // 다시 한 번 돌려보자!
			// Why? : 순환구간이 존재하기 때문. 즉, 음의 가중치가 있어서 최소값 갱신 필요가 있어지는 상황이 오게 됨!!
			a = edges[j].second.first;
			b = edges[j].second.second;
			c = edges[j].first;
			if (d[a] != INF && d[a] + c < d[b]) {
				minusCycle = true;		break;
			}
		}
		if (minusCycle) printf("#%d %s\n", tc, "YES");
		else printf("#%d %s\n", tc, "NO");
	}
	return 0;
}

#endif





// 플로이드 워셜 알고리즘
// (중상) [교육P-0006] 가장 먼 두 도시 
#if 01

#include <cstdio>
using namespace std;
#define NMAX	(300)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

int T, N;
int city[NMAX + 5][NMAX + 5];
int max_dist;

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		// input
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &city[i][j]);
			}
		}
		max_dist = 0;
		// get min distance
		for (int k = 1; k <= N; k++) {
			for (int s = 1; s <= N; s++) {
				for (int e = 1; e <= N; e++) {
					if (s == e) continue;
					city[s][e] = MIN(city[s][e], city[s][k] + city[k][e]);
				}
			}
		}
		// result
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (max_dist < city[i][j]) max_dist = city[i][j];
			}
		}
		printf("#%d %d\n", tc, max_dist);
	}
	return 0;
}

#endif





// (중상) [기출P-0051] 조상이 키컸으면 
#if 01

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(10000)

int T, N, K, Q;
pair<int, int> parent[NMAX+5];
vector<int> group[NMAX + 5];
int familyTree[15][NMAX + 5];
int depth[NMAX + 5];

void init() {
	for (int i = 1; i <= Q; i++) {
		group[i].clear();
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &Q);
		printf("#%d", tc);
		init();
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &a, &b);	// a : 부모, b : i번 놈의 키
			parent[i] = { a, b };
		}
		for (int i = 1; i <= Q; i++) {
			scanf("%d", &a);
			for (int j = 1; j <= a; j++) {
				scanf("%d", &b);
				group[i].push_back(b);
			}
		}
		// 자 그럼 조상 찾자!

	}
	return 0;
}

#endif
