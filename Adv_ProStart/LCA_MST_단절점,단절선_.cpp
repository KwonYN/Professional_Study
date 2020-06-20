/************************/
/* [ 2020.02.19 day 8 ] */
/************************/


// (중상) [기출P-0051] 조상이 키컸으면 
/*
	이들을 도와 공통 조상들 중 "가장 키가 컸던" 구성원의 키를 출력하는 프로그램을 작성하라.
*/
#if 01

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(10000)

int T, N, K, Q;
vector<int> parent[NMAX + 5];
int ki[NMAX + 5];
int familyTree[15][NMAX + 5];
int depth[NMAX + 5];
int bin[15];

void init() {
	for (int i = 1; i <= N; i++) {
		depth[i] = 0;
		parent[i].clear();
	}
}

void get_depth() {
	queue<int> que;
	int out;

	que.push(1);
	while (!que.empty()) {
		out = que.front();	que.pop();
		for (int next : parent[out]) {
			depth[next] = depth[out] + 1;
			que.push(next);
		}
	}
}

void print_depth() {
	printf("print_depth\n");
	for (int i = 1; i <= N; i++) printf("%d ", depth[i]);
	printf("\n");
}

void make_familyTree() {
	//familyTree[0][1] = 0;
	for (int i = 1; i < 15; i++) {
		for (int j = 1; j <= N; j++) {
			familyTree[i][j] = familyTree[i - 1][familyTree[i - 1][j]];
		}
	}
}

int get_LCA(int a, int b) {
	int tmp, diff;

	if (depth[a] != depth[b]) {	// 두 정점의 depth가 다르다면??
		// 아래에 있는 정점을 위로 올려서 depth를 맞춰준다 (a가 더 깊이 있음)
		if (depth[a] < depth[b]) { tmp = a; a = b; b = tmp; }
		diff = depth[a] - depth[b];
		for (int i = 14; i >= 0; i--) {
			if (diff >= bin[i]) {
				diff -= bin[i];
				a = familyTree[i][a];
			}
			if (diff == 0) break;
		}
	}

	if (a == b) return a;	// 타고 타고 올라왔는데 공통조상이 a == b이다??
	// 같이  depth를 올라가면서 a, b 가 같은지 확인! (일단 둘의 깊이는 같다!!)
	for (int i = 14; i >= 0; i--) {
		if (depth[a] >= bin[i]) {
			if (familyTree[i][a] != familyTree[i][b]) {
				a = familyTree[i][a];	b = familyTree[i][b];
			}
		}
	}
	return familyTree[0][a];
	// 최소공통조상이 Root라고 하더라도, Root의 조상은 Root임!! 그래서 상관 없음
}

int get_max_ki(int n) {
	int max = ki[n];
	for (int d = depth[n]; d >= 0; d--) {
		if (max < ki[familyTree[0][n]]) max = ki[familyTree[0][n]];
		n = familyTree[0][n];
	}
	return max;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b, c;
	scanf("%d", &T);
	bin[0] = 1;
	for (int i = 1; i < 15; i++) bin[i] = (bin[i - 1] << 1);	// 2의 제곱
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &Q);
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &a, &b);	// a : 부모, b : i번 놈의 키
			parent[a].push_back(i); // a의 아들은 i이다
			familyTree[0][i] = a;	// i의 2^0 번째(==1) 조상은 부모 a이다!
			ki[i] = b;				// i의 키는 b이다
		}
		get_depth();
		//print_depth();
		make_familyTree();
		printf("#%d", tc);
		for (int i = 1; i <= Q; i++) {
			scanf("%d %d", &a, &b);
			for (int j = 1; j < a; j++) {
				scanf("%d", &c);
				b = get_LCA(b, c);
			}
			//printf("[%d] 최소공통조상은? : %d\n", i, start_no);
			printf(" %d", get_max_ki(b));
		}
		printf("\n");
		init();
	}
	return 0;
}
#endif

