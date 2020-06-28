import java.io.*;
import java.util.*;
 
class Solution
{
    static int T, W, B, MAX = 1000;
    static double[][] dp = new double[MAX+1][MAX+1]; // dp[i][j] : 백마 i이고 흑마 j일때 백마가 남을 확률
    public static void main(String[] args) throws Exception 
    {
        process();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            W = Integer.parseInt(st.nextToken());
            B = Integer.parseInt(st.nextToken());
            //System.out.printf("#%d %.6f %.6f %.6f\n", tc, dp[W][B], dp[B][W], 1-dp[W][B]-dp[B][W]);
            System.out.println("#" + tc + " " + dp[W][B] + " " + dp[B][W] + " " + (1-dp[W][B]-dp[B][W]));
        }
    }   
 
    static void process()
    {
        for(int i=1; i<=MAX; i++)
            dp[i][0] = 1;
     
        for(int i=1; i<=MAX; i++)
        {
            for(int j=1; j<=MAX; j++)
            {
                int tot = (i+j)*(i+j-1)/2;
                int ww = i*(i-1)/2;
                int bb = j*(j-1)/2;
                dp[i][import java.util.*;
import java.io.*;
  public class Solution {
   static int T, N, M, B, ans;
   static ArrayList<Edge>[] map;
   static int[][] dp;
    
   public  static class Edge {
      int node, cost;
      Edge (int node, int cost) {
         this.node = node;
         this.cost = cost;
      }
   }
   public static void main(String[] argus) throws Exception {
      //System.setIn(new FileInputStream("자동차여행.txt"));
      BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      StringTokenizer st = new StringTokenizer(br.readLine());
      T = Integer.parseInt(st.nextToken());
      for(int tc = 1; tc <= T; tc ++) {
         st = new StringTokenizer(br.readLine());
         N = Integer.parseInt(st.nextToken()); //도시 수 2<=N<=5000
         M = Integer.parseInt(st.nextToken()); //도로 수 1<=M<=1,000,000
         B = Integer.parseInt(st.nextToken()); //통행료  1,000 <= B<=1,000,000
         map = new ArrayList [N+1];
         for(int i = 1; i <=N; i++) {
            map[i] = new ArrayList<Edge>();
         }
          
         for(int i=1; i <= M; i++) {
            st = new StringTokenizer(br.readLine());
            int S = Integer.parseInt(st.nextToken());
            int E = Integer.parseInt(st.nextToken());
            int C = Integer.parseInt(st.nextToken());
            if( C <=B )
            map[S].add(new Edge(E, C));     
            
         }
          
         ans = repeat();
         bw.write("#"+tc + " ");
         bw.write(String.valueOf(ans));
         bw.write("\n");
         bw.flush();
      }
      bw.close();
   }
   static int repeat() {
      dp = new int[1001][N+1]; //dp[i][j] :i번 이동 후 j 도시에 도착해쓸 때의 누적통행료
      //초기값
      int ret = 0;
      for(int i=0; i <= 1000; i++) {
         Arrays.fill(dp[i], 987654321);
      }
      for(int i=0; i < map[1].size(); i++) {
         int node = map[1].get(i).node;
         int cost = map[1].get(i).cost;
         if(dp[1][node] > cost) {
            dp[1][node] = cost;
         }
         ret = 1;
      }
       
      for(int i=1; i <= B/1000; i++) { //통행료 / 최소통행료 = 몇번
         for(int j=1; j <= N; j++) { // 출발도시
            for(int k=0; k < map[j].size(); k++) { //도착도시
               if( B >= dp[i][j]) {
                  int n = map[j].get(k).node;
                  int cost = dp[i][j] + map[j].get(k).cost;
                  if( cost <= B && cost <= dp[i+1][n]) { //이전값이 있으면
                     dp[i+1][n] = cost;
                     if(ret <= i+1) {
                        ret = i+1;
                     }                     
                  }
               }
                
            }
         }
      }
       
      return ret;
   }
    
    
    
}
