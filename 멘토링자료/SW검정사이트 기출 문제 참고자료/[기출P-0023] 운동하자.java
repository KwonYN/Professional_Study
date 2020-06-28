import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
  
public class Solution {
    static int T,N,M;
    static final long MAX = 600000000000L;
    static final long MOD = 1000000007L;
    static long[][] roads = new long[501][501];
    static long[][] shorestRoad = new long[501][501];
    static long[][] DP ;  //DP[i][j]: 1번 교차로에서부터  i 번 이동 시, j 위치 경우의 수
    public static ArrayList<Integer>[] list = new ArrayList[501];
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for (int tc = 1; tc <= T; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());   // 500
            M = Integer.parseInt(st.nextToken());
            //DP = new long[N+1][N];
            DP = new long[N+1][N+1];
            for (int i = 1; i < N+1; i++) {
                for (int j = 1; j < N+1; j++) {
                    if(i==j) continue;
                    roads[i][j] =  MAX;
                    shorestRoad[i][j] =  MAX;
                }
            }
              
            for (int i = 0; i < M; i++) {
                st = new StringTokenizer(br.readLine());
                int s = Integer.parseInt(st.nextToken());
                int e = Integer.parseInt(st.nextToken());
                long w = Long.parseLong(st.nextToken());
                roads[s][e] = roads[e][s]  = w;
                shorestRoad[s][e]  = shorestRoad[e][s]  = w;
            }
              
            for (int i = 1; i < N+1; i++) {
                list[i] = new ArrayList<Integer>();
            }
  
            flowdW();
            removeShortest();
  
            //DP[i][j]: 1번 교차로에서부터  i 번 이동 시, j 위치 경우의 수
            DP[0][1] = 1;
            for (int i = 0; i < N; i++) {
                for (int j = 1; j < N+1; j++) {
                    for (int adjN : list[j]) {
                        DP[i+1][adjN] = (DP[i+1][adjN]+DP[i][j])%MOD;
                    }
                }
            }
              
            long sum = 0;
            for (int i = 1; i < N; i++) {
                sum = (sum+DP[i][2])%MOD;
            }
            System.out.println("#"+tc+" " + sum );
        }
        br.close();
    }
      
    public static void flowdW() {
        for (int k = 1; k < N+1; k++) {
            for (int i = 1; i < N+1; i++) {
                for (int j = 1; j < N+1; j++) {
                    if( shorestRoad[i][j] > shorestRoad[i][k] + shorestRoad[k][j]){
                        shorestRoad[i][j] = shorestRoad[i][k] + shorestRoad[k][j];
                    }
                }
            }           
        }
    }
      
    public static void removeShortest() {
        for (int i = 1; i < N+1; i++) {
            for (int j = 1; j < N+1; j++) {
                if(i==j)continue;
                if(roads[i][j] ==MAX || shorestRoad[i][j] ==MAX) continue;
                if(roads[i][j] == shorestRoad[i][j] ) continue;
                list[i].add(j);
            }
        }
    }   
}
