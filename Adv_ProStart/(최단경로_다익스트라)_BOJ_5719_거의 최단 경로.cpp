// BOJ_5719_거의 최단 경로
/*
    입력한 출발점과 도착점 사이의 최단 경로를 검색
    교통 상황을 고려하지 않고 최단 경로를 검색하는 경우에는
        극심한 교통 정체를 경험할 수 있다.
    이 네비게이션은 절대로 최단 경로를 찾아주지 않는다. 항상 거의 최단 경로를 찾아준다.
        (최단 경로에 포함되지 않는 도로로만 이루어진 경로 중 가장 짧은 것)
       
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define INF (0x7fffffff)

typedef pair<int, int> pii;
int N, M;
int S, D;
int edges[510][510];
int dijk[510];

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            edges[i][j] = -1;
        }
    }
}

void get_min_dist() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < N; i++) dijk[i] = INF;
    pq.push({ 0, S });    dijk[S] = 0;
    while (!pq.empty()) {
        pii cur = pq.top(); pq.pop();
        for (int i = 0; i < N; i++) {
            if (edges[cur.second][i] == -1) continue;
            if (dijk[i] > dijk[cur.second] + edges[cur.second][i]) {
                dijk[i] = dijk[cur.second] + edges[cur.second][i];
                pq.push({dijk[i], i});
            }
        }
    }
}

void erase_edges() {
    queue<int> que;
    que.push(D);
    while (!que.empty()) {
        int out = que.front();  que.pop();
        for (int i = 0; i < N; i++) {
            if (edges[i][out] == -1) continue;
            if (dijk[out] == dijk[i] + edges[i][out] ) {
                edges[i][out] = -1;
                que.push(i);
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int u, v, p;      
    while (true) {
        scanf("%d %d", &N, &M);
        if (N == 0 && M == 0) break;
        init();
        scanf("%d %d", &S, &D);
        for (int i = 1; i <= M; i++) {
            scanf("%d %d %d", &u, &v, &p);
            edges[u][v] = p; // u --(p)--> v
        }

        get_min_dist();
        erase_edges();
        get_min_dist();

        printf("%d\n", dijk[D] == INF ? -1 : dijk[D]);
    }
    return 0;
}
#endif

// 또 다른 방법!!
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF     (987654321)

typedef pair<int, int> pii;
int N, M, S, D;
vector<pii> edges[510];
int dijk[510];
bool chk[510][510];

void init() {
    for (int i = 0; i < N; i++) {
        edges[i].clear();
        for (int j = 0; j < N; j++) {
            chk[i][j] = false;
        }
    }
}

void dijkstra() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < N; i++) dijk[i] = INF;
    pq.push({ 0, S });  dijk[S] = 0;
    while (!pq.empty()) {
        pii cur = pq.top();     pq.pop();
        for (pii next : edges[cur.second]) {
            if (chk[cur.second][next.second] == false) continue;
            if (dijk[next.second] > dijk[cur.second] + next.first) {
                dijk[next.second] = dijk[cur.second] + next.first;
                pq.push({ dijk[next.second] , next.second });
            }
        }
    }
}

void erase_edges() {
    queue<int> que;
    que.push(D);
    while (!que.empty()) {
        int out = que.front();      que.pop();
        for (int i = 0; i < N; i++) {
            if (chk[i][out] == false) continue;
            for (pii prev : edges[i]) {
                if (prev.second == out && dijk[out] == dijk[i] + prev.first) {
                    chk[i][out] = false;
                    que.push(i);
                }
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int u, v, p;
    while (true) {
        scanf("%d %d", &N, &M);
        if (N == 0 && M == 0) break;
        init();
        scanf("%d %d", &S, &D);
        for (int i = 1; i <= M; i++) {
            scanf("%d %d %d", &u, &v, &p);
            edges[u].push_back({ p, v }); // u--(p)-->v
            chk[u][v] = true;
        }
        dijkstra();
        erase_edges();
        dijkstra();
        printf("%d\n", dijk[D] == INF ? -1 : dijk[D]);
    }
    return 0;
}
#endif
