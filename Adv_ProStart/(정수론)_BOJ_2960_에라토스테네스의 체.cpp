// BOJ_2960_에라토스테네스의 체
#if 01
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
