/************************/
/* [ 2020.02.17 day 6 ] */
/************************/


// (중상) [연습P-0023] 동맹의 동맹은 동맹 
#if 01

#include <iostream>
#include <algorithm>
using namespace std;
#define NMAX	(100000)

int T, N, Q;
int relation[NMAX+10];
int cnt;

void init(int n) { for (int i = 1; i <= n; i++) relation[i] = i; }

int find(int v)
{
	if (relation[v] == v) return v;
	return relation[v] = find(relation[v]);
}

void ally(int a, int b) { relation[find(a)] = find(b); }

bool check(int a, int b) { return (a == b); }

int main()
{
	int a, b, c;
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cnt = 0;
		cin >> N;
		init(N);
		cin >> Q;
		for (int q = 1; q <= Q; q++)
		{
			cin >> a >> b >> c;
			if (a == 0) ally(b, c);
			else if (check(find(b), find(c))) cnt++;
		}

		cout << "#" << tc << " " << cnt << endl;
	}
	return 0;
}

#endif

// BOJ_1717_집합의 표현 : cout으로 출력하면 시간 초과, printf로 출력하면 통과..;;
#if 01

#include <cstdio>
#define NMAX	(1000000)

int N, Q;
int relation[NMAX + 10];

void init(int n) { for (int i = 1; i <= n; i++) relation[i] = i; }

int find(int v)
{
	if (relation[v] == v) return v;
	return relation[v] = find(relation[v]);
}

void ally(int a, int b) { relation[find(a)] = find(b); }

bool check(int a, int b) { return (a == b); }

int main()
{
	int a, b, c;

	scanf("%d %d", &N, &Q);
	init(N);
	for (int q = 1; q <= Q; q++)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (a == 0) ally(b, c);
		else
		{
			if (check(find(b), find(c))) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}

#endif
// cout.tie(NULL); 과 endl이 아닌 "\n" 사용으로 더욱 빨라짐..;;
#if 01
#include <iostream>
#include <algorithm>
using namespace std;
#define NMAX	(1000000)

int N, Q;
int relation[NMAX + 10];

void init(int n) { for (int i = 1; i <= n; i++) relation[i] = i; }

int find(int v)
{
	if (relation[v] == v) return v;
	return relation[v] = find(relation[v]);
}

void ally(int a, int b) { relation[find(a)] = find(b); }

bool check(int a, int b) { return (a == b); }

int main()
{
	int a, b, c;
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> Q;
	init(N);
	for (int q = 1; q <= Q; q++)
	{
		cin >> a >> b >> c;
		if (a == 0) ally(b, c);
		else
		{
			if (check(find(b), find(c))) cout << "YES\n";
			else cout << "NO\n";

		}
	}
	return 0;
}
#endif



// 위상정렬 : 비순환 방향 그래프에서 방향성을 거스르지 않고 정점들을 나열! (우선순위에 따라 배치)
//			- 그 우선순위는 indegree(즉, 들어오는 간선)이 0인 것부터! (그 정점 없애주면서 outdegree 간선도 없앰)

// 관련 블로그 : https://zoomkoding.github.io/algorithm/2019/07/02/Topological-Sort-1.html
// ★★ Q 직접 만들어서도 풀어보자!! ★★
// (중상) [교육P-0008] 임계 경로 : 방향성 간선
/*
	작업은 항상 1번 공정에서 시작하며, N번 공정에서 끝난다.
	입력으로 주어지는 정보를 그래프로 표현했을 때, 그래프는 DAG(Directed Acyclic Graph)가 되며,
	1번 정점으로 들어오는 간선의 개수는 0이고, N번 정점에서 나가는 간선의 개수 또한 0이다.
	그리고 항상 작업이 완료되도록 입력이 주어진다.
*/
#if 01

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define NMAX	(100000)
#define MMAX	(300000)

int T, N, M;
int indegree[NMAX + 10];
vector<pair<int, int>> edges[NMAX + 2]; // ★★★★ vector 사용법 마스터하기!!
int t[NMAX + 10];
queue<int> que;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int a, b, c, out;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{

		cin >> N >> M;
		for (int i = 1; i <= N; i++) { //  초기화
			indegree[i] = 0;
			edges[i].clear();
			t[i] = 0;
		}
		for (int i = 1; i <= M; i++)
		{
			cin >> a >> b >> c;
			edges[a].push_back({ b, c }); // 인접리스트 - vector && pair 사용
			indegree[b]++;				  // 각 정점의 indegree(들어오는 간선) 수를 미리 세어 놓자!
		}
		for (int i = 1; i <= N; i++) {
			if (indegree[i] == 0) que.push(i);
		}
		while (!que.empty()) {
			int out = que.front();	que.pop();
			if (out == N) break;
			for (pair<int, int> next : edges[out]) {
				t[next.first] = max(t[next.first], t[out] + next.second);
				if (--indegree[next.first] == 0) que.push(next.first);
			}
		}

		cout << "#" << tc << " " << t[N] << "\n";
	}

	return 0;
}

