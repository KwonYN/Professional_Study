// BOJ_10845_큐
/*
    push X: 정수 X를 큐에 넣는 연산이다.
    pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다.
         만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
    size: 큐에 들어있는 정수의 개수를 출력한다.
    empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
    front: 큐의 가장 앞에 있는 정수를 출력한다.
           만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
    back: 큐의 가장 뒤에 있는 정수를 출력한다.
          만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX (10000)

enum COMMAND { POP = 0, PUSH = 1, SIZE = 2, BACK = 3, EMPTY = 4, FRONT = 5 };   

int N;  // N : 1 ~ 10,000
int que[MAX+10];    // 1 ~ 100,000
int wp, rp;

int get_command(char* com) {
    int len = 0;
    while (com[len]) len++;
    if (len == 3) return POP;
    if (len == 4) {
        if (com[3] == 'h') return PUSH;
        if (com[3] == 'e') return SIZE;
        if (com[3] == 'k') return BACK;
    }
    if (len == 5) {
        if (com[4] == 'y') return EMPTY;
        if (com[3] == 't') return FRONT;
    }
}

int main()
{
    char command[10];
    int com_num;
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    wp = rp = 0;
    while (N--) {
        scanf("%s", command);
        com_num = get_command(command);
        if (com_num == POP) {
            if (wp <= rp) printf("%d\n", -1);
            else printf("%d\n", que[rp++]);
        }
        else if (com_num == PUSH) {
            scanf("%d", &com_num);
            que[wp++] = com_num;
        }
        else if (com_num == SIZE) printf("%d\n", wp - rp);
        else if (com_num == BACK) {
            if (wp <= rp) printf("%d\n", -1);
            else printf("%d\n", que[wp - 1]);
        }
        else if (com_num == EMPTY) {
            if (wp <= rp) printf("%d\n", 1);
            else printf("%d\n", 0);
        }
        else {
            if (wp <= rp) printf("%d\n", -1);
            else printf("%d\n", que[rp]);
        }
    }
    return 0;
}
#endif




// BOJ_2504_괄호의 값
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    
    return 0;
}
#endif




// BOJ_11058_크리보드
// Ctrl A + Ctrl C + Ctrl V(★여러 번 가능!!!!!★)
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100)

int N;
long long kriii[NMAX+10];
int clipboard, max_result;

int main()
{
    int tmp1, tmp2;
    freopen("in.txt", "r", stdin);
    max_result = 0;
    kriii[0] = 0;   kriii[1] = 1;   kriii[2] = 2;   kriii[3] = 3;
    for (int i = 4; i < NMAX; i++) {
        tmp1 = max(kriii[i - 1] + 1, kriii[i-1] + kriii[max_result]*(i - (max_result+1)));
        tmp2 = kriii[i - 3] * 2;
        if (tmp1 <= tmp2) {
            max_result = i - 3;
            kriii[i] = tmp2;
        }
        else kriii[i] = tmp1;
    }
    scanf("%d", &N);
    printf("%lld\n", kriii[N]);
    return 0;
}
#endif

// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100)

int N;
long long kriii[NMAX + 10];

int main()
{
    freopen("in.txt", "r", stdin);
    kriii[0] = 0;   kriii[1] = 1;   kriii[2] = 2;   kriii[3] = 3;
    //kriii[4] = 4;   kriii[5] = 5;   kriii[6] = 6;
    for (int i = 4; i <= NMAX; i++) {
        kriii[i] = kriii[i - 1] + 1;
        for (int j = 1; j <= i - 3; j++) {
            kriii[i] = max(kriii[i], kriii[i-j-2]*(j+1));
        }
    }
    scanf("%d", &N);
    printf("%lld\n", kriii[N]);
    return 0;
}
#endif




// BOJ_12869_뮤탈리스크
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int hp[5];
int min_attack;
int list_cnt;
int list[7][4], tmp_list[4], chk[4];

void dfs(int d) {
    if (d >= N) {
        list_cnt++;
        for (int i = 1; i <= N; i++) {
            list[list_cnt][i] = tmp_list[i];
        }
        return;
    }
    for (int j = 1; j <= N; j++) {
        if (chk[j]) continue;
        chk[j] = 1;
        tmp_list[d] = j;
        dfs(d+1);
        tmp_list[d] = 0;
        chk[j] = 0;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    min_attack = 0x7fffffff;        list_cnt = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &hp[i]);
    dfs(0);
    for (int i = 1; i <= list_cnt; i++) {
        for (int j = 1; j <= N; j++) printf("%d ", list[i][j]);
        printf("\n");
    }
    return 0;
}
#endif
// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{

    return 0;
}
#endif





// BOJ_11404_플로이드
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define INF     (987654321)

int n, m;
int weights[110][110];

int main()
{
    freopen("in.txt", "r", stdin);
    int a, b, c;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) weights[i][j] = 0;
            else weights[i][j] = INF;
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (weights[a][b] > c) weights[a][b] = c;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                weights[i][j] = min(weights[i][j], weights[i][k]+weights[k][j]);
            }
        }
    }
        
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (weights[i][j] == INF) printf("%d ", 0);
            else printf("%d ", weights[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#endif





// BOJ_5719_거의 최단 경로
/*
    입력한 출발점과 도착점 사이의 최단 경로를 검색
    교통 상황을 고려하지 않고 최단 경로를 검색하는 경우에는
        극심한 교통 정체를 경험할 수 있다.
    이 네비게이션은 절대로 최단 경로를 찾아주지 않는다. 항상 거의 최단 경로를 찾아준다.
        (최단 경로에 포함되지 않는 도로로만 이루어진 경로 중 가장 짧은 것)
       
*/
#if 0
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
#if 0
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





// BOJ_11657_타임머신
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define INF (987654321)

int N, M;
pair<int, pair<int, int>> edges[6010];
int min_time[510];

int main()
{
    freopen("in.txt", "r", stdin);
    int a, b, c; // c == 0 : 순간이동 // c < 0 : 타임머신
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) min_time[i] = INF;
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &a, &b, &c);
        edges[i] = { c, {a, b} };
    }

    min_time[1] = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= M; j++) {
            c = edges[j].first;
            a = edges[j].second.first;
            b = edges[j].second.second;
            if (min_time[a] != INF) {
                if (min_time[b] > min_time[a] + c) min_time[b] = min_time[a] + c;
            }
        }
    }
    bool isCycle = false;
    for (int j = 1; j <= M; j++) {
        c = edges[j].first;
        a = edges[j].second.first;
        b = edges[j].second.second;
        if (min_time[a] != INF) {
            if (min_time[b] > min_time[a] + c) {
                isCycle = true;  break;
            }
        }
    }

    if (isCycle) printf("%d\n", -1);
    else {
        for (int i = 2; i <= N; i++) {
            if (min_time[i] != INF) printf("%d\n", min_time[i]);
            else printf("%d\n", -1);
        }
    }
    return 0;
}
#endif





// BOJ_1654_랜선 자르기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define KMAX    (10000)

typedef long long ll;
int K, N;
ll max_len, lan[KMAX + 10], result;

bool get_cnt(ll target_len) {
    ll cnt = 0;
    for (int i = 0; i < K; i++) {
        cnt += (lan[i] / target_len);
    }
    if (cnt >= N) return true;
    return false;
}

int main()
{
    freopen("in.txt", "r", stdin);
    max_len = result = -1;
    scanf("%d %d", &K, &N);
    for (int i = 0; i < K; i++) {
        scanf("%lld", &lan[i]);
        max_len = max(max_len, lan[i]);
    }
    sort(lan, lan + K);

    ll s = 1, e = max_len, m;
    while (s <= e) {
        /*if ((s & 1) && (e & 1)) m = s / 2 + e / 2 + 1;
        else m = s / 2 + e / 2;*/
        // => 계속 if문을 통해 검증을 하다 보니 시간 초과...;;

        m = (s + e) / 2; // 여기에서 int 범위를 넘을 수도 있음!!!
        if (get_cnt(m)) {
            s = m + 1;
            if (result < m) result = m;
        }
        else e = m - 1;
    }
    printf("%lld\n", result);
    return 0;
}
#endif




// BOJ_10775_공항 : Union-Find
// 뒤에서부터 하는 것을 생각하는 것이 중요!!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define GMAX    (100000)

int G, P, max_cnt, gi[GMAX+10];
int gate[GMAX + 10]; // parent

int arrange_plane(int no) {
    if (no == gate[no]) return no;
    return gate[no] = arrange_plane(gate[no]);
}

int main()
{
    freopen("in.txt", "r", stdin);
    // initialization
    max_cnt = 0;

    // input
    scanf("%d", &G);
    for (int i = 0; i <= G; i++) gate[i] = i;
    scanf("%d", &P);
    for (int i = 1; i <= P; i++) scanf("%d", &gi[i]);

    // arrange plane
    int gate_num;
    for (int i = 1; i <= P; i++) {
        gate_num = arrange_plane(gi[i]);
        if (gate_num == 0) break;
        gate[gate_num]--;
        max_cnt++;
    }

    // print
    printf("%d\n", max_cnt);
    return 0;
}
#endif




// BOJ_2143_두 배열의 합
/*
    부배열 :  A[i], A[i+1], …, A[j-1], A[j] (단, 1 ≤ i ≤ j ≤ n)
    부 배열의 합은 A[i]+…+A[j]를 의미
    A의 부 배열의 합에 B의 부 배열의 합을 더해서
        T가 되는 모든 부 배열 쌍의 개수를 구하라!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX (1000)

typedef long long ll;
int T, n, m, A[MAX+10], B[MAX+10];
int AA[MAX*MAX], BB[MAX*MAX], a_cnt, b_cnt;
ll cnt;

void input() {
    cnt = a_cnt = b_cnt = 0;
    scanf("%d", &T);
    A[0] = B[0];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        A[i] += A[i - 1];
        for (int j = 0; j < i; j++) {
            AA[a_cnt++] = A[i] - A[j];
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &B[i]);
        B[i] += B[i - 1];
        for (int j = 0; j < i; j++) {
            BB[b_cnt++] = B[i] - B[j];
        }
    }
    sort(AA, AA + a_cnt);       sort(BB, BB + b_cnt);
}

void get_cnt() {
    int l = 0, r = b_cnt-1;
    int tmp_l;
    ll cnt_l, cnt_r;
    while ((l < a_cnt) && (r >= 0)) {
        if (AA[l] + BB[r] == T) {
            tmp_l = l;
            cnt_l = cnt_r = 0;
            while ((AA[l] + BB[r] == T) && (l < a_cnt)) { l++; cnt_l++; }
            while ((AA[tmp_l] + BB[r] == T) && (r >= 0)) { r--; cnt_r++; }
            //printf("cnt_l = %lld, cnt_r = %lld\n", cnt_l, cnt_r);
            cnt += (cnt_l*cnt_r);
        }
        else if (AA[l] + BB[r] > T) r--;
        else l++;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    input();
    /*printf("[AA] : ");
    for (int i = 0; i < a_cnt; i++) printf("%d ", AA[i]);
    printf("\n[BB] : ");
    for (int i = 0; i < b_cnt; i++) printf("%d ", BB[i]);
    printf("\n");*/
    get_cnt();
    printf("%lld\n", cnt);
    return 0;
}
#endif




// BOJ_2579_계단 오르기
/*
    계단 오르기 게임: 계단 아래 시작점부터 계단 꼭대기에 위치한 도착점까지 가는 게임
    계단을 밟으면 그 계단에 쓰여 있는 점수를 얻게 됨.

    1) 계단은 한 번에 "한" 계단씩 또는 "두" 계단씩 오를 수 있다.
       즉, 한 계단을 밟으면서 이어서 다음 계단이나,
                                     다음 다음 계단으로 오를 수 있다.
    2) "연속된 세" 개의 계단을 모두 밟아서는 "안" 된다.
       단, 시작점은 계단에 포함되지 않는다.
    3) "마지막" 도착 계단은 "반드시" 밟아야 한다.

    총 점수의 최댓값을 구하는 프로그램
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (300)
int N; // 계단의 개수
int stair[NMAX + 10];
pair<int, int> score[NMAX + 10];

void dfs_step(int prev, int now, int inarow) {
    if (inarow >= 3) return;
    if (now > N) return;
    if ((now - prev == 1) && (score[now].second < 
        score[prev].second + stair[now])) {
        score[now] = { inarow,  };
    }
    score[now].second = max(score[now].second, score[prev].second + stair[now]);
    dfs_step(now, now + 1, inarow + 1);
    dfs_step(now, now + 2, 1);
}

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    stair[0] = 0;       score[0] = { 0, 0 };
    for (int i = 1; i <= N; i++) scanf("%d", &stair[i]);
    dfs_step(0, 0, 0);
    for (int i = 0; i <= N; i++) printf("%d ", score[i].second);
    printf("\n");
    printf("%d\n", score[N].second);
    return 0;
}
#endif

// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (300)

int N;
int stair[NMAX + 10];
int score[NMAX + 10];

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &stair[i]);
    score[1] = stair[1];
    score[2] = stair[1] + stair[2];
    score[3] = max(stair[1] + stair[3], stair[2] + stair[3]);
    for (int i = 4; i <= N; i++) {
        score[i] = max(score[i-3] + stair[i-1] + stair[i], score[i - 2] + stair[i]);
    }
    printf("%d\n", score[N]);
    return 0;
}
#endif





// BOJ_2887_행성터널
/*
    N개의 행성. 효율적으로 지배하고파. 행성을 연결하는 터널 만들자!
    행성은 3차원 좌표 위의 한 점임.
    => (a, b, c)와 (d, f, e)를 터널 연결할 때 min( abs(a-d), min( abs(b-f), abs(c-e) ) )
    터널을 총 N-1개 건설해서 모든 행성이 서로 연결되게 하려고 함. 최소비용으로!

    모든 거리를 오름차순으로 배열화할 수 있다면!?!?!?
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX     (100000)

typedef struct { int x, y, z, no; }NODE;
typedef struct { int dist, v1, v2; }EDGES;
NODE planet[MAX + 10];
int N, min_cost, cnt;
vector<EDGES> edges;
int parent[MAX+10];

bool cmp_x(NODE &a, NODE &b) { return a.x < b.x; }
bool cmp_y(NODE &a, NODE &b) { return a.y < b.y; }
bool cmp_z(NODE &a, NODE &b) { return a.z < b.z; }
bool cmp_e(EDGES &a, EDGES &b) { return a.dist < b.dist; }

int find(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find(parent[v]);
}

bool find_chk(int a, int b) { return find(a) != find(b); }

void unite(int v1, int v2) { parent[find(v1)] = find(v2); }

int main()
{
    freopen("in.txt", "r", stdin);
    int a, b, c;
    min_cost = cnt = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) parent[i] = i;
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &a, &b, &c);
        planet[i] = { a, b, c, i };
    }
    sort(planet, planet + N, cmp_x);
    for (int i = 1; i < N; i++) {
        edges.push_back({ abs(planet[i-1].x - planet[i].x), planet[i-1].no, planet[i].no });
    }
    /*printf("[x] : ");
    for (int i = 0; i < N; i++) printf("%d ", planet[i].x);
    printf("\n");*/

    sort(planet, planet + N, cmp_y);
    for (int i = 1; i < N; i++) {
        edges.push_back({ abs(planet[i-1].y - planet[i].y), planet[i - 1].no, planet[i].no });
    }
    /*printf("[y] : ");
    for (int i = 0; i < N; i++) printf("%d ", planet[i].y);
    printf("\n");*/

    sort(planet, planet + N, cmp_z);
    for (int i = 1; i < N; i++) {
        edges.push_back({ abs(planet[i-1].z - planet[i].z), planet[i - 1].no, planet[i].no });
    }
    /*printf("[z] : ");
    for (int i = 0; i < N; i++) printf("%d ", planet[i].z);
    printf("\n");*/

    sort(edges.begin(), edges.end(), cmp_e);
    /*printf("[dist] : ");
    for (EDGES node : edges) printf("%d ", node.dist);
    printf("\n");*/

    for (EDGES node : edges) {
        if (find_chk(node.v1, node.v2)) {
            unite(node.v1, node.v2);
            cnt++;
            min_cost += node.dist;
        }
        if (cnt == N - 1) break;
    }
    printf("%d\n", min_cost);
    return 0;
}
#endif





// BOJ_9370_미확인 도착지
#if 0
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




// BOJ_2748_피보나치 수 2
/*
    0, 1로 시작
*/
#if 0
    #pragma warning(disable: 4996)
    #include <cstdio>
    #include <algorithm>
    using namespace std;
    #define NMAX    (90)

    int n;
    long long dp[NMAX+10];

    int main() {
        freopen("in.txt", "r", stdin);
        dp[0] = 0;  dp[1] = 1;
        for (int i = 2; i <= NMAX; i++) {
            dp[i] = dp[i - 2] + dp[i - 1];
        }
        scanf("%d\n", &n);
        printf("%lld\n", dp[n]);
        return 0;
    }
#endif




// BOJ_1003_피보나치 함수
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX       (40)

int T;
int cnt[2][NMAX+10];

int main() {
    freopen("in.txt", "r", stdin);
    int num;
    cnt[0][0] = 1;  cnt[1][0] = 0;
    cnt[0][1] = 0;  cnt[1][1] = 1;
    for (int i = 2; i <= NMAX; i++) {
        cnt[0][i] = cnt[0][i-1] + cnt[0][i-2];
        cnt[1][i] = cnt[1][i-1] + cnt[1][i-2];
    }
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &num);
        printf("%d %d\n", cnt[0][num], cnt[1][num]);
    }
    return 0;
}
#endif




// BOJ_11653_소인수분해
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX     (10000000)

int N; // N : 1 ~ 1천만
vector<int> soinsu;
bool eratos[MAX];
int sosu[MAX], sosu_cnt;

int main() {
    freopen("in.txt", "r", stdin);
    sosu_cnt = 0;
    for (int i = 2; i < MAX; i++) {
        if (eratos[i] != false) continue;
        sosu[++sosu_cnt] = i;
        for (int j = 2 * i; j < MAX; j += i) eratos[j] = true;
    }
    scanf("%d", &N);
    int point = 1;
    while (N != 1) {
        if (N % sosu[point] == 0) {
            N /= sosu[point];
            soinsu.push_back(sosu[point]);
        }
        else point++;
    }
    for (int print : soinsu) printf("%d\n", print);
    return 0;
}
#endif

// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int N;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    int point = 2;
    while (N != 1) {
        if (N % point == 0) {
            printf("%d\n", point);
            N /= point;
        }
        else point++;
    }
    return 0;
}
#endif




// BOJ_2960_에라토스테네스의 체
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int N, K;
bool eratos[1001];
bool flag;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d %d", &N, &K);
    int cnt = 0;
    for (int i = 2; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            if (eratos[j] == false) {
                eratos[j] = true;
                if (++cnt == K) {
                    printf("%d\n", j);
                    flag = true;
                    break;
                }
            }
        }
        if (flag) break;
    }
    return 0;
}
#endif




// BOJ_2504_괄호의 값
#if 0
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define MAX     (30)

typedef struct { int val, loc; }OPERATION;
int stack[MAX + 10], sp, osp;
OPERATION op[MAX + 10];

int convert_to_int(char ch) {
    if (ch == '(') return 1;
    if (ch == ')') return 2;
    if (ch == '[') return -1;
    return -3;
}

int main() {
    ios::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);
    freopen("in.txt", "r", stdin);
    string str;     int len, res;
    sp = osp = 0;   stack[0] = 0;
    cin >> str;     len = str.length();
    for (int i = 0; i < len; i++) {
        stack[++sp] = convert_to_int(str[i]);
        res = stack[sp - 1] * stack[sp];
        if (((res == 2) || (res == 3)) && ((stack[sp - 1] == 1) || (stack[sp - 1] == -1))) {
            op[++osp] = { res, sp-1 };
            sp -= 2;
            for (int j = osp; j > 0; j--) {
                if(op[j].loc > op[j-1].loc) break;
                if (op[j].loc == op[j - 1].loc) op[j - 1].val += op[j].val;
                else if (op[j].loc < op[j - 1].loc) {
                    op[j-1].val *= op[j].val;
                    op[j - 1].loc = op[j].loc;
                }
                osp--;
            }
        }
    }
    /*for (int i = 0; i <= osp; i++) {
        cout << op[i].val << ", " << op[i].loc << "\n";
    }*/
    if (sp > 0) cout << 0 << "\n";
    else cout << op[osp].val << "\n";
    return 0;
}
#endif



// BOJ_1837_암호제작
#if 0
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define KMAX    (1000000)

string P;
int K, len, r;
int sosu[KMAX], sosu_cnt;
bool eratos[KMAX+10], quality;

bool get_quotient(int n) {
    int num = 0;
    for (int i = 0; i < len; i++) {
        num = (num * 10 + (P[i] - '0')) % n;
    }
    return (num == 0);
}

int main() {
    freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);
    eratos[0] = eratos[1] = true;      sosu_cnt = 0;
    for (int i = 2; i <= KMAX; i++) {
        if (eratos[i]) continue;    // eratos[i] == false인 값이
        sosu[++sosu_cnt] = i;       // sosu[sosu_cnt]에 들어감!
        for (int j = i + i; j <= KMAX; j += i) eratos[j] = true;
    }
    cin >> P;               cin >> K;       
    len = P.length();       quality = true;
    for (int i = 1; i <= sosu_cnt; i++) {
        if (sosu[i] >= K) break;
        else if (get_quotient(sosu[i])) {
            r = sosu[i];
            quality = false;
            break;
        }
    }
    if (quality) cout << "GOOD" << "\n";
    else cout << "BAD " << r << "\n";
    return 0;
}
#endif





// BOJ_1644_소수의 연속합
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (4000000)

bool eratos[NMAX + 10];
int sosu[NMAX], sosu_cnt, N, cnt;

int main() {
    freopen("in.txt", "r", stdin);
    eratos[0] = eratos[1] = true;   sosu_cnt = 0;
    for (int i = 2; i <= NMAX; i++) {
        if (eratos[i]) continue;
        sosu[++sosu_cnt] = i;
        for (int j = i + i; j <= NMAX; j += i) eratos[j] = true;
    }
    int num;
    scanf("%d", &N);        cnt = 0;
    for (int i = 1; i <= sosu_cnt; i++) {
        num = 0;
        if (sosu[i] > N) break;
        for (int j = i; j <= sosu_cnt; j++) {
            //printf("(+될 소수 : %d) => %d\n", sosu[i], num);
            num += sosu[j];
            if (num >= N) {
                if (num == N) cnt++;
                break;
            }
        }
        //printf("=========================\n");
    }
    printf("%d\n", cnt);
    return 0;
}
#endif




// BOJ_2096_내려가기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (50000)

int N;
pair<int, int> arr[NMAX + 10][4];

int main() {
    freopen("in.txt", "r", stdin);
    int a, b, c, n;
    scanf("%d", &N);        n = N / 2;
    arr[0][1] = arr[0][2] = arr[0][3] = { 0, 0 };
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        arr[i][1] = { a, a };
        arr[i][2] = { b, b };
        arr[i][3] = { c, c };
        arr[i][1].first += max(arr[i-1][1].first, arr[i-1][2].first); // max
        arr[i][1].second += min(arr[i - 1][1].second, arr[i - 1][2].second); // min
        arr[i][2].first += max(arr[i - 1][1].first, max(arr[i - 1][2].first, arr[i-1][3].first));
        arr[i][2].second += min(arr[i - 1][1].second, min(arr[i - 1][2].second, arr[i - 1][3].second));        
        arr[i][3].first += (max(arr[i - 1][3].first, arr[i - 1][2].first));
        arr[i][3].second += min(arr[i - 1][3].second, arr[i - 1][2].second);
        //printf("%4d/%4d/%4d\n", a, b, c);
        //printf("%2d%2d/%2d%2d/%2d%2d\n", arr[i][1].first, arr[i][1].second, arr[i][2].first, arr[i][2].second, arr[i][3].first, arr[i][3].second);
    }
    arr[0][1] = arr[n][1];
    arr[0][2] = arr[n][2];
    arr[0][3] = arr[n][3];      n = N - n;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        arr[i][1] = { a, a };
        arr[i][2] = { b, b };
        arr[i][3] = { c, c };
        arr[i][1].first += max(arr[i - 1][1].first, arr[i - 1][2].first); // max
        arr[i][1].second += min(arr[i - 1][1].second, arr[i - 1][2].second); // min
        arr[i][2].first += max(arr[i - 1][1].first, max(arr[i - 1][2].first, arr[i - 1][3].first));
        arr[i][2].second += min(arr[i - 1][1].second, min(arr[i - 1][2].second, arr[i - 1][3].second));        
        arr[i][3].first += (max(arr[i - 1][3].first, arr[i - 1][2].first));
        arr[i][3].second += min(arr[i - 1][3].second, arr[i - 1][2].second);
        //printf("%4d/%4d/%4d\n", a, b, c);
        //printf("%2d%2d/%2d%2d/%2d%2d\n", arr[i][1].first, arr[i][1].second, arr[i][2].first, arr[i][2].second, arr[i][3].first, arr[i][3].second);
    }
    printf("%d %d\n", max(arr[n][1].first, max(arr[n][2].first, arr[n][3].first)),
                      min(arr[n][1].second, min(arr[n][2].second, arr[n][3].second)));
    return 0;
}
#endif



// BOJ_17472_다리만들기2
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define INF     (987654321)

typedef pair<int, pair<int, int>> pipii;
int N, M;
int island[12][12], island_cnt;
int bridge_dist;
int island_dist[8][8];
int parent[8];
vector<pipii> bridge;

bool comp(pipii &n1, pipii &n2) { return n1.first < n2.first; }

int find_island(int n) {
    printf("# n = %d, parent[n] = %d\n", n, parent[n]);
    if (parent[n] == n); return n;
    printf("$ n = %d, parent[n] = %d\n", n, parent[n]);
    return parent[n] = find_island(parent[n]);
}

void union_island(int n1, int n2) { 
    parent[find_island(n1)] = find_island(n2);
}

