// BOJ_11058_크리보드
// Ctrl A + Ctrl C + Ctrl V(★여러 번 가능!!!!!★)

#if 01
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
