// BOJ_9370_미확인 도착지
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX    (2000)
#define INF     (987654321)

typedef pair<int, int> pii;
int T, n, m, t, s, g, h;
vector<pii> edges[NMAX+10];
vector<int> nomin;
vector <pii> arrival;
int dijk[NMAX+10];

bool cmp(pii &a, pii &b) {
    return a.second < b.second;
}

void init() {
    for (int i = 1; i <= n; i++) {
        edges[i].clear();
    }
    nomin.clear();
    arrival.clear();
}

int dijkstra(int start, int end) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 1; i <= n; i++) dijk[i] = INF;
    dijk[start] = 0;    pq.push({ 0, start });
    while (!pq.empty()) {
        pii cur = pq.top(); pq.pop();
        if (cur.second == end) break;
        for (pii next : edges[cur.second]) {
            if (dijk[next.second] > dijk[cur.second] + next.first) {
                dijk[next.second] = dijk[cur.second] + next.first;
                pq.push({ dijk[next.second], next.second });
            }
        }
    }
    return dijk[end];
}

int main() {
    freopen("in.txt", "r", stdin);
    int a, b, d, x;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {   // T : 1 ~ 100
        scanf("%d %d %d", &n, &m, &t);  // n : 2 ~ 2000
        init();
        scanf("%d %d %d", &s, &g, &h);  // s, g, h : 1 ~ n
        for (int i = 1; i <= m; i++) {  // m : 1 ~ 50000
            scanf("%d %d %d", &a, &b, &d);  // a, b : 1 ~ n // 1 ~ d ~ 1000
            edges[a].push_back({ d, b });
            edges[b].push_back({ d, a });
        }
        int sg, sh, gx, hx, gh = INF;
        int result1, result2;
        for (pii node : edges[g]) {
            if (gh > node.first) gh = node.first;
        }
        for (pii node : edges[h]) {
            if (gh > node.first) gh = node.first;
        }
        //printf("[tc : %d]\n", tc);
        for (int i = 1; i <= t; i++) {  // t : 1 ~ 100
            scanf("%d", &x);
            result1 = result2 = INF;
            sg = dijkstra(s, g);
            sh = dijkstra(s, h);
            gx = dijkstra(g, x);
            hx = dijkstra(h, x);
            if (sg != INF && hx != INF) result1 = sg + gh + hx;
            if (sh != INF && gx != INF) result2 = sh + gh + gx;
            if (result1 == INF && result2 == INF) continue;
            result1 = min(result1, result2);
            if(result1 <= dijkstra(s, x)) arrival.push_back({ result1, x });

           /* printf("s(%d) -> g(%d) : %d\n", s, g, sg);
            printf("g(%d) -> h(%d) : %d\n", g, h, gh);
            printf("h(%d) -> x(%d) : %d\n", h, x, hx);
            printf("=> %d\n===========================\n", result1);
            printf("s(%d) -> h(%d) : %d\n", s, h, sh);
            printf("h(%d) -> g(%d) : %d\n", h, g, gh);
            printf("g(%d) -> x(%d) : %d\n", g, x, gx);
            printf("=> %d\n\n", result2);*/
        }
        sort(arrival.begin(), arrival.end(), cmp);
        int prev = arrival[0].first;
        for (pii arrv : arrival) {
            //if (prev == arrv.first) {
                printf("%d ", arrv.second);
            //}
        }
        printf("\n");
    }
    return 0;
}
#endif
