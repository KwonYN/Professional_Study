// BOJ_10775_공항 : Union-Find
// 뒤에서부터 하는 것을 생각하는 것이 중요!!
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define GMAX    (100000)

int G, P, max_cnt, gi[GMAX+10];
int gate[GMAX + 10]; // parent

int arrange_plane(int no) {
    if (no == gate[no]) return no;
    return gate[no] = arrange_plane(gate[no]);
}

int main()
{
    freopen("in.txt", "r", stdin);
    // initialization
    max_cnt = 0;

    // input
    scanf("%d", &G);
    for (int i = 0; i <= G; i++) gate[i] = i;
    scanf("%d", &P);
    for (int i = 1; i <= P; i++) scanf("%d", &gi[i]);

    // arrange plane
    int gate_num;
    for (int i = 1; i <= P; i++) {
        gate_num = arrange_plane(gi[i]);
        if (gate_num == 0) break;
        gate[gate_num]--;
        max_cnt++;
    }

    // print
    printf("%d\n", max_cnt);
    return 0;
}
#endif
