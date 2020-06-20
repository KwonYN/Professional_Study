// BOJ_2143_두 배열의 합
/*
    부배열 :  A[i], A[i+1], …, A[j-1], A[j] (단, 1 ≤ i ≤ j ≤ n)
    부 배열의 합은 A[i]+…+A[j]를 의미
    A의 부 배열의 합에 B의 부 배열의 합을 더해서
        T가 되는 모든 부 배열 쌍의 개수를 구하라!
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX (1000)

typedef long long ll;
int T, n, m, A[MAX+10], B[MAX+10];
int AA[MAX*MAX], BB[MAX*MAX], a_cnt, b_cnt;
ll cnt;

void input() {
    cnt = a_cnt = b_cnt = 0;
    scanf("%d", &T);
    A[0] = B[0];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        A[i] += A[i - 1];
        for (int j = 0; j < i; j++) {
            AA[a_cnt++] = A[i] - A[j];
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &B[i]);
        B[i] += B[i - 1];
        for (int j = 0; j < i; j++) {
            BB[b_cnt++] = B[i] - B[j];
        }
    }
    sort(AA, AA + a_cnt);       sort(BB, BB + b_cnt);
}

void get_cnt() {
    int l = 0, r = b_cnt-1;
    int tmp_l;
    ll cnt_l, cnt_r;
    while ((l < a_cnt) && (r >= 0)) {
        if (AA[l] + BB[r] == T) {
            tmp_l = l;
            cnt_l = cnt_r = 0;
            while ((AA[l] + BB[r] == T) && (l < a_cnt)) { l++; cnt_l++; }
            while ((AA[tmp_l] + BB[r] == T) && (r >= 0)) { r--; cnt_r++; }
            //printf("cnt_l = %lld, cnt_r = %lld\n", cnt_l, cnt_r);
            cnt += (cnt_l*cnt_r);
        }
        else if (AA[l] + BB[r] > T) r--;
        else l++;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    input();
    /*printf("[AA] : ");
    for (int i = 0; i < a_cnt; i++) printf("%d ", AA[i]);
    printf("\n[BB] : ");
    for (int i = 0; i < b_cnt; i++) printf("%d ", BB[i]);
    printf("\n");*/
    get_cnt();
    printf("%lld\n", cnt);
    return 0;
}
#endif
