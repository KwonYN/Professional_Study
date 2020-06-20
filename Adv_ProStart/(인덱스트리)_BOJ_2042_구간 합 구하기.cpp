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
