#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int T, n, m;
int A[1010], B[1010];
int AA[4000010], BB[4000010];
long long cnt;
int a_cnt, b_cnt;

int main()
{
    //freopen("in.txt", "r", stdin);
    cnt = 0;	A[0] = B[0] = 0;
    a_cnt = b_cnt = 0;
    scanf("%d", &T);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        A[i] += A[i - 1];
	for (int j = 0; j < i; j++) {
            AA[ a_cnt++ ] = A[i] - A[j];
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &B[i]);
        B[i] += B[i - 1];
        for (int j = 0; j < i; j++) {
            BB[ b_cnt++ ] = B[i] - B[j];
        }
    }
    sort(AA, AA+a_cnt);		sort(BB, BB+b_cnt);

    int l = 0;	int r = b_cnt-1;
    int sum, tmp_cnt_l, tmp_cnt_r, tmp_l;
    while(l < a_cnt && r >= 0) {
        sum = AA[l] + BB[r];
        if(sum == T) {
	    tmp_l = l;
	    tmp_cnt_l = tmp_cnt_r = 0;
            while(AA[l] + BB[r] == T && l < a_cnt) {
                l++;	tmp_cnt_l++;
            }
            while(AA[tmp_l] + BB[r] == T && 0 <= r) {
                r--;	tmp_cnt_r++;
            }
            cnt += (tmp_cnt_l * tmp_cnt_r);
        }
        else if(sum < T) l++;
        else if(sum > T) r--;
    }

    printf("%lld\n", cnt);
    return 0;
}
