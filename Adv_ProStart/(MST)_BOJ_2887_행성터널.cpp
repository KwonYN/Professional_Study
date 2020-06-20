// BOJ_2887_행성터널
/*
    N개의 행성. 효율적으로 지배하고파. 행성을 연결하는 터널 만들자!
    행성은 3차원 좌표 위의 한 점임.
    => (a, b, c)와 (d, f, e)를 터널 연결할 때 min( abs(a-d), min( abs(b-f), abs(c-e) ) )
    터널을 총 N-1개 건설해서 모든 행성이 서로 연결되게 하려고 함. 최소비용으로!

    모든 거리를 오름차순으로 배열화할 수 있다면!?!?!?
*/
#if 01
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