bool chk_island(int n1, int n2) { return (find_island(n1) != find_island(n2)); }

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    // 입력
    scanf("%d %d", &N, &M);
    island_cnt = 0;     bridge_dist = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &tmp);
            if (tmp) {
                if (island[i][j - 1]) {
                    island[i][j] = island[i][j - 1];
                }
                else if (island[i - 1][j]) {
                    island[i][j] = island[i - 1][j];
                }
                else island[i][j] = ++island_cnt;
            }
            else island[i][j] = tmp;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) printf("%d ", island[i][j]);
        printf("\n");
    }

    // 다리 길이 및 인접 섬 만들기
    for (int i = 1; i <= island_cnt; i++)
        for (int j = 1; j <= island_cnt; j++)
            island_dist[i][j] = INF;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int y = i, x = j;
            if (island[i][j]) {
                while (true) {
                    if (++y > N) break;
                    if (island[y][x] == island[i][j]) break;
                    else if (island[y][x] && island[y][x] != island[i][j]) {
                        if (y - i < 3) break;
                        else if (island_dist[island[i][j]][island[y][x]] > y - i - 1) {
                            island_dist[island[i][j]][island[y][x]] = y - i - 1;
                            break;
                        }
                    }
                }
                y = i;
                while (true) {
                    if (++x > M) break;
                    if (island[y][x] == island[i][j]) break;
                    else if (island[y][x] && island[y][x] != island[i][j]) {
                        if (x - j < 3) break;
                        else if (island_dist[island[i][j]][island[y][x]] > x - j - 1) {
                            island_dist[island[i][j]][island[y][x]] = x - j - 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    // MST 돌리기
    for (int i = 1; i <= island_cnt; i++) parent[i] = i;
    for (int i = 1; i <= island_cnt; i++) {
        for (int j = 1; j <= island_cnt; j++) {
            if (island_dist[i][j] == INF) continue;
            bridge.push_back({ island_dist[i][j] , {i, j} });
        }
    }
    sort(bridge.begin(), bridge.end(), comp);
    int num = 1;
    bool break_point = false;
    for (int i = 1; i <= island_cnt; i++) printf("%d ", parent[i]);
    printf("\n");
    for (pipii node : bridge) {
        if (chk_island(node.second.first, node.second.second)) {
            printf("node.second.first = %d, node.second.second = %d\n", node.second.first, node.second.second);
            union_island(node.second.first, node.second.second);
            num++;
            bridge_dist += node.first;
            printf("%d -[dist:%d]-> %d\n", node.second.first, node.first, node.second.second);
            for (int i = 1; i <= island_cnt; i++) printf("%d ", parent[i]);
            printf("\n");
        }
        else if (num == island_cnt) { break_point = true; break; }
    }

    // 출력
    printf("===출력===\n");
    for (int i = 1; i <= island_cnt; i++) printf("%d ", parent[i]);
    printf("\n");
    for (pipii node : bridge) {
        printf("%d -[dist:%d]-> %d\n", node.second.first, node.first, node.second.second);
    }
    printf("num = %d, bridge_dist = %d\n", num, bridge_dist);
    if (!break_point || !bridge_dist) bridge_dist = -1;
    printf("%d\n", bridge_dist);
    return 0;
}
#endif
// Re
#if 0
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define INF     (987654321)

typedef pair<int, pair<int, int>> pipii;
int N, M;
int map[12][12], island[12][12], island_cnt;
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };
int bridge[8][8], bridge_dist, dist[8][8];
vector<pipii> bridges;
int parent[8];

void BFS_numbering(int sy, int sx, int num) {
    queue<pair<int, int>> que;
    bool chk[12][12] = { false };
    que.push({ sy, sx });       chk[sy][sx] = true;
    island[sy][sx] = num;
    while (!que.empty()) {
        pair<int, int> node = que.front();  que.pop();
        for (int i = 0; i < 4; i++) {
            sy = node.first + dy[i];
            sx = node.second + dx[i];
            if (sy < 1 || sy > N || sx < 1 || sx > M) continue;
            if (chk[sy][sx]) continue;
            if (map[sy][sx]) {
                que.push({ sy, sx });
                chk[sy][sx] = true;
                island[sy][sx] = num;
            }
        }
    }
}

bool comp(pipii &n1, pipii &n2) { return n1.first < n2.first; }

int find(int n) {
    if (n == parent[n]) return n;
    return parent[n] = find(parent[n]);
}

void ally(int n1, int n2) {
    parent[find(n1)] = find(n2);
}

bool chk_false(int n1, int n2) { return find(n1) != find(n2); }

int main() {
    freopen("in.txt", "r", stdin);
    island_cnt = bridge_dist = 0;
    // 입력
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) scanf("%d", &map[i][j]);
    // 섬 넘버링
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j]) {
                if (island[i][j]) continue;
                BFS_numbering(i, j, ++island_cnt);
            }
        }
    }
    /*printf("island : \n");
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            printf("%d ", island[i][j]);
        }
        printf("\n");
    }*/

    // 섬 간 다리 거리
    for (int i = 1; i <= island_cnt; i++) for (int j = 1; j <= island_cnt; j++) dist[i][j] = INF;
    /*printf("이전 dist : \n");
    for (int i = 1; i <= island_cnt; i++) {
        for (int j = 1; j <= island_cnt; j++) {
            printf("%9d ", dist[i][j]);
        }
        printf("\n");
    }*/
    int y, x;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (island[i][j]) {
                y = i, x = j;
                while (true) {
                    if (++y > N) break;
                    if (island[y][j] == island[i][j]) break;
                    else if (island[y][j]) {
                        if (y - i < 3) break;
                        else if (dist[island[i][j]][island[y][j]] > y - i - 1) {
                            dist[island[i][j]][island[y][j]] = y - i - 1;
                            break;
                        }
                    }
                }
                while (true) {
                    if (++x > M) break;
                    if (island[i][x] == island[i][j]) break;
                    else if (island[i][x]) {
                        if (x - j < 3) break;
                        else if (dist[island[i][j]][island[i][x]] > x - j - 1) {
                            dist[island[i][j]][island[i][x]] = x - j - 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    /*printf("이후 dist : \n");
    for (int i = 1; i <= island_cnt; i++) {
        for (int j = 1; j <= island_cnt; j++) {
            printf("%9d ", dist[i][j]);
        }
        printf("\n");
    }*/

    // 다리들을 길이 기준으로 오름차순 정리
    for (int i = 1; i <= island_cnt; i++) {
        for (int j = 1; j <= island_cnt; j++) {
            if (dist[i][j] == INF) continue;
            bridges.push_back({ dist[i][j] , {i, j} });
        }
    }
    sort(bridges.begin(), bridges.end(), comp);
    /*printf("정렬 후 bridges : \n");
    for (pipii node : bridges) {
        printf("%d -[dist:%d]->%d\n", node.second.first, node.first, node.second.second);
    }*/

    // union-find => MST
    for (int i = 1; i <= island_cnt; i++) parent[i] = i;
    int cnt = 1;    bool break_point = false;
    for (pipii node : bridges) {
        if (chk_false(node.second.first, node.second.second)) {
            ally(node.second.first, node.second.second);
            cnt++;
            bridge_dist += node.first;
        }
        if (cnt == island_cnt) { break_point = true; break; }
    }

    // 출력
    //printf("cnt = %d, bridge_dist = %d\n", cnt, bridge_dist);
    if (!break_point || !bridge_dist) bridge_dist = -1;
    printf("%d\n", bridge_dist);
    return 0;
}
#endif





// BOJ_2042_구간 합 구하기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (1000000)

typedef long long ll;
enum OPERATION { CHANGE = 1, PRINT = 2 };
int N, M, K; // N : 1 ~ 1백만, M : 1 ~ 1만, K : 1 ~ 1만
             //                (변경 횟수)  (구간합 구하는 횟수)
ll tree[2100000];
int maldan;

void make_tree() {
    for (int i = maldan - 1; i >= 1; i--) {
        tree[i] = tree[i<<1] + tree[(i<<1) | 1];
    }
}

void update(int order, int new_val) {
    tree[order] = new_val;
    while (order > 1) {
        order >>= 1;
        tree[order] = tree[order<<1] + tree[(order<<1) | 1];
    }
}

ll search_sum(int s, int e) {
    ll ret = 0;
    while (s <= e) {
        if (s & 1) ret += tree[s++];
        if (!(e & 1)) ret += tree[e--];
        s >>= 1; e >>= 1;
    }
    return ret;
}

void print_tree() {
    printf("\nprint_tree\n");
    int order = 2;
    for (int i = 1; i < (maldan<<1); i++) {
        printf("%3d", tree[i]);
        if (i >= order - 1) {
            printf("\n");
            order *= 2;
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    int a, b, c;
    scanf("%d %d %d", &N, &M, &K);
    for (maldan = 1; maldan < N; maldan <<= 1);
    //printf("maldan = %d\n", maldan);
    for (int i = 0; i < N; i++) scanf("%d", &tree[maldan+i]);
    make_tree();
    //print_tree();
    for (int i = 1; i <= M + K; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (a == CHANGE) {
            update(b + maldan - 1, c);
            //print_tree();
        }
        else if (a == PRINT) {
            printf("%lld\n", search_sum(b + maldan - 1, c + maldan - 1));
        }
    }
    return 0;
}
#endif




// BOJ_1849_순열
// 시간초과 코드
#if 0
#pragma warning(disable : 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N;
int arr[NMAX+10], zrr[NMAX+10];

int main() {
    freopen("in.txt", "r", stdin);
    int tmp, j;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) zrr[i] = i - 1; // 0의 개수
    for (int i = 1; i <= N; i++) {
        scanf("%d", &tmp);
        for (j = tmp + 1; j <= N; j++) {
            if (zrr[j] == tmp) break;
        }
        arr[j] = i;
        for (int k = j; k <= N; k++) zrr[k]--;
    }
    for (int i = 1; i <= N; i++) printf("%d\n", arr[i]);
    return 0;
}
#endif

// Re
#if 0
#pragma warning(disable : 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N, maldan, mal;
int arr[NMAX*4]; // 0의 개수!

void make_zero_arr() {
    int idx = (maldan>>1);
    for (int i = idx; i <= maldan - 1; i++) {
        arr[i] = 2;
    }
    for (int i = idx - 1; i >= 1; i--) {
        arr[i] = arr[i << 1] + arr[(i << 1) | 1];
    }
}

void update(int order, int new_val) {
    int idx = 1;
    while (idx < mal) {
        if (arr[idx << 1] > order) idx <<= 1;
        else {
            order -= arr[idx << 1];
            idx = (idx << 1) | 1;
        }
    }
    if (arr[idx] == 1) {
        if (!arr[idx << 1]) arr[idx << 1] = new_val;
        else arr[(idx << 1) | 1] = new_val;
    }
    else {
        arr[idx * 2 + order] = new_val;
    }
    while (idx > 1) {
        arr[idx]--;
        idx >>= 1;
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    scanf("%d", &N);
    for (maldan = 1; maldan < N; maldan<<=1);
    mal = maldan >> 1;
    make_zero_arr();
    for (int i = 1; i <= N; i++) {
        scanf("%d", &tmp);
        update(tmp, i);
    }
    for (int i = maldan; i < maldan + N; i++) printf("%d\n", arr[i]);
    return 0;
}
#endif




// BOJ_11659_구간 합 구하기 4
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N, M;
int maldan, tree[NMAX*4];

void make_tree() {
    for (int i = maldan - 1; i >= 1; i--) {
        tree[i] = tree[i<<1] + tree[(i<<1) | 1];
    }
}

int search_sum(int s, int e) {
    int ret = 0;
    while (s <= e) {
        if (s & 1) ret += tree[s++];
        if (!(e & 1)) ret += tree[e--];
        s /= 2;        e /= 2;
    }
    return ret;
}

int main() {
    freopen("in.txt", "r", stdin);
    int a, b;
    scanf("%d %d", &N, &M);
    for (maldan = 1; maldan < N; maldan <<= 1);
    for (int i = 0; i < N; i++) scanf("%d", &tree[i+maldan]);
    make_tree();
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", search_sum(a+maldan-1, b+maldan-1));
    }
    return 0;
}
#endif




// BOJ_11505_구간 곱 구하기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (1000000)
#define MOD     (1000000007)

int N, M, K;
long long tree[NMAX * 4];
int maldan;

void make_tree() {
    for (int i = maldan - 1; i >= 1; i--) {
        tree[i] = (tree[i << 1] * tree[(i << 1) | 1]) % MOD;
    }
}

void update(int order, int new_val) {
    tree[order] = (long long)new_val;
    while (order > 1) {
        order >>= 1;
        tree[order] = (tree[order<<1] * tree[(order<<1)|1]) % MOD;
    }
}

long long search_multi(int s, int e) {
    long long ret = 1;
    while (s <= e) {
        if (s & 1) ret = (ret * tree[s++]) % MOD;
        if(!(e & 1)) ret = (ret * tree[e--]) % MOD;
        s >>= 1;    e >>= 1;
    }
    return ret;
}

int main() {
    freopen("in.txt", "r", stdin);
    int a, b, c;
    scanf("%d %d %d", &N, &M, &K);
    for (maldan = 1; maldan < N; maldan <<= 1);
    for (int i = 0; i < N; i++) scanf("%lld", &tree[maldan + i]);
    make_tree();
    for (int i = 0; i < M + K; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1) {
            update(b+maldan-1, c);
        }
        else {
            printf("%lld\n", search_multi(b+maldan-1, c+maldan-1));
        }
    }
    return 0;
}
#endif




// BOJ_2842_집배원 한상덕
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX    (50)

typedef pair<int, int> pii;
typedef struct { int y, x; }NODE;
NODE start;
int N, height[NMAX+5][NMAX+5], house_cnt;
char village[NMAX+5][NMAX+5];
bool height_range[1000001];
int height_cnt, tmp_cnt;
int range[2501];
int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int low, high;
bool chk[NMAX+5][NMAX+5];

bool bfs(int s, int e) {
    queue<pii> que;
    int ny, nx, cnt = 0;
    if (height[start.y][start.x] < s || height[start.y][start.x] > e) return false;
    que.push({ start.y, start.x }); chk[start.y][start.x] = true;
    while (!que.empty()) {
        pii out = que.front();  que.pop();
        for (int i = 0; i < 8; i++) {
            ny = out.first + dy[i];     nx = out.second + dx[i];
            if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
            if (chk[ny][nx]) continue;
            if (height[ny][nx] < s || height[ny][nx] > e) continue;
            if (village[ny][nx] == 'K') {
                if (++cnt == house_cnt) return true;
            }
            chk[ny][nx] = true;
            que.push({ ny, nx });
        }
    }
    return false;
}

void init() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            chk[i][j] = false; // 체크(visit)배열 초기화
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    char ch_tmp[NMAX + 5];
    house_cnt = height_cnt = tmp_cnt = 0;
    // 입력
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%s", ch_tmp + 1);
        for (int j = 1; j <= N; j++) village[i][j] = ch_tmp[j];
        for(int j = 1; j <= N; j++) {
            if (village[i][j] == 'P') start = { i, j };
            else if (village[i][j] == 'K') ++house_cnt;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &tmp);
            height[i][j] = tmp;
            if (!height_range[tmp]) {
                height_cnt++;
                height_range[tmp] = true;
            }
        }
    }
    // 고도 오름차순으로 정렬
    for (int i = 1; i <= 1000000; i++) {
        if (height_range[i]) range[++tmp_cnt] = i;
        if (tmp_cnt == height_cnt) break;
    }
    // 최대, 최소 고도 가정 -> 직접 돌아보기!
    low = 1;        high = 1;
    while (low <= high || high <= height_cnt) {
        init();
        if (!bfs(range[low], range[high])) high++;
        else low++;
    }
    printf("%d\n", range[high] - range[low]);
    return 0;
}
#endif

// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX    (50)
#define CHK_HEIGHT(s, e, h)    ( (((s) <= (h)) && ((h) <= (e))) ? true : false)

typedef struct { int y, x; }NODE;
NODE postoffice;
int N, house_cnt;
char village[NMAX+5][NMAX+5];
int height[NMAX+5][NMAX+5], height_cnt;
bool height_range[1000010];
int range[NMAX * NMAX + 5];
int dy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
bool visited[NMAX+5][NMAX+5];

bool bfs_house(int s, int e) {
    queue<NODE> que;
    int ny = postoffice.y, nx = postoffice.x, cnt = 0;
    if (!CHK_HEIGHT(s, e, height[ny][nx])) return false;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) visited[i][j] = false;
    que.push({ ny, nx }); visited[ny][nx] = true;
    while (!que.empty()) {
        NODE out = que.front(); que.pop();
        for (int i = 0; i < 8; i++) {
            ny = out.y + dy[i];     nx = out.x + dx[i];
            if (ny < 1 || ny > N || nx < 1 || nx > N || visited[ny][nx]) continue;
            if (!CHK_HEIGHT(s, e, height[ny][nx])) {
                if (village[ny][nx] == 'K') return false;
                continue;
            }
            if (village[ny][nx] == 'K') {
                if (++cnt == house_cnt) return true;
            }
            visited[ny][nx] = true;
            que.push({ ny, nx });
        }
    }
    return false;
}

int main() {
    freopen("in.txt", "r", stdin);
    char input_tmp[NMAX+5];
    int int_tmp;
    house_cnt = height_cnt = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%s", input_tmp+1);
        for (int j = 1; j <= N; j++) {
            village[i][j] = input_tmp[j];
            if (input_tmp[j] == 'P') postoffice = { i, j };
            else if (input_tmp[j] == 'K') ++house_cnt;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &int_tmp);
            height[i][j] = int_tmp;
            if (!height_range[int_tmp]) {
                height_range[int_tmp] = true;
                ++height_cnt;
            }
        }
    }
    for (int i = 1, cnt = 0; i <= 1000000; i++) {
        if (height_range[i]) {
            range[++cnt] = i;
            if (cnt == height_cnt) break;
        }
    }

    int low = 1, high = 1, min_diff = 987654321;
    while (low <= high && high <= height_cnt) {

        if (!bfs_house(range[low], range[high])) high++;
        else {
            if (min_diff > range[high] - range[low]) {
                min_diff = range[high] - range[low];
            }
            low++;
        }
    }
    printf("%d\n", min_diff);
    return 0;
}
#endif




// BOJ_1517_버블소트
/*
    버블소트 수행할 때 Swap이 몇 번 일어났는가?
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (500000)

typedef long long ll;
int N, arr[NMAX+5], arr_tmp[NMAX+5];

ll sort_n_get_swap_cnt(int s, int e) {
    if (s == e) return 0;
    int m = (s + e) / 2;
    ll swap_cnt = sort_n_get_swap_cnt(s, m) + sort_n_get_swap_cnt(m+1, e);
    // merge sort
    int left = s, right = e;
    int idx = 1;
    while (left <= m || right <= e) {
        if (left <= m && (right > e || arr[left] <= arr[right])) {
            arr_tmp[idx++] = arr[left++];
        }
        else {
            arr_tmp[idx++] = arr[right++];
            swap_cnt += (ll)(m - left + 1);
        }
    }
    for (int i = s; i <= e; i++) arr[i] = arr_tmp[i-s+1];
    return swap_cnt;
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    /*
    // 심플소트
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (arr[i] < arr[j]) {
                int tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    */
    /*
    // 버블소트
    for (int i = N - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j + 1] = tmp;
            }
        }
    }
    */
    for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    printf("%lld\n", sort_n_get_swap_cnt(1, N));
    return 0;
}
#endif




// BOJ_2357_최솟값과 최댓값
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

typedef struct { int mn, mx; }NODE;
int N, M;
NODE tree[NMAX * 4];
int maldan;

void make_tree() {
    for (int i = maldan - 1; i >= 1; i--) {
        tree[i].mn = min(tree[i<<1].mn, tree[(i<<1)|1].mn);
        tree[i].mx = max(tree[i<<1].mx, tree[(i<<1)|1].mx);
    }
}

NODE search_mx_mn(int s, int e) {
    NODE result = { 987654321, -1 };
    while (s < e) {
        if (s & 1) {
            result.mn = min(result.mn, tree[s].mn);
            result.mx = max(result.mx, tree[s++].mx);
            s++;
        }
        if (!(e & 1)) {
            result.mn = min(result.mn, tree[e].mn);
            result.mx = max(result.mx, tree[e--].mx);
        }
        s >>= 1; e >>= 1;
    }
    return result;
}

int main() {
    freopen("in.txt", "r", stdin);
    int tmp, a, b;
    scanf("%d %d", &N, &M);
    for (maldan = 1; maldan < N; maldan <<= 1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &tmp);
        tree[maldan + i] = { tmp, tmp };
    }
    for (int i = maldan + N; i < 2 * maldan; i++) {
        tree[i] = tree[maldan+N-1];
    }
    make_tree();
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        NODE result = search_mx_mn(a, b);
        printf("%d %d\n", result.mn, result.mx);
    }
    return 0;
}
#endif

// Re : 퇴근 후 풀어보자!! (세그먼트 트리 만들기!)
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N, M, maldan, arr[NMAX+5];
int max_tree[NMAX * 4];
int min_tree[NMAX * 4];// 최소, 최대값 트리

int make_max_tree(int s, int e, int arr_idx) {
    if (s == e) return max_tree[arr_idx] = arr[s];
    int m = (s + e) / 2;
    return max_tree[arr_idx] = max(make_max_tree(s, m, (arr_idx<<1)),
                                   make_max_tree(m+1, e, (arr_idx<<1)|1));
}

int make_min_tree(int s, int e, int arr_idx) {
    if (s == e) return min_tree[arr_idx] = arr[s];
    int m = (s + e) / 2;
    return min_tree[arr_idx] = min(make_min_tree(s, m, (arr_idx<<1)),
                                   make_min_tree(m+1, e, (arr_idx<<1)|1));
}

int search_max(int s, int e, int left, int right, int arr_idx) {
    if(left > e || right < s) return 0;
    if (left <= s && e <= right) return max_tree[arr_idx];
    int m = (s + e) / 2;
    return max(search_max(s, m, left, right, (arr_idx<<1)),
               search_max(m + 1, e, left, right, (arr_idx<<1)|1));
}

int search_min(int s, int e, int left, int right, int arr_idx) {
    if (left > e || right < s) return 0x7fffffff;
    if (left <= s && e <= right) return min_tree[arr_idx];
    int m = (s + e) / 2;
    return min(search_min(s, m, left, right, (arr_idx<<1)),
               search_min(m + 1, e, left, right, (arr_idx<<1)|1));
}

int main() {
    freopen("in.txt", "r", stdin);
    int a, b, min_val, max_val;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    make_max_tree(1, N, 1);     make_min_tree(1, N, 1);
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &a, &b);
        min_val = search_min(1, N, a, b, 1);
        max_val = search_max(1, N, a, b, 1);
        printf("%d %d\n", min_val, max_val);
    }
    return 0;
}
#endif




// BOJ_11660_시간 합 구하기 5
#if 0
#pragma warning(disable : 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (1024)

int N, arr[NMAX+5][NMAX+5], M;

int main() {
    freopen("in.txt", "r", stdin);
    int x1, y1, x2, y2;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &arr[i][j]);
            arr[i][j] += arr[i][j - 1];
        }
        for (int j = 1; j <= N; j++) {
            arr[i][j] += arr[i-1][j];
        }
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", arr[x2][y2] - arr[x1-1][y2] - arr[x2][y1-1] + arr[x1-1][y1-1]);
    }
    return 0;
}
#endif




// BOJ_11049_행렬 곱셈 순서
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(500)

typedef struct { int r, c; }MATRIX;
int N;
MATRIX matrix[NMAX + 5];
int cnt_mult[NMAX + 5][NMAX + 5];

int main() {
    freopen("in.txt", "r", stdin);
    // 입력
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d %d", &matrix[i].r, &matrix[i].c);
    // DP
    for (int i = 1; i < N; i++) cnt_mult[i][i + 1] = matrix[i].r * matrix[i].c * matrix[i + 1].c;
    int idx, tmp;
    for (int i = 2; i < N; i++) {
        for (int j = 1; j <= N - i; j++) {
            idx = i + j;
            int tmp = 0x7fffffff;
            for (int k = j + 1; k < idx - 1; k++) {
                tmp = min(tmp, cnt_mult[j][k] + cnt_mult[k+1][idx] + matrix[j].r*matrix[k+1].r*matrix[idx].c);
            }
            cnt_mult[j][idx] = min(tmp, 
                min(cnt_mult[j][idx-1] + matrix[j].r*matrix[idx-1].c*matrix[idx].c, 
                    cnt_mult[j+1][idx] + matrix[j].r*matrix[j+1].r*matrix[idx].c));
        }
    }
    printf("%d\n", cnt_mult[1][N]);
    return 0;
}
#endif





// BOJ_5052_전화번호 목록 : 내 코드
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX     (10000)

bool isConsistent;
struct PHONE_NUM {
    bool isEnd, isNext;
    PHONE_NUM* next_num[10];
    PHONE_NUM() : isEnd(false), isNext(false) { 
        for (int i = 0; i < 10; i++) next_num[i] = nullptr;
    }
    ~PHONE_NUM() {
        for (int i = 0; i < 10; i++) if (next_num[i]) delete next_num[i];
    }
    void insert(char* phone_num) {
        if (*phone_num == '\0') {   // 끝이라면
            isEnd = true;
            if (isNext) isConsistent = false;
            return;
        }
        int nextNum = *phone_num - '0';
        if (next_num[nextNum] == nullptr) next_num[nextNum] = new PHONE_NUM;
        isNext = true;
        if (isEnd) isConsistent = false;
        next_num[nextNum]->insert(phone_num + 1);
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    int t, n;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        PHONE_NUM* root = new PHONE_NUM;
        isConsistent = true;
        for (register int i = 0; i < n; i++) {
            char input_num[11];
            scanf("%s", input_num);
            root->insert(input_num);
        }
        if (!isConsistent) printf("NO\n");
        else printf("YES\n");
        delete root;
    }
    return 0;
}
#endif

// 남의 코드
#if 0
#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int TrieNode = 10; // 트라이 노드마다 포인터 개수

struct Trie
{
    Trie* next[TrieNode]; // 다음 노드를 가리키는 포인터 배열
    bool finish; // 이 노드에서 끝나는 전화번호가 있는가?
    bool nextChild; // 이 노드의 자식이 있는가?

    // 생성자
    Trie()
    {
        fill(next, next + TrieNode, nullptr);
        finish = nextChild = false;
    }

    // 소멸자
    ~Trie()
    {
        for (int i = 0; i < TrieNode; i++)
            if (next[i])
                delete next[i];
    }

    // 문자열 key를 현재 노드부터 삽입. 삽입 후 일관성이 있는지를 리턴
    bool insert(const char* key)
    {
        // 문자열의 끝이라면
        if (*key == '\0')
        {
            finish = true;

            // 문자열이 끝났는데도
            // 자식이 있다면 일관성이 없다.
            if (nextChild)
                return 0;
            else
                return 1;
        }

        int nextKey = *key - '0';

        // 다음으로 가는 트라이가 없다면
        if (!next[nextKey])
            next[nextKey] = new Trie;

        nextChild = true;

        // 여기까지 왔다는 의미는 트라이의 자식이 분명히 있다는것.
        // 이때 자식 에서 일관성이 없던게 밝혀지거나
        // finish가 true라면 일관성이 없다는 의미.
        bool get = next[nextKey]->insert(key + 1);

        return !finish && get;
    }
};

int main()
{
    freopen("in.txt", "r", stdin);
    int tc;
    scanf("%d", &tc);

    while (tc--)
    {
        int n;
        scanf("%d", &n);

        // 트라이의 루트 생성
        Trie* root = new Trie;

        bool chk = true;

        for (int i = 0; i < n; i++)
        {
            char phone[11];
            scanf("%s", phone);

            // 일관성이 없다면
            if (chk && root->insert(phone) == 0)
                chk = false;
        }

        if (chk)
            printf("YES\n");
        else
            printf("NO\n");

        // 트라이 소멸
        delete root;
    }

    return 0;
}
#endif

// 남의 코드2
#if 0
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
using namespace std;
#define N 10000
#define LNG 10

int idx = 0;
int cnt = 0;
struct Node {
    bool finished;
    int point[LNG];
    void init() {
        for (register int i = 0; i < LNG; i++) {
            point[i] = 0;
        }
    }
};

Node node[N * 6];

Node* newNode() {
    node[idx].init();
    node[idx].finished = false;
    return &node[idx++];
}

int main() {
    ios_base::sync_with_stdio(false);    cin.tie(0);    cout.tie(0);
    int tc, n;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cin >> n;
        idx = 0;
        string phone;
        Node* pv = newNode();
        bool consis = false;
        for (register int i = 0; i < n; i++)
        {
            cin >> phone;
            Node* cur = pv;
            register int lng = phone.length();

            if (!consis) {
                for (int j = 0; j < lng; j++) {
                    int pos = phone[j] - '0';
                    if (cur->point[pos] == 0) {
                        Node* node = newNode();
                        cur->point[pos] = idx - 1;
                    }
                    else if (node[cur->point[pos]].finished == true) {
                        consis = true;
                    }
                    cur = &node[cur->point[pos]];
                }
                for (int k = 0; k < 10; k++) {
                    if (cur->point[k] > 0)
                        consis = true;
                }
                cur->finished = true;
            }
        }
        if (consis) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
    return 0;
}
#endif




// BOJ_9934_완전 이진 트리
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX     (1024)

int K, maldan;
int arr[MAX + 5], arr_idx;

struct NODE { int num; bool visited; };
NODE tree[MAX + 5] = { {0, false} };

void insert(int depth, int tree_idx) {
    //printf("depth = %d, tree_idx = %d\n", depth, tree_idx);
    if (depth > K || tree[tree_idx].visited) return;
    insert(depth + 1, tree_idx << 1);
    if (!tree[tree_idx].visited) {
        tree[tree_idx].num = arr[arr_idx++];
        tree[tree_idx].visited = true;
    }
    insert(depth + 1, (tree_idx << 1) | 1);
    if (!tree[tree_idx].visited) {
        tree[tree_idx].num = arr[arr_idx++];
        tree[tree_idx].visited = true;
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &K);
    maldan = 1;
    for (int i = 1; i <= K; i++) {
        maldan <<= 1;
    }
    //printf("maldan = %d\n", maldan);
    for (int i = 1; i < maldan; i++) scanf("%d", &arr[i]);
    arr_idx = 1;
    insert(1, 1);
    int cnt = 2;
    for (int i = 1; i < maldan; i++) {
        printf("%d ", tree[i].num);
        if (i >= cnt-1) {
            cnt <<= 1;
            printf("\n");
        }
    }
    return 0;
}
#endif

