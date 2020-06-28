import java.io.*;
import java.util.*;
//검문소 정리소스
public class Solution {
    static int N, M;
    static ArrayList<ArrayList<Integer>> town;
    static int visited[];
    static boolean load[];
    static long dp[];
    static long result;
 
    public static void main(String[] args) throws Exception {
 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
 
        int T = Integer.parseInt(br.readLine()); // Test
 
        for (int t = 1; t <= T; t++) {
            st = new StringTokenizer(br.readLine(), " ");
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
 
            town = new ArrayList<ArrayList<Integer>>();
            visited = new int[N + 1];
            load = new boolean[M + 1];
            dp = new long[N + 1];
            result = -1;
            for (int i = 0; i <= N; i++) {
                town.add(new ArrayList<Integer>());
            }
            for (int i = 1; i <= M; i++) {
                st = new StringTokenizer(br.readLine(), " ");
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                town.get(a).add(b);
                town.get(b).add(a);
            }
 
            dfs(1, 0, 1);
            System.out.print("#" + t + " ");
            System.out.println(result > 0 ? result : -1);
 
        }
 
    }
 
    private static int dfs(int now, int prev, int depth) {
        visited[now] = depth;
        int ret = visited[now];
         
        for (int i = 0; i < town.get(now).size(); i++) {
            int next = town.get(now).get(i);
            if (prev == next) continue; // 부모로는 다시 가지않는다.
            if (visited[next] == 0) { // 처음방문하는 곳이면
                int ret2 = dfs(next, now, depth + 1);
                if(ret2 > depth) {//단절선
                    result = Math.max(result, (N-(dp[next]+1))*(dp[next]+1)*2);
                }
                    ret = Math.min(ret, ret2);
            } else {
                ret = Math.min(ret, visited[next]);
            }
        }
        dp[prev] = dp[prev] + dp[now] + 1;
        return ret;
    }
 
}
