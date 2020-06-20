/*
    시간복잡도 및 공간복잡도 잘 따져보고 알고리즘에 접근하자!!
    그러기 위해서는 내가 사용하는 알고리즘의 시간복잡도가 어떻게 되는지, 공간복잡도는 또 얼마나 되는지 확실하게 알고 있어야겠지!?!?!?
*/

// BOJ_11653_소인수분해
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX     (10000000)

int N; // N : 1 ~ 1천만
vector<int> soinsu;
bool eratos[MAX];
int sosu[MAX], sosu_cnt;

int main() {
    freopen("in.txt", "r", stdin);
    sosu_cnt = 0;
    for (int i = 2; i < MAX; i++) {
        if (eratos[i] != false) continue;
        sosu[++sosu_cnt] = i;
        for (int j = 2 * i; j < MAX; j += i) eratos[j] = true;
    }
    scanf("%d", &N);
    int point = 1;
    while (N != 1) {
        if (N % sosu[point] == 0) {
            N /= sosu[point];
            soinsu.push_back(sosu[point]);
        }
        else point++;
    }
    for (int print : soinsu) printf("%d\n", print);
    return 0;
}
#endif

// Re
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int N;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    int point = 2;
    while (N != 1) {
        if (N % point == 0) {
            printf("%d\n", point);
            N /= point;
        }
        else point++;
    }
    return 0;
}
#endif