// ★★★★★★★★★★★★★★★★★★★★★★★
/*
	구성원 수가 N이라고 한다면, LCA의 familyTree[K][V]를 만들 때 걸리는 시간은?
		=> N이 10만 정도라고 한다면, K는 최대 16 ~ 17 정도 될 것이다. (log(10만)은 약 16 ~ 17임)
		   그러므로 최악의 경우에는 N*log(N) 만큼의 시간복잡도를 가지고 있을 것이다!
		   ==> tc개수 * Q(질문 개수) * K * logN( N이 1만이니까 14~15 )
				= 30 * ( 10000 * 100 * 14 ) = 30 * 약 1000만
*/

// (중상) [기출P-0051] 조상이 키컸으면  - 다시~!

/*
	공통 조상들 중 가장 키가 컸던 구성원을 찾고 싶다.
	자기 자신도 자신의 조상으로 간주한다는 것이다.
*/
#if 01

#include <cstdio>
#include <queue>
using namespace std;
#define NMAX	(10000)
#define MAX(a, b)	( ( (a) > (b) ) ? (a) : (b) )

int T, N, Q, K;
int parent[15][NMAX+5];
int height[NMAX+5];	// 키
int depth[NMAX+5];
vector<int> childs[NMAX+5];
int bin[15];

void make_depth() { // 여기에서 최대 키를 저장해가면서!!
	queue<int> que;
	int out, max_height;

	depth[1] = 0;
	que.push(1);
	while (!que.empty()) {
		out = que.front(); que.pop();
		for (int child : childs[out]) {
			max_height = height[out];
			if (max_height > height[child]) height[child] = max_height;
			depth[child] = depth[out] + 1;
			que.push(child);

		}
	}
}

void make_tree() {
	for (int i = 1; i < 15; i++) {
		for (int j = 1; j <= N; j++) {
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}
}

int lca(int a, int b) {
	if (depth[a] != depth[b]) {
		if (depth[a] < depth[b]) { int tmp = a; a = b; b = tmp; }
		int diff = depth[a] - depth[b];
		for (int i = 14; i >= 0; i--) {
			if (diff >= bin[i]) {
				diff -= bin[i];
				a = parent[i][a];
			}
			if (diff == 0) break;
		}
	}
	if (a == b) return a;
	// a, b가 같지 않은 depth 중 가장 최상위로 올라간다.
	for (int i = 14; i >= 0; i--) {
		if (parent[i][a] != parent[i][b]) {
			a = parent[i][a];		b = parent[i][b];
		}
	}
	return parent[0][a];
}

void init() {
	for (int i = 1; i <= N; i++) {
		childs[i].clear();
		depth[i] = 0;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b;
	scanf("%d", &T);
	bin[0] = 1;
	for (int i = 1; i < 15; i++) bin[i] = bin[i - 1] << 1;
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &Q);
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &parent[0][i], &height[i]);
			childs[parent[0][i]].push_back(i);
		}
		parent[0][1] = 1;	// 루트만 자기 자신을 부모로 둔다!!
		make_depth();
		make_tree();
		printf("#%d", tc);
		for (int q = 1; q <= Q; q++) {
			scanf("%d %d", &K, &a);
			for (int n = 2; n <= K; n++) {
				scanf("%d", &b);
				a = lca(a, b);
			}
			printf(" %d", height[a]);
		}
		printf("\n");
		init();
	}
	return 0;
}

#endif




// [사전A-0030]기지국 점검 , [기출P-0019]일방통행 도 비슷한 문제!!
// (중상) [연습P-0011] K번째 최단 경로 : 1 ~ N
/*
	이미 갔던 경로인지 체크 어떻게 하지?
*/
#if 01

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100000)
#define MMAX	(500000)
#define KMAX	(10)
#define INF		(987654321)

int T, N, M, K;
long long result;
vector<pair<int, int>> edges[NMAX+5]; // 거리, 도착지점 순
vector<priority_queue<int, vector<int>, greater<int>>> dijk[NMAX+5];

