// 감독_주영ver.
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;
#define INF (987654321)

struct NODE {
    int n, idx;
    NODE(){}
    NODE(int x, int y) {this->n = x; this->idx = y;}
};

NODE getMin(NODE a, NODE b) {
    if (a.n < b.n) return a;
    if (b.n < a.n) return b;
    if (a.idx < b.idx) return a;
    return b;
}

NODE getMax(NODE a, NODE b) {
    if (a.n > b.n) return a;
    if (b.n > a.n) return b;
    if (a.idx > b.idx) return a;
    return b;
}

NODE maketree(int s, int e, int index, int arr[], NODE tree[], NODE (*func)(NODE, NODE))
{
    if (s == e) return tree[index] = NODE(arr[s], s);
    int m = (s + e) / 2;
    return tree[index] = func(maketree(s, m, index<<1, arr, tree, func),
                            maketree(m + 1, e, (index<<1)+1, arr, tree, func));
}

NODE query(int s, int e, int index, int left, int right, NODE tree[], NODE (*func)(NODE, NODE), int v)
{
    if (left > e || right < s) return NODE(v, v);
    if (left <= s && e <= right) return tree[index];
    int m = (s + e) / 2;
    return func(query(s, m, index<<1, left, right, tree, func, v),
                query(m+1, e, (index<<1)+1, left, right, tree, func, v));
}

int N, K, high[300002], low[3000002];
NODE * high_tree;
NODE * low_tree;

int main()
{
    int TC; scanf("%d", &TC);
    for (int t = 1; t <= TC; t++) {
        scanf("%d %d", &N, &K);
        for (int n = 1; n <= N; n++) scanf("%d %d", &low[n], &high[n]);
        high_tree = new NODE [N*2+2];
        low_tree = new NODE [N*2+2];
        maketree(1, N, 1, high, high_tree, getMax);
        maketree(1, N, 1, low, low_tree, getMin);
        int ans_sub = INF, ans_index = INF;
        for (int i = 1; i <= N-K+1; i++) {
            int tmp_sub, tmp_index;
            NODE high_1st = query(1, N, 1, i, i+K-1, high_tree, getMax, -1);
            NODE high_2nd = getMax(query(1, N, 1, i, high_1st.idx-1, high_tree, getMax, -1),
                                   query(1, N, 1, high_1st.idx+1, i + K - 1, high_tree, getMax, -1));
            NODE low_1st = query(1, N, 1, i, i+K-1, low_tree, getMin, INF);
            NODE low_2nd = getMin(query(1, N, 1, i, low_1st.idx-1, low_tree, getMin, INF),
                                  query(1, N, 1, low_1st.idx+1, i + K - 1, low_tree, getMin, INF));
            int tmp = high_1st.n - low_2nd.n > high_2nd.n - low_1st.n;
            if (tmp > 0) {
                tmp_sub = high_2nd.n - low_1st.n; 
                tmp_index = high_1st.idx;
            } else if (tmp < 0) {
                tmp_sub = high_1st.n - low_2nd.n;
                tmp_index = low_1st.idx;
            } else {
                tmp_sub = high_1st.n - low_2nd.n;
                tmp_index = (high_1st.idx <= low_1st.idx ? high_1st.idx : low_1st.idx);
            }
            if (ans_sub > tmp_sub) {
                ans_sub = tmp_sub;
                ans_index = tmp_index;
            }
        }
        printf("#%d %d %d\n", t, ans_sub, ans_index);
    }

    return 0;
}
