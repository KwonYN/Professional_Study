import java.io.*;
import java.util.*;
 
public class Solution {
    static class Group {
        public int minx, maxx, miny, maxy;
        public int cnt;
    }
    static class Line {
        public int x1, y1, x2, y2;
        public int minx, maxx, miny, maxy;
        public Line(int x1, int y1, int x2, int y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
            this.minx = Math.min(x1, x2);
            this.maxx = Math.max(x1, x2);
            this.miny = Math.min(y1, y2);
            this.maxy = Math.max(y1, y2);
        }
    }
    static int T;
    static int N, M, K;
    static Line[] L = new Line[2001];
    static Group[] G = new Group[2001];
    static int[] par = new int[2001];
    static int[] root = new int[2001];
    static int[] X = new int[4001];
    static int[] Y = new int[4001];
    static int[] Xc = new int[4001];
    static int[] Yc = new int[4001];
    static int A, B, C;
     
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        for (int n = 1; n <= 2000; n++) {
            G[n] = new Group();
        }
 
        T = Integer.parseInt(br.readLine());
        for (int test_case = 1; test_case <= T; test_case++) {
            N = Integer.parseInt(br.readLine());
             
            int a, b;
            int x1, y1, x2, y2;
            StringTokenizer st;
            for (int i = 1; i <= N; i++) {
                st = new StringTokenizer(br.readLine());
                x1 = Integer.parseInt(st.nextToken());
                y1 = Integer.parseInt(st.nextToken());
                x2 = Integer.parseInt(st.nextToken());
                y2 = Integer.parseInt(st.nextToken());
                L[i] = new Line(x1, y1, x2, y2);
            }
            Arrays.sort(L, 1, N+1, new Comparator<Line>() {
                @Override
                public int compare(Line o1, Line o2) {
                    return o1.minx - o2.minx;
                }
            });
            for (int i = 1; i <= N; i++) {
                G[i].minx = L[i].minx; G[i].maxx = L[i].maxx;
                G[i].miny = L[i].miny; G[i].maxy = L[i].maxy;
                G[i].cnt = 1;
                par[i] = i;
            }
            for (int i = 1; i <= N; i++) {
                for (int j = i+1; j <= N; j++) {
                    if (L[i].maxx < L[j].minx) break;
                    if (!isCross(L[i], L[j])) continue;
                    union (i, j);
                }
            }
            for (int i = 1; i <= N; i++) find(i);
             
            A = 0; B = 0; C = 0;
 
            int xs = 0, ys = 0;
            for (int i = 1; i <= N; i++) {
                if (par[i] != i) continue;
                X[xs++] = G[i].minx; X[xs++] = G[i].maxx;
                Y[ys++] = G[i].miny; Y[ys++] = G[i].maxy;
                B = Math.max(B, G[par[i]].cnt);
                root[A++] = i;
            }
 
            int nxs = 0, nys = 0;
            Xc[nxs] = 0; Yc[nys] = 0;
            Arrays.sort(X, 0, xs);
            Arrays.sort(Y, 0, ys);
            for (int xi = 1; xi < xs; xi++) {
                if (X[nxs] != X[xi]) { X[++nxs] = X[xi]; Xc[nxs] = 0; }
            }
            for (int yi = 1; yi < ys; yi++) {
                if (Y[nys] != Y[yi]) { Y[++nys] = Y[yi]; Yc[nys] = 0; }
            }
            nxs++; nys++;
             
            int s, e;
            for (int i = 0; i < A; i++) {
                int ix = root[i];
                s = Arrays.binarySearch(X, 0, nxs, G[ix].minx);
                e = Arrays.binarySearch(X, 0, nxs, G[ix].maxx);
                Xc[s]++; Xc[e+1]--;
                s = Arrays.binarySearch(Y, 0, nys, G[ix].miny);
                e = Arrays.binarySearch(Y, 0, nys, G[ix].maxy);
                Yc[s]++; Yc[e+1]--;
            }
            int maxCon = Math.max(Xc[0], Yc[0]);
            for (int xi = 1; xi < nxs; xi++) { Xc[xi] += Xc[xi-1]; maxCon = Math.max(maxCon, Xc[xi]); }
            for (int yi = 1; yi < nys; yi++) { Yc[yi] += Yc[yi-1]; maxCon = Math.max(maxCon, Yc[yi]); }
            C = A - maxCon + 1;
             
            bw.write("#" + test_case + " " + A + " " + B + " " + C + "\n");
        }
        bw.flush();
        bw.close();
    }
     
    public static void union(int a, int b) {
        int A = find(a);
        int B = find(b);
        if (A == B) return;
        par[B] = A;
        G[A].minx = Math.min(G[A].minx, G[B].minx);
        G[A].maxx = Math.max(G[A].maxx, G[B].maxx);
        G[A].miny = Math.min(G[A].miny, G[B].miny);
        G[A].maxy = Math.max(G[A].maxy, G[B].maxy);
        G[A].cnt += G[B].cnt;
    }
 
    public static int find(int i) {
        if (par[i] != i) par[i] = find(par[i]);
        return par[i];
    }
     
    public static boolean isCross(Line l1, Line l2) {
        if (l1.maxx < l2.minx || l2.maxx < l1.minx
         || l1.maxy < l2.miny || l2.maxy < l1.miny) 
            return false;
        int a = ccw(l1.x1, l1.y1, l1.x2, l1.y2, l2.x1, l2.y1);
        int b = ccw(l1.x1, l1.y1, l1.x2, l1.y2, l2.x2, l2.y2);
        int c = ccw(l2.x1, l2.y1, l2.x2, l2.y2, l1.x1, l1.y1);
        int d = ccw(l2.x1, l2.y1, l2.x2, l2.y2, l1.x2, l1.y2);
        if (0 >= a*b && 0 >= c*d) return true;
        return false;
    }
 
    public static int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
        long ret = (long)(x2-x1)*(y3-y1) - (long)(x3-x1)*(y2-y1);
        return (ret == 0)? 0 : (ret < 0)? -1 : 1; 
    }
}
