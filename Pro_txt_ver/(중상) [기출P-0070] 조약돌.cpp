// (중상) [기출P-0070] 조약돌 게임 
// 위상정렬 : https://m.blog.naver.com/ndb796/221236874984
/*
	(조건)
	한 조약돌에서 시작해서 연결선을 따라 움직일 때, 
	낮은 점수를 먼저 보고 높은 점수를 보게 되는 것을 반복해서
		(위의 그림에서 왼쪽 조약돌에서 오른쪽 조약돌로 움직이는 것을 말함)
	원래 조약돌로 돌아올 수 있는 경우는 없다.
	=> 한 번 진득~~허니 생각해보면!! 사이클이 없다는 소리이다!!
*/
#if 0
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(200010)

typedef long long ll;
typedef pair<int, pair<int, int>> pipii;
typedef pair<pair<int, int>, pair<int, int>> ppiipii;
int T, N, M, K;
int indegree[NMAX], order, result[NMAX];
vector<pipii> edges[NMAX];
ll total_score;
ppiipii save[MMAX];

void init() {
	total_score = 0LL;		order = 0;
	for(int i = 1; i <= N; i++) {
		edges[i].clear();
		indegree[i] = result[i] = 0;
	}
}

void input() {
	int a, b, p, q, save_cnt = 0;
	scanf("%d %d %d", &N, &M, &K);
	init();
	for(int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &a, &b, &p, &q);
		if(p > q) {
			edges[a].push_back({p, {b, q}});
			indegree[b]++;
		}
		else if(p < q) {
			edges[b].push_back({q, {a, p}});
			indegree[a]++;
		}
		else {
			save[++save_cnt] = { {a, p}, {b, q} };
		}
	}
	bool flag;
	for(int i = 1; i <= save_cnt; i++) {
		ppiipii tmp = save[i];
		a = tmp.first.first;
		b = tmp.second.first;
		p = tmp.first.second;
		q = tmp.second.second;
		flag = true;
		for(pipii edge : edges[a]) {
			if(edge.second.first == b) {
				flag = false;
				edges[a].push_back({ p, { b, q } });
				indegree[b]++;
				break;
			}
		}
		if(flag) {
			edges[b].push_back({ q, { a, p } });
			indegree[a]++;
		}
	}
}

void pick_joyak() {
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 1; i <= N; i++) if(indegree[i] == 0) pq.push(i);
	while(!pq.empty()) {
		int out = pq.top();		pq.pop();
		result[++order] = out;
		for(pipii edge : edges[out]) {
			total_score += 1LL*edge.first;
			if(--indegree[edge.second.first] == 0) pq.push(edge.second.first);
		}
	}
}

void output(int tc) { printf("#%d %lld %d\n", tc, total_score, result[K]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		pick_joyak();
		output(tc);
	}
	return 0;
}
#endif


#if 01
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(200010)

typedef long long ll;
typedef pair<int, pair<int, int>> pipii;
int T, N, M, K;
int indegree[NMAX], order, result[NMAX];
vector<pipii> edges[NMAX];
ll total_score;

void init() {
	total_score = 0LL;		order = 0;
	for(int i = 1; i <= N; i++) {
		edges[i].clear();
		indegree[i] = result[i] = 0;
	}
}

void input() {
	int a, b, p, q;
	scanf("%d %d %d", &N, &M, &K);
	init();
	for(int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &a, &b, &p, &q);
		if(p > q) {
			edges[a].push_back({p, {b, q}});
			indegree[b]++;
		}
		else if(p < q) {
			edges[b].push_back({q, {a, p}});
			indegree[a]++;
		}
		else {
			total_score += 1LL*p;
		}
	}
}

void pick_joyak() {
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 1; i <= N; i++) if(indegree[i] == 0) pq.push(i);
	while(!pq.empty()) {
		int out = pq.top();		pq.pop();
		result[++order] = out;
		for(pipii edge : edges[out]) {
			total_score += 1LL*edge.first;
			if(--indegree[edge.second.first] == 0) pq.push(edge.second.first);
		}
	}
}

void output(int tc) { printf("#%d %lld %d\n", tc, total_score, result[K]); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		pick_joyak();
		output(tc);
	}
	return 0;
}
#endif