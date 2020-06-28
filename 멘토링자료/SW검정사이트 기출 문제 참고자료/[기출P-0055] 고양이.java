
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
 
import java.io.*;
import java.util.*;
 
public class Solution {
    public static int T;
    public static int N;
    public static int[] A = new int[300001];
    public static List<Integer>[] graph = new List[300001];
    public static long[][] D = new long[300001][2];
    public static long Answer;
     
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
 
        for (int i = 1; i <= 300000; i++) graph[i] = new ArrayList<Integer>();
         
        T = Integer.parseInt(br.readLine());
        for (int test_case = 1; test_case <= T; test_case++) {
            N = Integer.parseInt(br.readLine());
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                A[i] = Integer.parseInt(st.nextToken());
                graph[i].clear();
            }
            int a, b;
            for (int i = 1; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                a = Integer.parseInt(st.nextToken());
                b = Integer.parseInt(st.nextToken());
                graph[a].add(b);
                graph[b].add(a);
            }
             
            dfs(1, 0);
             
            bw.write("#" + test_case + " " + ((D[1][0] + D[1][1])%1000000007) + "\n");
        }
        bw.flush();
        bw.close();
        br.close();
    }
 
 
    private static void dfs(int curr, int par) {
        D[curr][1] = A[curr];
        D[curr][0] = -1*(D[curr][1]-1);
         
        for (int next : graph[curr]) {
            if (next == par) continue;
            dfs(next, curr);
            D[curr][1] = (2*D[curr][1]*D[next][0] + (D[curr][1]+D[curr][0])*D[next][1]) % 1000000007;
            D[curr][0] = (2*D[curr][0]*D[next][0] + D[curr][0]*D[next][1]) % 1000000007;
        }
    }
 
}
 