void init() {
	result = -1ll;
	for (int i = 1; i < N; i++) {
		edges[i].clear();
		dijk[i].clear();
	}
}

int get_K() { // 가중치, 정점 순으로 들어가고 넣어줌
	priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
	pq.push({ 0, 1 });		dijk[1].push_back.push_back(0);
	while (!pq.empty()) {
		pair<int, int> cur = pq.top();	pq.pop();

		for (priority_queue<int, vector<int>, greater<int>> q : dijk[cur.second]) {
			int qcur = q.top();
			if (cur.first > dijk[qcur]) continue;
			dijk[cur.second] = cur.first;
		}
		
		for (pair<int, int> next : edges[cur.second]) {
			if (dijk[cur.first] > dijk[next.first] + next.first) {
				pq.push();
			}
			//if (cur.first > next) continue;
			//dijk[cur.second].push_back(next);
		}
	}

	return -1;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int x, y, z;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		scanf("%d %d %d", &N, &M, &K);
		for (int e = 1; e <= M; e++) {
			scanf("%d %d %d", &x, &y, &z);
			edges[x].push_back({ z, y });
			edges[y].push_back({ z, x });
		}
		result = get_K();
		printf("#%d %lld\n", tc, result);
	}
	return 0;
}

#endif

// 선배님
/*
	간선 개수 E, 정점 개수 V
	=> 다익스트라 시간복잡도 : E*log(V) (최악은 E*log(E))
	=> 50만 * 20 = 1tc당 약 100만
	=> 완전탐색(ex. bfs, dfs 역시) 비벼볼 수 없다..ㅠㅠ

	=> 그렇다면 다익스트라 / 벨만포드( V * E == 10만 * 50만 ==> 불가!! ) / 플로이드 워셜( V^3 ==> 역시 불가 )

	=> (다익스트라)
*/
#if 01

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100000)

int T, N, M, K;
vector<pair<long long, int>> edges[NMAX+5]; // 거리, 도착지점 순
//int dijk[NMAX+5];
int visited[NMAX+5];

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		//dijk[i] = INF;
		visited[i] = 0;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int x, y, z;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &M, &K);
		init();
		for (int e = 1; e <= M; e++) {
			scanf("%d %d %d", &x, &y, &z);
			edges[x].push_back({z, y});
			edges[y].push_back({z, x});
		}

		priority_queue< pair<long long, int>,
			vector<pair<long long, int>>,
			greater<pair<long long, int>> > pq;
		pair<long long, int> cur;
		pq.push(make_pair(0ll, 1));
		while (!pq.empty()) {
			cur = pq.top();		pq.pop();
			// 우선순위 큐(가중치 기준 최소 힙)이라서 가능한 것!!
			// 어떻게 들어가든 가중치(여기에서는 거리)가 작은 것부터 나오기 때문!!
			// 1->N까지 두 번만에 가든, 100번 거쳐서 가든 그 다음에 pop되는 값은 거리가 가장 짧은 것!!
			if (++visited[cur.second] > K) continue;
			if ((cur.second == N) && (visited[N] == K)) break;
			for (pair<long long, int> e : edges[cur.second]) {
				//if (cur.first + e.first < dijk[e.second]) {
				pq.push(make_pair((cur.first + e.first), e.second));
				//}
			}
		}
		if (visited[N] < K) printf("#%d %d\n", tc, -1);
		else printf("#%d %lld\n", tc, cur.first);
	}
	return 0;
}
#endif

// 인터넷 코드 참고
#include    <cstdio>
#include    <vector>
#include    <queue>
#pragma warning(disable:4996)
 
std::vector< std::pair<int, int> > edges[1111]; //a -> b c시간 일 때 최대 2000000 * 1000의 시간이 나올 수 있음
std::priority_queue<int> paths[1111];
 
