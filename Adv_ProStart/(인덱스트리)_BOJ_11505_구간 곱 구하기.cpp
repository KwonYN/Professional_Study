// BOJ_11505_구간 곱 구하기
#if 01
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
