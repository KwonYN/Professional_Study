import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.StringTokenizer;
 
class Edge {
    int s, e, v;
 
    public Edge(int s, int e, int v) {
        this.s = s;
        this.e = e;
        this.v = v;
    }
}
 
public class Solution {
 
    static int N, M, T;
    static ArrayList<Edge> AL;
    static long[] D;
 
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
 
        for (int testcase = 1; testcase <= T; testcase++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            // AL = new ArrayList[N+1];
            AL = new ArrayList<>();
            D = new long[N + 1];
 
            // Init
            D[1] = 0;
            for (int i = 2; i <= N; i++) {
                D[i] = -1;
            }
 
            for (int i = 0; i < M; i++) {
                st = new StringTokenizer(br.readLine());
                int s = Integer.parseInt(st.nextToken());
                int e = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());
 
                AL.add(new Edge(s, e, v));
 
            }
 
            Collections.sort(AL, new Comparator<Edge>() {
                public int compare(Edge a, Edge b) {
                    return a.v - b.v;
                }
            });
 
            for (int i = 0; i < AL.size(); i++) {
                Edge cur = AL.get(i);
                int s = cur.s;
                int e = cur.e;
                int v = cur.v;
 
                long s_v = D[s];
                long e_v = D[e];
 
                if (D[s] != -1) {
                    long temp_e_v = D[s] + v;
                    e_v = Math.max(temp_e_v, D[e]);
                }
                if (D[e] != -1) {
                    long temp_s_v = D[e] + v;
                    s_v = Math.max(temp_s_v, D[s]);
                }
 
                D[e] = e_v;
                D[s] = s_v;
 
            }
 
            long sol = 0;
            for (int i = 0; i < N + 1; i++) {
                sol += D[i];
            }
 
            System.out.println("#" + testcase + " " + sol);
 
        }
 
    }
 
}
