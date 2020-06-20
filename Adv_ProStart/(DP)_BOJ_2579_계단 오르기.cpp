// BOJ_2579_계단 오르기
/*
    계단 오르기 게임: 계단 아래 시작점부터 계단 꼭대기에 위치한 도착점까지 가는 게임
    계단을 밟으면 그 계단에 쓰여 있는 점수를 얻게 됨.

    1) 계단은 한 번에 "한" 계단씩 또는 "두" 계단씩 오를 수 있다.
       즉, 한 계단을 밟으면서 이어서 다음 계단이나,
                                     다음 다음 계단으로 오를 수 있다.
    2) "연속된 세" 개의 계단을 모두 밟아서는 "안" 된다.
       단, 시작점은 계단에 포함되지 않는다.
    3) "마지막" 도착 계단은 "반드시" 밟아야 한다.

    총 점수의 최댓값을 구하는 프로그램
*/
/*
    dp[n] = max( dp[n-3] + stair[n-1] + stair[n], dp[n-2] + stair[n] );
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX    (300)

int N;
int stair[NMAX + 10];
int score[NMAX + 10];

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &stair[i]);
    score[1] = stair[1];
    score[2] = stair[1] + stair[2];
    score[3] = max(stair[1] + stair[3], stair[2] + stair[3]);
    for (int i = 4; i <= N; i++) {
        score[i] = max(score[i-3] + stair[i-1] + stair[i], score[i - 2] + stair[i]);
    }
    printf("%d\n", score[N]);
    return 0;
}
