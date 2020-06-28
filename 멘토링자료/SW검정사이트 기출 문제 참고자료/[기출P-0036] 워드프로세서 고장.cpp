#include <cstdio>
 
#define MAX_Q 1000
 
struct WORD {
    int bef;
    int pos;
    int cnt;
};
 
class QUE {
public:
    WORD wd[MAX_Q];
    int start, end;
    int sz;
 
    QUE(int _start, int _end, int _sz) : start(_start), end(_end), sz(_sz) {};
 
    void push(WORD w)
    {
        wd[end] = w;
        end = (end + 1) % MAX_Q;
        sz++;
    }
 
    void pop(void)
    {
        start = (start + 1) % MAX_Q;
        sz--;
    }
 
    WORD front(void)
    {
        return wd[start];
    }
};
 
using namespace std;
 
int T, K; // 1 ≤ K ≤ 100
 
char str[1001]; //보고서는 최소 1글자, 최대 1,000 글자
int  s_len;
char voca[100][1001];
int  len[100];
 
bool comp(int pos, int id) {              // strcmp
    for (int i = 0; i < len[id]; i++) {
        if (str[pos + i] != voca[id][i])
            return false;
    }
 
    return true;
}
 
int length(char *st) {
    int cnt = 0;
    while (st[cnt] != 0) cnt++;
 
    return cnt;
}
 
int main()
{
    scanf("%d", &T);
    for (int ts = 1; ts <= T; ts++) {
        scanf("%d", &K);
        scanf("%s", str);
        s_len = length(str);
        for (int i = 0; i < K; i++) {
            scanf("%s", voca[i]);
            len[i] = length(voca[i]);
        }
         
        QUE myque(0, 0, 0);
        WORD now, nxt;    // 이전단어, 현재까지의 칸, 단어사용수
        now.bef = -1;
        now.pos = now.cnt  = 0;
        myque.push(now);
         
        int dp[1001];            // 각 자리별 최소 단어사용 DP
        for (int i = 0; i <= s_len; i++) dp[i] = 1001;
 
        int n_pos;
        while (myque.sz) {
            now = myque.front();
            myque.pop();
 
            if (now.cnt > dp[now.pos])         // 더 작은 단어로 채워진 이력이 있으면 버리자
                continue;
 
            for (int i = 0; i < K; i++) {
                if (now.bef == i) continue;    // 이전 단어와 겹치면 안됨
 
                if (comp(now.pos, i)) {        // 다음단어와 비교
                    n_pos = now.pos + len[i];  // 다음 위치
 
                    if (n_pos == s_len) {      // 끝까지 왔으면, 최소값 저장
                        dp[s_len] = (dp[s_len] < now.cnt + 1) ? dp[s_len] : now.cnt + 1;
                    }
                    else if (n_pos < s_len) {  // 작으면 다음 자리에서 더 작은 수가 있으면 버리고, 아니면 저장
                        if (dp[n_pos] > now.cnt + 1) {   // '=' 는 빼야 함. 1 ~ K 까지 하기 때문에 같은 이전단어를 만들 가능성이 없음
 
                            dp[n_pos] = now.cnt + 1;
                            nxt.pos = n_pos;
                            nxt.bef = i;
                            nxt.cnt = now.cnt + 1;
 
                            myque.push(nxt);
                        }
                    }
                }
            } // for - i
        } // while que
 
        if(dp[s_len] != 1001)
            printf("#%d %d\n", ts, dp[s_len]);
        else
            printf("#%d -1\n", ts);
    }
 
    return 0;
}