// Re
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX (1024)

int K, arr[MAX+5], tree[MAX+5], maldan, arr_idx;

void visiting_building(int depth, int tree_idx) {
    if (depth > K || tree[tree_idx] != -1) return;
    visiting_building(depth + 1, tree_idx << 1);
    if (tree[tree_idx] == -1) { tree[tree_idx] = arr[arr_idx++]; }
    visiting_building(depth + 1, (tree_idx << 1)|1);
    if (tree[tree_idx] == -1) { tree[tree_idx] = arr[arr_idx++]; }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &K);
    maldan = 1;
    for (int i = 1; i <= K; i++) maldan <<= 1;
    for (int i = 1; i < maldan; i++) scanf("%d", &arr[i]);
    for (int i = 1; i < maldan; i++) tree[i] = -1;
    arr_idx = 1;
    visiting_building(1, 1);
    arr_idx = 2;
    for (int i = 1; i < maldan; i++) {
        printf("%d ", tree[i]);
        if (arr_idx-1 == i) {
            printf("\n");
            arr_idx <<= 1;
        }
    }
    return 0;
}
#endif




// [교욱P-0022] 히스토그램에서 가장 큰 직사각형
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

typedef long long ll;
int T, N, stptr;
struct STACK { int idx, height; };
STACK stack[NMAX+5];
ll area, tmp_area;

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        stptr = 0;  area = N;
        scanf("%d", &tmp);
        stack[stptr++] = { 0, tmp };
        for (int i = 1; i < N; i++) {
            scanf("%d", &tmp);
            area = max(area, (ll)tmp);
            tmp_area = 0;
            while ((stptr != 0) && (stack[stptr-1].height >= tmp)) {
                stptr--;
                tmp_area = max(tmp_area, (ll)tmp*((ll)i - stack[stptr].idx + 1));
            }
            area = max(area, tmp_area);
            stack[stptr] = { stptr++, tmp };
        }
        for (int i = 0; i <= stptr; i++) {
            printf("[%d] %d, ", stack[i].idx, stack[i].height);
        }
        printf("\nstptr = %d\n", stptr);
        printf("#%d %lld\n", tc, area);
    }
    return 0;
}
#endif
// Re : 이거 못 푼 버전임. 푼 것은 회사컴에 있음!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define STACK_MAX	(100000)

typedef long long ll;
struct STACK { int height, idx; };
int T, N;
STACK stack[STACK_MAX + 5];
int stptr;
ll area;

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    ll tmp_area;
    bool flag;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        stptr = 0;		area = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d", &tmp);
            area = max(area, (ll)tmp);
            tmp_area = 0;		flag = false;
            while ((stptr != 0) && (stack[stptr - 1].height >= tmp)) {
                tmp_area = max(tmp_area, (ll)tmp*((ll)i - stack[--stptr].idx + 1));
                flag = true;
            }
            if (flag) stack[stptr] = { tmp, stack[stptr++].idx };
            else {
                for (int j = stptr - 1; j >= 0; j--) {
                    tmp_area = max(tmp_area, (ll)stack[j].height*((ll)i - stack[j].idx + 1));
                }
                stack[stptr++] = { tmp, i };
            }
            area = max(area, tmp_area);
        }
        //printf("stptr = %d\n", stptr);
        printf("#%d %lld\n", tc, area);
    }
    return 0;
}
#endif



// (중상) [연습P-0023] 동맹의 동맹은 동맹
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int T, N, Q, relationship[NMAX+5], cnt;

int find(int v) { // ★ v가 바라보는 애를 찾음
    if (relationship[v] == v) return v;
    return relationship[v] = find(relationship[v]);
    // v가 바라보는 애가 바라보는 애를 찾고
    // v가 바라보는 애가 얘를 바라볼 수 있도록 (경로 압축)
}

void ally(int v1, int v2) {
    relationship[find(v1)] = find(v2);
    // v1과 v2가 각각 바라보는 애를 찾아서
    // v1이 바라보는 애가 v2가 바라보는 애를 바라볼 수 있도록
}

bool chk_alliance(int v1, int v2) { // 둘이 동맹관계임을 밝힘
    return find(v1) == find(v2);
}

int main() {
    freopen("in.txt", "r", stdin);
    int a, b, c;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        // 초기화 : 자기 자신을 바라보게 함
        for (int i = 1; i <= N; i++) relationship[i] = i;
        cnt = 0;
        scanf("%d", &Q);
        for (int i = 1; i <= Q; i++) {
            scanf("%d %d %d", &a, &b, &c);
            if (!a) { ally(b, c); }
            else { if (chk_alliance(b, c)) cnt++; }
        }
        printf("#%d %d\n", tc, cnt);
    }
    return 0;
}
#endif




// BOJ_1849_순열
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N, A[NMAX + 5], tree[NMAX * 4 + 5], maldan, arr[NMAX + 5];

void make_tree() {
    int mal = maldan << 1;
    for (int i = mal - 1; i >= maldan; i--) tree[i] = 1;
    for (int i = maldan - 1; i >= 1; i--) {
        tree[i] = tree[i << 1] + tree[(i << 1) | 1];
    }
}