#endif



// ★★ 최대/최소 스패닝 트리!!! ★★
// (중상) [교육P-0007] 군사 도로망 
// 양방향 통행 가능(무향), 두 도시 연결하는 간선은 최대 하나의 도로만 존재, 순환되지 않도록
// 도로 정비 과정에서 존재하는 도로를 제거해야 하는 경우도 있음에 주의하라
#if 01

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define NKMAX	(250000)

typedef struct { int s, e, w; }EXIST;
EXIST existed[NKMAX+10];
EXIST constructable[NKMAX + 10];

int T, N, M, K;
long long min_cost;
int chk[NKMAX+10];

bool cmp(const EXIST &p1, const EXIST &p2) { // 구조체 멤버 변수 w를 기준으로 오름차순 정렬
	if (p1.w < p2.w)  return true;
	if (p1.w == p2.w) return p1.s < p2.s;	 // 혹시나 같다면, 그냥 s를 기준으로 하자!
	return false;							// 그게 아니라면 e지 뭐
}

int find(int v)
{
	if (chk[v] == v) return v;		// 가장 최상위 대표 번호 리턴
	return chk[v] = find(chk[v]);	// ★
}

void ally(int a, int b) { chk[find(a)] = find(b); }

bool false_check(int a, int b) { return (find(a) != find(b)); }

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		min_cost = 0;
		cin >> N >> M >> K;
		// chk 배열 초기화(parent 배열)
		for(int i = 1; i <= N; i++) chk[i] = i;
		// 존재하는 다리 중 제거해도 되는 다리들
		for (int i = 0; i < M; i++) {
			cin >> a >> b >> c;
			existed[i].s = a;	existed[i].e = b;	existed[i].w = c;
		}
		stable_sort(existed, existed + M, cmp);
		for (int i = M - 1; i >= 0; i--) {	// 최대스패닝트리 :
										// 최대(비용)을 골라 안 없애주고, 최대한 최소 비용 드는 걸 선택
			EXIST tmp = existed[i];
			if (false_check(tmp.s, tmp.e)) ally(tmp.s, tmp.e);	// 순환X && 연결X라면 연결
			else min_cost += tmp.w;								// 아니면 그 다리 제거
		}
		// 없어서 새로 만들어야 하는 다리들
		for (int i = 0; i < K; i++) {
			cin >> a >> b >> c;
			constructable[i].s = a;	constructable[i].e = b;	constructable[i].w = c;
		}
		stable_sort(constructable, constructable + K, cmp);
		for (int i = 0; i < K; i++) {	// 최소스패닝트리 :
									// 최소 비용 드는 다리 먼저 만들어 연결하면 최소비용이 나오겠지?
			EXIST tmp = constructable[i];
			if (false_check(tmp.s, tmp.e))		// 순환X && 연결X라면 그 다리 만들어야지
			{
				min_cost += tmp.w;
				ally(tmp.s, tmp.e);
			}
		}

		cout << "#" << tc << " " << min_cost << "\n";
	}

	return 0;
}

