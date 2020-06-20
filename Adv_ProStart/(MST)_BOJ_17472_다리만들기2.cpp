// BOJ_17472_다리만들기2
#if 01
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