struct comp
{
    bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) 
    {
        return a.second > b.second;
    }
};
std::priority_queue< std::pair<int, int>, std::vector<  std::pair<int, int> >, comp > q; //다익스트라 알고리즘용
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
 
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[a].push_back(std::make_pair(b, c));
    }
 
    //다익스트라 알고리즘 
    q.push(std::make_pair(1,0)); //1번 점으로 가는데 최단 경로는 0 (시작점이므로)
    paths[1].push(0);
    while (!q.empty())
    {
        int vertex = q.top().first;
        int time = q.top().second;
        q.pop();
 
        for (auto next : edges[vertex])
        {
            if (paths[next.first].size() < k)
                paths[next.first].push(time + next.second);
            else if (paths[next.first].top() > time + next.second)
            {
                paths[next.first].pop();
                paths[next.first].push(time + next.second);
            }
            else
                continue;
 
            q.push(std::make_pair(next.first, time + next.second));
        }
    }
 
    for (int i = 1; i <= n; ++i)
        printf("%d\n", (paths[i].size() == k) ? paths[i].top() : -1);
 
    return 0;
}


출처: https://dyndy.tistory.com/230 [DY N DY]

출처: https://dyndy.tistory.com/230 [DY N DY]






// (중) [사전A-0018] [10월 PRO 검정 사전 테스트] 인터스텔라 항해 : 워프 항법 Re......
#if 01

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX		(30)
#define INF		(987654321)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

int T, Y, X, M, W;
pair<int, pair<int, int>> space[MAX+2][MAX+2];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int dijk[MAX + 2][MAX + 2];

void init() {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			space[i][j] = { 0, {-1, -1} }; // 0,0이 시작점이므로 헷갈릴까봐
			dijk[i][j] = INF;
		}
	}
}

void get_exit() {
	/*queue<pair<int, int>> que;
	pair<int, int> out;
	pair<int, pair<int, int>> pipii;
	int ny, nx;

	que.push({ 0, 0 }); dijk[0][0] = 0;
	while (!que.empty()) {
		out = que.front();	que.pop();
		pipii = space[out.first][out.second];
		if
			if (dijk[out.first][out.second] != INF)
	}*/
}

int main()
{
	freopen("in.txt", "r", stdin);
	int sy, sx, ey, ex, tm;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &X, &Y);
		scanf("%d", &M);
		for (int i = 0; i < M; i++) {	// 메테오
			scanf("%d %d", &sx, &sy);
			space[sy][sx] = { INF, {-1, -1} };
		}
		scanf("%d", &W);
		for (int i = 0; i < W; i++) {	// 워프
			scanf("%d %d %d %d %d", &sx, &sy, &ex, &ey, &tm);
			space[sy][sx] = { tm, { ey, ex } };
		}
		get_exit();
		printf("#%d ", tc);
		init();
	}
	return 0;
}

#endif

/*
	 -10000 ≤ tw ≤ 10000
	 워프는 시공간을 왜곡하므로, 어떤 워프는 항해할 때 시간까지 거꾸로 가게 한다.
	 다시 말해, 시간이 거꾸로 가는 항해를 하게 되는 워프도 존재할 수 있다.
	 즉, 위의 예시의 워프의 워프 항법 시간이 -1시간이라 하면 이 워프에서 워프 항법을 하게 될 경우
	 1시간 과거로 가게 되므로. 총 3시간 만에 탈출할 수 있다.
	 
	 ==> 음의 Cycle 쌉가능!
*/
// 선배님 - 벨만 포드 알고리즘
/*
	< 계산복잡성 >
	벨만-포드 알고리즘은 그래프 모든 엣지에 대해 edge relaxation을 시작노드를 제외한 전체 노드수 만큼 반복 수행하고,
	마지막으로 그래프 모든 엣지에 대해 edge relaxation을 1번 수행해 주므로, 그 계산복잡성은 O(|V||E|)이 됩니다.
	그런데 dense graph는 엣지 수가 대개 노드 수의 제곱에 근사하므로 간단하게 표현하면 O(|V|3)이 됩니다.
	이는 다익스트라 알고리즘(O(|V|2)보다 더 큰데, 벨만-포드 알고리즘은 음수인 가중치까지 분석할 수 있기 때문에
	일종의 trade-off라고 생각해도 될 것 같다는 생각이 듭니다.
*/
#if 01

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX		(30)
#define INF		(987654321)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