void update(int val, int cnt, int tree_idx) {
    while (true) {
        tree[tree_idx]--;
        if (tree[tree_idx << 1] > cnt) tree_idx <<= 1;
        else {
            cnt -= tree[tree_idx << 1];
            tree_idx = tree_idx << 1 | 1;
        }
        if (tree_idx >= maldan) {
            tree[tree_idx]--;
            arr[tree_idx - maldan] = val;
            break;
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    scanf("%d", &N);
    for (maldan = 1; maldan < N; maldan <<= 1);
    make_tree();
    for (int i = 1; i <= N; i++) {
        //scanf("%d", &A[i]);
        scanf("%d", &tmp);
        update(i, tmp, 1);
    }
    /*int cnt = 2;
    for (int i = 1; i < (maldan<<1); i++) {
        printf("%3d", tree[i]);
        if (cnt - 1 == i) { cnt <<= 1; printf("\n"); }
    }*/
    for (int i = 0; i < N; i++) printf("%d\n", arr[i]);
    return 0;
}
#endif




// BOJ_1572_중앙값
// 시간초과..!!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX    (250000)

int N, K; // N : 1 ~ 25만, K : 1 ~ 5천
int arr[NMAX + 10];
long long median_sum;
vector<int> brr;

int main() {
    freopen("in.txt", "r", stdin);
    median_sum = 0;
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = K; i <= N; i++) {
        brr.clear();
        for (int j = 0; j < K; j++) {
            brr.push_back(arr[i - j]);
        }
        sort(brr.begin(), brr.end());
        //printf("median = %d\n", brr[(K+1) / 2-1]);
        median_sum += brr[(K + 1) / 2 - 1];
    }
    printf("%lld\n", median_sum);
    return 0;
}
#endif

// Re : 다시 풀어야 함!ㅠ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (250000)

typedef long long ll;
int N, K, arr[NMAX+4], brr[NMAX+4], tree[NMAX*4];

// 머지소트에서 힌트를 얻어서
void merge(int left, int mid, int right) {
    int l = left, r = mid+1, tmp = left;

    while (l <= mid && r <= right) {
        if (arr[l] < arr[r]) brr[tmp++] = arr[l++];
        else brr[tmp++] = arr[r++];
    }
    while (l <= mid) brr[tmp++] = arr[l++];
    while (r <= right) brr[tmp++] = arr[r++];
    for (int i = left; i <= right; i++) arr[i] = brr[i];
}

void merge_sort(int left, int right) {
    if (left < right) {
        int m = (left + right) / 2;
        merge_sort(left, m);
        merge_sort(m + 1, right);
        merge(left, m, right);
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    return 0;
}
#endif

// ReRe : Merge Sort Tree로도 못 풀었다.. ㅠ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (250000)

int N, K, arr[NMAX+5], tree[NMAX*4], tmp[NMAX+5], result[NMAX+5];
long long sum_med;

long long Merge_Sort_Tree(int s, int e, int left, int right) {
    if (left > e || right < s) return 0LL;
    if (s == e) return (long long)arr[s];
    int m = (s + e) / 2;
    Merge_Sort_Tree(s, m, left, right);
    Merge_Sort_Tree(m+1, e, left, right);
    int idx1 = s, idx2 = m + 1, idx3 = s;
    while (idx1 <= m && idx2 <= e) {
        if (idx2 > e || arr[idx1] <= arr[idx2]) tmp[idx3++] = arr[idx1++];
        else tmp[idx3++] = arr[idx2++];
    }
    //tree[tree_idx] = tmp[(s-1 + (e-s+1)/2)];
    return (long long)tmp[(left - 1 + (right - left + 1) / 2)];
}

//long long Find_Med(int s, int e, int left, int right, int tree_idx) {
//    if (left > e || right < s) return 0;
//    if (s <= left && right <= e) return tree[tree_idx];
//    int m = (s + e) / 2;
//    return Find_Med(s, m, left, right, tree_idx << 1) + Find_Med(m + 1, e, left, right, (tree_idx << 1) | 1);
//}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d %d", &N, &K);     sum_med = 0;
    for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    for (int i = 0; i < N - K + 1; i++) {
        sum_med += Merge_Sort_Tree(1, N, i+1, i+K);
    }
    //for (int i = 0; i < N - K + 1; i++) {
    //    sum_med += Find_Med(1, N, i + 1, i + K, 1);
    //}
    printf("%lld\n", sum_med);
    return 0;
}
#endif






// (중상) [기출P-0037] 섬나라
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMMAX	(500)
#define QMAX	(100000)

typedef struct { int y, x; }NODE;
int T, N, M, Q;
pair<int, NODE> island[NMMAX + 5][NMMAX + 5];
vector<NODE> q[QMAX + 5];
bool chk[QMAX + 5]; 
int input_num[QMAX + 5];
int cnt_island[QMAX + 5];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

NODE find(int y, int x) {
    if (island[y][x].second.y == y && island[y][x].second.x == x) return island[y][x].second;
    return island[y][x].second = find(island[y][x].second.y, island[y][x].second.x);
}

void _union(NODE v1, NODE v2) {
    NODE node1 = find(v1.y, v1.x);
    NODE node2 = find(v2.y, v2.x);
    island[node1.y][node1.x].second = {node2.y, node2.x};
}

void bfs_unions_find(int y, int x) {
    queue<NODE> que;
    bool chk_bfs[NMMAX + 5][NMMAX + 5] = { false };
    int ny, nx;
    que.push({ y, x });   chk_bfs[y][x] = true;
    while (!que.empty()) {
        NODE cur = que.front();     que.pop();
        for (int i = 0; i < 4; i++) {
            ny = cur.y + dy[i];     nx = cur.x + dx[i];
            if (ny < 1 || ny > N || nx < 1 || nx > M || chk_bfs[ny][x]) continue;
            _union({ny, nx}, { y, x });
            que.push({ ny, nx });
            chk_bfs[ny][nx] = true;
        }
    }
}

void init() {
    for (int i = 1; i <= QMAX; i++) {
        q[i].clear();
        chk[i] = false;
        input_num[i] = 0;
        cnt_island[i] = 0;
    }
}

int main() {
    int tmp;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        // 초기화
        init();
        // 입력
        scanf("%d %d", &N, &M);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                scanf("%d", &island[i][j].first);
                island[i][j].second = { i, j };
                q[island[i][j].first].push_back({ i, j });
            }
        }
        scanf("%d", &Q);
        for (int i = 1; i <= Q; i++) {
            scanf("%d", &tmp);
            if (!chk[tmp]) {
                chk[tmp] = true;
                input_num[i] = tmp; // 중복제거
                for (NODE cur : q[tmp]) {
                    island[cur.y][cur.x].first = -1;
                }
            }
            else input_num[i] = 0;
        }
        // 섬 넘버링 : 현재 다 파괴한 상태이므로, 남아있는 -1이 아닌 양수들의 군집을 섬으로 간주하고, Union 해주어야 함!
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (!(island[i][j].second.y == i && island[i][j].second.x == j)) continue;
                bfs_unions_find(i, j);
                cnt_island[Q]++;
            }
        }

        // num_cnt ~ 1까지 섬을 복원해주면서, 복원된 땅의 사방에 있는 섬과 Union -> 거꾸로 섬의 개수 저장해줌(cnt_island[i])
        // input_num[i] == 0이면 continue로 넘어가줌
        for (int i = Q - 1; i >= 1; i--) {
            for (NODE cur : q[i + 1]) {
                for (int j = 0; j < 4; j++) {
                    ;
                }
            }
        }

        // 출력
        printf("#%d", tc);
        for (int i = 1; i <= Q; i++) {
            if (cnt_island[i] == 0) printf(" %d", cnt_island[i] = cnt_island[i - 1]);
            else printf(" %d", cnt_island[i]);
        }
        printf("\n");
    }
    return 0;
}
#endif
/*
#1 1 1 1 2 2 2 3 7 12 12 15 15 15 18 24 36 36 38 38 38 38 47 55 55 90 110 110 110 110 110 113 146 183 183 214 241 315 426 470 470 470 470 532 532 532 532 532 532 532 532 656 656 676 676 687 740 805 805 805 805 805 919 1040 1040 1090 1090 1107 1143 1180 1194 1208 1208 1223 1223 1223 1223 1223 1247 1247 1247 1247 1247 1262 1262 1279 1284 1284 1284 1284 1284 1284 1284 1284 1284 1284 1284 1284 1278 1278 1278
#2 1 1 1 1 1 2 5 6 13 27 43 43 64 64 64 120 120 120 196 218 394 426 426 426 503 668 668 684 684 684 874 894 898 898 1038 1135 1135 1188 1188 1204 1204 1299 1299 1299 1299 1299 1299 1307 1307 1307 1307 1307 1307 1307 1307 1316 1316 1316 1315 1315 1315 1313 1307 1307 1307 1305 1305 1305 1305 1305 1310 1278 1278 1262 1262 1262 1262 1262 1194 1194 1194 1194 1153 1153 1141 1141 1141 1141 1141 1141 1141 1141 1141 1141 1141 1141 1141 1040 1040 1040
#3 1 1 2 2 3 3 9 17 36 62 67 94 94 153 153 153 210 283 331 469 628 782 1048 1048 1048 1153 1463 1463 1875 1875 2407 2407 2975 2975 3396 3893 4645 5212 6067 6067 6330 6838 6838 6838 7316 7316 7316 8925 9944 9944 11709 11709 11890 13873 13873 13873 13873 13873 13873 15609 17275 18701 18701 20071 20071 20553 20553 22208 22208 22705 24357 24357 24866 24866 24866 25760 25760 26756 26756 26756 26756 26756 26756 26756 26756 26756 26756 26756 27976 28720 29894 29894 29894 30275 30275 30275 30417 30417 30417 30417 30417 30417 30417 30417 30417 30417 31231 31231 31802 31802 31802 31802 31802 31802 31802 31802 31802 32100 32100 32186 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32197 32117 32117 32117 32072 32072 31868 31615 31615 31615 31615 31270 30833 30833 30833 30833 30833 30833 30458 30458 30458 30458 30458 30458 30458 30458 30458 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 29109 28430 27818 27121 27121 26680 26372 26372 26372 26372 26372 26372 26372 26372 26372 26372 25106 25106 25106 24173 24173 24173 24173 22375 21586 21586 21586 21586 21586 21586 19424 19424 17269 17269 17269 17269 17269 17269 17269 17269 17269 17269 17269 16732 16732 16732 16732 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 16390 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14600 14082 14082 14082 14082 14082 14082 14082 14082 14082 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 13185 12780 12780 12780 12780 12780 12780 12780 12780 12780 12780 11370 11370 11370 10758 10758 10758 10758 10758 10758 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 10704 9880 9880 9880 9880 9880 9880 9880 9880 9880 9880 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7643 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 7048 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 6828 5374 5374 5374 5374 5374 5374 5374 5374 5374 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4219 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 4017 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 1666 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 841 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541 541
#4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 8 8 9 9 9 9 9 9 9 9 9 9 9 11 11 11 11 11 11 11 11 11 11 11 11 12 12 12 12 12 12 12 12 12 12 12 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 14 16 16 16 16 16 16 16 16 16 17 17 17 17 17 17 17 18 18 18 18 18 18 18 18 18 18 18 18 18 18 18 18 19 19 19 19 19 19 19 20 20 21 21 21 21 21 22 23 23 23 23 23 23 23 23 23 25 26 26 26 26 26 26 26 26 26 26 27 27 27 29 30 30 30 30 30 32 32 32 32 32 32 32 33 34 34 34 34 34 34 35 36 36 36 36 36 36 36 37 37 37 37 37 36 36 36 36 36 36 37 38 38 38 38 38 38 39 40 40 40 41 41 41 41 41 42 42 42 43 44 44 44 44 45 45 45 45 45 45 46 46 46 46 47 47 47 47 48 48 48 48 48 48 50 50 50 52 52 52 52 53 53 53 53 53 54 54 55 55 55 56 56 56 56 56 56 56 56 56 57 57 58 58 58 58 58 58 59 59 60 60 60 60 61 61 61 61 61 63 63 63 63 65 66 66 66 67 67 67 68 69 69 69 70 70 70 72 71 72 71 71 71 72 72 72 72 72 74 74 74 75 75 75 75 75 76 77 78 79 79 83 84 84 84 85 85 87 88 89 89 89 91 91 91 91 92 92 92 93 94 94 94 94 95 95 95 95 95 95 96 96 96 96 96 99 99 99 99 99 99 99 99 99 99 99 99 99 99 99 101 102 102 102 102 102 103 104 107 107 109 109 109 109 109 110 109 109 110 110 110 111 111 112 112 113 113 113 113 113 113 113 113 114 114 115 115 115 115 116 118 120 120 120 120 120 120 122 124 124 124 124 126 127 127 127 127 127 127 128 128 129 129 129 130 133 133 134 135 135 137 137 141 146 146 146 146 148 148 150 150 150 150 151 151 155 155 156 156 157 159 160 162 166 171 171 171 174 174 174 174 176 176 176 176 177 177 177 179 180 180 180 180 180 180 181 181 181 182 182 182 184 184 184 185 185 185 185 185 185 186 186 187 188 188 189 191 191 195 196 198 200 204 205 206 207 207 207 208 209 209 209 209 209 211 211 211 211 213 213 216 216 216 216 217 217 217 217 217 218 221 223 226 227 227 227 229 229 230 230 230 232 232 233 234 234 236 236 235 236 239 239 238 239 239 239 240 240 241 241 241 242 246 246 246 246 246 248 248 250 250 250 251 251 251 251 253 254 254 254 254 255 256 257 257 257 260 260 260 260 262 263 263 263 263 264 264 264 264 267 268 268 268 268 269 269 269 269 269 273 273 273 274 275 275 276 278 278 279 279 279 285 288 289 289 290 291 291 296 300 300 300 300 300 301 303 305 306 307 308 308 308 308 309 310 310 312 317 320 321 321 321 325 325 325 325 327 328 328 328 333 334 334 334 337 338 339 339 341 341 344 348 348 348 348 355 355 358 362 362 365 365 367 367 368 370 370 374 374 376 377 378 380 381 381 381 381 381 381 381 381 382 385 386 391 391 391 392 394 394 394 398 398 398 397 399 401 402 405 410 413 414 414 418 419 419 422 422 423 423 424 425 425 425 425 425 425 425 425 424 429 429 430 430 431 433 436 436 436 436 437 438 438 441 441 446 446 446 446 448 448 450 450 453 457 462 464 464 465 467 467 468 468 468 469 473 473 473 474 474 473 475 476 476 480 483 483 484 489 489 489 493 498 498 498 501 503 503 503 505 505 508 508 511 511 512 512 513 513 513 521 526 527 531 531 531 533 533 533 537 537 544 544 548 549 549 549 549 549 552 552 555 556 556 558 558 558 562 564 564 566 566 566 566 566 572 572 574 574 574 575 580 580 582 583 586 589 589 589 593 594 594 599 599 601 604 612 613 613 615 615 615 617 620 625 625 625 625 629 630 630 631 633 633 633 635 637 638 637 640 642 647 654 659 659 663 663 663 664 664 667 668 673 675 676 678 680 686 687 691 695 697 703 705 706 707 707 712 715 717 717 717 717 719 719 721 724 726 726 732 736 739 739 740 742 743 749 749 751 752 752 752 756 756 756 756 756 756 759 764 767 770 772 773 776 776 780 782 782 782 782 782 782 783 784 791 792 796 796 797 801 804 807 813 814 815 816 815 815 816 821 824 831 833 833 833 838 841 842 842 843 843 843 846 846 846 852 852 852 859 859 862 865 867 870 874 878 878 878 878 881 881 882 882 883 890 890 892 894 895 899 901 902 908 920 922 925 928 933 933 937 937 938 942 944 944 949 953 958 958 959 965 971 972 971 973 973 973 977 982 982 982 982 984 987 994 994 999 999 1001 1001 1003 1005 1007 1007 1007 1009 1016 1023 1027 1030 1036 1043 1048 1051 1056 1058 1059 1060 1068 1072 1073 1076 1077 1081 1088 1088 1091 1091 1096 1096 1105 1108 1107 1107 1108 1111 1111 1111 1111 1111 1119 1125 1125 1127 1133 1134 1142 1144 1144 1144 1144 1150 1150 1150 1150 1159 1164 1167 1173 1173 1177 1177 1180 1182 1184 1184 1185 1188 1194 1194 1196 1205 1212 1212 1212 1217 1219 1223 1231 1231 1231 1233 1236 1236 1241 1244 1251 1253 1257 1260 1260 1265 1265 1265 1265 1268 1268 1268 1268 1268 1277 1277 1277 1281 1283 1283 1288 1288 1288 1288 1300 1311 1311 1323 1328 1329 1331 1334 1337 1338 1344 1345 1348 1359 1367 1369 1375 1376 1383 1392 1392 1397 1397 1397 1401 1401 1410 1417 1422 1429 1433 1442 1446 1448 1449 1452 1454 1455 1465 1465 1477 1479 1479 1479 1479 1487 1498 1498 1508 1512 1518 1518 1523 1525 1528 1538 1540 1545 1546 1549 1557 1557 1557 1559 1559 1562 1562 1567 1578 1578 1579 1582 1582 1582 1582 1589 1601 1603 1603 1608 1608 1610 1611 1616 1619 1619 1621 1623 1628 1634 1639 1639 1639 1639 1646 1646 1646 1649 1649 1649 1651 1655 1655 1659 1665 1670 1671 1671 1677 1682 1682 1687 1694 1702 1706 1706 1709 1709 1709 1709 1709 1712 1713 1713 1714 1714 1714 1714 1722 1729 1739 1744 1749 1753 1756 1764 1764 1764 1764 1766 1773 1776 1776 1777 1787 1800 1800 1812 1820 1820 1825 1830 1834 1834 1834 1834 1835 1844 1852 1852 1862 1863 1870 1874 1887 1893 1893 1896 1896 1901 1903 1911 1921 1925 1925 1936 1939 1939 1939 1946 1953 1953 1962 1964 1966 1969 1978 1983 1992 2000 2005 2012 2015 2017 2022 2022 2029 2035 2039 2048 2056 2056 2062 2067 2070 2070 2072 2072 2072 2072 2072 2072 2080 2086 2086 2086 2086 2087 2095 2103 2106 2106 2106 2111 2121 2121 2125 2125 2134 2139 2139 2142 2142 2142 2150 2151 2151 2161 2166 2172 2179 2188 2193 2193 2197 2207 2219 2219 2219 2224 2224 2224 2231 2242 2249 2250 2251 2258 2258 2264 2266 2282 2292 2300 2307 2316 2324 2333 2333 2337 2355 2368 2368 2371 2371 2371 2371 2373 2373 2379 2379 2379 2379 2387 2397 2405 2407 2408 2408 2411 2418 2418 2420 2432 2446 2446 2448 2459 2464 2464 2464 2464 2473 2473 2475 2477 2483 2503 2517 2522 2532 2535 2542 2547 2547 2547 2554 2554 2567 2567 2572 2574 2581 2588 2599 2606 2606 2609 2613 2617 2621 2622 2622 2623 2632 2638 2638 2640 2640 2640 2650 2659 2659 2659 2661 2661 2661 2666 2666 2676 2676 2676 2688 2688 2688 2698 2717 2723 2726 2726 2726 2726 2741 2741 2745 2745 2745 2753 2758 2756 2760 2762 2766 2775 2777 2780 2780 2780 2780 2780 2799 2799 2799 2798 2812 2827 2840 2845 2845 2845 2854 2854 2864 2879 2886 2886 2886 2903 2919 2921 2930 2952 2953 2953 2955 2971 2971 2982 2982 2982 2982 2990 3005 3020 3031 3043 3052 3052 3066 3067 3084 3088 3088 3099 3099 3099 3099 3114 3114 3119 3125 3125 3125 3134 3142 3155 3155 3166 3166 3183 3190 3190 3190 3198 3204 3204 3204 3204 3224 3232 3232 3230 3236 3254 3271 3271 3274 3283 3292 3297 3298 3315 3334 3338 3339 3348 3350 3360 3364 3371 3379 3379 3392 3395 3404 3404 3408 3408 3415 3431 3445 3445 3449 3459 3459 3473 3484 3493 3499 3499 3499 3499 3499 3502 3506 3506 3510 3526 3529 3541 3550 3553 3553 3559 3559 3560 3560 3575 3574 3582 3591 3605 3605 3620 3620 3620 3625 3625 3634 3634 3634 3636 3636 3636 3639 3639 3639 3639 3639 3639 3639 3654 3660 3666 3666 3669 3669 3682 3682 3682 3692 3696 3696 3710 3710 3711 3711 3719 3719 3728 3735 3735 3743 3746 3758 3774 3774 3776 3776 3784 3784 3784 3784 3796 3796 3809 3809 3809 3816 3816 3816 3828 3828 3840 3840 3840 3840 3862 3862 3866 3874 3876 3876 3894 3903 3913 3919 3928 3928 3928 3939 3944 3949 3950 3950 3971 3971 3971 3981 3994 3994 3994 3995 3999 4017 4022 4022 4022 4030 4042 4047 4059 4059 4076 4087 4094 4109 4126 4133 4133 4158 4158 4158 4160 4160 4170 4182 4183 4193 4195 4219 4233 4233 4246 4246 4262 4262 4275 4275 4275 4280 4282 4295 4295 4301 4301 4308 4311 4311 4314 4314 4314 4329 4329 4329 4329 4329 4348 4363 4387 4397 4397 4417 4417 4417 4424 4438 4444 4450 4450 4451 4451 4472 4472 4484 4513 4525 4525 4538 4538 4538 4555 4561 4582 4597 4597 4611 4611 4628 4652 4661 4663 4677 4683 4684 4706 4713 4724 4727 4737 4737 4737 4737 4742 4757 4757 4779 4796 4820 4837 4848 4848 4849 4857 4857 4857 4876 4876 4902 4902 4918 4954 4967 4981 5005 5009 5033 5044 5061 5092 5113 5113 5115 5115 5117 5138 5154 5154 5170 5170 5171 5186 5204 5208 5215 5238 5252 5252 5261 5261 5261 5281 5281 5281 5284 5284 5294 5306 5306 5330 5344 5344 5351 5351 5375 5384 5387 5412 5433 5436 5447 5447 5460 5470 5470 5478 5491 5491 5506 5536 5553 5564 5590 5611 5613 5613 5613 5616 5616 5617 5617 5620 5620 5651 5661 5685 5685 5699 5699 5699 5751 5751 5751 5751 5751 5751 5751 5751 5759 5763 5763 5785 5801 5801 5801 5801 5801 5801 5809 5809 5827 5852 5852 5873 5873 5887 5905 5905 5912 5912 5925 5931 5956 5962 6000 6000 6014 6033 6033 6033 6033 6033 6054 6054 6054 6073 6073 6073 6073 6079 6091 6091 6102 6102 6111 6111 6111 6112 6114 6114 6114 6114 6114 6135 6138 6154 6154 6154 6154 6175 6179 6214 6214 6214 6222 6222 6222 6246 6246 6246 6246 6246 6265 6280 6303 6334 6342 6353 6371 6389 6391 6405 6405 6411 6428 6448 6488 6504 6504 6514 6521 6521 6521 6547 6547 6552 6571 6571 6571 6571 6597 6606 6606 6620 6629 6629 6629 6629 6635 6635 6635 6674 6700 6718 6718 6718 6743 6764 6764 6782 6800 6810 6828 6835 6835 6859 6873 6873 6873 6901 6933 6933 6934 6952 6952 6973 6973 6985 6993 6993 7033 7036 7042 7059 7059 7072 7084 7089 7099 7127 7127 7127 7134 7134 7145 7145 7179 7202 7206 7211 7228 7256 7279 7279 7279 7285 7290 7290 7332 7345 7360 7383 7406 7406 7414 7414 7434 7435 7445 7445 7468 7468 7468 7498 7501 7511 7518 7523 7535 7590 7603 7638 7670 7670 7670 7700 7703 7725 7747 7747 7765 7765 7807 7817 7843 7865 7879 7895 7924 7943 7966 7966 8012 8012 8039 8046 8050 8071 8075 8104 8104 8104 8104 8104 8127 8136 8156 8180 8203 8224 8231 8232 8242 8242 8262 8262 8262 8266 8266 8266 8270 8270 8292 8292 8292 8292 8292 8302 8316 8316 8329 8329 8331 8345 8345 8345 8352 8388 8388 8412 8445 8489 8516 8523 8523 8523 8546 8559 8559 8559 8579 8579 8589 8589 8595 8595 8597 8605 8605 8610 8610 8630 8630 8636 8664 8664 8684 8691 8691 8691 8725 8757 8757 8757 8784 8784 8784 8808 8837 8837 8837 8879 8901 8907 8918 8918 8934 8944 8951 8968 8968 8974 8984 9000 9000 9043 9058 9065 9098 9098 9098 9098 9119 9119 9140 9148 9157 9157 9172 9192 9192 9194 9200 9231 9231 9254 9254 9266 9266 9266 9266 9281 9281 9281 9296 9296 9308 9319 9357 9357 9357 9388 9406 9416 9439 9443 9443 9487 9487 9487 9503 9503 9531 9531 9576 9619 9647 9647 9664 9670 9706 9706 9706 9717 9717 9747 9747 9781 9796 9796 9796 9811 9817 9836 9859 9859 9859 9880 9880 9886 9886 9909 9909 9915 9915 9921 9953 9953 9983 9983 10016 10028 10028 10028 10032 10032 10074 10093 10093 10115 10146 10167 10187 10213 10213 10213 10214 10214 10214 10214 10214 10232 10253 10253 10271 10284 10293 10293 10293 10293 10293 10305 10305 10305 10306 10306 10334 10381 10396 10396 10411 10411 10449 10449 10449 10449 10449 10489 10511 10534 10534 10540 10545 10545 10550 10550 10572 10579 10579 10579 10580 10618 10643 10691 10691 10691 10695 10700 10700 10700 10700 10738 10738 10765 10765 10765 10786 10786 10795 10837 10867 10892 10930 10958 10958 10958 10958 10998 10998 10998 11027 11059 11065 11065 11071 11071 11074 11074 11074 11122 11122 11122 11122 11122 11136 11136 11136 11136 11139 11139 11150 11150 11174 11211 11214 11214 11229 11244 11244 11266 11281 11281 11304 11322 11322 11322 11322 11322 11325 11342 11359 11359 11374 11375 11413 11413 11429 11429 11429 11429 11467 11467 11467 11467 11467 11498 11541 11582 11582 11582 11613 11613 11613 11613 11613 11613 11613 11613 11622 11622 11653 11681 11685 11694 11694 11694 11694 11694 11713 11713 11713 11713 11713 11726 11726 11726 11726 11747 11761 11761 11761 11761 11771 11793 11793 11793 11793 11814 11814 11814 11814 11840 11851 11860 11882 11886 11890 11890 11901 11916 11916 11916 11918 11918 11948 11963 11966 11980 12022 12022 12057 12057 12062 12062 12098 12098 12098 12111 12111 12111 12148 12154 12162 12162 12162 12162 12162 12200 12208 12215 12247 12247 12247 12247 12247 12256 12256 12256 12286 12325 12357 12357 12357 12357 12378 12384 12384 12402 12402 12446 12446 12509 12509 12551 12551 12562 12564 12564 12586 12587 12600 12600 12600 12626 12664 12676 12707 12727 12742 12744 12750 12750 12750 12750 12775 12775 12775 12775 12794 12810 12810 12810 12830 12830 12846 12872 12872 12872 12920 12920 12930 12930 12966 12982 12982 12982 12982 12982 12982 12982 13031 13032 13032 13032 13049 13053 13101 13101 13124 13138 13138 13145 13145 13148 13148 13180 13204 13224 13237 13237 13237 13237 13237 13237 13237 13250 13297 13320 13320 13358 13375 13375 13375 13375 13375 13396 13396 13415 13435 13435 13435 13435 13443 13443 13443 13474 13474 13508 13521 13542 13542 13548 13548 13548 13548 13552 13552 13582 13582 13582 13582 13582 13582 13626 13652 13665 13665 13698 13698 13698 13698 13720 13720 13776 13816 13857 13857 13860 13860 13860 13890 13890 13918 13918 13918 13940 13946 13993 13999 13999 14028 14028 14051 14051 14060 14060 14079 14079 14107 14107 14107 14107 14146 14146 14177 14188 14213 14213 14237 14237 14245 14245 14272 14293 14310 14310 14310 14310 14310 14310 14329 14350 14360 14360 14360 14360 14360 14377 14399 14419 14419 14419 14461 14461 14461 14461 14461 14461 14468 14468 14474 14474 14474 14474 14488 14510 14518 14518 14568 14574 14574 14588 14588 14610 14655 14672 14700 14700 14700 14704 14704 14741 14741 14746 14746 14746 14765 14765 14800 14800 14800 14809 14815 14815 14835 14835 14869 14869 14869 14898 14904 14913 14913 14930 14957 14978 15009 15039 15039 15039 15039 15039 15056 15074 15074 15115 15148 15184 15210 15210 15210 15210 15228 15230 15230 15261 15272 15291 15314 15330 15366 15366 15366 15366 15366 15366 15366 15366 15389 15389 15400 15400 15450 15450 15484 15510 15558 15558 15558 15568 15604 15650 15688 15707 15707 15712 15727 15727 15739 15773 15782 15815 15815 15877 15877 15877 15877 15877 15892 15892 15892 15892 15892 15892 15900 15900 15908 15934 15934 15968 15968 15968 15978 16022 16032 16032 16042 16062 16062 16065 16088 16088 16088 16093 16093 16119 16122 16138 16168 16168 16168 16186 16208 16208 16208 16231 16244 16244 16259 16262 16262 16269 16299 16330 16330 16336 16336 16340 16340 16347 16383 16402 16417 16429 16429 16433 16450 16450 16450 16450 16458 16483 16483 16483 16499 16512 16512 16512 16512 16514 16514 16529 16553 16561 16571 16571 16571 16599 16599 16623 16623 16623 16648 16670 16670 16675 16687 16687 16687 16717 16717 16717 16761 16764 16764 16764 16802 16802 16838 16838 16838 16838 16861 16861 16861 16893 16893 16893 16919 16938 16968 16968 16968 16968 17000 17000 17014 17035 17050 17064 17064 17064 17064 17064 17064 17064 17100 17100 17113 17113 17113 17113 17124 17124 17138 17139 17140 17167 17167 17169 17172 17186 17186 17190 17203 17203 17203 17225 17230 17230 17230 17256 17256 17317 17366 17397 17397 17397 17403 17423 17449 17480 17483 17483 17496 17525 17545 17545 17583 17583 17596 17605 17615 17615 17615 17655 17655 17662 17679 17692 17692 17731 17731 17752 17763 17804 17808 17808 17808 17808 17808 17808 17808 17823 17823 17823 17834 17835 17835 17844 17844 17844 17868 17902 17902 17902 17921 17921 17946 17952 17952 17965 17965 17989 18017 18049 18076 18083 18115 18115 18115 18115 18122 18122 18153 18164 18173 18173 18196 18215 18215 18255 18255 18295 18325 18335 18335 18335 18335 18335 18377 18377 18381 18388 18388 18388 18401 18401 18401 18401 18401 18439 18478 18478 18494 18494 18523 18571 18571 18571 18583 18583 18583 18586 18611 18611 18613 18613 18613 18650 18650 18650 18689 18692 18692 18706 18706 18724 18739 18769 18769 18769 18769 18802 18843 18858 18858 18858 18858 18885 18885 18905 18905 18906 18907 18907 18911 18911 18911 18930 18939 18975 18975 18975 19004 19017 19017 19017 19023 19023 19048 19048 19048 19048 19048 19062 19062 19062 19062 19062 19062 19069 19074 19074 19080 19086 19086 19094 19094 19109 19125 19168 19205 19205 19205 19205 19214 19214 19219 19219 19219 19219 19247 19262 19262 19262 19282 19297 19313 19313 19321 19321 19321 19321 19358 19398 19398 19401 19401 19401 19401 19405 19438 19462 19462 19462 19468 19468 19495 19495 19504 19504 19504 19504 19504 19504 19527 19527 19527 19552 19552 19552 19575 19589 19589 19589 19589 19592 19614 19644 19644 19644 19664 19668 19699 19742 19742 19742 19787 19787 19808 19808 19809 19809 19829 19829 19852 19873 19873 19873 19876 19891 19891 19891 19891 19920 19920 19962 20004 20012 20028 20028 20050 20050 20057 20091 20091 20091 20117 20126 20180 20180 20182 20182 20182 20215 20215 20215 20225 20237 20269 20278 20319 20319 20331 20340 20369 20391 20412 20431 20431 20455 20455 20470 20486 20486 20486 20486 20486 20486 20509 20509 20509 20517 20534 20534 20534 20537 20537 20537 20537 20537 20553 20553 20568 20568 20572 20599 20618 20618 20618 20644 20644 20674 20674 20683 20684 20709 20709 20709 20709 20709 20709 20725 20725 20725 20725 20745 20771 20771 20771 20784 20804 20804 20830 20861 20873 20873 20873 20873 20873 20873 20918 20927 20949 20949 20954 20975 20981 20989 20989 20989 21025 21037 21055 21077 21111 21123 21127 21127 21127 21159 21163 21179 21179 21184 21200 21200 21217 21218 21218 21218 21239 21252 21252 21271 21282 21282 21309 21324 21324 21355 21355 21362 21363 21376 21386 21386 21386 21413 21464 21490 21526 21534 21534 21534 21534 21534 21555 21555 21555 21555 21555 21598 21598 21604 21647 21647 21656 21656 21687 21687 21687 21713 21720 21720 21720 21720 21720 21720 21747 21747 21747 21747 21750 21750 21750 21755 21767 21783 21806 21813 21820 21835 21851 21851 21851 21883 21883 21887 21887 21899 21916 21916 21951 21965 22004 22008 22008 22035 22040 22066 22099 22099 22138 22138 22138 22149 22149 22149 22149 22149 22149 22166 22166 22186 22186 22186 22186 22186 22186 22186 22185 22199 22199 22216 22235 22235 22242 22242 22242 22242 22242 22242 22264 22283 22339 22339 22339 22348 22355 22355 22355 22355 22355 22387 22387 22387 22420 22420 22420 22440 22440 22440 22440 22440 22442 22447 22447 22451 22493 22493 22517 22517 22517 22517 22517 22517 22559 22559 22592 22606 22617 22617 22617 22617 22617 22617 22617 22638 22659 22659 22659 22689 22689 22730 22741 22741 22757 22790 22790 22790 22796 22827 22827 22827 22870 22880 22889 22940 22961 22961 22988 22988 22988 23018 23033 23051 23051 23078 23102 23102 23102 23102 23105 23123 23123 23123 23149 23174 23177 23177 23177 23201 23201 23231 23231 23231 23231 23231 23231 23250 23268 23276 23276 23309 23345 23345 23367 23367 23367 23388 23407 23407 23407 23450 23450 23450 23489 23517 23538 23538 23538 23581 23581 23584 23626 23626 23626 23626 23632 23632 23636 23636 23636 23641 23641 23641 23652 23673 23682 23682 23682 23682 23701 23701 23701 23701 23719 23719 23742 23742 23742 23776 23776 23776 23776 23776 23776 23776 23775 23775 23775 23818 23834 23851 23851 23851 23851 23851 23851 23851 23880 23886 23933 23936 23936 23936 23954 23954 23964 23964 23964 23964 23970 23970 23994 24012 24043 24043 24081 24081 24081 24094 24094 24094 24109 24109 24118 24128 24158 24158 24158 24177 24177 24197 24197 24197 24228 24228 24228 24226 24226 24226 24226 24239 24239 24242 24266 24279 24286 24286 24325 24339 24362 24362 24369 24369 24369 24369 24370 24392 24392 24394 24394 24405 24434 24434 24434 24458 24494 24508 24525 24525 24525 24535 24535 24535 24535 24535 24535 24546 24572 24590 24590 24590 24612 24621 24621 24621 24621 24657 24657 24666 24676 24678 24678 24697 24697 24697 24712 24712 24755 24755 24765 24765 24765 24779 24807 24823 24835 24835 24835 24835 24835 24848 24859 24898 24927 24930 24930 24954 24954 24954 24954 24954 24954 24954 24954 24954 24954 24954 24978 24978 24978 24978 24978 24978 24990 24991 24991 24993 25006 25006 25012 25031 25031 25031 25042 25059 25059 25064 25064 25076 25076 25107 25107 25107 25107 25107 25107 25107 25107 25110 25110 25129 25129 25144 25154 25193 25199 25199 25198 25198 25198 25215 25215 25215 25215 25215 25248 25269 25269 25269 25269 25269 25269 25269 25292 25292 25292 25313 25348 25348 25371 25379 25379 25379 25379 25379 25388 25389 25426 25432 25459 25459 25459 25466 25479 25507 25516 25516 25516 25516 25534 25534 25534 25541 25541 25541 25563 25583 25589 25589 25618 25630 25630 25630 25630 25630 25641 25641 25647 25647 25647 25647 25647 25664 25696 25696 25702 25710 25710 25710 25710 25710 25710 25732 25732 25732 25740 25758 25758 25758 25758 25780 25805 25805 25811 25811 25843 25843 25843 25855 25867 25867 25893 25914 25914 25914 25928 25958 25958 25958 25958 25980 25980 25980 25980 25980 25993 25993 25993 26016 26042 26042 26066 26070 26100 26100 26100 26124 26124 26124 26124 26135 26135 26135 26140 26140 26140 26140 26148 26148 26148 26173 26173 26173 26173 26173 26173 26187 26187 26187 26187 26189 26201 26201 26201 26207 26207 26226 26226 26226 26226 26226 26239 26263 26263 26263 26286 26297 26297 26308 26308 26308 26308 26308 26308 26311 26311 26311 26327 26327 26353 26353 26383 26398 26398 26398 26398 26398 26401 26417 26417 26425 26425 26425 26425 26425 26425 26425 26446 26448 26459 26480 26480 26480 26480 26490 26490 26490 26510 26519 26519 26527 26527 26527 26548 26548 26548 26548 26570 26620 26626 26647 26654 26679 26679 26679 26679 26704 26704 26704 26704 26716 26730 26739 26743 26758 26758 26758 26774 26778 26778 26778 26788 26815 26837 26837 26837 26841 26852 26852 26852 26859 26859 26893 26893 26893 26893 26893 26893 26922 26922 26931 26931 26931 26950 26951 26951 26960 26960 26960 26960 26960 26960 26960 26960 26960 26960 26987 26987 26987 26987 27003 27003 27015 27027 27027 27027 27027 27027 27050 27050 27066 27066 27066 27077 27077 27077 27077 27077 27087 27120 27136 27136 27172 27171 27171 27171 27171 27171 27177 27177 27177 27181 27206 27206 27209 27209 27209 27222 27222 27245 27281 27281 27281 27281 27281 27281 27281 27281 27287 27287 27288 27288 27305 27305 27305 27326 27326 27326 27328 27328 27328 27328 27328 27328 27333 27333 27333 27333 27333 27333 27333 27333 27333 27333 27334 27360 27360 27360 27383 27383 27383 27383 27383 27391 27391 27391 27391 27423 27423 27424 27424 27424 27424 27424 27425 27430 27430 27430 27430 27453 27453 27453 27453 27460 27466 27466 27466 27481 27481 27481 27481 27507 27507 27507 27533 27533 27533 27561 27561 27566 27588 27604 27611 27611 27614 27614 27614 27627 27650 27665 27665 27665 27666 27666 27676 27676 27683 27683 27684 27684 27684 27686 27689 27689 27706 27706 27720 27720 27720 27720 27720 27762 27780 27780 27785 27785 27785 27800 27800 27800 27800 27800 27808 27808 27808 27808 27808 27813 27829 27842 27859 27897 27897 27909 27917 27917 27927 27927 27927 27933 27942 27942 27942 27942 27942 27942 27959 27959 27959 27959 27975 27975 28009 28019 28019 28032 28036 28049 28052 28052 28052 28061 28061 28061 28061 28061 28061 28065 28068 28075 28091 28091 28091 28129 28142 28151 28151 28152 28165 28165 28165 28165 28165 28165 28165 28180 28185 28185 28185 28185 28185 28185 28185 28185 28185 28185 28187 28192 28192 28192 28192 28218 28218 28218 28218 28218 28218 28239 28239 28239 28239 28247 28247 28247 28247 28250 28250 28250 28264 28264 28264 28289 28289 28289 28299 28299 28299 28299 28299 28305 28313 28314 28321 28359 28376 28403 28411 28411 28411 28411 28433 28433 28442 28462 28462 28479 28489 28508 28524 28524 28524 28529 28531 28535 28535 28547 28547 28585 28585 28585 28610 28610 28610 28610 28611 28611 28611 28635 28640 28638 28638 28644 28644 28644 28656 28656 28667 28667 28667 28667 28667 28676 28676 28676 28676 28687 28709 28709 28709 28709 28716 28716 28716 28746 28756 28753 28753 28776 28792 28792 28808 28808 28808 28808 28808 28808 28808 28813 28813 28813 28813 28813 28813 28832 28832 28832 28832 28832 28832 28832 28832 28851 28851 28869 28869 28881 28881 28881 28914 28920 28921 28921 28921 28921 28921 28933 28933 28933 28933 28933 28933 28933 28943 28945 28947 28947 28947 28976 28976 29015 29015 29015 29021 29032 29032 29035 29035 29039 29039 29037 29037 29037 29043 29043 29047 29066 29066 29066 29072 29072 29072 29077 29077 29077 29077 29100 29100 29110 29110 29110 29110 29110 29110 29110 29128 29132 29132 29132 29132 29136 29141 29141 29145 29145 29145 29145 29169 29170 29170 29188 29188 29188 29204 29213 29239 29239 29249 29255 29255 29276 29276 29276 29287 29287 29287 29287 29297 29297 29297 29297 29299 29299 29299 29307 29317 29317 29320 29326 29326 29344 29344 29357 29370 29379 29379 29379 29379 29379 29379 29399 29414 29414 29414 29419 29420 29420 29421 29421 29421 29421 29427 29427 29432 29436 29436 29460 29472 29472 29472 29472 29472 29472 29474 29474 29497 29497 29497 29497 29497 29497 29497 29501 29501 29501 29501 29501 29501 29501 29517 29517 29516 29516 29516 29516 29516 29516 29519 29519 29519 29522 29541 29541 29541 29575 29575 29582 29582 29582 29609 29609 29609 29609 29609 29621 29623 29631 29631 29631 29642 29642 29642 29642 29648 29653 29653 29653 29653 29653 29653 29653 29653 29653 29660 29660 29660 29660 29660 29672 29672 29672 29672 29672 29672 29671 29671 29680 29680 29680 29680 29687 29716 29716 29716 29726 29726 29726 29726 29726 29726 29726 29726 29726 29726 29755 29755 29755 29755 29764 29764 29764 29764 29764 29764 29766 29766 29766 29767 29785 29791 29798 29810 29817 29819 29820 29820 29820 29820 29820 29820 29820 29820 29820 29827 29832 29848 29848 29860 29863 29863 29871 29879 29879 29879 29879 29879 29879 29879 29879 29888 29911 29911 29911 29911 29930 29930 29948 29948 29948 29948 29963 29963 29987 29997 29997 29997 29997 29997 30002 30014 30014 30016 30036 30036 30052 30053 30058 30058 30062 30068 30082 30082 30092 30092 30092 30092 30092 30095 30095 30095 30099 30099 30099 30099 30105 30128 30128 30140 30142 30142 30142 30142 30154 30164 30164 30181 30181 30181 30181 30181 30181 30181 30196 30196 30196 30196 30199 30199 30200 30200 30200 30200 30200 30200 30200 30217 30217 30217 30217 30217 30217 30222 30222 30254 30254 30254 30254 30254 30269 30269 30273 30273 30273 30273 30274 30291 30291 30294 30294 30297 30297 30301 30301 30301 30301 30301 30301 30308 30308 30312 30313 30313 30313 30314 30314 30314 30314 30314 30314 30322 30322 30322 30337 30337 30337 30336 30349 30349 30349 30354 30354 30354 30354 30376 30374 30382 30382 30382 30382 30381 30381 30381 30381 30378 30378 30378 30378 30378 30378 30378 30388 30388 30396 30396 30396 30396 30396 30396 30396 30401 30402 30407 30407 30407 30417 30417 30422 30434 30434 30434 30434 30434 30438 30438 30457 30471 30471 30475 30475 30475 30475 30475 30475 30475 30487 30487 30487 30486 30486 30494 30494 30494 30494 30506 30506 30508 30516 30516 30516 30516 30516 30516 30516 30521 30530 30530 30530 30530 30530 30530 30538 30546 30549 30549 30549 30561 30577 30578 30579 30595 30595 30595 30595 30595 30595 30595 30618 30618 30618 30626 30642 30642 30642 30642 30642 30642 30642 30642 30639 30639 30642 30642 30648 30648 30648 30648 30648 30653 30653 30653 30653 30653 30653 30653 30653 30653 30653 30669 30669 30669 30686 30686 30703 30703 30703 30703 30703 30703 30703 30717 30717 30717 30717 30717 30721 30721 30726 30728 30728 30731 30733 30733 30748 30748 30753 30753 30757 30753 30753 30753 30753 30774 30774 30774 30774 30774 30782 30782 30782 30782 30782 30782 30782 30786 30782 30775 30777 30777 30777 30785 30785 30785 30787 30803 30803 30815 30823 30840 30846 30853 30853 30855 30855 30855 30855 30865 30865 30865 30865 30865 30869 30869 30869 30869 30869 30869 30880 30887 30887 30886 30886 30892 30892 30892 30892 30892 30892 30892 30892 30892 30892 30892 30895 30905 30917 30938 30959 30959 30969 30972 30973 30973 30973 30973 30973 30973 30973 30973 30973 30973 30976 30986 30991 30991 30991 30996 30996 30996 30996 30999 30999 30999 30999 30999 31005 31005 31010 31010 31010 31010 31010 31010 31010 31026 31026 31026 31029 31029 31029 31029 31029 31029 31029 31029 31029 31028 31028 31030 31030 31030 31030 31030 31030 31051 31051 31051 31052 31052 31052 31052 31048 31048 31078 31092 31110 31110 31119 31123 31123 31129 31134 31134 31134 31134 31150 31150 31154 31154 31166 31178 31189 31197 31197 31197 31213 31213 31213 31213 31213 31217 31231 31231 31224 31224 31224 31227 31249 31249 31252 31248 31248 31255 31260 31260 31260 31260 31260 31260 31260 31260 31260 31280 31280 31280 31280 31300 31300 31300 31300 31304 31304 31318 31318 31318 31318 31318 31318 31315 31315 31328 31331 31331 31331 31339 31339 31339 31349 31349 31349 31349 31349 31349 31348 31358 31358 31358 31358 31358 31358 31358 31358 31358 31358 31361 31370 31370 31370 31370 31370 31375 31380 31384 31389 31389 31389 31389 31389 31389 31389 31392 31392 31392 31392 31398 31398 31398 31398 31398 31398 31409 31419 31419 31423 31425 31425 31430 31437 31450 31460 31460 31460 31460 31460 31460 31458 31456 31455 31455 31455 31460 31460 31460 31478 31481 31480 31480 31480 31498 31498 31498 31498 31498 31498 31500 31500 31500 31514 31514 31517 31517 31517 31517 31517 31517 31517 31517 31543 31558 31558 31558 31561 31561 31561 31561 31561 31561 31584 31606 31606 31606 31606 31606 31605 31605 31608 31612 31612 31612 31616 31617 31624 31630 31644 31638 31638 31638 31638 31640 31640 31640 31640 31640 31640 31640 31640 31637 31638 31637 31637 31644 31640 31655 31647 31659 31659 31659 31659 31659 31661 31661 31661 31661 31661 31661 31661 31661 31669 31669 31669 31665 31665 31665 31665 31667 31667 31670 31670 31670 31670 31670 31670 31670 31670 31670 31670 31674 31674 31674 31674 31687 31687 31687 31691 31691 31691 31698 31702 31702 31702 31702 31702 31702 31702 31702 31702 31706 31725 31732 31732 31745 31758 31758 31758 31765 31765 31765 31779 31779 31779 31779 31779 31779 31779 31779 31779 31779 31779 31779 31794 31794 31794 31794 31794 31794 31794 31794 31794 31798 31803 31803 31803 31803 31803 31803 31803 31803 31801 31801 31801 31801 31801 31801 31801 31802 31810 31810 31810 31810 31827 31841 31843 31843 31843 31840 31840 31840 31840 31844 31844 31844 31843 31845 31845 31845 31854 31854 31854 31854 31854 31866 31866 31866 31866 31866 31866 31866 31866 31866 31866 31869 31881 31878 31877 31877 31877 31877 31877 31877 31877 31877 31877 31878 31878 31878 31885 31895 31896 31896 31889 31889 31889 31893 31893 31894 31894 31894 31900 31900 31900 31900 31906 31906 31915 31908 31908 31917 31917 31914 31914 31914 31912 31912 31912 31912 31912 31912 31912 31929 31929 31929 31929 31929 31929 31929 31929 31929 31929 31929 31929 31929 31929 31930 31930 31938 31938 31938 31938 31938 31938 31938 31938 31938 31938 31946 31946 31946 31946 31948 31948 31948 31948 31948 31948 31948 31953 31953 31953 31953 31953 31951 31951 31951 31949 31949 31949 31949 31949 31952 31952 31952 31952 31952 31952 31952 31952 31952 31953 31959 31959 31961 31961 31967 31967 31970 31970 31970 31970 31970 31982 31982 31982 31982 31982 31982 31982 31982 31982 31976 31976 31976 31977 31977 31977 31977 31980 31987 31987 31998 31998 31998 31998 31996 31996 31996 31996 31996 32004 32004 32006 32006 32006 32006 32006 32006 32006 32006 32006 32006 32006 32009 32009 32026 32026 32031 32041 32041 32041 32041 32041 32041 32041 32042 32042 32042 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32055 32055 32055 32055 32055 32055 32055 32055 32058 32058 32058 32072 32072 32072 32071 32071 32071 32071 32071 32071 32084 32092 32092 32092 32092 32092 32092 32092 32093 32093 32093 32094 32094 32094 32094 32094 32094 32107 32107 32109 32111 32111 32111 32111 32111 32111 32116 32114 32114 32114 32114 32117 32117 32121 32127 32134 32134 32134 32135 32152 32152 32152 32152 32152 32152 32154 32154 32154 32154 32154 32154 32154 32154 32154 32154 32154 32154 32154 32154 32154 32161 32161 32161 32177 32177 32180 32180 32180 32180 32180 32180 32180 32180 32180 32180 32188 32177 32177 32176 32176 32176 32176 32175 32175 32175 32174 32174 32174 32174 32174 32171 32175 32176 32177 32177 32177 32181 32177 32177 32203 32203 32203 32203 32212 32212 32212 32212 32206 32206 32206 32206 32206 32206 32206 32208 32208 32208 32208 32208 32208 32208 32208 32208 32215 32216 32216 32216 32219 32219 32219 32222 32222 32222 32224 32224 32224 32226 32226 32226 32226 32226 32226 32230 32230 32235 32235 32235 32236 32236 32236 32236 32236 32236 32236 32236 32236 32236 32236 32236 32249 32249 32249 32249 32249 32249 32249 32251 32263 32263 32263 32263 32264 32264 32264 32264 32264 32253 32253 32253 32254 32254 32261 32264 32264 32264 32264 32264 32264 32264 32266 32266 32267 32267 32272 32286 32286 32286 32286 32286 32286 32286 32286 32286 32288 32288 32296 32296 32297 32297 32297 32297 32297 32298 32298 32298 32298 32298 32303 32300 32310 32314 32314 32314 32314 32314 32314 32314 32314 32314 32314 32314 32314 32308 32308 32308 32308 32308 32308 32308 32324 32324 32326 32326 32326 32326 32326 32334 32338 32341 32341 32341 32341 32344 32344 32347 32347 32348 32348 32348 32359 32359 32359 32359 32359 32359 32359 32366 32367 32367 32367 32367 32367 32367 32365 32365 32365 32364 32364 32364 32364 32364 32364 32364 32364 32364 32363 32363 32364 32360 32362 32362 32362 32362 32363 32363 32363 32363 32363 32363 32365 32365 32365 32365 32365 32349 32349 32349 32353 32353 32353 32353 32353 32353 32353 32353 32353 32353 32353 32356 32356 32356 32356 32356 32356 32356 32356 32356 32356 32356 32356 32356 32360 32360 32360 32360 32360 32360 32360 32360 32360 32360 32360 32357 32357 32357 32357 32357 32357 32357 32357 32357 32354 32354 32354 32354 32356 32356 32356 32360 32361 32361 32361 32361 32361 32361 32361 32361 32361 32361 32369 32371 32371 32371 32375 32375 32375 32375 32375 32375 32375 32375 32376 32376 32376 32376 32376 32387 32387 32387 32394 32391 32391 32391 32391 32391 32391 32399 32399 32399 32398 32398 32398 32398 32398 32398 32396 32396 32396 32396 32396 32400 32400 32400 32400 32398 32398 32394 32406 32406 32406 32406 32406 32417 32417 32417 32417 32417 32411 32411 32417 32417 32417 32419 32419 32419 32419 32419 32419 32428 32430 32433 32433 32433 32433 32433 32433 32439 32440 32440 32440 32440 32440 32440 32440 32440 32440 32426 32426 32426 32426 32423 32422 32425 32426 32426 32418 32418 32418 32418 32418 32418 32418 32418 32418 32418 32419 32413 32416 32416 32416 32416 32416 32413 32413 32417 32417 32417 32415 32414 32414 32414 32414 32414 32414 32414 32414 32414 32414 32414 32414 32414 32414 32417 32419 32419 32419 32419 32419 32425 32425 32425 32425 32425 32427 32427 32427 32427 32427 32427 32427 32431 32431 32431 32431 32431 32431 32431 32431 32431 32431 32431 32436 32436 32436 32436 32435 32435 32435 32435 32435 32435 32435 32435 32435 32435 32435 32435 32435 32435 32436 32436 32436 32436 32436 32434 32434 32434 32424 32425 32425 32425 32426 32426 32426 32426 32426 32426 32426 32426 32426 32430 32430 32434 32434 32434 32439 32439 32439 32440 32437 32442 32440 32444 32447 32445 32445 32445 32445 32445 32445 32445 32443 32443 32443 32443 32443 32443 32443 32443 32446 32446 32445 32445 32445 32441 32441 32441 32440 32440 32440 32440 32440 32440 32440 32440 32440 32440 32440 32440 32440 32443 32443 32443 32443 32443 32443 32443 32443 32443 32446 32446 32446 32446 32452 32451 32451 32451 32451 32447 32446 32446 32446 32446 32446 32446 32446 32446 32446 32446 32446 32449 32449 32449 32449 32449 32449 32449 32443 32443 32443 32443 32443 32447 32457 32457 32457 32457 32457 32460 32460 32460 32460 32460 32462 32462 32462 32462 32462 32462 32462 32461 32461 32461 32471 32470 32470 32470 32478 32483 32483 32483 32483 32483 32483 32483 32481 32481 32480 32480 32477 32467 32467 32467 32467 32467 32467 32467 32468 32473 32473 32489 32489 32483 32483 32483 32483 32483 32483 32480 32480 32480 32479 32479 32479 32479 32478 32478 32478 32478 32478 32480 32480 32480 32479 32480 32480 32480 32484 32484 32484 32484 32484 32484 32484 32484 32484 32484 32484 32484 32484 32484 32486 32486 32486 32482 32482 32482 32482 32480 32480 32480 32480 32480 32480 32477 32477 32477 32477 32477 32475 32475 32475 32475 32475 32479 32479 32477 32477 32477 32477 32472 32472 32472 32465 32465 32472 32472 32472 32474 32474 32474 32474 32474 32476 32476 32476 32476 32476 32476 32477 32477 32477 32477 32494 32494 32494 32495 32495 32495 32495 32495 32494 32494 32494 32490 32490 32489 32484 32478 32478 32475 32475 32475 32475 32475 32475 32475 32475 32475 32475 32475 32475 32475 32475 32475 32476 32476 32476 32471 32471 32471 32471 32471 32471 32471 32471 32471 32470 32468 32466 32466 32466 32466 32466 32464 32464 32462 32458 32458 32458 32458 32458 32458 32471 32471 32473 32473 32473 32473 32473 32473 32473 32473 32473 32473 32473 32473 32473 32473 32468 32467 32464 32464 32479 32476 32476 32476 32476 32476 32476 32477 32477 32477 32477 32477 32482 32482 32483 32483 32483 32483 32483 32483 32483 32483 32483 32483 32483 32485 32485 32485 32485 32478 32478 32478 32478 32478 32473 32473 32467 32467 32467 32467 32467 32467 32467 32467 32462 32462 32462 32458 32458 32458 32458 32461 32461 32463 32458 32445 32442 32442 32442 32442 32447 32447 32447 32444 32444 32444 32444 32441 32441 32441 32441 32435 32435 32435 32435 32435 32435 32433 32433 32433 32433 32433 32433 32433 32433 32433 32430 32430 32430 32430 32430 32430 32430 32430 32430 32437 32440 32445 32445 32445 32449 32449 32449 32449 32449 32449 32449 32449 32449 32449 32453 32453 32453 32453 32453 32453 32451 32451 32451 32451 32451 32451 32458 32461 32461 32467 32467 32467 32467 32466 32466 32466 32466 32466 32466 32466 32459 32459 32459 32458 32458 32463 32463 32463 32458 32458 32458 32453 32453 32453 32453 32452 32454 32454 32454 32454 32454 32454 32444 32444 32444 32444 32444 32444 32444 32444 32444 32444 32444 32444 32444 32444 32444 32438 32438 32438 32438 32445 32445 32445 32445 32445 32445 32441 32441 32441 32438 32433 32433 32433 32433 32433 32433 32433 32433 32433 32433 32432 32432 32432 32432 32433 32433 32433 32433 32440 32440 32440 32438 32440 32440 32440 32440 32440 32440 32440 32440 32440 32440 32440 32441 32441 32441 32437 32437 32437 32437 32437 32437 32437 32437 32439 32439 32439 32433 32433 32433 32433 32433 32433 32438 32438 32438 32438 32438 32435 32437 32437 32443 32443 32443 32443 32443 32443 32443 32444 32444 32443 32443 32443 32443 32438 32434 32446 32446 32446 32446 32446 32446 32446 32436 32436 32436 32436 32436 32436 32436 32435 32435 32425 32425 32424 32424 32424 32424 32424 32424 32428 32428 32428 32428 32428 32427 32427 32425 32425 32425 32416 32416 32416 32416 32416 32416 32416 32416 32417 32417 32417 32412 32412 32412 32400 32412 32413 32413 32413 32413 32413 32413 32413 32413 32413 32413 32413 32413 32413 32419 32419 32417 32417 32417 32417 32417 32417 32411 32418 32418 32418 32418 32418 32418 32418 32421 32426 32426 32426 32426 32426 32426 32426 32426 32426 32424 32424 32424 32424 32424 32424 32415 32415 32415 32417 32417 32417 32404 32404 32405 32405 32405 32405 32405 32405 32399 32394 32394 32394 32394 32394 32394 32390 32389 32389 32393 32393 32393 32389 32397 32399 32399 32399 32399 32399 32399 32399 32405 32405 32405 32389 32387 32389 32383 32383 32383 32383 32381 32381 32381 32385 32385 32385 32382 32382 32382 32382 32382 32390 32390 32390 32390 32390 32378 32378 32378 32378 32377 32377 32377 32377 32377 32372 32372 32372 32372 32372 32372 32372 32372 32372 32373 32373 32373 32373 32373 32373 32370 32370 32370 32370 32369 32369 32369 32369 32369 32369 32367 32367 32367 32361 32361 32362 32362 32360 32360 32360 32360 32360 32360 32343 32339 32339 32339 32339 32339 32338 32335 32335 32335 32335 32335 32335 32335 32335 32335 32335 32335 32335 32335 32335 32335 32327 32327 32327 32325 32325 32325 32325 32325 32325 32325 32325 32319 32319 32307 32307 32297 32297 32297 32297 32294 32294 32290 32290 32290 32280 32280 32280 32280 32280 32280 32280 32280 32280 32279 32272 32272 32272 32272 32272 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32267 32264 32264 32264 32264 32264 32264 32264 32265 32265 32265 32265 32265 32256 32256 32268 32268 32268 32268 32263 32254 32254 32257 32257 32247 32234 32234 32234 32234 32234 32234 32234 32234 32234 32234 32234 32235 32235 32235 32235 32235 32235 32235 32235 32232 32228 32228 32228 32228 32228 32228 32228 32228 32228 32228 32229 32225 32225 32225 32225 32225 32225 32225 32225 32220 32217 32217 32216 32216 32216 32216 32216 32216 32216 32216 32216 32211 32210 32210 32210 32208 32208 32208 32208 32208 32208 32208 32208 32208 32208 32207 32207 32207 32207 32207 32207 32207 32205 32205 32203 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32202 32203 32203 32203 32203 32203 32203 32202 32198 32198 32198 32198 32198 32198 32200 32200 32200 32200 32200 32200 32200 32200 32200 32196 32186 32186 32186 32186 32186 32186 32186 32182 32182 32182 32181 32181 32181 32181 32171 32171 32171 32171 32171 32171 32170 32170 32170 32170 32159 32159 32159 32159 32161 32161 32161 32161 32161 32161 32161 32161 32161 32155 32155 32155 32155 32155 32157 32154 32154 32151 32140 32140 32140 32140 32139 32127 32127 32126 32126 32126 32126 32126 32126 32126 32126 32126 32126 32126 32129 32129 32129 32129 32123 32123 32123 32123 32123 32123 32123 32124 32124 32124 32124 32124 32124 32116 32113 32111 32109 32101 32100 32101 32092 32092 32085 32085 32088 32088 32084 32084 32084 32081 32081 32081 32079 32079 32076 32076 32068 32068 32068 32063 32063 32063 32063 32061 32057 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32053 32047 32047 32047 32047 32047 32047 32052 32052 32052 32052 32052 32052 32052 32052 32052 32052 32052 32052 32052 32052 32052 32049 32040 32040 32040 32040 32035 32035 32035 32035 32035 32035 32035 32035 32035 32036 32034 32034 32034 32030 32029 32029 32029 32029 32029 32031 32031 32021 32021 32021 32021 32021 32021 32021 32021 32019 32019 32019 32019 32019 32019 32022 32014 32014 32014 32014 32015 32009 32009 32009 32009 32009 32009 32009 32009 32008 32008 32008 32008 31999 31999 32000 32000 32000 32000 31994 31994 31994 31986 31986 31986 31986 31986 31986 31986 31986 31986 31986 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31980 31976 31974 31974 31974 31974 31974 31974 31974 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31962 31948 31948 31948 31948 31948 31938 31938 31938 31938 31930 31930 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31922 31912 31912 31912 31912 31912 31912 31912 31912 31912 31912 31912 31912 31912 31905 31905 31905 31905 31905 31910 31910 31901 31902 31903 31903 31903 31902 31902 31902 31902 31902 31902 31888 31888 31888 31887 31887 31887 31882 31882 31882 31882 31880 31880 31873 31873 31873 31876 31876 31876 31876 31876 31876 31867 31867 31867 31867 31867 31867 31860 31860 31860 31860 31860 31853 31851 31851 31848 31848 31848 31848 31848 31843 31843 31843 31843 31843 31843 31843 31843 31843 31843 31843 31843 31843 31843 31843 31839 31839 31839 31839 31839 31839 31834 31834 31830 31830 31830 31825 31825 31825 31820 31820 31820 31820 31822 31822 31822 31822 31822 31822 31822 31822 31822 31818 31818 31810 31801 31801 31795 31794 31794 31794 31794 31794 31794 31791 31791 31791 31791 31791 31784 31784 31784 31784 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31786 31784 31784 31784 31784 31784 31784 31784 31778 31778 31778 31773 31773 31763 31763 31762 31762 31762 31762 31762 31762 31762 31760 31760 31760 31760 31760 31766 31762 31762 31762 31762 31762 31762 31761 31761 31742 31742 31742 31742 31742 31742 31742 31742 31742 31742 31744 31744 31744 31744 31744 31744 31744 31744 31740 31722 31722 31722 31722 31722 31722 31722 31722 31722 31722 31722 31722 31722 31717 31710 31710 31710 31710 31710 31710 31710 31710 31710 31710 31710 31709 31709 31709 31709 31696 31696 31696 31696 31696 31696 31696 31696 31696 31696 31696 31696 31696 31689 31689 31689 31689 31690 31678 31678 31678 31678 31678 31678 31678 31674 31674 31674 31674 31674 31674 31662 31662 31662 31662 31662 31662 31662 31662 31662 31646 31646 31646 31645 31645 31645 31631 31631 31631 31631 31625 31625 31625 31625 31625 31625 31625 31625 31619 31619 31613 31613 31613 31613 31610 31610 31610 31610 31610 31610 31610 31605 31583 31583 31583 31583 31583 31583 31583 31583 31583 31583 31583 31583 31566 31566 31541 31541 31541 31541 31541 31541 31541 31541 31540 31540 31540 31540 31540 31540 31533 31533 31523 31523 31523 31523 31523 31518 31518 31499 31499 31499 31499 31499 31499 31487 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31486 31483 31483 31483 31483 31478 31478 31478 31478 31478 31478 31478 31478 31478 31469 31469 31469 31469 31469 31469 31469 31469 31469 31458 31458 31458 31458 31457 31457 31457 31457 31457 31457 31457 31457 31457 31459 31459 31459 31459 31459 31459 31459 31459 31459 31459 31459 31459 31450 31450 31450 31450 31450 31450 31450 31450 31450 31450 31450 31448 31448 31446 31431 31431 31431 31417 31417 31417 31417 31417 31417 31417 31417 31417 31410 31410 31410 31410 31401 31383 31383 31383 31362 31362 31362 31362 31362 31362 31362 31362 31362 31362 31362 31362 31362 31362 31355 31355 31355 31355 31355 31355 31355 31358 31358 31358 31357 31357 31357 31357 31357 31357 31357 31355 31355 31355 31355 31355 31355 31355 31355 31355 31351 31353 31338 31338 31338 31338 31338 31338 31338 31338 31338 31338 31338 31338 31338 31338 31324 31324 31324 31324 31324 31324 31324 31325 31318 31318 31318 31318 31318 31318 31318 31318 31318 31313 31309 31309 31309 31309 31309 31309 31309 31309 31309 31309 31309 31309 31310 31310 31310 31310 31310 31310 31310 31310 31310 31288 31288 31288 31288 31288 31288 31288 31288 31288 31267 31267 31267 31267 31267 31267 31267 31267 31267 31267 31256 31256 31252 31240 31240 31240 31240 31240 31240 31240 31240 31240 31242 31242 31240 31240 31240 31240 31240 31240 31240 31240 31240 31240 31240 31240 31240 31240 31225 31225 31225 31225 31225 31225 31225 31225 31225 31225 31218 31207 31207 31207 31207 31207 31205 31205 31205 31196 31196 31196 31196 31196 31196 31196 31196 31186 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31182 31178 31178 31178 31178 31178 31168 31168 31168 31168 31168 31168 31168 31143 31135 31135 31135 31135 31118 31118 31118 31118 31118 31111 31111 31110 31110 31110 31110 31110 31105 31105 31105 31105 31105 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31103 31101 31101 31101 31101 31101 31101 31101 31101 31101 31098 31075 31073 31073 31059 31055 31055 31055 31046 31046 31037 31037 31026 31026 31016 31016 31016 31011 31011 31010 31010 31010 31010 31010 31010 31010 31008 31008 31008 31008 30986 30986 30986 30986 30986 30986 30986 30986 30984 30984 30984 30984 30984 30984 30984 30984 30984 30984 30984 30976 30976 30976 30978 30974 30974 30961 30961 30961 30961 30947 30947 30938 30938 30936 30936 30936 30936 30933 30933 30933 30933 30933 30911 30911 30911 30911 30912 30912 30912 30912 30912 30912 30912 30912 30912 30912 30912 30913 30913 30913 30913 30913 30912 30912 30912 30912 30913 30913 30913 30913 30913 30911 30911 30911 30897 30898 30898 30898 30893 30893 30893 30893 30893 30893 30893 30893 30893 30889 30889 30889 30889 30889 30889 30889 30874 30874 30874 30874 30866 30866 30866 30866 30866 30857 30857 30857 30857 30861 30861 30861 30846 30846 30846 30846 30846 30846 30846 30834 30834 30834 30834 30834 30834 30834 30834 30834 30834 30834 30834 30834 30824 30824 30824 30824 30824 30824 30824 30824 30807 30807 30807 30803 30803 30806 30806 30806 30806 30806 30806 30806 30800 30793 30793 30793 30793 30793 30793 30793 30793 30793 30784 30784 30784 30779 30779 30763 30763 30762 30761 30761 30761 30753 30753 30753 30753 30753 30753 30753 30753 30753 30753 30753 30753 30750 30750 30750 30750 30750 30750 30750 30746 30745 30739 30739 30739 30739 30739 30739 30739 30739 30739 30739 30739 30739 30730 30725 30725 30713 30707 30707 30695 30684 30684 30684 30684 30684 30684 30684 30684 30684 30681 30681 30681 30681 30681 30681 30681 30681 30681 30663 30663 30643 30643 30637 30637 30627 30623 30623 30623 30623 30620 30620 30620 30620 30620 30617 30617 30617 30616 30616 30616 30616 30616 30616 30616 30612 30612 30612 30612 30612 30612 30612 30612 30612 30608 30590 30590 30590 30556 30556 30556 30556 30556 30555 30555 30555 30549 30549 30534 30534 30534 30534 30527 30527 30518 30518 30515 30515 30515 30515 30515 30515 30515 30515 30515 30515 30515 30506 30506 30506 30494 30494 30494 30494 30494 30494 30494 30494 30494 30494 30485 30485 30485 30485 30484 30484 30484 30484 30484 30477 30477 30476 30476 30476 30476 30476 30476 30476 30476 30476 30455 30456 30456 30451 30444 30444 30435 30435 30435 30436 30436 30436 30419 30419 30407 30407 30407 30394 30394 30395 30395 30395 30395 30395 30389 30389 30389 30389 30389 30389 30389 30389 30389 30389 30389 30389 30389 30389 30389 30361 30361 30356 30356 30356 30356 30356 30356 30356 30356 30356 30356 30356 30356 30356 30356 30356 30357 30357 30357 30357 30357 30357 30357 30357 30357 30357 30357 30357 30357 30328 30328 30312 30312 30312 30312 30312 30312 30312 30312 30312 30312 30312 30312 30298 30298 30284 30284 30284 30284 30284 30284 30284 30284 30284 30284 30284 30284 30281 30281 30275 30275 30275 30275 30275 30275 30275 30275 30275 30275 30275 30275 30270 30270 30270 30270 30270 30270 30270 30270 30270 30260 30258 30258 30258 30258 30258 30258 30258 30236 30231 30230 30230 30230 30230 30230 30230 30230 30230 30230 30230 30230 30224 30224 30224 30224 30224 30224 30224 30224 30224 30224 30224 30224 30224 30213 30213 30213 30213 30201 30194 30194 30194 30191 30191 30191 30191 30191 30191 30191 30191 30185 30185 30185 30185 30185 30185 30185 30185 30185 30185 30185 30185 30185 30185 30185 30175 30175 30175 30175 30175 30164 30164 30164 30164 30164 30146 30146 30143 30135 30135 30135 30135 30130 30130 30131 30131 30131 30131 30131 30131 30131 30131 30131 30131 30131 30131 30133 30133 30135 30135 30135 30135 30135 30135 30135 30135 30135 30135 30135 30134 30121 30121 30121 30121 30121 30121 30121 30121 30121 30116 30116 30116 30110 30110 30102 30102 30102 30102 30096 30094 30094 30088 30088 30088 30088 30088 30088 30088 30071 30071 30071 30071 30071 30062 30062 30062 30062 30062 30062 30052 30052 30052 30046 30046 30046 30046 30046 30046 30046 30031 30024 30025 30025 30025 30025 30025 30025 30025 30025 30025 30025 30025 30025 30025 30025 30021 30021 30021 30021 29996 29996 29996 29996 29996 29965 29965 29965 29965 29965 29965 29965 29965 29965 29965 29965 29963 29963 29963 29963 29963 29959 29959 29959 29959 29955 29955 29955 29955 29943 29943 29943 29943 29943 29943 29943 29943 29943 29943 29943 29943 29943 29943 29932 29932 29930 29930 29930 29930 29930 29930 29930 29930 29930 29926 29926 29926 29921 29921 29899 29899 29899 29899 29899 29899 29899 29889 29889 29889 29889 29889 29884 29884 29884 29884 29884 29880 29880 29880 29875 29875 29875 29875 29872 29872 29852 29852 29852 29852 29852 29852 29852 29843 29843 29843 29843 29840 29796 29796 29779 29779 29779 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29765 29764 29764 29764 29764 29764 29764 29764 29764 29764 29764 29753 29753 29753 29753 29753 29748 29739 29728 29728 29728 29728 29728 29728 29728 29728 29728 29728 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29717 29714 29714 29714 29714 29714 29714 29714 29714 29714 29714 29714 29690 29683 29683 29683 29683 29672 29666 29666 29666 29666 29647 29647 29647 29647 29647 29647 29647 29647 29647 29647 29647 29633 29633 29633 29633 29633 29633 29633 29633 29620 29620 29620 29620 29620 29620 29620 29620 29620 29621 29613 29617 29617 29617 29617 29609 29609 29609 29609 29609 29609 29609 29600 29600 29600 29600 29595 29595 29595 29595 29595 29595 29595 29595 29595 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29584 29576 29565 29565 29557 29557 29557 29557 29557 29556 29556 29556 29556 29556 29556 29556 29556 29556 29556 29525 29525 29525 29525 29518 29518 29518 29518 29518 29518 29492 29492 29464 29464 29464 29464 29464 29464 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29457 29454 29434 29434 29431 29431 29427 29427 29427 29422 29420 29420 29420 29420 29420 29414 29400 29400 29400 29400 29400 29400 29400 29400 29400 29400 29400 29395 29395 29395 29396 29377 29377 29377 29377 29368 29368 29368 29368 29368 29368 29364 29364 29364 29363 29363 29363 29343 29343 29343 29343 29343 29322 29302 29302 29300 29300 29300 29300 29296 29296 29296 29296 29296 29296 29292 29292 29277 29277 29277 29277 29277 29277 29267 29267 29267 29267 29267 29267 29267 29267 29267 29267 29261 29261 29261 29261 29250 29250 29250 29250 29250 29250 29250 29250 29250 29250 29250 29250 29250 29250 29242 29242 29242 29242 29242 29242 29242 29242 29242 29228 29228 29228 29228 29228 29228 29223 29223 29223 29222 29222 29222 29222 29222 29222 29222 29222 29222 29222 29214 29214 29214 29214 29214 29200 29200 29200 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29195 29175 29173 29173 29171 29171 29171 29171 29171 29171 29171 29171 29171 29171 29170 29170 29170 29170 29170 29170 29170 29170 29170 29170 29148 29148 29148 29148 29148 29144 29144 29144 29144 29144 29144 29144 29144 29144 29144 29144 29144 29124 29124 29124 29115 29115 29115 29115 29109 29099 29099 29099 29073 29073 29073 29061 29061 29061 29061 29061 29061 29061 29061 29061 29061 29053 29032 29032 29032 29031 29015 29015 29011 29007 29007 29007 29007 29007 29007 29007 29005 29005 29005 29005 29005 29005 29005 29005 29005 29005 29005 29005 28999 28974 28972 28972 28972 28972 28970 28970 28970 28945 28945 28945 28945 28945 28945 28940 28915 28903 28903 28903 28903 28903 28903 28903 28903 28903 28903 28895 28895 28895 28889 28889 28889 28889 28889 28889 28889 28889 28889 28889 28889 28889 28889 28889 28889 28892 28892 28892 28886 28886 28866 28861 28861 28861 28861 28848 28848 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28841 28808 28808 28808 28808 28807 28807 28807 28807 28808 28803 28803 28803 28803 28803 28803 28803 28803 28803 28799 28799 28781 28781 28781 28781 28781 28781 28781 28770 28770 28750 28750 28750 28739 28739 28738 28738 28738 28738 28738 28738 28738 28738 28738 28738 28738 28738 28738 28734 28711 28711 28711 28710 28703 28700 28700 28700 28700 28700 28700 28700 28700 28700 28700 28700 28693 28693 28693 28693 28693 28693 28693 28693 28693 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28665 28651 28651 28612 28612 28612 28612 28612 28602 28602 28602 28602 28602 28602 28602 28602 28602 28602 28602 28583 28583 28583 28583 28578 28578 28574 28574 28574 28560 28560 28535 28535 28537 28537 28537 28537 28537 28537 28537 28537 28537 28537 28537 28527 28527 28527 28527 28527 28524 28524 28524 28524 28523 28523 28523 28523 28523 28521 28521 28521 28521 28521 28521 28501 28463 28463 28463 28463 28463 28463 28463 28463 28463 28452 28443 28443 28443 28432 28432 28429 28429 28429 28413 28413 28413 28413 28407 28392 28392 28392 28392 28392 28392 28392 28392 28392 28392 28392 28392 28392 28392 28392 28384 28384 28384 28384 28384 28384 28384 28384 28384 28382 28382 28382 28375 28375 28375 28375 28375 28375 28365 28365 28359 28359 28359 28359 28359 28359 28359 28359 28355 28355 28349 28349 28349 28345 28340 28340 28340 28340 28340 28340 28325 28325 28325 28325 28325 28325 28325 28325 28325 28325 28324 28324 28324 28324 28324 28324 28321 28321 28321 28321 28321 28316 28316 28316 28316 28316 28316 28316 28293 28293 28293 28293 28293 28293 28293 28293 28293 28293 28293 28276 28276 28276 28276 28276 28276 28272 28272 28272 28272 28272 28272 28272 28272 28272 28272 28272 28272 28272 28241 28241 28241 28241 28241 28230 28230 28228 28228 28215 28208 28208 28208 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28202 28192 28192 28192 28192 28187 28187 28187 28187 28187 28187 28187 28187 28174 28174 28174 28149 28149 28146 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28144 28132 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28104 28089 28089 28089 28089 28089 28083 28083 28083 28083 28083 28083 28083 28060 28060 28060 28060 28060 28060 28060 28060 28060 28060 28060 28060 28051 28051 28051 28045 28045 28045 28045 28045 28031 28031 28031 28031 28031 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 28030 27997 27997 27997 27997 27997 27997 27997 27997 27997 27997 27997 27997 27997 27997 27990 27990 27990 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27985 27971 27971 27971 27971 27971 27971 27971 27971 27971 27971 27971 27971 27971 27959 27948 27948 27948 27948 27948 27948 27934 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27922 27920 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27911 27902 27902 27902 27902 27886 27886 27886 27886 27886 27875 27875 27875 27875 27875 27846 27846 27846 27846 27846 27846 27842 27842 27842 27830 27830 27826 27826 27826 27826 27826 27826 27826 27826 27826 27826 27826 27824 27824 27824 27824 27824 27824 27824 27824 27824 27812 27812 27812 27812 27812 27812 27812 27812 27812 27812 27810 27810 27810 27810 27810 27810 27810 27810 27810 27809 27799 27799 27799 27799 27799 27799 27799 27799 27799 27799 27799 27799 27799 27799 27760 27760 27741 27723 27723 27723 27723 27723 27723 27716 27716 27716 27716 27716 27716 27716 27716 27716 27716 27716 27693 27694 27694 27694 27694 27694 27694 27694 27691 27691 27691 27691 27691 27691 27691 27691 27691 27691 27691 27691 27682 27678 27678 27678 27678 27678 27678 27678 27678 27678 27678 27678 27678 27678 27678 27659 27659 27659 27659 27659 27659 27659 27659 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27652 27641 27641 27641 27641 27641 27641 27641 27641 27641 27641 27641 27641 27638 27624 27624 27624 27614 27614 27614 27614 27614 27611 27609 27609 27609 27609 27609 27609 27609 27609 27609 27609 27609 27609 27586 27586 27586 27586 27586 27586 27586 27586 27586 27586 27586 27586 27586 27586 27586 27557 27547 27547 27547 27528 27511 27511 27511 27499 27499 27499 27499 27499 27499 27499 27499 27499 27499 27499 27499 27490 27479 27479 27477 27477 27477 27477 27477 27477 27477 27477 27477 27477 27477 27475 27475 27475 27475 27450 27450 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27444 27441 27441 27441 27441 27441 27437 27437 27437 27437 27437 27437 27437 27437 27437 27437 27437 27437 27437 27427 27427 27426 27426 27418 27418 27418 27418 27406 27406 27406 27406 27406 27402 27402 27391 27391 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27388 27389 27389 27389 27389 27389 27380 27370 27370 27370 27370 27370 27370 27370 27370 27370 27370 27370 27370 27370 27370 27350 27350 27350 27350 27350 27350 27353 27353 27353 27352 27352 27352 27352 27352 27349 27349 27349 27338 27338 27312 27312 27312 27312 27312 27312 27312 27290 27290 27290 27290 27290 27290 27290 27290 27290 27290 27290 27283 27274 27274 27257 27257 27257 27257 27257 27251 27251 27241 27221 27221 27221 27221 27221 27221 27221 27221 27221 27221 27221 27221 27198 27198 27198 27179 27179 27174 27174 27174 27174 27174 27174 27174 27174 27174 27174 27174 27174 27161 27161 27157 27157 27144 27144 27144 27144 27144 27142 27142 27142 27142 27122 27122 27122 27103 27103 27103 27103 27103 27103 27103 27103 27103 27093 27090 27081 27072 27072 27072 27053 27052 27041 27041 27041 27041 27041 27041 27041 27041 27041 27023 27023 27023 27023 27018 27018 27018 27018 27018 27016 27016 27016 27016 27016 26991 26991 26988 26988 26988 26982 26982 26982 26982 26982 26982 26982 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26973 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26963 26960 26960 26960 26960 26960 26952 26940 26940 26940 26940 26940 26930 26930 26930 26930 26930 26930 26930 26930 26930 26930 26930 26930 26930 26930 26930 26903 26903 26893 26893 26893 26893 26890 26890 26890 26890 26890 26879 26879 26879 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26868 26865 26865 26842 26842 26842 26834 26834 26834 26834 26834 26830 26825 26825 26814 26811 26811 26811 26811 26811 26796 26796 26796 26796 26796 26796 26796 26796 26796 26796 26796 26796 26796 26783 26783 26776 26776 26776 26776 26776 26776 26776 26776 26777 26777 26777 26777 26777 26777 26777 26777 26777 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26764 26763 26761 26761 26761 26761 26761 26761 26761 26761 26761 26761 26761 26761 26761 26752 26739 26739 26739 26737 26737 26735 26727 26727 26727 26727 26727 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26707 26706 26706 26706 26706 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26684 26651 26651 26651 26651 26651 26644 26644 26644 26644 26644 26644 26644 26644 26644 26644 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26636 26610 26610 26610 26610 26610 26601 26597 26597 26597 26597 26597 26597 26597 26597 26597 26597 26597 26597 26559 26559 26559 26533 26518 26518 26518 26518 26520 26517 26506 26506 26506 26506 26506 26476 26476 26476 26476 26476 26476 26476 26476 26476 26475 26475 26475 26475 26475 26475 26475 26475 26475 26475 26475 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26457 26454 26454 26454 26454 26454 26454 26454 26454 26454 26454 26454 26454 26454 26443 26443 26443 26442 26442 26442 26442 26442 26413 26413 26413 26413 26394 26394 26394 26394 26390 26390 26390 26390 26390 26390 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26384 26375 26375 26375 26375 26375 26375 26371 26371 26371 26371 26371 26371 26371 26371 26371 26371 26371 26371 26371 26371 26371 26365 26365 26365 26365 26365 26365 26361 26361 26361 26361 26361 26361 26319 26319 26309 26309 26309 26309 26309 26278 26267 26267 26265 26265 26265 26265 26265 26265 26265 26265 26265 26265 26265 26248 26248 26248 26245 26245 26245 26241 26241 26235 26235 26235 26235 26235 26235 26235 26235 26230 26208 26208 26208 26208 26208 26202 26202 26202 26202 26202 26202 26202 26202 26189 26148 26148 26148 26148 26148 26148 26148 26148 26148 26148 26148 26128 26128 26128 26128 26097 26097 26097 26097 26097 26098 26076 26070 26070 26070 26070 26070 26070 26059 26059 26059 26047 26047 26005 26005 26005 26005 26005 26005 26005 26005 26005 26005 26005 26001 26001 26001 26001 26001 26001 25988 25988 25980 25980 25968 25968 25961 25961 25961 25961 25961 25915 25915 25915 25915 25915 25915 25915 25904 25895 25895 25895 25895 25895 25874 25874 25874 25874 25874 25874 25874 25874 25874 25871 25858 25858 25858 25858 25858 25858 25858 25858 25845 25845 25845 25845 25845 25845 25845 25845 25845 25845 25845 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25837 25836 25836 25836 25836 25836 25836 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25818 25810 25810 25810 25810 25810 25810 25810 25810 25810 25810 25810 25810 25810 25810 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25795 25787 25787 25787 25787 25787 25787 25787 25787 25787 25787 25771 25771 25771 25771 25771 25771 25771 25771 25754 25754 25754 25754 25754 25754 25754 25754 25754 25742 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25737 25725 25725 25725 25725 25725 25706 25706 25706 25706 25706 25706 25706 25706 25706 25706 25706 25706 25706 25706 25706 25688 25688 25688 25688 25688 25688 25672 25672 25672 25672 25672 25672 25672 25672 25672 25655 25655 25655 25655 25655 25655 25655 25655 25655 25655 25648 25618 25618 25618 25618 25618 25618 25607 25607 25594 25583 25583 25583 25583 25583 25583 25583 25583 25583 25583 25583 25583 25566 25566 25566 25566 25566 25566 25566 25566 25566 25566 25566 25566 25566 25566 25565 25565 25565 25565 25553 25553 25553 25553 25553 25553 25553 25539 25539 25539 25539 25539 25539 25539 25539 25538 25538 25538 25538 25538 25538 25538 25538 25538 25538 25530 25530 25530 25530 25530 25530 25530 25530 25530 25530 25524 25524 25524 25524 25524 25524 25524 25524 25524 25524 25524 25518 25518 25518 25518 25518 25518 25518 25494 25494 25494 25494 25494 25494 25494 25494 25494 25494 25494 25494 25494 25465 25465 25465 25465 25465 25465 25459 25453 25452 25452 25443 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25436 25425 25425 25425 25425 25425 25425 25425 25425 25405 25364 25364 25364 25364 25364 25364 25364 25364 25364 25351 25348 25348 25348 25348 25348 25335 25335 25335 25335 25335 25305 25305 25305 25305 25305 25294 25294 25294 25284 25284 25284 25284 25284 25284 25284 25284 25284 25284 25284 25284 25284 25274 25274 25274 25274 25274 25274 25274 25247 25247 25247 25247 25247 25247 25247 25247 25247 25247 25247 25247 25242 25242 25242 25242 25242 25242 25242 25242 25242 25242 25242 25215 25183 25183 25183 25177 25177 25177 25177 25177 25177 25177 25168 25168 25168 25168 25168 25168 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25137 25134 25134 25134 25119 25119 25119 25119 25119 25119 25119 25119 25119 25119 25119 25119 25119 25119 25119 25096 25096 25096 25096 25074 25074 25074 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25065 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25060 25037 25037 25037 25037 25037 25037 25037 25033 25033 25033 25033 25024 25024 25024 25024 25024 25024 25024 25024 25024 25024 25024 25024 25024 25024 25024 24984 24984 24984 24984 24967 24951 24951 24951 24951 24946 24919 24919 24919 24919 24919 24919 24919 24919 24919 24919 24919 24908 24908 24908 24908 24901 24901 24901 24901 24901 24901 24901 24901 24882 24882 24873 24873 24873 24873 24873 24873 24873 24873 24873 24873 24870 24870 24870 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24868 24857 24857 24857 24857 24857 24857 24857 24854 24854 24854 24854 24854 24854 24854 24854 24854 24854 24854 24854 24854 24854 24839 24839 24839 24839 24839 24839 24839 24839 24839 24839 24839 24839 24839 24839 24814 24814 24814 24806 24806 24806 24800 24800 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24797 24792 24792 24792 24789 24789 24789 24789 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24774 24768 24768 24768 24768 24768 24768 24768 24768 24768 24768 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24762 24735 24735 24735 24735 24730 24730 24730 24730 24730 24730 24730 24714 24681 24681 24681 24681 24681 24658 24658 24658 24658 24658 24658 24658 24631 24631 24631 24631 24631 24631 24631 24631 24631 24631 24631 24604 24604 24593 24593 24593 24593 24593 24593 24593 24593 24593 24593 24593 24591 24589 24589 24588 24588 24588 24588 24588 24588 24588 24588 24588 24588 24588 24588 24588 24588 24556 24556 24556 24556 24556 24556 24556 24556 24531 24531 24531 24531 24531 24531 24531 24531 24531 24531 24531 24531 24531 24531 24528 24528 24528 24528 24528 24528 24528 24501 24501 24473 24473 24473 24473 24473 24473 24473 24473 24473 24473 24467 24467 24467 24467 24467 24467 24467 24467 24467 24467 24467 24467 24467 24467 24436 24436 24436 24436 24436 24420 24403 24403 24403 24403 24403 24403 24403 24403 24374 24374 24374 24346 24346 24346 24346 24346 24346 24346 24346 24346 24346 24345 24345 24345 24333 24333 24333 24333 24333 24321 24321 24321 24321 24321 24321 24321 24321 24321 24321 24321 24321 24307 24307 24307 24307 24307 24307 24307 24307 24307 24307 24307 24307 24299 24299 24299 24299 24299 24299 24253 24253 24253 24253 24248 24248 24248 24248 24248 24248 24237 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24222 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24216 24195 24166 24166 24166 24166 24166 24133 24133 24133 24129 24129 24129 24129 24129 24129 24129 24129 24129 24129 24128 24128 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24115 24110 24108 24108 24104 24092 24092 24092 24092 24092 24092 24092 24092 24092 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24055 24051 24051 24031 24031 24031 24031 24031 24000 24000 24000 24000 24000 24000 24000 23951 23935 23933 23933 23925 23925 23925 23925 23925 23925 23898 23898 23898 23898 23898 23898 23898 23898 23898 23898 23898 23898 23898 23898 23898 23890 23890 23869 23869 23869 23869 23869 23870 23870 23870 23870 23870 23839 23839 23839 23839 23839 23839 23839 23839 23839 23839 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23832 23813 23813 23813 23813 23813 23813 23813 23813 23813 23813 23813 23812 23804 23804 23804 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23775 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23765 23763 23763 23763 23763 23763 23763 23763 23763 23763 23763 23763 23747 23747 23747 23747 23747 23747 23747 23747 23747 23747 23747 23747 23747 23747 23747 23740 23740 23740 23740 23732 23730 23730 23730 23730 23730 23730 23730 23730 23730 23730 23730 23730 23730 23730 23728 23728 23728 23728 23713 23709 23709 23709 23709 23709 23709 23709 23691 23691 23691 23691 23691 23691 23691 23691 23691 23691 23691 23691 23691 23683 23683 23683 23683 23683 23682 23682 23682 23682 23682 23682 23682 23682 23682 23676 23676 23676 23676 23676 23676 23676 23664 23660 23660 23660 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23645 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23632 23625 23625 23625 23625 23625 23625 23625 23625 23625 23625 23625 23611 23611 23611 23611 23611 23611 23611 23611 23603 23603 23603 23603 23603 23603 23603 23587 23587 23587 23587 23587 23587 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23572 23568 23568 23568 23554 23554 23554 23554 23554 23554 23554 23554 23554 23554 23554 23554 23554 23552 23552 23552 23552 23552 23552 23552 23552 23552 23552 23552 23531 23531 23531 23531 23531 23531 23531 23531 23531 23531 23531 23531 23531 23531 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23512 23502 23502 23502 23499 23488 23488 23488 23488 23488 23488 23488 23488 23488 23488 23488 23488 23488 23488 23487 23487 23487 23487 23487 23487 23487 23487 23487 23481 23481 23481 23481 23481 23481 23481 23479 23473 23473 23473 23473 23473 23457 23457 23457 23457 23457 23426 23426 23426 23426 23426 23426 23426 23426 23414 23414 23414 23414 23414 23414 23414 23414 23414 23414 23414 23414 23414 23414 23392 23392 23392 23392 23392 23392 23375 23375 23375 23375 23375 23375 23375 23375 23375 23370 23370 23370 23370 23370 23370 23370 23370 23370 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23365 23356 23356 23356 23356 23356 23356 23356 23343 23343 23343 23343 23343 23343 23343 23343 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23339 23325 23325 23325 23325 23325 23325 23325 23325 23325 23325 23325 23315 23315 23309 23309 23309 23309 23309 23309 23309 23282 23282 23282 23282 23282 23282 23282 23282 23277 23277 23277 23277 23277 23277 23277 23277 23275 23275 23275 23275 23275 23275 23275 23275 23275 23275 23275 23275 23275 23275 23265 23265 23265 23265 23265 23265 23255 23241 23241 23241 23241 23241 23241 23241 23241 23219 23219 23219 23218 23217 23211 23211 23207 23207 23207 23207 23207 23207 23207 23207 23207 23207 23207 23194 23187 23187 23187 23187 23187 23187 23187 23187 23187 23154 23154 23154 23154 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23148 23138 23138 23138 23138 23138 23138 23138 23138 23138 23138 23138 23138 23133 23133 23133 23133 23133 23133 23133 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23108 23094 23094 23094 23094 23094 23094 23094 23094 23094 23086 23086 23086 23086 23086 23086 23086 23086 23086 23085 23085 23085 23085 23085 23085 23085 23085 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23055 23047 23047 23047 23047 23047 23025 23025 23025 23025 23025 23025 23025 23025 23025 23025 23014 23014 23014 23014 23014 23014 23014 22992 22992 22992 22992 22992 22992 22992 22992 22992 22992 22992 22989 22989 22985 22984 22984 22984 22984 22984 22984 22984 22984 22984 22984 22984 22976 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22975 22969 22969 22969 22943 22937 22937 22937 22937 22937 22937 22937 22937 22937 22937 22937 22937 22937 22937 22932 22932 22932 22932 22932 22932 22932 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22904 22885 22885 22885 22885 22885 22885 22885 22885 22885 22885 22885 22885 22885 22875 22875 22875 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22874 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22869 22864 22864 22864 22864 22864 22840 22840 22840 22840 22840 22840 22820 22820 22820 22820 22820 22820 22820 22820 22820 22790 22790 22790 22785 22785 22785 22780 22780 22780 22780 22780 22780 22780 22780 22780 22780 22780 22762 22762 22762 22762 22762 22762 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22750 22740 22740 22740 22740 22740 22740 22740 22734 22734 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22727 22722 22722 22697 22679 22679 22679 22679 22679 22679 22679 22660 22660 22660 22660 22660 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22653 22640 22640 22635 22635 22635 22635 22635 22635 22635 22635 22635 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22634 22633 22633 22633 22633 22633 22633 22633 22633 22633 22633 22633 22633 22628 22628 22613 22613 22613 22613 22613 22596 22596 22596 22596 22566 22566 22566 22566 22566 22566 22566 22566 22566 22566 22566 22562 22562 22562 22562 22562 22562 22562 22562 22561 22561 22561 22561 22561 22561 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22558 22554 22554 22554 22554 22554 22554 22554 22554 22554 22554 22554 22544 22522 22522 22522 22522 22522 22522 22522 22522 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22520 22510 22510 22510 22510 22510 22510 22476 22476 22476 22476 22476 22476 22476 22476 22476 22476 22476 22476 22476 22454 22454 22454 22452 22452 22452 22452 22452 22452 22452 22452 22452 22447 22447 22444 22444 22444 22444 22444 22444 22432 22427 22427 22427 22427 22427 22427 22427 22427 22419 22378 22378 22378 22378 22378 22378 22378 22378 22376 22376 22376 22376 22376 22312 22312 22312 22312 22312 22312 22312 22312 22312 22280 22280 22269 22269 22269 22269 22269 22269 22269 22269 22269 22269 22269 22269 22269 22269 22269 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22263 22239 22239 22239 22239 22239 22239 22239 22239 22239 22205 22205 22205 22205 22205 22205 22205 22205 22205 22205 22205 22205 22205 22205 22188 22188 22188 22188 22188 22188 22188 22188 22182 22182 22182 22182 22174 22174 22166 22166 22166 22166 22166 22166 22166 22166 22166 22157 22157 22157 22157 22157 22157 22157 22157 22157 22157 22153 22153 22153 22153 22153 22153 22138 22138 22138 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22137 22106 22106 22106 22106 22106 22106 22100 22095 22095 22095 22095 22095 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22092 22086 22079 22079 22048 22036 22020 22020 22020 22013 22013 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22010 22005 22005 22005 22005 22005 22005 22005 22005 22005 22005 22005 21973 21973 21973 21973 21973 21973 21973 21945 21945 21945 21942 21941 21924 21924 21924 21924 21924 21924 21924 21924 21924 21924 21924 21924 21924 21922 21922 21922 21919 21919 21919 21919 21919 21919 21919 21919 21919 21919 21919 21919 21919 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21905 21901 21889 21883 21883 21883 21883 21883 21883 21883 21883 21883 21883 21879 21879 21879 21879 21879 21826 21826 21826 21826 21826 21826 21826 21826 21826 21826 21826 21826 21821 21821 21821 21821 21821 21821 21821 21821 21821 21821 21821 21821 21821 21821 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21810 21804 21804 21775 21775 21775 21775 21775 21775 21775 21775 21775 21762 21762 21762 21762 21762 21762 21762 21762 21762 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21748 21728 21728 21728 21728 21728 21728 21728 21728 21728 21728 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21713 21711 21711 21711 21682 21662 21662 21644 21644 21644 21644 21644 21644 21631 21624 21624 21624 21624 21624 21624 21624 21624 21622 21622 21622 21622 21622 21622 21622 21622 21622 21622 21622 21622 21622 21622 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21613 21576 21576 21576 21542 21542 21542 21542 21542 21542 21542 21542 21542 21542 21523 21523 21523 21523 21523 21521 21521 21521 21521 21510 21510 21510 21510 21510 21510 21510 21510 21510 21510 21510 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21481 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21456 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21437 21432 21432 21418 21418 21418 21418 21418 21418 21418 21418 21418 21418 21418 21418 21418 21418 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21417 21412 21412 21411 21411 21411 21411 21411 21411 21411 21411 21389 21389 21389 21389 21389 21389 21389 21389 21389 21389 21389 21389 21388 21388 21388 21388 21388 21388 21388 21388 21388 21388 21377 21377 21377 21377 21377 21377 21377 21377 21377 21377 21377 21376 21376 21373 21373 21373 21373 21373 21373 21373 21373 21373 21356 21356 21356 21356 21343 21319 21319 21319 21319 21319 21319 21319 21319 21319 21319 21319 21318 21317 21317 21317 21317 21317 21309 21309 21268 21268 21268 21268 21268 21268 21258 21255 21255 21255 21255 21247 21247 21247 21247 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21243 21234 21234 21234 21234 21205 21205 21205 21205 21205 21205 21205 21205 21205 21185 21185 21185 21185 21185 21175 21175 21175 21175 21175 21175 21175 21175 21175 21175 21175 21175 21175 21175 21169 21169 21169 21169 21169 21169 21169 21169 21169 21169 21169 21169 21169 21166 21166 21166 21166 21166 21166 21160 21160 21160 21160 21160 21160 21160 21160 21160 21160 21160 21139 21139 21139 21139 21139 21139 21139 21139 21133 21133 21133 21133 21133 21133 21133 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21123 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21115 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21108 21090 21082 21082 21082 21082 21082 21082 21082 21082 21082 21082 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21076 21035 21035 21035 21035 21035 21035 21031 21031 21031 21031 21031 21031 21031 21031 21031 21031 21031 21031 21031 21031 21030 21030 21027 21027 21027 21027 21027 21027 21027 21010 21004 21004 21004 20991 20991 20991 20986 20986 20986 20986 20986 20986 20986 20986 20986 20986 20986 20986 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20972 20969 20969 20969 20969 20969 20969 20969 20969 20969 20969 20969 20969 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20965 20959 20959 20959 20959 20959 20959 20959 20959 20959 20942 20942 20942 20942 20942 20939 20939 20939 20939 20939 20939 20939 20939 20939 20939 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20918 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20910 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20901 20899 20897 20897 20897 20897 20897 20897 20897 20897 20897 20897 20893 20893 20887 20887 20887 20887 20887 20887 20887 20887 20887 20887 20887 20843 20843 20843 20843 20843 20843 20843 20843 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20830 20809 20809 20809 20756 20756 20756 20756 20756 20755 20755 20755 20755 20755 20755 20755 20755 20747 20747 20747 20747 20747 20747 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20745 20721 20721 20721 20721 20721 20721 20721 20721 20721 20721 20721 20719 20719 20711 20711 20711 20711 20711 20711 20711 20711 20711 20711 20711 20711 20690 20690 20690 20690 20690 20690 20690 20690 20681 20681 20681 20681 20663 20663 20663 20663 20663 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20622 20612 20612 20612 20612 20588 20588 20588 20588 20588 20588 20588 20588 20588 20588 20588 20588 20588 20588 20588 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20563 20562 20562 20549 20549 20549 20549 20549 20549 20504 20504 20504 20504 20504 20504 20504 20504 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20471 20452 20452 20452 20452 20452 20452 20452 20452 20452 20452 20452 20452 20448 20448 20448 20448 20448 20448 20448 20448 20436 20436 20436 20436 20436 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20429 20425 20425 20417 20417 20417 20411 20411 20411 20411 20411 20411 20411 20411 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20406 20363 20363 20363 20363 20363 20363 20363 20336 20336 20336 20336 20336 20336 20336 20328 20315 20315 20315 20315 20315 20315 20315 20264 20264 20264 20264 20264 20264 20264 20264 20264 20264 20260 20260 20260 20260 20260 20260 20260 20260 20259 20259 20259 20259 20244 20244 20244 20244 20244 20244 20244 20236 20236 20236 20213 20213 20213 20213 20213 20213 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20207 20177 20167 20167 20167 20167 20167 20167 20167 20167 20167 20167 20167 20167 20167 20167 20146 20146 20146 20146 20146 20146 20139 20139 20139 20139 20139 20139 20139 20139 20139 20139 20134 20134 20134 20134 20134 20134 20134 20134 20134 20134 20134 20134 20134 20134 20134 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20111 20108 20108 20108 20108 20108 20074 20074 20074 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20046 20038 20038 20038 20038 20038 20038 20038 20038 20038 20030 20030 20022 20022 20022 20022 20022 20022 19980 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19963 19943 19943 19943 19943 19943 19943 19943 19943 19943 19943 19941 19941 19941 19941 19941 19941 19941 19941 19941 19941 19941 19941 19909 19909 19909 19909 19909 19909 19909 19909 19909 19909 19909 19909 19895 19895 19895 19895 19892 19892 19892 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19890 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19881 19859 19859 19859 19859 19859 19859 19859 19859 19858 19858 19845 19845 19839 19839 19839 19839 19839 19839 19839 19839 19839 19839 19827 19827 19827 19827 19827 19827 19827 19827 19827 19827 19827 19827 19827 19827 19827 19792 19792 19761 19761 19761 19761 19761 19761 19761 19761 19761 19761 19761 19761 19761 19761 19761 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19748 19744 19744 19744 19744 19744 19744 19744 19735 19735 19735 19735 19735 19735 19735 19735 19735 19733 19733 19730 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19728 19707 19707 19707 19707 19707 19707 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19690 19678 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19661 19660 19660 19660 19660 19660 19660 19660 19641 19641 19607 19607 19607 19607 19607 19607 19607 19607 19607 19607 19607 19607 19607 19607 19607 19588 19588 19565 19553 19553 19553 19553 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19492 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19487 19456 19456 19433 19433 19433 19433 19433 19433 19433 19433 19433 19433 19433 19433 19433 19433 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19425 19422 19422 19422 19422 19422 19422 19422 19410 19410 19410 19410 19410 19410 19410 19410 19410 19410 19410 19410 19410 19410 19401 19401 19401 19401 19401 19401 19401 19401 19401 19401 19401 19401 19401 19401 19387 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19384 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19372 19365 19365 19365 19365 19365 19365 19365 19365 19365 19365 19365 19365 19365 19365 19365 19297 19297 19297 19297 19297 19297 19296 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19290 19282 19282 19282 19282 19275 19275 19275 19275 19275 19275 19275 19275 19261 19261 19261 19261 19261 19261 19261 19261 19261 19261 19261 19256 19256 19256 19256 19256 19256 19256 19256 19256 19225 19225 19225 19225 19209 19209 19209 19209 19209 19209 19209 19209 19209 19194 19194 19187 19187 19187 19187 19187 19175 19175 19175 19175 19170 19170 19170 19170 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19151 19140 19140 19140 19140 19140 19140 19140 19140 19140 19140 19126 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19121 19116 19116 19116 19116 19116 19116 19116 19116 19116 19116 19116 19101 19101 19101 19101 19101 19101 19101 19101 19101 19101 19101 19101 19101 19068 19068 19068 19068 19068 19068 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19057 19044 19044 19044 19044 19040 19029 19029 19029 19029 19029 19029 19029 19029 19029 19024 19024 19024 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 19021 18966 18966 18966 18966 18966 18966 18966 18966 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18948 18940 18940 18940 18940 18940 18940 18940 18940 18940 18940 18940 18940 18934 18930 18930 18930 18930 18930 18930 18930 18930 18930 18930 18930 18930 18926 18926 18926 18926 18926 18926 18926 18926 18926 18926 18926 18926 18926 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18908 18885 18885 18885 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18878 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18877 18871 18871 18871 18871 18871 18871 18871 18871 18871 18871 18871 18871 18871 18871 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18853 18851 18851 18851 18851 18851 18851 18851 18851 18851 18851 18851 18851 18850 18850 18850 18850 18850 18838 18838 18838 18838 18838 18838 18838 18838 18838 18827 18827 18827 18827 18827 18799 18799 18799 18799 18799 18799 18784 18784 18784 18784 18784 18784 18784 18784 18784 18784 18784 18784 18784 18784 18784 18743 18743 18743 18743 18743 18743 18743 18743 18743 18743 18743 18743 18743 18743 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18736 18733 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18730 18728 18728 18728 18719 18719 18719 18719 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18716 18704 18695 18695 18695 18695 18686 18686 18686 18686 18686 18686 18686 18686 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18677 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18649 18635 18635 18635 18614 18614 18614 18614 18614 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18589 18581 18581 18581 18571 18571 18571 18571 18571 18571 18571 18571 18571 18571 18571 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18570 18566 18566 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18559 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18537 18519 18519 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18513 18488 18488 18488 18488 18488 18488 18488 18488 18488 18488 18488 18487 18487 18487 18487 18487 18487 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18470 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18441 18422 18422 18422 18422 18422 18422 18420 18420 18420 18420 18420 18420 18420 18420 18420 18420 18420 18420 18420 18420 18418 18418 18418 18418 18411 18411 18411 18411 18406 18406 18406 18406 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18401 18399 18399 18399 18399 18399 18399 18399 18399 18399 18399 18399 18399 18399 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18390 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18386 18380 18380 18380 18380 18380 18380 18380 18380 18380 18380 18380 18380 18379 18379 18379 18379 18379 18379 18358 18358 18358 18343 18343 18343 18343 18340 18340 18340 18340 18340 18340 18340 18340 18340 18340 18340 18340 18340 18340 18340 18335 18335 18321 18321 18321 18321 18315 18315 18315 18315 18315 18315 18302 18302 18302 18296 18296 18296 18296 18296 18296 18296 18296 18296 18293 18293 18293 18293 18293 18293 18293 18293 18293 18293 18269 18269 18269 18269 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18244 18235 18235 18235 18235 18235 18235 18235 18235 18235 18235 18235 18213 18213 18213 18213 18213 18213 18213 18213 18213 18213 18213 18213 18213 18202 18202 18202 18192 18192 18192 18192 18192 18192 18192 18192 18192 18192 18192 18192 18192 18192 18187 18187 18187 18187 18187 18187 18187 18178 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18176 18162 18162 18162 18162 18162 18162 18162 18143 18143 18143 18143 18143 18143 18143 18143 18143 18143 18130 18130 18130 18130 18130 18130 18069 18069 18069 18069 18069 18069 18069 18069 18069 18069 18069 18066 18066 18066 18066 18066 18066 18066 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18043 18040 18040 18040 18040 18040 18040 18040 18040 18040 18040 18039 18039 18039 18039 18039 18039 18039 18039 18039 18039 18039 18039 18033 18033 18033 18033 18033 18033 18033 18033 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18026 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 18024 17991 17991 17991 17991 17991 17991 17991 17991 17991 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17980 17934 17923 17919 17917 17917 17917 17917 17917 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17901 17895 17895 17895 17895 17895 17895 17895 17895 17895 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17869 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17848 17846 17846 17846 17846 17846 17846 17846 17846 17846 17846 17844 17844 17844 17844 17844 17844 17844 17844 17844 17844 17844 17844 17830 17830 17793 17793 17793 17793 17793 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17770 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17727 17702 17702 17702 17702 17702 17694 17694 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17687 17674 17674 17668 17668 17668 17668 17668 17668 17662 17662 17662 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17661 17634 17634 17634 17634 17634 17613 17611 17611 17571 17565 17549 17549 17549 17549 17549 17549 17549 17542 17542 17542 17542 17542 17542 17542 17542 17542 17542 17542 17542 17542 17542 17534 17534 17534 17534 17534 17523 17516 17516 17516 17516 17516 17516 17516 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17510 17503 17503 17503 17503 17503 17503 17503 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17466 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17464 17461 17461 17461 17461 17461 17461 17461 17461 17461 17461 17461 17461 17461 17439 17439 17439 17439 17439 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17425 17416 17416 17416 17416 17416 17416 17416 17415 17406 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17404 17388 17388 17388 17388 17388 17388 17388 17388 17388 17388 17388 17388 17387 17387 17387 17384 17384 17384 17384 17384 17381 17381 17381 17381 17381 17381 17381 17381 17381 17381 17381 17381 17381 17381 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17339 17315 17315 17315 17315 17315 17315 17315 17315 17315 17315 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17296 17285 17285 17285 17285 17285 17285 17285 17285 17285 17285 17285 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17284 17269 17269 17269 17269 17269 17269 17269 17269 17269 17267 17267 17267 17267 17267 17267 17267 17267 17257 17257 17257 17257 17248 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17243 17233 17233 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17204 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17195 17178 17178 17178 17178 17178 17178 17178 17178 17178 17178 17178 17178 17178 17178 17178 17168 17168 17168 17168 17168 17168 17168 17168 17168 17168 17168 17168 17168 17168 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17165 17160 17160 17160 17160 17160 17160 17160 17160 17160 17160 17160 17160 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17148 17145 17145 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17142 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17140 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17137 17125 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17101 17088 17088 17088 17088 17088 17088 17084 17084 17070 17070 17070 17070 17070 17070 17070 17070 17070 17070 17070 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17062 17054 17054 17054 17054 17054 17048 17048 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17031 17028 17028 17028 17028 17028 17028 17028 17025 17025 17025 17025 17025 17025 17025 17025 17025 16998 16998 16998 16998 16998 16998 16989 16989 16989 16989 16989 16989 16985 16985 16985 16985 16985 16985 16973 16973 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16961 16955 16955 16955 16955 16955 16955 16955 16955 16942 16942 16942 16942 16942 16942 16942 16942 16942 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16931 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16925 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16913 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16910 16861 16861 16861 16853 16853 16853 16853 16853 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16845 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16844 16823 16823 16823 16823 16823 16823 16823 16823 16823 16813 16813 16813 16813 16813 16813 16813 16813 16813 16813 16813 16813 16802 16802 16802 16802 16802 16802 16802 16766 16766 16766 16766 16766 16766 16766 16766 16761 16761 16761 16761 16761 16761 16761 16759 16759 16754 16754 16754 16754 16754 16754 16754 16754 16754 16754 16754 16754 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16737 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16707 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16706 16676 16676 16676 16676 16676 16676 16676 16676 16676 16676 16672 16672 16672 16670 16670 16670 16670 16670 16670 16670 16670 16670 16670 16670 16670 16670 16670 16663 16663 16663 16663 16663 16663 16663 16663 16663 16663 16646 16646 16646 16622 16622 16622 16622 16622 16622 16622 16622 16622 16622 16611 16605 16605 16605 16605 16605 16591 16591 16591 16591 16591 16591 16591 16587 16587 16587 16587 16575 16575 16572 16562 16562 16562 16562 16562 16558 16558 16558 16558 16558 16558 16558 16558 16558 16558 16558 16558 16558 16558 16555 16544 16544 16544 16544 16544 16544 16544 16542 16542 16535 16535 16535 16535 16535 16535 16535 16535 16535 16535 16510 16510 16510 16508 16508 16508 16508 16508 16508 16508 16508 16508 16508 16508 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16500 16495 16495 16495 16495 16495 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16493 16487 16487 16487 16487 16487 16487 16487 16487 16487 16481 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16475 16472 16472 16472 16472 16472 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16458 16427 16427 16427 16427 16427 16427 16427 16427 16427 16427 16427 16427 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16426 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16414 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16364 16351 16351 16351 16337 16337 16337 16337 16337 16329 16329 16329 16329 16329 16329 16329 16329 16329 16329 16329 16329 16318 16306 16306 16306 16306 16305 16282 16282 16282 16282 16282 16282 16282 16282 16282 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16281 16268 16268 16268 16268 16268 16268 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16259 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16225 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16210 16189 16189 16189 16173 16173 16173 16173 16173 16173 16173 16173 16173 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16165 16140 16140 16130 16130 16130 16130 16125 16105 16105 16105 16105 16105 16105 16105 16105 16105 16105 16105 16104 16104 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16101 16086 16086 16086 16086 16086 16086 16086 16086 16071 16071 16063 16063 16063 16063 16063 16063 16063 16063 16063 16063 16063 16061 16061 16061 16061 16061 16061 16061 16061 16061 16061 16061 16061 16061 16061 16049 16049 16049 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16036 16035 16035 16003 16003 16003 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15998 15997 15985 15985 15985 15985 15985 15985 15985 15985 15985 15985 15985 15985 15966 15966 15966 15966 15966 15966 15966 15966 15966 15966 15966 15923 15923 15921 15921 15919 15919 15919 15919 15919 15919 15919 15919 15919 15919 15919 15919 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15911 15904 15904 15904 15904 15904 15904 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15893 15881 15881 15881 15881 15881 15881 15881 15881 15881 15881 15881 15881 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15869 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15858 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15850 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15840 15835 15835 15832 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828 15828
#5 125000 125000 0 0
#6 2 3
#7 10 10 0
*/

