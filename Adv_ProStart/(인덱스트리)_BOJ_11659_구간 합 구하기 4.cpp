// BOJ_11659_구간 합 구하기 4
#if 01
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