#endif

// cin, cout이 아닌  scanf, printf로 하면 더욱 빨라짐!!
#if 01

#include <cstdio>
#include <algorithm>
using namespace std;

#define NKMAX   (250000)

typedef struct { int s, e, w; }EXIST;
EXIST existed[NKMAX + 10];
EXIST constructable[NKMAX + 10];

int T, N, M, K;
long long min_cost;
int chk[NKMAX + 10];

bool cmp(const EXIST &p1, const EXIST &p2) {
	if (p1.w < p2.w)  return true;
	if (p1.w == p2.w) return p1.s < p2.s;
	return false;
}

int find(int v) {
	if (chk[v] == v) return v;
	return chk[v] = find(chk[v]);
}

void ally(int a, int b) { chk[find(a)] = find(b); }

bool false_check(int a, int b) { return (find(a) != find(b)); }

int main() {
	int a, b, c;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		min_cost = 0ll;
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 1; i <= N; i++) chk[i] = i;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &c);
			existed[i].s = a;   existed[i].e = b;   existed[i].w = c;
		}
		stable_sort(existed, existed + M, cmp);
		for (int i = M - 1; i >= 0; i--) {
			EXIST tmp = existed[i];
			//if (false_check(tmp.s, tmp.e)) ally(tmp.s, tmp.e);
			if (find(tmp.s) != find(tmp.e)) ally(tmp.s, tmp.e);
			else min_cost += tmp.w;
		}

		for (int i = 0; i < K; i++) {
			scanf("%d %d %d", &a, &b, &c);
			constructable[i].s = a; constructable[i].e = b; constructable[i].w = c;
		}
		stable_sort(constructable, constructable + K, cmp);
		for (int i = 0; i < K; i++) {
			EXIST tmp = constructable[i];
			//if (false_check(tmp.s, tmp.e)) {
			if (find(tmp.s) != find(tmp.e)) {
				min_cost += tmp.w;
				ally(tmp.s, tmp.e);
			}
		}
		printf("#%d %lld\n", tc, min_cost);
	}
	return 0;
}

#endif

// 새로운 풀이
// existed(부시(싼 비용)거나 유지(비싼 비용)해야 하는 다리 관련)의 가중치는 *(-1)을,,
// constructable(새로 만들(싼 비용)거나 안 만드는(비싼 비용) 다리 관련)의 가중치는 그대로
// 거기에서 바로 Kruskal 알고리즘 ㄱㄱ!!
#if 01

#include <cstdio>
#include <algorithm>
using namespace std;
#define NKMAX   (250000)

typedef struct { int s, e, w; }EXIST;
EXIST kruskal[NKMAX*2+2];

int T, N, M, K, MK;
long long min_cost;
int chk[NKMAX + 2];

bool cmp(const EXIST &p1, const EXIST &p2) {
	if (p1.w < p2.w)  return true;
	if (p1.w == p2.w) return p1.s < p2.s;
	return false;
}

int find(int v) {
	if (chk[v] == v) return v;
	return chk[v] = find(chk[v]);
}

void ally(int a, int b) { chk[find(a)] = find(b); }