// Re : 아주 잘못 나오고 있음ㅋ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMMAX	(500)
#define QMAX	(100000)

typedef struct { int y, x; }NODE;
int T, N, M, Q, numbering;
int island[NMMAX + 5][NMMAX + 5], see[NMMAX * NMMAX + 5];
vector<NODE> q[QMAX + 5];
bool chk_dup[QMAX + 5];
int visited[NMMAX + 5][NMMAX + 5];
int input_num[QMAX + 5];
int cnt_island[QMAX + 5];
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };

void init() {
    numbering = 0;
    for (int i = 1; i <= QMAX; i++) {
        q[i].clear();
        chk_dup[i] = false;
        cnt_island[i] = input_num[i] = 0; // 굳이 해주지 않아도 될듯
    }
}

void input() {
    int tmp;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &island[i][j]);
            q[island[i][j]].push_back({ i, j });
            visited[i][j] = -1;
            see[(i - 1) * M + j] = (i - 1) * M + j; // 초기화
        }
    }
    // 테두리
    for (int i = 0; i <= N + 1; i++) island[i][0] = island[i][M + 1] = -1;
    for (int i = 0; i <= M + 1; i++) island[0][i] = island[N + 1][i] = -1;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d", &tmp);
        if (!chk_dup[tmp]) {
            chk_dup[tmp] = true;
            input_num[i] = tmp; // 중복제거
            for (NODE cur : q[tmp]) {
                island[cur.y][cur.x] = -1; // 파괴
            }
        }
        else input_num[i] = 0;
    }
}

