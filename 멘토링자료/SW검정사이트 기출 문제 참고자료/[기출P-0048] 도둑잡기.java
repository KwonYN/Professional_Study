import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class Solution {
     
    static boolean dfs(int node) {
         
        visited[node] = true;
        for (int i = 0; i < map[node].size(); i++) {
             
            int next = map[node].get(i);
            if (!visited[next]) {
                if(dfs(next))
                    return true;
            }
            else if (!finished[next]) {
                return true;
            }
        }
        finished[node] = true;
        return false;
         
    }
     
    static boolean IsCycle(int pos, int end) {
         
        if(pos == end) {
            return true;
        }
         
        visited[pos] = true;
 
        for (int i = 0; i < map[pos].size(); i++) {
            int next = map[pos].get(i);
            if(visited[next] == false)
                if(IsCycle(next,end))
                    return true;
        }
         
        return false;
    }
     
    static int T,N,M,roadCnt;
    static ArrayList<Integer>[] map;
    static int[][] road;
    static boolean[] visited;
    static boolean[] finished;
    static StringTokenizer st;
     
    public static void main(String[] args) throws Exception, IOException {
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
         
        T = Integer.parseInt(br.readLine());
         
        for (int tc = 1; tc <= T ; tc++) {
             
            st = new StringTokenizer(br.readLine());
             
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
             
            map = new ArrayList[N + 1];
             
            for (int i = 0; i <= N; i++) {
                map[i] = new ArrayList<Integer>();
            }
 
            road = new int[M + 1][2];
            roadCnt = 0;
            for (int i = 0; i < M; i++) {
                st = new StringTokenizer(br.readLine());
                 
                int from = Integer.parseInt(st.nextToken());
                int to = Integer.parseInt(st.nextToken());
                int direction = Integer.parseInt(st.nextToken());
                 
                //단방향인 것들만 인접리스트로 작성, 양방향인 것들은 road[][]에 담는다??
                 
                if (direction == 1) {
                    map[from].add(to);
                }
                else {
                    road[roadCnt][0] = from;
                    road[roadCnt][1] = to;
                     
                    roadCnt++;
                }
                 
            }
             
            int[] ans = new int[roadCnt];
             
            visited = new boolean[N+1];
            finished = new boolean[N+1];
             
            boolean find = false;
            for (int i = 1; i <= N; i++) {
                if (dfs(i)) {
                    System.out.print("#" + tc + " ");
                    System.out.println("impossible");
                    find = true;
                    break;
                }
            }
            if(find)
               continue;
             
             
            //싸이클이 여부에 따라 양방향
            for (int i = 0; i < roadCnt; i++) {
                 
                Arrays.fill(visited, false);
                int from = road[i][0];
                int to = road[i][1];
                 
                boolean possible = IsCycle(to,from);
                 
                if(!possible) {
                    map[from].add(to);
                    ans[i] = 0;
                }
                else {
                    map[to].add(from);
                    ans[i] = 1;
                }
                 
            }
             
            System.out.print("#" + tc + " ");
            for(int i=0; i<roadCnt; i++)
                System.out.print(String.valueOf(ans[i]));
            System.out.println();
 
             
             
        }
         
         
         
    }
 
}
