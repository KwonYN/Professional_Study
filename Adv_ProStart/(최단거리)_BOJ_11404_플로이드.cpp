// BOJ_11404_플로이드
#if 01
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
