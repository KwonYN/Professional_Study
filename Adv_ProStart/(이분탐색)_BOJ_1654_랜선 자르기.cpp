// BOJ_1654_랜선 자르기
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define KMAX    (10000)

typedef long long ll;
int K, N;
ll max_len, lan[KMAX + 10], result;

bool get_cnt(ll target_len) {
    ll cnt = 0;
    for (int i = 0; i < K; i++) {
        cnt += (lan[i] / target_len);
    }
    if (cnt >= N) return true;
    return false;
}

int main()
{
    freopen("in.txt", "r", stdin);
    max_len = result = -1;
    scanf("%d %d", &K, &N);
    for (int i = 0; i < K; i++) {
        scanf("%lld", &lan[i]);
        max_len = max(max_len, lan[i]);
    }
    sort(lan, lan + K);

    ll s = 1, e = max_len, m;
    while (s <= e) {
        /*if ((s & 1) && (e & 1)) m = s / 2 + e / 2 + 1;
        else m = s / 2 + e / 2;*/
        // => 계속 if문을 통해 검증을 하다 보니 시간 초과...;;

        m = (s + e) / 2; // 여기에서 int 범위를 넘을 수도 있음!!!
        if (get_cnt(m)) {
            s = m + 1;
            if (result < m) result = m;
        }
        else e = m - 1;
    }
    printf("%lld\n", result);
    return 0;
}
#endif
