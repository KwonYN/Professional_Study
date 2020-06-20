// BOJ_1849_순열
// 시간초과 코드
#if 0
#pragma warning(disable : 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N;
int arr[NMAX+10], zrr[NMAX+10];

int main() {
    freopen("in.txt", "r", stdin);
    int tmp, j;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) zrr[i] = i - 1; // 0의 개수
    for (int i = 1; i <= N; i++) {
        scanf("%d", &tmp);
        for (j = tmp + 1; j <= N; j++) {
            if (zrr[j] == tmp) break;
        }
        arr[j] = i;
        for (int k = j; k <= N; k++) zrr[k]--;
    }
    for (int i = 1; i <= N; i++) printf("%d\n", arr[i]);
    return 0;
}
#endif

// Re
#if 01
#pragma warning(disable : 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (100000)

int N, maldan, mal;
int arr[NMAX*4]; // 0의 개수!

void make_zero_arr() {
    int idx = (maldan>>1);
    for (int i = idx; i <= maldan - 1; i++) {
        arr[i] = 2;
    }
    for (int i = idx - 1; i >= 1; i--) {
        arr[i] = arr[i << 1] + arr[(i << 1) | 1];
    }
}

void update(int order, int new_val) {
    int idx = 1;
    while (idx < mal) {
        if (arr[idx << 1] > order) idx <<= 1;
        else {
            order -= arr[idx << 1];
            idx = (idx << 1) | 1;
        }
    }
    if (arr[idx] == 1) {
        if (!arr[idx << 1]) arr[idx << 1] = new_val;
        else arr[(idx << 1) | 1] = new_val;
    }
    else {
        arr[idx * 2 + order] = new_val;
    }
    while (idx > 1) {
        arr[idx]--;
        idx >>= 1;
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    int tmp;
    scanf("%d", &N);
    for (maldan = 1; maldan < N; maldan<<=1);
    mal = maldan >> 1;
    make_zero_arr();
    for (int i = 1; i <= N; i++) {
        scanf("%d", &tmp);
        update(tmp, i);
    }
    for (int i = maldan; i < maldan + N; i++) printf("%d\n", arr[i]);
    return 0;
}
#endif
