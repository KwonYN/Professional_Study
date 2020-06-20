// BOJ_1644_소수의 연속합
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (4000000)

bool eratos[NMAX + 10];
int sosu[NMAX], sosu_cnt, N, cnt;

int main() {
    freopen("in.txt", "r", stdin);
    eratos[0] = eratos[1] = true;   sosu_cnt = 0;
    for (int i = 2; i <= NMAX; i++) {
        if (eratos[i]) continue;
        sosu[++sosu_cnt] = i;
        for (int j = i + i; j <= NMAX; j += i) eratos[j] = true;
    }
    int num;
    scanf("%d", &N);        cnt = 0;
    for (int i = 1; i <= sosu_cnt; i++) {
        num = 0;
        if (sosu[i] > N) break;
        for (int j = i; j <= sosu_cnt; j++) {
            //printf("(+될 소수 : %d) => %d\n", sosu[i], num);
            num += sosu[j];
            if (num >= N) {
                if (num == N) cnt++;
                break;
            }
        }
        //printf("=========================\n");
    }
    printf("%d\n", cnt);
    return 0;
}
#endif



// 남의코드도 봐보자 오 좋다 투포인터!
#include <cstdio>
#include <vector>
using namespace std;
 
int main(){
    int N;
    scanf("%d", &N);
    // 에라토스테네스의 체로 소수 뽑기
    bool np[4000000] = {0};
    vector<int> prime(1, 2);
    for(int i=3; i<4000000; i+=2){
        if(np[i]) continue;
        prime.push_back(i);
        if(1LL*i*i >= 4000000) continue;
        for(int j=i*i; j<4000000; j+=i*2)
            np[j] = true;
    }
 
    // 결과 구하기
    int result = 0, sum = 0, lo = 0, hi = 0;
    while(1){
        if(sum >= N) sum -= prime[lo++];
        else if(hi == prime.size()) break;
        else sum += prime[hi++];
        if(sum == N) result++;
    }
    printf("%d\n", result);
}