int main() {
	int a, b, c;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		min_cost = 0ll;
		scanf("%d %d %d", &N, &M, &K);
		MK = M + K;
		for (int i = 1; i <= N; i++) chk[i] = i;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &c);
			min_cost += c;	// ★ IDEA : 후에 안 부실 다리들을 음스로서 min_cost에 더해줄 것이므로!!! ★
			kruskal[i].s = a;   kruskal[i].e = b;   kruskal[i].w = c*(-1); // 가중치 변형!!
		}
		for (int i = M; i < MK; i++) {
			scanf("%d %d %d", &a, &b, &c);
			kruskal[i].s = a; kruskal[i].e = b; kruskal[i].w = c;
		}
		sort(kruskal, kruskal + MK, cmp);

		for (int i = 0; i < MK; i++) {
			EXIST tmp = kruskal[i];
			if (find(tmp.s) != find(tmp.e)) {
				ally(tmp.s, tmp.e);
				min_cost += tmp.w;
			}
		}
		printf("#%d %lld\n", tc, min_cost);
	}
	return 0;
}

#endif


// 참고 ㄷㄷ - 빠름
#if 01
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100001

struct Edge {
	int v, w;
	int cost;
	bool exist;

	bool operator<(const Edge& e) const {
		return cost < e.cost;
	}
};

int n, m, k;
vector<Edge> edges;
int parent[MAX_N];
long long ans;

int find(int a) {
	if (parent[a] == a) return a;
	else return parent[a] = find(parent[a]);
}
void Union(int a, int b) {
	int roota = find(a);
	int rootb = find(b);
	parent[roota] = rootb;
}

void kruskal() {
	sort(edges.begin(), edges.end());
	for (Edge e : edges) {

		int vroot = find(e.v);
		int wroot = find(e.w);
		if (vroot != wroot) {
			Union(e.v, e.w);
			ans += e.cost;
		}
	}

}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {

		edges.clear();
		for (int i = 0; i < MAX_N; i++) {
			parent[i] = i;
		}

		scanf("%d %d %d", &n, &m, &k);
		ans = 0;
		for (int i = 0; i < m; i++) {
			int v, w, cost;
			scanf("%d %d %d", &v, &w, &cost);
			ans += cost;
			struct Edge e;
			e.v = v; e.w = w; e.cost = 0 - cost; e.exist = true;
			edges.push_back(e);
		}
		kruskal();

		edges.clear();
		for (int i = 0; i < k; i++) {
			int v, w, cost;
			scanf("%d %d %d", &v, &w, &cost);
			struct Edge e;
			e.v = v; e.w = w; e.cost = cost; e.exist = false;
			edges.push_back(e);
		}
		kruskal();

		printf("#%d %lld\n", t, ans);
	}
	return 0;
}
#endif

// 아카춘 선배님
#if 01

#include <stdio.h>
#include <vector>
#include <algorithm>


using namespace std;
int parent[100011];
vector<int> v[500011];

int N, M, K;
long long ans;

void input(void)
{
	int i;
	int a, b, c;
	scanf("%d %d %d", &N, &M, &K);
	for (i = 0; i <= N; i++)
	{
		parent[i] = i;
	}
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		v[i].clear();
		v[i].push_back(a);
		v[i].push_back(b);
		v[i].push_back(-1 * c);
		ans += c;
	}
	for (i = M; i < M + K; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		v[i].clear();
		v[i].push_back(a);
		v[i].push_back(b);
		v[i].push_back(c);
	}
}

bool comp(const vector<int> & v1, const vector<int> & v2)
{
	return v1[2] < v2[2];
}

int find(int a)
{
	if (parent[a] == a) return a;
	else return parent[a] = find(parent[a]);
}

void unite(int a, int b)
{
	int aroot = find(a);
	int broot = find(b);

	parent[aroot] = broot;
}



int main(void)
{
	int tc, T;
	int i;
	int lines = 0;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{

		ans = 0;
		input();
		int cnt = 0;
		int nums = M + K;
		lines = 0;

		sort(v, v + nums, comp);

		while (cnt < N - 1)
		{
			if (find(v[lines][0]) != find(v[lines][1]))
			{
				unite(v[lines][0], v[lines][1]);
				ans += v[lines][2];
				cnt++;
			}
			lines++;
		}

		printf("#%d %lld\n", tc, ans);

	}

	return 0;
}

#endif




