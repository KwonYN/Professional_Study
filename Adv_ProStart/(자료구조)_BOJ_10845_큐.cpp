// BOJ_10845_큐
/*
    push X: 정수 X를 큐에 넣는 연산이다.
    pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다.
         만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
    size: 큐에 들어있는 정수의 개수를 출력한다.
    empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
    front: 큐의 가장 앞에 있는 정수를 출력한다.
           만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
    back: 큐의 가장 뒤에 있는 정수를 출력한다.
          만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX (10000)

enum COMMAND { POP = 0, PUSH = 1, SIZE = 2, BACK = 3, EMPTY = 4, FRONT = 5 };   

int N;  // N : 1 ~ 10,000
int que[MAX+10];    // 1 ~ 100,000
int wp, rp;

int get_command(char* com) {
    int len = 0;
    while (com[len]) len++;
    if (len == 3) return POP;
    if (len == 4) {
        if (com[3] == 'h') return PUSH;
        if (com[3] == 'e') return SIZE;
        if (com[3] == 'k') return BACK;
    }
    if (len == 5) {
        if (com[4] == 'y') return EMPTY;
        if (com[3] == 't') return FRONT;
    }
}

int main()
{
    char command[10];
    int com_num;
    freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    wp = rp = 0;
    while (N--) {
        scanf("%s", command);
        com_num = get_command(command);
        if (com_num == POP) {
            if (wp <= rp) printf("%d\n", -1);
            else printf("%d\n", que[rp++]);
        }
        else if (com_num == PUSH) {
            scanf("%d", &com_num);
            que[wp++] = com_num;
        }
        else if (com_num == SIZE) printf("%d\n", wp - rp);
        else if (com_num == BACK) {
            if (wp <= rp) printf("%d\n", -1);
            else printf("%d\n", que[wp - 1]);
        }
        else if (com_num == EMPTY) {
            if (wp <= rp) printf("%d\n", 1);
            else printf("%d\n", 0);
        }
        else {
            if (wp <= rp) printf("%d\n", -1);
            else printf("%d\n", que[rp]);
        }
    }
    return 0;
}
#endif