typedef struct { int ey, ex, tm; }TELE;
TELE w[MAX*MAX];

int T, Y, X, M, W;
int space[MAX + 2][MAX + 2];
int dijk[MAX + 2][MAX + 2];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int w_cnt;

void init() {
	w_cnt = 0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			space[i][j] = 0; // 0,0이 시작점이므로 헷갈릴까봐
			dijk[i][j] = INF;
		}
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int sy, sx, ey, ex, tm;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &X, &Y);
		init();
		//return 0;
		scanf("%d", &M);
		for (int i = 0; i < M; i++) {	// 메테오
			scanf("%d %d", &sx, &sy);
			space[sy][sx] = -1;
		}
		scanf("%d", &W);
		for (int i = 0; i < W; i++) {	// 워프
			scanf("%d %d %d %d %d", &sx, &sy, &ex, &ey, &tm);
			w[++w_cnt] = { ey, ex, tm };
			space[sy][sx] = w_cnt;
		}

		// get_exit
		int ny, nx, nt;
		bool cantExit = false;
		dijk[0][0] = 0; // 시작 노드는 0으로 시작!
		
		// 벨만-포드 알고리즘은 시작노드를 제외한 전체 노드수 만큼의 edge relaxation을 수행해야 합니다. 
		for (int i = 0; i < Y*X - 1; i++) {
			for (int y = 0; y < Y; y++) {
				for (int x = 0; x < X; x++) {
					if (dijk[y][x] != INF && !((y == Y - 1) && (x == X - 1))) {
						if (!space[y][x]) {	// 아무 것도 없음(메테오도, 웜홀도)
							for (int d = 0; d < 4; d++) {
								ny = y + dy[d];		nx = x + dx[d];
								if (ny < 0 || ny >= Y || nx < 0 || nx >= X) continue;
								if (space[ny][nx] != -1 && dijk[ny][nx] > dijk[y][x] + 1) {
									dijk[ny][nx] = dijk[y][x] + 1;
								}
							}
						}
						else if (space[y][x] > 0) {
							ny = w[space[y][x]].ey;
							nx = w[space[y][x]].ex;
							nt = w[space[y][x]].tm;
							if (dijk[ny][nx] > dijk[y][x] + tm) {
								dijk[ny][nx] = dijk[y][x] + tm;
							}
						}
					}
				}
			}
		}
		
		// "다익스트라 알고리즘(Dijkstra’s algorithm)"과 달리 벨만-포드 알고리즘은 가중치가 음수인 경우에도 적용 가능합니다.
		// 그러나 다음과 같이 음수 가중치가 사이클(cycle)을 이루고 있는 경우에는 작동하지 않습니다.
		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				if (dijk[y][x] != INF && !((y == Y - 1) && (x == X - 1))) {
					if (!space[y][x]) {	// 아무 것도 없음(메테오도, 웜홀도)
						for (int d = 0; d < 4; d++) {
							ny = y + dy[d];		nx = x + dx[d];
							if (ny < 0 || ny >= Y || nx < 0 || nx >= X) continue;
							if (space[ny][nx] != -1 && dijk[ny][nx] > dijk[y][x] + 1) {
								dijk[ny][nx] = dijk[y][x] + 1;
							}
						}
					}
					else if (space[y][x] > 0) {
						ny = w[space[y][x]].ey;
						nx = w[space[y][x]].ex;
						nt = w[space[y][x]].tm;
						if (dijk[ny][nx] > dijk[y][x] + tm) {
							dijk[ny][nx] = dijk[y][x] + tm;
							cantExit = true;	// 음의 가중치 때문에 더 작아진다면, mininf!!
						}
					}
				}
			}
		}
		printf("#%d ", tc);
		if (cantExit) printf("mininf\n");
		else if (dijk[Y - 1][X - 1] == INF) printf("noway\n");
		else printf("%d\n", dijk[Y-1][X-1]);
	}
	return 0;
}