int find(int v) {
    if (see[v] == v) return v;
    return see[v] = find(see[v]);
}

void _union(int v1, int v2) {
    v1 = find(v1);
    v2 = find(v2);
    see[v1] = v2;
}

void bfs(int y, int x) {
    queue<NODE> que;
    int ny, nx;
    que.push({ y, x });		visited[y][x] = ++numbering;
    while (!que.empty()) {
        NODE out = que.front();			que.pop();
        for (int d = 0; d < 4; d++) {
            ny = out.y + dy[d];
            nx = out.x + dx[d];
            // 파괴됐거나 방문되지 않은 곳(파괴ed)이라면
            // (island는 번호를 담기 위함이고, visited는 섬의 numbering을 담당)
            // 따라서 visited의 번호를 가지고 union, find를 해주는 것!!
            if (island[ny][nx] == -1 || visited[ny][nx] != -1) continue;
            que.push({ ny, nx });
            visited[ny][nx] = numbering;
            _union(see[(ny - 1) * M + nx], see[(y-1)*M + x]);
        }
    }
}

void island_numbering() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (island[i][j] == -1 || visited[i][j] != -1) continue;
            bfs(i, j);
        }
    }
    cnt_island[Q] = numbering;
}

void get_island_cnt() {
    int ny, nx, num = 0;
    for (int i = Q; i > 1; i--) {
        num = input_num[i];
        if (num == 0) continue;
        else {
            bool tmp = false;
            for (NODE cur : q[num]) {
                island[cur.y][cur.x] = num;
                for (int d = 0; d < 4; d++) {
                    ny = cur.y + dy[d];
                    nx = cur.x + dx[d];
                    if (island[ny][nx] == -1 || visited[ny][nx] == -1) continue;
                    tmp = true;
                    // 복원된 노드를 중심으로 상하좌우를 보되
                    // 같은 섬인지(대표자 노드가 같은지), 다른 섬인지(대표자 노드가 다른지)를 확인 후
                    // 같으면 섬 수 그대로, 다르면 섬 수 -1
                    if (visited[cur.y][cur.x] == -1) {
                        visited[cur.y][cur.x] = visited[ny][nx];
                    }
                    else {
                        if (find(see[(cur.y - 1) * M + cur.x]) != find(see[(ny - 1) * M + nx])) {
                            _union(see[(cur.y - 1) * M + cur.x], see[(ny - 1) * M + nx]);
                            numbering--;
                        }
                    }
                }
                if (!tmp) numbering++;
            }
            cnt_island[i - 1] = numbering;
            //printf("numbering : %d\n", numbering);
        }
    }
}

