// BOJ_2096_내려가기
#if 01
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
