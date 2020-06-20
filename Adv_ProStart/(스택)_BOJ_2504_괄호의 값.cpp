// BOJ_2504_괄호의 값
#if 01
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define MAX     (30)

typedef struct { int val, loc; }OPERATION;
int stack[MAX + 10], sp, osp;
OPERATION op[MAX + 10];

int convert_to_int(char ch) {
    if (ch == '(') return 1;
    if (ch == ')') return 2;
    if (ch == '[') return -1;
    return -3;
}

int main() {
    ios::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);
    freopen("in.txt", "r", stdin);
    string str;     int len, res;
    sp = osp = 0;   stack[0] = 0;
    cin >> str;     len = str.length();
    for (int i = 0; i < len; i++) {
        stack[++sp] = convert_to_int(str[i]);
        res = stack[sp - 1] * stack[sp];
        if (((res == 2) || (res == 3)) && ((stack[sp - 1] == 1) || (stack[sp - 1] == -1))) {
            op[++osp] = { res, sp-1 };
            sp -= 2;
            for (int j = osp; j > 0; j--) {
                if(op[j].loc > op[j-1].loc) break;
                if (op[j].loc == op[j - 1].loc) op[j - 1].val += op[j].val;
                else if (op[j].loc < op[j - 1].loc) {
                    op[j-1].val *= op[j].val;
                    op[j - 1].loc = op[j].loc;
                }
                osp--;
            }
        }
    }
    /*for (int i = 0; i <= osp; i++) {
        cout << op[i].val << ", " << op[i].loc << "\n";
    }*/
    if (sp > 0) cout << 0 << "\n";
    else cout << op[osp].val << "\n";
    return 0;
}
#endif