void output(int t) {
    printf("#%d", t);
    for (int i = 1; i <= Q; i++) {
        /*if (input_num[i] == 0) printf(" %d", cnt_island[i - 1]);
        else printf(" %d", cnt_island[i]);*/
        printf(" %d", cnt_island[i]);
    }
    printf("\n");
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        // 초기화
        init();
        // 입력
        input();
        /*for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                printf("%d ", island[i][j]);
            }
            printf("\n");
        }*/
        // 섬 넘버링 : 현재 다 파괴한 상태이므로, 남아있는 -1이 아닌 양수들의 군집을 섬으로 간주하고, Union 해주어야 함!
        island_numbering();
        // num_cnt ~ 1까지 섬을 복원해주면서, 복원된 땅의 사방에 있는 섬과 Union -> 거꾸로 섬의 개수 저장해줌(cnt_island[i])
        // input_num[i] == 0이면 continue로 넘어가줌
        get_island_cnt();
        // 출력
        output(tc);
    }
    return 0;
}
#endif

// ReRe : 드뎌 ㅠㅠ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMMAX   (500)
#define QMAX    (100000)
#define GET_NUM(a, b)   ( (a-1)*M + b )

struct NODE { int y, x; };
int T, N, M, Q, island_cnt;
int map[NMMAX + 5][NMMAX + 5];
bool visited[NMMAX + 5][NMMAX + 5];
int parent[NMMAX * NMMAX + 5];
vector<NODE> save_node[QMAX+5];
int query[QMAX + 5];
bool chk_query[QMAX + 5];
int result_cnt[QMAX + 5];
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };

void init() { // 초기화
    island_cnt = 0;
    for (int i = 0; i <= QMAX; i++) {
        save_node[i].clear();
        //query[i] = result_cnt[i] = 0; // 굳이 해줄 필요는 없을 듯
        chk_query[i] = false;
    }
}

void input() {
    int tmp;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &tmp);
            map[i][j] = tmp;
            visited[i][j] = false;
            save_node[tmp].push_back({ i, j });
            parent[GET_NUM(i, j)] = GET_NUM(i, j); // union find 초기화
            //printf("[%d, %d] => %d\n", i, j, GET_NUM(i, j));
        }
        map[i][0] = map[i][M + 1] = -1; // 테두리1
    }
    // 테두리2 => 그어주기(못 빠져나가도록)
    for (int j = 0; j <= M + 1; j++) map[0][j] = map[N + 1][j] = -1;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d", &tmp);
        if (!chk_query[tmp]) {
            chk_query[tmp] = true;
            query[i] = tmp;
            for (NODE node : save_node[tmp]) { // 파괴
                map[node.y][node.x] = -1;
            }
        }
        else query[i] = 0;
    }
}

int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
}

void _union(int v1, int v2) {
    v1 = find(v1);
    v2 = find(v2);
    parent[v1] = v2;
}

bool chk_parent(int v1, int v2) {
    return find(v1) != find(v2);
}

void bfs(int y, int x) {
    queue<NODE> que;
    int ny, nx;
    que.push({ y, x });     visited[y][x] = true;
    while (!que.empty()) {
        NODE node = que.front();        que.pop();
        for (int d = 0; d < 4; d++) {
            ny = node.y + dy[d];
            nx = node.x + dx[d];
            if (map[ny][nx] == -1 || visited[ny][nx]) continue;
            visited[ny][nx] = true;
            que.push({ ny, nx });
            _union(GET_NUM(ny, nx), GET_NUM(node.y, node.x));
        }
    }
}

void print_map() {
    printf("print_map\n");
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            printf("%3d", map[i][j]);
        }
        printf("\n");
    }
}

void operation() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == -1 || visited[i][j]) continue;
            bfs(i, j);          island_cnt++;
        }
    }
    result_cnt[Q] = island_cnt;
    //print_map();
}

void get_island_cnt() {
    int tmp, ny, nx;
    for (int i = Q; i > 1; i--) { // 첫 번째 query로 파괴된 상태까지만 구하면 된다!
        tmp = query[i];
        if (!tmp) {
            result_cnt[i-1] = result_cnt[i];
        }
        else {
            //bool flag;
            for (NODE node : save_node[tmp]) {
                map[node.y][node.x] = tmp;
                island_cnt++;
                //flag = true;
                for (int d = 0; d < 4; d++) {
                    ny = node.y + dy[d];
                    nx = node.x + dx[d];
                    if (map[ny][nx] == -1) continue;
                    //flag = false;
                    if (chk_parent(GET_NUM(ny, nx), GET_NUM(node.y, node.x))) {
                        _union(GET_NUM(ny, nx), GET_NUM(node.y, node.x));
                        island_cnt--;
                    }
                }
                //if (flag) island_cnt++;
            }
            result_cnt[i-1] = island_cnt;
        }
        //print_map();
    }
}

void output(int tc) {
    printf("#%d", tc);
    /*printf("\n");
    for (int i = 1; i <= Q; i++) printf(" %d", query[i]);
    printf("\n");*/
    for (int i = 1; i <= Q; i++) {
        if(!query[i]) result_cnt[i] = result_cnt[i-1];
        printf(" %d", result_cnt[i]);
    }
    printf("\n");
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        operation();
        //print_map();
        get_island_cnt();
        output(tc);
    }
    return 0;
}
#endif

// 남의 코드 : 분석해보자!
#if 0
#include<vector>
#include<stdio.h>
#include<algorithm>
using namespace std;

typedef pair<int, int> pp;

int n, m, q, query[100001];
int mp[501][501], check[100001], answer[100001], tmp[501][501];
int xx, yy, dx[4] = { 0,1,0,-1 }, dy[4] = { 1,0,-1,0 }, cnt, mx;
pp uni[501][501];
vector<pp> list[100001];

pp getParent(pp node) {
    if (uni[node.first][node.second] == node) return node;
    return uni[node.first][node.second] = getParent(uni[node.first][node.second]);
}

void Logic(int i) {
    int size = list[i].size();
    int x, y, j, k;

    for (j = 0; j < size; j++) {
        pp pi = list[i][j];
        x = pi.first;
        y = pi.second;
        tmp[x][y] = 1;
        cnt++;
        for (k = 0; k < 4; k++) {
            xx = x + dx[k];
            yy = y + dy[k];
            if (xx<1 || yy<1 || xx>n || yy>m || !tmp[xx][yy])continue;
            pp p1 = getParent(uni[x][y]);
            pp p2 = getParent(uni[xx][yy]);
            if (p1 != p2) {
                uni[p1.first][p1.second] = p2;
                cnt--;
            }
        }
    }
}

int main()
{
    int i, j, t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; tt++) {
        scanf("%d%d", &n, &m);

        mx = cnt = 0;
        for (i = 1; i <= 100000; i++) {
            list[i].clear();
            check[i] = answer[i] = 0;
        }
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                scanf("%d", &mp[i][j]);
                tmp[i][j] = 0;
                uni[i][j] = make_pair(i, j);

                list[mp[i][j]].push_back(make_pair(i, j));
                if (mp[i][j] > mx) mx = mp[i][j];
            }
        }
        scanf("%d", &q);
        for (i = 1; i <= q; i++) {
            scanf("%d", &query[i]);
            check[query[i]]++;
        }

        for (i = 1; i <= mx; i++) {
            if (!check[i]) Logic(i);
        }

        for (i = q; i >= 1; i--) {
            answer[i] = cnt;

            check[query[i]]--;
            if (!check[query[i]]) {
                Logic(query[i]);
            }
        }
        printf("#%d", tt);
        for (i = 1; i <= q; i++)
            printf(" %d", answer[i]);
        printf("\n");
    }
    return 0;
}
#endif




// (중상) [기출P-0041] K-Heap 슈퍼이벤트 
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define QMAX	(300000)
#define TMAX	(100000)

int T, Q, tree[TMAX * 4 + 1], maldan;

void init() {
    for (int i = 1; i < (maldan << 1); i++) tree[i] = 0;
}

void update(int node_idx) {
    int tree_idx = maldan + node_idx - 1;
    while (tree_idx >= 1) {
        tree[tree_idx]++;
        tree_idx >>= 1;
    }
}

int get_num(int tree_idx, int order) {
    while (tree_idx < maldan) {
        tree[tree_idx]--;
        if (tree[tree_idx << 1] >= order) tree_idx <<= 1;
        else {
            tree_idx <<= 1;
            order -= tree[tree_idx];
            tree_idx |= 1;
        }
    }
    tree[tree_idx]--;
    return tree_idx - maldan + 1;
}

void input_operation_output(int tc) {
    int a, b;
    printf("#%d", tc);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d %d", &a, &b);
        if (a == 1) update(b);
        else printf(" %d", get_num(1, b));
    }
    printf("\n");
}

int main() {
    freopen("in.txt", "r", stdin);
    for (maldan = 1; maldan < TMAX; maldan <<= 1);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        init();
        input_operation_output(tc);
    }
    return 0;
}
#endif

// 예전 코드 (2020.02)
#if 0
#include <cstdio>
#define NMAX	100000
#define QMAX	300000

int T, Q;
int card_tree[NMAX * 4];
int maldan;

void add_card(int n)
{
    int idx = maldan + n - 1;
    card_tree[idx]++;
    while (idx > 1)
    {
        idx /= 2;
        //card_tree[idx] = card_tree[idx<<1] + card_tree[(idx<<1)|1];
        card_tree[idx]++;
    }
}

void del_card(int n)
{
    int idx = maldan + n - 1;
    card_tree[idx]--;
    while (idx > 1)
    {
        idx /= 2;
        //card_tree[idx] = card_tree[idx<<1] + card_tree[(idx<<1)|1];
        card_tree[idx]--;
    }
}

int find_dangchum(int order)
{
    int idx = 1;
    int result;

    while (idx < maldan)
    {
        if (card_tree[idx << 1] >= order)
        {
            idx <<= 1;
            //if (card_tree[idx] != order) order -= card_tree[idx];
        }
        else
        {
            idx <<= 1;
            order -= card_tree[idx];
            idx |= 1;
        }
    }
    result = idx - maldan + 1;
    del_card(result);
    return result;
}

void input()
{
    int a, XK;

    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++)
    {
        scanf("%d %d", &a, &XK);
        if (a == 1) add_card(XK);
        else printf("%d ", find_dangchum(XK));
    }
}

void init()
{
    for (int i = 1; i < 2 * maldan; i++) card_tree[i] = 0;
}

int main(void)
{
    scanf("%d", &T);
    for (maldan = 1; maldan < NMAX; maldan *= 2);
    for (int tc = 1; tc <= T; tc++)
    {
        printf("#%d ", tc);
        input();
        init();
        printf("\n");
    }

    return 0;
}
#endif




