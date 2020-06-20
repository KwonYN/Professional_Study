// BOJ_11657_타임머신
#if 01
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
