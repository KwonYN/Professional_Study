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
                dp[i][j] = ww*dp[i-1][j]/tot + bb*dp[i][j-1]/tot + i*j*dp[i-1][j-1]/tot;
            }
        }
    }
}