// (중상) [교육P-0026] 최저 공통 조상
#if 01

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define MAX	(100000)
#define ABS(a)	( ( (a) < 0 ) ? -(a) : (a) )

int bin[18] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};
int T, N, Q;
int depth[MAX+2]; // 1 : 깊이
int familyTree[18][MAX+2];
int chk[MAX+2];
vector<int> edges[MAX + 5];

void get_depth() {
	queue<int> que;
	int out;

	depth[1] = 0;
	que.push(1);
	while (!que.empty()) {
		out = que.front();  que.pop();
		for (int next : edges[out]) {
			depth[next] = depth[out] + 1;
			que.push(next);
		}
	}
}


void make_familyTree() {
	familyTree[0][1] = 1;
	for (int i = 1; i < 18; i++) {
		for (int j = 1; j <= N; j++) {
			familyTree[i][j] = familyTree[i-1][familyTree[i-1][j]];
		}
	}
}

/*
int get_LCA(int a, int b) {
	int big, small, depth_diff = 0;
	int bb, ss;
	//printf("a = %d && b = %d \n", a, b);

	if (a > b) { big = a, small = b; }
	else { big = b, small = a; }
	if (parent[big][1] != parent[small][1])  depth_diff = ABS( (parent[big][1]-parent[small][1]) );
	//printf("depth_diff = %d\n", depth_diff);
	if (!depth_diff) return big;
	for (int i = 17; i >= 0; i--) {
		if (depth_diff >= bin[i]) {
			depth_diff -= (i+1);
			small = familyTree[i][small];
			//printf("Hidoyi %d\n", i);
			//printf("small = %d\n\n", small);
		}
	}
	//printf("보정 depth_diff = %d\n", depth_diff);

	// 깊이를 맞추어 줬다면, 그 다음에 공통조상은 어떻게 찾지?
	if (small == big) return big;
	int i = 0;
	while (true) {
		bb = familyTree[i][small];
		ss = familyTree[i++][big];
		if (bb == ss) return bb;
	}
}
*/

int get_LCA(int a, int b, int depth_diff) { // a가 더 깊음
	if (depth_diff != 0) {
		for (int i = 17; i >= 0; i--) {
			if (depth_diff >= bin[i]) {
				depth_diff -= bin[i];
				a = familyTree[i][a];
			}
			if (a == b) return a;
		}
	}

	if (a == b) return a;
	for (int i = 17; i >= 0; i--) {
		if (depth[a] >= bin[i]) {
			if (familyTree[i][a] != familyTree[i][b]) {
				a = familyTree[i][a];	b = familyTree[i][b];
			}
		}
	}
	return familyTree[0][a];
	// 병시나
	//else if (familyTree[0][a] = familyTree[0][b]) return familyTree[0][a];
}

int main() {
	int a, b, tmp;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)	{
		scanf("%d %d", &N, &Q);
		for (int i = 1; i <= N; i++) edges[i].clear();
		for (int i = 2; i <= N; i++) {
			scanf("%d", &familyTree[0][i]);
			edges[familyTree[0][i]].push_back(i);
		}
		get_depth();
		make_familyTree();
		printf("#%d", tc);
		for (int q = 1; q <= Q; q++) {
			scanf("%d %d", &a, &b);
			if (depth[a] < depth[b]) { tmp = a; a = b; b = tmp;  }
			printf(" %d", get_LCA(a, b, depth[a] - depth[b]));
		}
		printf("\n");
	}
	return 0;
}

#endif

// Re....... tq
#if 01
#pragma warning(disable: 4996)

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define MAX	(100000)
#define X	(18)

int T, N, Q;
int bin[X];
int parent[X][MAX + 5];
int depth[MAX + 5];
vector<int> edges[MAX + 5];

