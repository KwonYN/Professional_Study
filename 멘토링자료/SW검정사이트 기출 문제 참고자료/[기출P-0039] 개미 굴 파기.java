import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.StringTokenizer;
 
public class Solution {
    static BufferedReader br;
    static BufferedWriter bw;
    static StringTokenizer st;
     
    static int N;
    static int[][] edges;
    static int[] sets;
    static List<int[]>[] nodes;
    static int[] vOrd;
    static int ans;
    public static void main(String[] args) throws Exception {
        //long start = System.currentTimeMillis();
        //System.setIn(new FileInputStream(Solution.class.getResource("sample_input2.txt").getPath()));
        br = new BufferedReader(new InputStreamReader(System.in));
        bw = new BufferedWriter(new OutputStreamWriter(System.out));
         
        int T = Integer.parseInt(br.readLine());
        for (int testCase = 1; testCase <= T; testCase++) {
            N = Integer.parseInt(br.readLine());
             
            nodes = new List[N+1];
            sets = new int[N+1];
            vOrd = new int[N+1];
             
            for (int i = 0; i <= N; i++) {
                nodes[i] = new ArrayList<int[]>();
                sets[i] = i;
            }
             
            edges = new int[N][3];
            for (int i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                edges[i][0] = Integer.parseInt(st.nextToken());
                edges[i][1] = Integer.parseInt(st.nextToken());
                edges[i][2] = Integer.parseInt(st.nextToken());
                nodes[edges[i][0]].add(new int[] {edges[i][1], edges[i][2]});
                nodes[edges[i][1]].add(new int[] {edges[i][0], edges[i][2]});
            }
             
            Arrays.sort(edges, new Comparator<int[]>() {
                public int compare(int[] o1, int[] o2) {
                    if(o1[2] < o2[2]) return -1;
                    if(o1[2] > o2[2]) return 1;
                    return 0;
                }
            });
                 
            bw.write("#" + testCase + " " + kruscal() +"\n");
            bw.flush();
        }
         
        //long end = System.currentTimeMillis();
        //bw.write("Time="+(end-start)+"ms\n");
        br.close();
        bw.flush();
        bw.close();
    }
     
    private static int kruscal() {
        int k = 0;
        int W = 0;
        int V = 0;
         
        for (int i = 0; i < N; i++) {
            if(isUnion(edges[i][0], edges[i][1])) {
                V = edges[i][0];
                W = edges[i][2];
            }else {
                union(edges[i][0], edges[i][1]);
                k++;
            }
        }
         
        if(k != N-1) return 0;
        return dfs(V, V, W, 1);
    }
     
    private static int dfs(int n, int s, int w, int o) {
        if(vOrd[n] > 0) {
            if(n == s) return 0;
            else return -1;
        }
         
        vOrd[n] = o;
        int sub = -1;
        for (int[] e : nodes[n]) {
            if(vOrd[e[0]] > 0 && vOrd[e[0]] == o-1) continue;
            int ret = dfs(e[0], s, w, o+1);
             
            if(ret > sub) {
                sub = ret;
                if(e[1] == w) sub++;
            }
        }
        return sub;
    }
 
    private static void union(int a, int b) {
        sets[find(a)] =find(b);
    }
    private static boolean isUnion(int a, int b) {
        return find(a)==find(b);
    }
     
    private static int find(int a) {
        if(sets[a] == a) return a;
        return sets[a] = find(sets[a]);
    }
}
