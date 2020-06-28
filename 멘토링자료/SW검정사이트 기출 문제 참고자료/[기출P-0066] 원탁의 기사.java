import java.io.*;
import java.util.*;
 
class Solution
{ 
    public static void main(String[] args) throws Exception 
    { 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine()); 
        for(int tc=1; tc<=T; tc++) 
        {
            int N = Integer.parseInt(br.readLine());
            int[] w = new int[N+1];
            int[] l = new int[N+1];
             
            // dp[i][j] = 그룹 변경을 i번했을때 j위치까지의 최대값
            int[][] dpW = new int[5][N+1]; // 승 패 승 패 승
            int[][] dpL = new int[5][N+1]; // 패 승 패 승 패
             
            for(int i=1; i<=N; i++) 
            { 
                StringTokenizer st = new StringTokenizer(br.readLine());
                w[i] = Integer.parseInt(st.nextToken());
                l[i] = Integer.parseInt(st.nextToken()); 
            } 
             
            for(int i=1; i<=N; i++) 
            {
                dpW[0][i] = dpW[0][i-1] + w[i]; 
                dpL[0][i] = dpL[0][i-1] + l[i];
            } 
             
            for(int i=1; i<=4; i++)
            {
                for(int j=i+1; j<=N; j++) 
                {
                    int a = (i & 1) == 0 ? w[j] : l[j];
                    int b = (i & 1) != 0 ? w[j] : l[j];
                    dpW[i][j] = Math.max(dpW[i-1][j-1], dpW[i][j-1]) + a;
                    dpL[i][j] = Math.max(dpL[i-1][j-1], dpL[i][j-1]) + b;                            
                }
            }
              
            int ans  = Math.max(Math.max(dpW[3][N], dpW[4][N]), Math.max(dpL[3][N], dpL[4][N]));
            System.out.println("#" + tc + " " + ans); 
        }
    } 
}