#endif
/*
[입출력 예제]
(입력)
4
3 3
2
2 1
1 2
0
4 3
2
2 1
3 1
1
3 0 2 2 0
4 2
0
1
2 0 1 0 -3
10 2
2
1 1
5 1
2
0 1 9 0 25
3 0 8 1 -6


(출력)
#1 noway
#2 4
#3 mininf
#4 -2			// 이거만 답이 다름 ㅠㅠ - 왜 안나오는지.. 디버깅 같이 도움 받자!!

*/





// (중) [사전A-0019] [11월 PRO 검정 사전 테스트] 내 고장 내 마을 
/*
	마을과 마을은 길로 연결되어 있는데,
	앞서 말했듯이 험준한 산지라서 다른 마을로 가고 싶을 땐 "길이 아닌 다른 곳으로 갈 수가 없"지.
	그래도 제법 길들이 잘 닦여 있어서 "이 길들을 잘 이용한다면" 어떤 마을에서든 못 가는 마을이 없어.
	참고로 길에 적힌 번호는 비용이 아니고 길의 번호를 뜻해.
	없어지면 안 되는 길의 번호들을 모두 알려줬으면 좋겠어.
*/
#if 01

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(NMAX*NMAX/2)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

int T, N, M;
vector<pair<int, int>> edges[NMAX+5];
vector<int> bridges[MMAX];
vector<int> vertex[MMAX];
bool isCut[MMAX];
int stay_cnt;
int order_num[MMAX], order;

void init() {
	stay_cnt = order = 0;
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
	}
	for (int i = 1; i <= M; i++) {
		isCut[i] = false;
		order_num[i] = -1;	// i번 노드(마을)에 아직 방문하지 않았다는 뜻
		bridges[i].clear();	vertex[i].clear();
	}
}

void make_bridge() {
	for (int i = 1; i <= M; i++) {
		for (int next : vertex[i]) { // i번 다리에 연결된 마을을 꺼냄
			for (pair<int, int> nn : edges[next]) {	// 그 마을과 연결된 모든 다리를 꺼냄
				if (i == nn.second) continue;
				bridges[i].push_back(nn.second);	// 그 다리와 i번 다리를 연결시킴
			}
		}
	}
}

int dfs(int s) {
	int childCnt = 0;
	int childLow, nowLow;
	order_num[s] = nowLow = ++order;

	for (int next : bridges[s]) {
		if (order_num[next] == -1) {
			childLow = dfs(next); // 아직 방문하지 않았다면 dfs 타고 방문해보자!
			if (childLow >= order_num[s] && s != 1 && !isCut[s]) {
				isCut[s] = true;	stay_cnt++;
			}
			childCnt++;
			nowLow = MIN(order_num[s], childLow);
		}
		else { // 방문해봤다면
			nowLow = MIN(nowLow, order_num[next]);
		}
	}
	if (s == 1 && childCnt >= 2 && !isCut[s]) {
		isCut[s] = true;	stay_cnt++;
	}
	return nowLow; //
}

void get_road(int tc) {
	printf("#%d %d", tc, stay_cnt);
	for (int i = 1; i <= M; i++) if (isCut[i]) printf(" %d", i);
	printf("\n");
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		init();
		for (int m = 1; m <= M; m++) {
			scanf("%d %d", &a, &b);
			vertex[m].push_back(a);
			vertex[m].push_back(b);

			edges[a].push_back({ b, m });	// a->b 길의 번호는  m
			edges[b].push_back({ a, m });	// b->a 길의 번호는  m (양방향. 왕래 가능.)
		}
		make_bridge();
		dfs(1);
		get_road(tc);
	}
	return 0;
}

