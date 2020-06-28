import java.io.*;
import java.util.*;
 
class Solution
{
    static int T, N, M, INF = 987654321;
    static int[][] map;
    static int[][][] dp;
    public static void main(String[] args) throws Exception 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine().trim());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine().trim());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());           
            map = new int[N+1][M+1];
            String str = "";
            for(int i=1; i<=N; i++)
            {
                str = br.readLine().trim();
                for(int j=1; j<=M; j++)
                {
                    char ch = str.charAt(j-1);
                    if(ch == 'S' || ch == 'E' || ch == '.')
                        continue;
                    if(ch == '#')
                        map[i][j] = -1;
                    else
                        map[i][j] = ch - '0';
                }
            }       
             
            // 두 명이 동시에 출발한다고 생각하고, (이동한 거리, 첫번째 사람의 x좌표, 두번째 사람의 x좌표)를 가지고 3차원 dp를 만든다.(y좌표는 자동적으로 구해짐)
            dp = new int[N+M][N+1][N+1]; // dp[i][j][k] : i번 이동하여 첫번째 사람이 j행, 두번째 사람이 k행에 있을 때 주울 수 있는 최대 보석
            for(int i=0; i<N+M; i++)    
                for(int j=0; j<=N; j++)
                    for(int k=0; k<=N; k++)
                        dp[i][j][k] = -INF;
            dp[0][0][0] = 0;    
            for(int i=1; i<N+M; i++)
            {
                int end = i >= N ? N : i;
                int start = i <= M ? 1 : i - M + 1;      
                for(int j=start; j<=end; j++)
                {
                    for(int k=start; k<=end; k++)
                    {
                        int x1 = j;
                        int y1 = i - j + 1;
       
                        int x2 = k;
                        int y2 = i - k + 1;
       
                        if(map[x1][y1] == -1 || map[x2][y2] == -1)
                        {
                            dp[i][j][k] = -INF;
                            continue;
                        }
                         
                        dp[i][j][k] = Math.max(Math.max(dp[i-1][j-1][k], dp[i-1][j][k-1]), 
                                Math.max(dp[i-1][j][k], dp[i-1][j-1][k-1])) + map[x1][y1];                            
                        if(j != k)
                            dp[i][j][k] += map[x2][y2];
                    }
                }                   
            }   
            System.out.println("#" + tc + " " + dp[N+M-1][N][N]);
        }
    }
}
