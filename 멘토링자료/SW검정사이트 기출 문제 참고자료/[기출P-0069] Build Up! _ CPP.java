#include <cstdio>
 
#define MAX_N   100
 
int mvs[8][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
int N, M, nos[MAX_N][MAX_N], ans;
int sets[MAX_N * MAX_N], mins[MAX_N * MAX_N][2], maxes[MAX_N * MAX_N][2], que[MAX_N * MAX_N][2];
bool visited[MAX_N][MAX_N];
 
int findSet(const int &a) {
    if (sets[a] == a) return a;
    else return sets[a] = findSet(sets[a]);
}
 
int findSet(const int &n, const int &m) {
    return findSet(n * M + m);
}
 
void unionSet(const int &s, const int &n, const int &m) {
    int b = findSet(n, m);
 
    sets[b] = s;
    if (maxes[b][0] > maxes[s][0]) maxes[s][0] = maxes[b][0];
    if (maxes[b][1] > maxes[s][1]) maxes[s][1] = maxes[b][1];
 
    if (mins[b][0] < mins[s][0]) mins[s][0] = mins[b][0];
    if (mins[b][1] < mins[s][1]) mins[s][1] = mins[b][1];
}
 
void bfs(const int &s) {
    int sIdx = -1, eIdx = -1, n, m, tn, tm, i;
    int NL = mins[s][0], NH = maxes[s][0], ML = mins[s][1], MH = maxes[s][1];
 
    for (n = NL; n <= NH; ++n) {
        for (m = ML; m <= MH; ++m) {
            visited[n][m] = false;
        }
    }
 
    for (m = ML; m <= MH; ++m) que[++eIdx][0] = NL, que[eIdx][1] = m, visited[NL][m] = true;
    if (NH > NL) {
        n = NH;
        for (m = ML; m <= MH; ++m) que[++eIdx][0] = n, que[eIdx][1] = m, visited[n][m] = true;
 
        for (n = NL + 1; n < NH; ++n) {
            que[++eIdx][0] = n, que[eIdx][1] = ML, visited[n][ML] = true;
            if (MH > ML) que[++eIdx][0] = n, que[eIdx][1] = MH, visited[n][MH] = true;
        }
    }
 
    while (++sIdx <= eIdx) {
        n = que[sIdx][0], m = que[sIdx][1];
 
        if (s == findSet(n, m)) ++ans;
        else {
            for (i = 0; i < 4; ++i) {
                tn = n + mvs[i][0], tm = m + mvs[i][1];
                if (tn >= NL && tn <= NH && tm >= ML && tm <= MH && !visited[tn][tm]) {
                    que[++eIdx][0] = tn, que[eIdx][1] = tm, visited[tn][tm] = true;
                }
            }
            for (i = 4; i < 8; ++i) {
                tn = n + mvs[i][0], tm = m + mvs[i][1];
                if (tn >= NL && tn <= NH && tm >= ML && tm <= MH && !visited[tn][tm] && (s != findSet(tn, tm))) {
                    que[++eIdx][0] = tn, que[eIdx][1] = tm, visited[tn][tm] = true;
                }
            }
        }
    }
}
 
int main() {
    int TC, iCase;
    int n, m, tn, tm, i, s;
    char input[MAX_N + 1];
 
    //freopen("C:/sample_input.txt", "r", stdin);
 
    scanf("%d", &TC);
 
    for (iCase = 1; iCase <= TC; ++iCase) {
        scanf("%d %d", &N, &M);
 
        s = -1, ans = 0;
        for (n = 0; n < N; ++n) {
            scanf("%s", input);
            for (m = 0; m < M; ++m) {
                ++s;
                sets[s] = s, mins[s][0] = maxes[s][0] = n, mins[s][1] = maxes[s][1] = m;
                nos[n][m] = input[m] - '0';
 
                for (i = 0; i < 2; ++i) {
                    tn = n + mvs[i][0], tm = m + mvs[i][1];
                    if (tn >= 0 && tm >= 0) {
                        if (nos[n][m] == nos[tn][tm]) unionSet(s, tn, tm);
                    }
                }
            }
        }
 
        s = -1;
        for (n = 0; n < N; ++n) {
            for (m = 0; m < M; ++m) {
                if (++s == findSet(n, m)) bfs(s);
            }
        }
 
        printf("#%d %d\n", iCase, ans);
    }
 
    return 0;
}