#endif // 복잡하지만 이렇게 풀 수 있지 않을까? (Re)


// 선배님
// Re : 단절선!! - dfs를 타는 선들만 단절선의 후보!!!!!! (좀 더 생각해보면 당연하지?)

// 해당 간선이  parent 가 아닐때.....;;
// child와 현재 정점 low 비교할 때, child low 가 더 클 때 단절선이 됨.

#if 01

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(NMAX*NMAX/2)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

int T, N, M;

vector<pair<int, int>> edges[NMAX + 5];
bool isCut[MMAX];
int cnt;
int order_num[MMAX], order;

void init() {
	cnt = order = 0;
	
}

int dfs(int now, int parent) {

	order_num[now] = ++order;
	int nowLow = order_num[now];
}

/*
< JAVA Code >

static int dfs(int node, int parent) {
	order[node] = ++cnt;
	int low = order[node], childLow = 0;
	for(Edge e : edges[node]) {
		if(order[e.b] == 0) {
			childLow = dfs(e.b, node);
			low = Math.min(childLow, low);
			if(childLow > order[node]) ans[ansN++] = e.i;
		}
		else if(e.b != parent) {
			low = Math.min(low, order[e.b]);
		}
	}
	return low;
}

*/

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		
		for (int m = 1; m <= M; m++) {
			scanf("%d %d", &a, &b);
			
		}
		

	}
	return 0;
}

#endif
/*
[입출력 예]
(입력)
3
4 4
1 2
4 2
3 2
3 4
10 10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 1
10 13
1 6
6 3
7 2
1 7
9 4
7 4
1 9
9 7
9 10
4 1
5 10
8 10
5 8


(출력)
#1 1 1
#2 0
#3 4 1 2 3 9

*/





// (중상) [연습P-0027] MST 
/*
	완전 그래프란 모든 가능한 쌍의 노드들 간에 에지가 존재하는 그래프를 말한다.
	그래프의 각 에지는 길이가 있으며, 에지들 간에 길이는 서로 다를 수 있다.
	최소 신장 트리(MST) : 일부를 골라서 전체가 트리가 되며 에지들의 길이 합이 최소가 되는 경우

	가능한 어떤 MST에도 속하지 않는 에지 e 각각에 대해서 Y(e)-X를 모두 계산했다고 했을 때,
	Y(e)-X의 가능한 최소값?

	=> 
		1) 주어진 그래프의 MST 구함 : X (N-1개 간선)
		2) 그 그래프를 기준으로, 하나 추가(e1) && 하나 제거(e2) : Y(e) - X = e1 - e2;
			- Cycle에서 가장 최소 더하고, 가장 최대 빼줌
			- 선 추가해서 이어지는 두 정점의 LCA 구함... -> 거기까지 사이클임.
												거기까지의 엣지들 중 최대 빼줌
*/
#if 01

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX		(300)
#define INF		(987654321)

int T, N, X, Ye;
int min_chang;
int d[MAX+5][MAX+5];
int parent[MAX+5];
vector<pair<int, int>> edges[MAX*MAX];

void init() {
	min_chang = INF;
	for (int i = 1; i < N; i++) {
		parent[i] = i;
		for (int j = i + 1; j <= N; j++) {
			scanf("%d", &d[i][j]);
		}
	}
}

int find(int v) {
	if (parent[v] == v) return v;
	return parent[v] = find(parent[v]);
}

void ally(int a, int b) { parent[find(a)] = find(b); }

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		init();
		for (int i = 1; i < N; i++) {
			for (int j = i + 1; j <= N; j++) {
				scanf("%d", &d[i][j]);
				edges[i].push_back({ d[i][j] , j });
				edges[j].push_back({ d[i][j] , i });
			}
		}

	}
	return 0;
}

#endif
/*
[입출력 예]
(입력)
3
3
1 1
1
3
1 1
2
4
1 3 8
1 2
2


(출력)
#1 -1
#2 1
#3 2
*/