// (중상) [기출P-0058] 탱크 : 못 품.. 밑에 푼 코드 있음
/*
    【 문제 이해 】
    모든 탱크에 대하여
    한 탱크(점수 : S)의
    왼쪽 아래 방향에 위치한 모든 탱크들의 점수느 S보다 크다.
    오른쪽 위 방향에 위치한 모든 탱크들 중 S보다 작은 점수모두 합산!
    (※ 탱크 공격해도 어떤 변화도 생기지 않음 주의!)
    (※ 두 탱크가 동일한 x좌표나 y좌표에 위치하는 경우 없음!!!!!)
    (※ 같은 점수를 가지고 있는 탱크 또한 없음!!!!!)

    【 풀이 생각 】
    1. 2차원 좌표(y, x)이니까 인덱스트리를 두 개 만들어서 각 좌표를 넣어주면 되지 않을까?
    2. 
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

struct TANK_NODE { int y, x, score; };
int T, N;
TANK_NODE tank[NMAX+5];
long long total_score;

void input() {
    int a, b, c;
    total_score = 0LL;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &a, &b, &c);
        tank[i] = { b, a, c };
    }
}

void output(int tc) { printf("#%d %lld\n", tc, total_score); }

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        ;
        output(tc);
    }
    return 0;
}
#endif

// (중상) [기출P-0058] 탱크
/*
    【 문제 이해 】
    모든 탱크에 대하여
    한 탱크(점수 : S)의
    왼쪽 아래 방향에 위치한 모든 탱크들의 점수는 S보다 크다.
    오른쪽 위 방향에 위치한 모든 탱크들 중 S보다 작은 점수모두 합산!
    (※ 탱크 공격해도 어떤 변화도 생기지 않음 주의!)
    (※ 두 탱크가 동일한 x좌표나 y좌표에 위치하는 경우 없음!!!!!)
    (※ 같은 점수를 가지고 있는 탱크 또한 없음!!!!!)

    【 풀이 생각 】
    1. 2차원 좌표(y, x)이니까 인덱스트리를 두 개 만들어서 각 좌표를 넣어주면 되지 않을까?
        => x보다 크고 y보다 크지만, score 또한 큰 경우를 솎아내기 어려움
           하나씩 비교를 한다면, 결국엔 1차원 배열 두 개로 하는 것과 다르지 않음
    2. Leaf Node에 공격하는 탱크를 기준으로
       3사분면 ~ 그 탱크 ~ 1사분면... 이렇게 Tree를 만들준다?
        => 좌상 ~ 우하의 y = -x 그래프 형태로 노드가 주어진다면
           Tree에 들어가는 것이 없게됨...
    3. Indexed Tree를 왜 사용할까 생각을 하게 됨
        => "순서"를 갖는 정보들이 있을 때,
           "구간"의 대표값이나 합/곱 등의 "연산"결과를 빠르게 얻을 수 있음

    ▼
      (y부터 해도 됨!)
    4. x(오름차순)를 기준으로 maldan ~ maldan + N - 1까지 깔아주고,
       y가 큰 순으로(내림차순) 그 y에 대응되는 x값을 Indexed Tree에서 확인,
       그 후에 거기서부터 leaf node의 마지막(x값이 가장 큰 노드)까지의 구간 합을 구해준다면?
       (단, Tree의 leaf node에 기록되는 대표값은 (x, y)의 score이고,
       위로 타고 올라가면서 += score을 해주면서 구간합을 구할 수 있도록 해줌!)

        => 어떻게 가능?
        : 구하고자 하는 것이 임의의 (x, y)를 기준으로
        이 노드보다 x, y 모두 큰 노드들의 score 중
        이 노드의 score보다 작은 것들의 합!
        : x 오름차순 정렬을 해서 leaf node에 깔아줌으로써 1, 4사분면을 확인할 수 있고,
          y 내림차순 정렬 후, 순서대로 넣어줌으로써 1사분면의 score을 솎아낼 수 있음!
          (이미 x는 오름차순으로 깔려있고, y가 큰 순으로 들어오므로
          그 노드 기준으로 1사분면에 있는 노드들을 찾아낼 수 있고,
          문제의 "왼쪽 아래 방향의 탱크의 점수가 크다는 것 보장"에서
          1사분면에 있는 score이 다 작음이 보장됨!)
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)
#define XYMAX   (1000000)

typedef long long ll;
int T, N, maldan;
bool x[XYMAX + 5];
pair<bool, pair<int, int>> y[XYMAX + 5];// 정렬을 해주기 위함(x - 오름, y - 내림)
int sort_x[XYMAX + 5], sort_y[NMAX + 5];
ll tree[NMAX * 4 + 5];	// 인덱스드트리 (x좌표 기준으로) - y좌표는 구간합 때 씀!
ll get_sum;

void init() {	// 초기화
    get_sum = 0LL;
    for (int i = 1; i <= XYMAX; i++) {
        x[i] = false;
        y[i] = { false, {0, 0} };
        sort_x[i] = 0;
        if (i >= N) continue;
        sort_y[i] = 0;
    }
    // tree 초기화
    for (maldan = 1; maldan < N; maldan <<= 1);
    for (int i = 1; i < maldan << 1; i++) tree[i] = 0LL;
}

void sort_xy() {	// x, y 정렬해주기 위함
    int cnt = 0;
    for (int i = 1; (cnt < N) && (i <= XYMAX); i++) {
        if (!x[i]) continue;
        sort_x[i] = cnt++;
    }	// tree[maldan+i]의 value는 sort_x[i]임!
    cnt = 0;
    for (int i = 1; (cnt < N) && (i <= XYMAX); i++) {
        if (!y[i].first) continue;
        sort_y[cnt++] = i;
    }	// 이후 y[sort_y[i]].second.first로 x에 접근!
        // 이후 y[sort_y[i]].second.second로 score에 접근!
}

void input() {
    int a, b, c;
    scanf("%d", &N);
    init();
    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &a, &b, &c);
        x[a] = true;		y[b].first = true;
        y[b] = { true, {a, c} };
    }
    sort_xy();
}

void attack_tank(int leaf_x_node, int leaf_score) {	// make tree && get total score
    int left = leaf_x_node, right = maldan + N - 1;
    // leaf_x_node ~ 끝 노드까지의 구간 합 구하기
    while (left <= right) {
        if (left & 1) get_sum += (1LL * tree[left++]);
        if (!(right & 1)) get_sum += (1LL * tree[right--]);
        left >>= 1;		right >>= 1;
    }
    // leaf_x_node에 leaf_score를 갱신해준 후, 위로 쭉 올라가면서 갱신
    while (leaf_x_node >= 1) {
        tree[leaf_x_node] += (1LL * leaf_score);
        leaf_x_node >>= 1;
    }
}

void operation() {
    for (int i = N - 1; i >= 0; i--) {
        attack_tank(maldan + sort_x[y[sort_y[i]].second.first],
            y[sort_y[i]].second.second);
    }
}

void output(int tc) { printf("#%d %lld\n", tc, get_sum); }

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        operation();
        output(tc);
    }
    return 0;
}
#endif

// sovley 코드
#if 0
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct tank {
    int x, y, score;
};
bool cmp(const tank& u, const tank& v) {
    return u.x > v.x;
}

vector<long long> tree;
int N, MAX_XY = 1000000, TREE_SIZE = 1 << ((int)ceil(log2(MAX_XY)) + 1);
tank tanks[100000];

void update(int node, int start, int end, int idx, int val) {
    if (idx < start || idx > end)
        return;
    tree[node] += val;
    if (start != end) {
        update(2 * node, start, (start + end) / 2, idx, val);
        update(2 * node + 1, (start + end) / 2 + 1, end, idx, val);
    }
}

long long query(int node, int start, int end, int i, int j) {
    if (j < start || end < i)
        return 0;
    if (i <= start && end <= j)
        return tree[node];
    return query(2 * node, start, (start + end) / 2, i, j) + query(2 * node + 1, (start + end) / 2 + 1, end, i, j);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        tree.clear();
        tree.resize(TREE_SIZE);
        cin >> N;
        for (int i = 0; i < N; i++) {
            int x, y, score;
            cin >> x >> y >> score;
            tanks[i] = { x, y, score };
        }
        sort(tanks, tanks + N, cmp);

        long long ans = 0;
        for (int i = 0; i < N; i++) {
            int idx = tanks[i].y, val = tanks[i].score;
            update(1, 1, MAX_XY, idx, val);
            ans += query(1, 1, MAX_XY, idx + 1, MAX_XY);
        }
        cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}

#endif




// (중상) [기출P-0005] 인터스텔라
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

typedef long long ll;
typedef pair<ll, int> pli;
int T, N, M, K, ss, ee;
long long dist[NMAX + 5][4];
vector<pli> edges[NMAX + 5];
ll MAX_DIST = 1LL * 100000 * 200000 + 1LL;

void input() {
    int a, b, c;
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; i++) {    // 초기화
        for (int j = 0; j <= K; j++) dist[i][j] = MAX_DIST;
        edges[i].clear();
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &a, &b, &c);
        edges[a].push_back({ 1LL * c, b });
        edges[b].push_back({ 1LL * c, a });
    }
    scanf("%d %d", &ss, &ee);
}

void dijkstra() {
    priority_queue<pair<pli, int>, vector<pair<pli, int>>, greater<pair<pli, int>>> pq;
    pq.push({ { 0LL, ss }, 0 });     dist[ss][0] = 0LL;
    while (!pq.empty()) {
        //ll d = pq.top().first.first;
        int node = pq.top().first.second;
        int k = pq.top().second;        pq.pop();
        if (node == ee) return;
        for (pli next : edges[node]) {
            if (dist[next.second][k] > dist[node][k] + 1LL * next.first) {
                dist[next.second][k] = dist[node][k] + 1LL * next.first;
                pq.push({ { dist[next.second][k], next.second }, k });
            }
            for (int i = 1; i <= K; i++) {
                if (k + i > K) continue;
                if (dist[next.second][k + i] > dist[node][k] + 1LL) {
                    dist[next.second][k + i] = dist[node][k] + 1LL;
                    pq.push({ { dist[next.second][k + i], next.second }, k + i });
                }
            }
        }
    }
}

void output(int tc) {
    ll min_dist = MAX_DIST;
    for (int i = 0; i <= K; i++) if (min_dist > dist[ee][i]) min_dist = dist[ee][i];
    printf("#%d %lld\n", tc, min_dist);
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        dijkstra();
        output(tc);
    }
    return 0;
}
#endif



// (중상) [교육P-0032] 패닉룸 2 
/*
    일반적인 다익스트라 문제
    하지만 시간초과를 해결해야 했음!!
    => 왜 시간초과?
        : 우선 qp(이 문제에서는 min_heap)를 사용하는 이유는
        최소값, 즉 최소 패닉의 합( .top() )을 뽑아내어 사방으로 진행시킴으로써
        (N, M)에 도착했을 때의 최소 패닉 합을 구해주기 위함!
        ( 특히 min_heap이므로 (N, M)에 처음으로 도착했을 때가 원하는 답임이 보장됨! )
        하지만 패닉들의 합을 pq에 넣어주지 않고 좌표만 넣어주었던 것...
        그러니 더 많이(?) 도는 문제 발생...
        -> 추후 다시 코드 보면서 알아보자!

    => 그렇다면 어떻게 시간초과 해결?
        :

*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define NMMAX	(500)
#define INF		(0x7fffffff)

typedef pair<int, pair<int, int>> pipii;	// typedef pair<int, int> pii;
int T, N, M;
int map[NMMAX + 5][NMMAX + 5], dijk[NMMAX + 5][NMMAX + 5];
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };

void input_init() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &map[i][j]);
            dijk[i][j] = INF;
        }
    }
    for (int i = 0; i <= N + 1; i++) map[i][0] = map[i][M + 1] = -1;
    for (int i = 0; i <= M + 1; i++) map[0][i] = map[N + 1][i] = -1;
}

void get_panic() {
    priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
    int y, x, ny, nx;
    pq.push({ map[1][1], { 1, 1 } });	dijk[1][1] = map[1][1];
    while (!pq.empty()) {
        pipii node = pq.top();		pq.pop();
        y = node.second.first;		x = node.second.second;
        if (node.first > dijk[y][x]) continue;
        if (y == N && x == M) return;
        for (int d = 0; d < 4; d++) {
            ny = y + dy[d];			nx = x + dx[d];
            if (map[ny][nx] == -1) continue;
            if (dijk[ny][nx] > dijk[y][x] + map[ny][nx]) {
                dijk[ny][nx] = dijk[y][x] + map[ny][nx];
                pq.push({ dijk[ny][nx], { ny, nx } });
            }
        }
    }
}

void output(int tc) { printf("#%d %d\n", tc, dijk[N][M]); }

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input_init();
        get_panic();
        output(tc);
    }
    return 0;
}
#endif



// [연습P-0012] 파티 참석하기
/*
    【 IDEA 1 】: 시간복잡도가...
    - s -[t]-> e를
      edges[s].push_back({ t, e });로 받아줌
    - 우선 X번방에서부터 Dijkstra를 끝까지 돌려
      come_back[]배열에 X로부터 i까지의 최단거리를 저장
      : 이후 i번 친구가 X번으로 왔다가 돌아갈 때 사용
    - 1 ~ N번방(X번방 제외)의 친구들이 X번방을 목적지로 하여
      Dijkstra를 돌림 (즉, 총 N-1번이 되겠지?)
      : i번 친구가 X번으로 가는 시간
    => 하지만 다익스트라 최악의 시간복잡도 O(E * log(E))
       (N-1) * E * log(E) + E * log(E) = N * E * log(E)
                                       = 5만 * 50만 * log(50만)
                                       = 5만 * 50만 * 16
                                       = 4천억........

    【 IDEA 2 】
    - s -[t]-> e를
      edges[s].push_back( { t, e } );와
      edges2[e].push_back( { t, s } );로 받아줌!!!
      => edges는 되돌아올 때.
         edges2는 X번방까지 갈 때 사용
    - 우선 X번방에서부터 Dijkstra를 끝까지 돌려
      come_back[]배열에 X로부터 i까지의 최단거리를 저장
      : 이후 i번 친구가 X번으로 왔다가 돌아갈 때 사용
    - IDEA1과 반대로 edges2를 이용하여
      위의 Dijkstra와 반대로 X -> i까지의 최단거리가 아니라
      i -> X까지의 최단거리를 만들어줌!! ( go[]배열에 최단거리 저장 )
      : edges와 반대로 거꾸로 저장해주었기 때문에 가능!!
    => 시간복잡도 :
       E * log(E) * 2 = 50만 * 2 * 16 = 1600만!!!!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX    (50000)
#define MMAX    (500000)
#define INF     (0x7fffffff)

typedef pair<int, int> pii;
int T, N, M, party_room, last_arrv;
vector<pii> edges[NMAX+5], edges2[NMAX+5];
int go[NMAX + 5], come_back[NMAX+5];

void init() {
    last_arrv = -1;
    for (int i = 1; i <= N; i++) {
        edges[i].clear();       edges2[i].clear();
        go[i] = come_back[i] = INF;
    }
}

void input() {
    int s, e, t;
    scanf("%d %d %d", &N, &M, &party_room);
    init();
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &s, &e, &t);
        edges[s].push_back({ t, e });   // "s" -[t]-> e
        edges2[e].push_back({ t, s });  // s -[t]-> "e"
    }
}

void make_come_back() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({ 0, party_room });     come_back[party_room] = 0;
    while (!pq.empty()) {
        pii node = pq.top();       pq.pop();
        for (pii next : edges[node.second]) {
            if (come_back[next.second] > come_back[node.second] + next.first) {
                come_back[next.second] = come_back[node.second] + next.first;
                pq.push({ come_back[next.second], next.second });
            }
        }
    }
}

void go_party() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({ 0, party_room });     go[party_room] = 0;
    while (!pq.empty()) {
        pii node = pq.top();       pq.pop();
        for (pii next : edges2[node.second]) {
            if (go[next.second] > go[node.second] + next.first) {
                go[next.second] = go[node.second] + next.first;
                pq.push({ go[next.second], next.second });
            }
        }
    }
}

void output(int tc) { 
    for (int i = 1; i <= N; i++) {
        if (go[i] == INF || come_back[i] == INF) continue;
        if (last_arrv < go[i] + come_back[i]) last_arrv = go[i] + come_back[i];
    }
    printf("#%d %d\n", tc, last_arrv);
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        make_come_back();
        go_party();
        output(tc);
    }
    return 0;
}
#endif




// (중상) [연습P-0008] 웜홀
/*
    【 문제 이해 】
    N개 농장(1~N 넘버링), M개 양방향 길, W개 웜홀(단방향 길, 이전 시간으로 되돌려줌)
    현재 위치 -> ... -> 현재위치일 때, 시간이 되돌아가있나?

    【 풀이 】
    가장 첫 번째 주어졌던 경로부터 시작한다고 하자!
    N-1번 : 모든 노드에서 출발하여 연결된 노드까지 한 칸씩 가자!
    마지막으로 다시 한 번 더 반복
    이 때, 갱신된 time_chk이 있다면 flag을 true로 바꿔주면서 끝!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (500)
#define MMAX    (2500)
#define WMAX    (2500)
#define INF     (0x7fffffff)

typedef pair<int, pair<int, int>> pipii;
int T, N, M, W;
int time_chk[NMAX+5];
pipii edges[2*MMAX+WMAX+5];
bool flag;

void init() {   // 초기화
    flag = false;
    for (int i = 1; i <= N; i++) {
        time_chk[i] = INF;
    }
}

void input() {
    int s, e, t;
    scanf("%d %d %d", &N, &M, &W);
    init();
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &s, &e, &t);
        edges[2*i-1] = { t, { s, e } };
        edges[2*i] = { t, { e, s } };
    }
    for (int i = 1; i <= W; i++) {
        scanf("%d %d %d", &s, &e, &t);
        edges[i + 2 * M] = { -t, { s, e } };
    }
}

void bellman_ford() {
    int tmp;
    pipii node;
    time_chk[edges[1].second.first] = 0;
    for (int i = 1; i < N; i++) {   // N-1번
        for (int j = 1; j <= 2 * M + W; j++) {  // 주어진 도로와 웜홀 모두 처리
            node = edges[j];
            if (time_chk[node.second.first] == INF) continue;
            tmp = time_chk[node.second.first] + node.first;
            if (time_chk[node.second.second] > tmp) {
                time_chk[node.second.second] = tmp;
            }
        }
        /*printf("[%d]", i);
        for (int k = 1; k <= N; k++) {
            printf(" %2d", time_chk[k]);
        }
        printf("\n");*/
    }
    for (int j = 1; j <= 2 * M + W; j++) {  // 주어진 도로와 웜홀 모두 처리
        node = edges[j];
        if (time_chk[node.second.first] == INF) continue;
        tmp = time_chk[node.second.first] + node.first;
        if (time_chk[node.second.second] > tmp) {
            flag = true;
            break;
        }
    }
    /*printf("[%d]", N);
    for (int k = 1; k <= N; k++) {
        printf(" %2d", time_chk[k]);
    }
    printf("\n");*/

}

void output(int tc) { printf("#%d %s\n", tc, (flag ? "YES" : "NO")); }

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        bellman_ford();
        output(tc);
    }
    return 0;
}
#endif




// (중상) [교육P-0006] 가장 먼 두 도시
/*
    【 문제 이해 】
    N개 도시 : 1~N 넘버링 && 두 도시 사이에는 항상 도로가 있음
                             a->b와 b->a 길이가 다를 수 있음
    거리 : a -> b를 하나 이상의 도로를 거쳐 가는 여러 가지 방법들 중 가장 길이가 짧은 것!
    도시 간 거리(가장 짧은 길이)가 가장 긴 곳?

    【 풀이 】
    ㅇ
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (300)

int T, N;   // N : ~300 (N^3도 가능)
int dist_adj[NMAX+5][NMAX+5];
int max_dist;

void input() {
    max_dist = -1;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &dist_adj[i][j]);
        }
    }
}

void floyd_warshall() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {      // 출발지
            for (int j = 1; j <= N; j++) {  // 목적지
                if(i == j) continue;
                if (dist_adj[i][j] > dist_adj[i][k] + dist_adj[k][j]) {
                    dist_adj[i][j] = dist_adj[i][k] + dist_adj[k][j];
                }
            }
        }
    }
}

void output(int tc) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (max_dist < dist_adj[i][j]) max_dist = dist_adj[i][j];
        }
    }
    printf("#%d %d\n", tc, max_dist);
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        floyd_warshall();
        output(tc);
    }
    return 0;
}
#endif




// (중상) [교육P-0008] 임계 경로
/*
    【 문제 이해 】
    N개의 공정, 그 사이의 M개의 작업 관계(작업시간)
    i보다 낮은 공정들 중, i와 연결되어 있는(?) 모든 작업이 끝나야 i를 수행할 수 있음
    이 때, N작업까지 끝냈을 때까지의 최소시간?

    【 문제 풀이 】
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX    (100000)
#define INF     (0x7fffffff)

typedef pair<int, int> pii;
int T, N, M;
int indegree[NMAX+5];
vector<pii> edges[NMAX+5];
int min_time[NMAX+5];

void init() {
    for (int i = 1; i <= N; i++) {
        indegree[i] = 0;
        edges[i].clear();
        min_time[i] = -1;
    }
}

void input() {
    int a, b, c;
    scanf("%d %d", &N, &M);
    init();
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &a, &b, &c);
        edges[a].push_back({c, b});
        indegree[b]++;
    }
}

void operating() {
    //priority_queue<pii, vector<pii>, less<pii>> pq;
    queue<pii> q;
    //pq.push({ 0, 1 });      min_time[1] = 0;
    q.push({ 0, 1 });      min_time[1] = 0;
    while (!q.empty()) {
        pii node = q.front();    q.pop();
        for (pii next : edges[node.second]) {
            min_time[next.second] = max(min_time[next.second], next.first + node.first);
            if (--indegree[next.second] == 0) {
                q.push({ min_time[next.second], next.second });
            }
        }
    }
}

void output(int tc) { printf("#%d %d\n", tc, min_time[N]); }

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        operating();
        output(tc);
    }
    return 0;
}
#endif




// (중상) [교육P-0007] 군사 도로망 
/*
    【 문제 이해 】
    N개의 도시, 도시들을 연결하는 도로(양방향, 두 노드 사이엔 최대 하나!)
    많은 도로가 파괴된 상태..
    -> 모든 쌍의 도시가 연결되어야! (파괴/건설하여)
    -> 단 하나의 길로만! 즉, 1에서 3으로 가는데 한 가지의 길(길 != 도로)만 있어야 함!
        즉, "사이클이 생기지 않도록!"

    【 문제 풀이 】
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define NMAX    (100000)
#define MMAX    (250000)
#define KMAX    (250000)

typedef tuple<int, int, int> tiii;  // cost, v1, v2
int T, N, M, K;
int city[NMAX + 5];
long long cost; // 100만 비용의 도로를 최대 249,999개 만들어야 할 수도!
tiii destroy[MMAX + 5], construct[MMAX + 5];

void init() {
    tiii zero = make_tuple(0, 0, 0);
    cost = 0LL;
    for (int i = 1; i <= N; i++) city[i] = i;
    for (int i = 0; i < M; i++) destroy[i] = zero;
    for (int i = 0; i < K; i++) construct[i] = zero;
}

int find(int v) {
    if (v == city[v]) return v;
    return city[v] = find(city[v]);
}

void _union(int v1, int v2) {
    v1 = find(v1);
    v2 = find(v2);
    city[v1] = v2;
}

bool chk_union(int v1, int v2) { return find(v1) == find(v2); }

bool compare_increasing(const tiii& t1, const tiii& t2) {   // 오름차순
    return get<0>(t1) < get<0>(t2);
}

bool compare_decreasing(const tiii& t1, const tiii& t2) {   // 내림차순
    return get<0>(t1) > get<0>(t2);
}

void input_init_operation() {
    int v1, v2, c, cnt = 0;
    // 입력
    scanf("%d %d %d", &N, &M, &K);
    init(); // 초기화
    // 입력1
    for (int i = 0; i < M; i++) {  // 제거 : 가장 싼 것부터 제거
        scanf("%d %d %d", &v1, &v2, &c);
        destroy[i] = make_tuple(c, v1, v2);
    }
    // 제거 : 사이클이 이루어지지 않으면 만들고,
    //        사이클이면 만들지 않으면서(제거) 비용을 더해줌
    sort(destroy, destroy + M, compare_decreasing);
    for (int i = 0; i < M; i++) {
        c = get<0>(destroy[i]);     // cost
        v1 = get<1>(destroy[i]);    // city1
        v2 = get<2>(destroy[i]);    // city2
        if (!chk_union(v1, v2)) { _union(v1, v2); cnt++; }
        else {
            cost += (1LL * c);
        }
    }
    // 입력2
    for (int i = 0; i < K; i++) {  // 건설 가능 : 가장 싼 것부터 건설
        scanf("%d %d %d", &v1, &v2, &c);
        construct[i] = make_tuple(c, v1, v2);
    }
    // 건설 : 사이클이 이루어지지 않는다면 건설, 아님 반대
    sort(construct, construct + K, compare_increasing);
    for (int i = 0; i < K; i++) {
        c = get<0>(construct[i]);     // cost
        v1 = get<1>(construct[i]);    // city1
        v2 = get<2>(construct[i]);    // city2
        if (cnt == N - 1) break;
        if (!chk_union(v1, v2)) {
            _union(v1, v2);
            cnt++;
            cost += (1LL * c);
        }
    }
}

void output(int tc) { printf("#%d %lld\n", tc, cost); }

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input_init_operation();
        output(tc);
    }
    return 0;
}
#endif






// (중상) [기출P-0024] 고속철 건설
/*
    【 문제 이해 】
    【 문제 풀이 】
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    return 0;
}
#endif





// (중상) [기출P-0032] 사격장
/*
    max heap과 min heap을 사용하면 풀릴 줄 알았지만,
    1 3이 주어지고 7 10이 주어졌을 때,
    4, 5, 6을 처리해주어야 하는 케이스를 생각하지 못했음.
    즉, 제대로 된 해결법이 아님!!
*/
// Max heap, Min heap 으로 못 품!!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define MMAX    (100000)

int T, N, M, customer[MMAX + 5];

void init() { for (int i = 1; i <= M; i++) customer[i] = 0; }

void input_operation() {
    int A, B, score;
    priority_queue<int, vector<int>, greater<int>> min_pq;
    priority_queue<int, vector<int>> max_pq;
    scanf("%d %d", &N, &M);
    init();
    scanf("%d %d", &A, &B);
    customer[1] = B - A + 1;
    min_pq.push(A);     max_pq.push(B);
    for (int i = 2; i <= M; i++) {
        scanf("%d %d", &A, &B);
        score = 0;
        if (min_pq.top() > A) {
            score += (min_pq.top() - A);
            min_pq.pop();
            min_pq.push(A);
        }
        if (max_pq.top() < B) {
            score += (B - max_pq.top());
            max_pq.pop();
            max_pq.push(B);
        }
        customer[i] = score;
    }
}

void output(int tc) {
    int result = 0;
    for (int i = 1; i <= M; i++) {
        if (i & 1) result += customer[i];
        else result -= customer[i];
    }
    printf("#%d %d\n", tc, result);
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input_operation();
        output(tc);
    }
    return 0;
}
#endif

// Re : Union Find로 풀어보자!!
/*
    1) l에 맞춰서 점수 얻을 수 있나? (전에 안 맞춘 것인가?)
    2) l == r인가?
    3) l이 이전의 r과 같은가? (그럼 자기 자신을 바라보고 있을 거잖아?)
    4)
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100000)
#define MMAX	(100000)
// 손님
int T, N, M, parent[NMAX + 5], customer[MMAX + 5];
// 점수판(과녁)
bool chk[NMAX + 5];

int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
}

void _union(int v1, int v2) {
    v1 = find(v1);
    v2 = find(v2);
    /*if (v1 < v2) parent[v1] = v2;
    else parent[v2] = v1;*/
    parent[v1] = v2;
}

bool chk_dup(int v1, int v2) {	// 중복 확인
    return find(v1) == find(v2);
}

void input_init_operation() {
    int l, r, score;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {	// 초기화
        parent[i] = i;		chk[i] = false;
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &l, &r);
        score = 0;
        l = find(l);	// 시작점을 찾아줌
        if (!chk[l]) { chk[l] = true;  score++; }
        while (l < r) {
            if (!chk_dup(l, l + 1)) {
                _union(l, l + 1);
                if (!chk[l + 1]) {
                    chk[l + 1] = true;
                    score++;
                }
                //printf("%d -> %d\n", l, l + 1);
            }
            l = find(l);
        }
        customer[i] = score;
        //printf("%d\n", score);
    }
}

void output(int tc) {
    int result = 0;
    for (int i = 1; i <= M; i++) {
        if (i & 1) result += customer[i];
        else result -= customer[i];
    }
    printf("#%d %d\n", tc, result);
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input_init_operation();
        output(tc);
    }
    return 0;
}
#endif


// Re : Indexed/Segment Tree로 풀어보자!!
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        ;
    }
    return 0;
}
#endif






// BOJ_11658_구간 합 구하기3
// 이차원 세그먼트 트리
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (1024)

int N, M, table[NMAX+5][NMAX+5];

void input() {
    int w, x1, y1, x2, y2, c;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d", &w);
        if (!w) {   // (x1, y1)을 c로 갱신
            scanf("%d %d %d", &x1, &y1, &c);
        }
        else {      // (x1, y1) ~ (x2, y2) 합
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    input();
    return 0;
}
#endif






// 청소년 상어
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

struct FISH { int y, x, dir; bool isDead; };
FISH fish[18];
FISH shark;
int map[5][5];
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int cnt;

void input() {
    int a, b;
    cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d %d", &a, &b);
            fish[a] = { i, j, --b, false };
            map[i][j] = a;
        }
    }
}

int get_dir(int d) {
    if (++d >= 8) d -= 8;
    return d;
}

void move_fish() {
    int ny, nx, nd, fish_tmp, map_tmp;
    bool end_flag;
    FISH tmp = { 0, 0, 0, false };
    for (int i = 1; i <= 16; i++) {
        if (fish[i].isDead) continue;
        end_flag = true;
        nd = fish[i].dir;
        for (int j = 0; j < 8; j++) {
            ny = fish[i].y + dy[nd];		nx = fish[i].x + dx[nd];
            if (ny < 0 || ny > 4 || nx < 0 || nx > 4 || !map[ny][nx]) nd = get_dir(nd);
            else {
                end_flag = false;
                break;
            }
        }
        if (end_flag) continue;
        tmp = fish[i];		fish_tmp = map[ny][nx];
        map_tmp = map[tmp.y][tmp.x];
        map[tmp.y][tmp.x] = map[ny][nx];
        map[ny][nx] = map_tmp;
        fish[i] = fish[fish_tmp];
        fish[fish_tmp] = tmp;
    }
}

void move_shark() {
    ;
}

void eat_fish_fat_shark() {
    shark = { 0, 0, fish[map[0][0]].dir, false };
    fish[map[0][0]].isDead = true;	cnt++;
    map[0][0] = 0;
    while (!shark.isDead || cnt == 16) {
        move_fish();
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    input();
    eat_fish_fat_shark();
    return 0;
}
#endif




// BOJ_1666_최대 증가 직사각형 집합
// 무슨 말인지 모르겠다...
#if 0
#pragma warning(disable:4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int N;

int main() {
    freopen("in.txt", "r", stdin);

    return 0;
}
#endif





// 개같다 문제가...
// BOJ_2842_집배원 한상덕
#if 0
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (50)

typedef struct { int y, x; }NODE;
NODE postoffice;
NODE house[NMAX*NMAX+10];
int house_cnt;
int N, height[NMAX+10][NMAX+10];
char village[NMAX+10][NMAX+10];
int max_height, min_height, result_height;
int dy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 }, dx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    house_cnt = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%c ", &village[i][j]);
            if (village[i][j] == 'P') postoffice = { i, j };
            else if (village[i][j] == 'K') house[++house_cnt] = { i, j };
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    result_height = 987654321;
    max_height = min_height = height[postoffice.y][postoffice.x];
    ;
    return 0;
}
#endif
 




// BOJ_1072_게임
#if 0
#include <cstdio>
#include <algorithm>
using namespace std;

int X, Y, additional_game_cnt;

int main() {
    freopen("in.txt", "r", stdin);
    additional_game_cnt = 0;
    scanf("%d %d", &X, &Y);
    ;
    printf("%d\n", additional_game_cnt);
    return 0;
}
#endif






// hackerrank_Forming a Magic Square
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    return 0;
}
#endif





// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