void make_familyTree() {
	parent[0][1] = 1;
	for (int i = 1; i < X; i++) {
		for (int j = 1; j <= N; j++) {
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}
}

void get_depth() {
	queue<int> que;
	int out;

	depth[1] = 0;
	que.push(1);
	while (!que.empty()) {
		out = que.front();	que.pop();
		for (int next : edges[out]) {
			depth[next] = depth[out] + 1;
			que.push(next);
		}
	}
}

int get_LCA(int a, int b) {
	int tmp, diff;

	if (depth[a] != depth[b]) {
		// 아래에 있는 정점을 위로 올려서 depth를 맞춰준다
		if (depth[a] < depth[b]) { tmp = a; a = b; b = tmp; }
		diff = depth[a] - depth[b];
		for (int i = X-1; i >= 0; i--) {
			if (diff >= bin[i]) {
				diff -= bin[i];
				a = parent[i][a];
			}
			if (diff == 0) break;
		}
	}

	// 둘의 깊이가 같은 영역

	if (a == b) return a;	
	// 같이  depth를 올라가면서 a, b 가 같은지 확인! (일단 둘의 깊이는 같다!!)
	for (int i = X-1; i >= 0; i--) {
		if (depth[a] >= bin[i]) {
			if (parent[i][a] != parent[i][b]) {
				a = parent[i][a];	b = parent[i][b];
			}
		}
	}
	return parent[0][a];
	// 최소공통조상이 Root라고 하더라도, Root의 조상은 Root임!! 그래서 상관 없음
}

int main()
{
	freopen("in.txt", "r", stdin);
	int a, b;
	// 2의 몇승 만들어주기
	bin[0] = 1;
	for (int i = 1; i < X; i++) bin[i] = (bin[i - 1] << 1);

	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		printf("#%d", tc);
		scanf("%d %d", &N, &Q);
		for (int i = 1; i <= N; i++) edges[i].clear();
		for (int i = 1; i < N; i++) {
			scanf("%d", &parent[0][i + 1]);
			edges[parent[0][i + 1]].push_back(i+1); // ★ 얘의 자식이 누구인지? (Oh..!!)
		}
		// 각 노드의 깊이 구하기
		get_depth();
		// 족보 만들기
		make_familyTree();
		// 질문
		for (int q = 1; q <= Q; q++) {
			scanf("%d %d", &a, &b);
			printf(" %d", get_LCA(a, b));
		}
		printf("\n");
	}

	return 0;
}

#endif

// 참고
#if 01

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int parent[18][100001], depth[100001];
vector<int> adj[100001];

void dfs(int node) {
	for (int next : adj[node]) {
		depth[next] = depth[node] + 1;
		dfs(next);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, Q;
		cin >> N >> Q;

		for (int i = 1; i <= N; i++)
			adj[i].clear();
		memset(parent, 0, sizeof(parent));
		memset(depth, 0, sizeof(depth));

		for (int i = 2; i <= N; i++) {
			cin >> parent[0][i];
			adj[parent[0][i]].push_back(i);
		}
		depth[1] = 0;
		dfs(1);
		for (int i = 2; i <= N; i++) {
			int k = 1;
			while ((1 << k) <= depth[i]) {
				parent[k][i] = parent[k - 1][parent[k - 1][i]];
				k++;
			}
		}

		cout << '#' << tc;
		while (Q--) {
			int a, b;
			cin >> a >> b;
			int diff = depth[a] - depth[b];
			if (diff < 0) {
				int tmp = a;
				a = b;
				b = tmp;
				diff = -diff;
			}
			for (int i = 0; diff; i++) {
				if (diff % 2)
					a = parent[i][a];
				diff /= 2;
			}

			if (a != b) {
				for (int i = 17; i >= 0; i--) {
					if (parent[i][a] && parent[i][a] != parent[i][b]) {
						a = parent[i][a];
						b = parent[i][b];
					}
				}
				a = parent[0][a];
			}
			cout << ' ' << a;
		}
		cout << '\n';
	}
	return 0;
}

#endif
