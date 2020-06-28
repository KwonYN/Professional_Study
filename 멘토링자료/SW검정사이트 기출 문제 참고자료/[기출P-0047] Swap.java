import java.io.*;
import java.util.*;
 
class Solution
{   
    static int T, N;
    static int[] num = new int[5000];
    static int[][] dp = new int[5000][5000];
    public static void main(String[] args) throws Exception
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());   
 
            st = new StringTokenizer(br.readLine());
            for(int i=0; i<N; i++)
                num[i] = Integer.parseInt(st.nextToken());
             
            for(int i=N-1; i>0; i--)
            {
                int swap = 0;
                for(int j=i-1; j>=0; j--)
                {                   
                    if(num[i] < num[j])
                        swap++;
                    else if(num[i] > num[j])
                        swap--;
                    dp[i][j] = swap;
                }
            }
                 
            int ans = 0;
            int ansCnt = 1;
            for(int i=0; i<N-1; i++)
            {
                int swap = 0;
                for(int j=i+1; j<N; j++)
                {                   
                    if(num[i] > num[j])
                        swap++;
                    else if(num[i] < num[j])
                        swap--;
                     
                    if(num[i] <= num[j])
                        continue;
                     
                    int cnt = dp[j][i] + swap - 1;
                    if(ans < cnt)
                    {
                        ans = cnt;
                        ansCnt = 1;
                    }
                    else if(ans == cnt)
                    {
                        ansCnt++;
                    }
                }
            }           
             
            if(ans == 0)
                ansCnt = 0;
             
            System.out.println("#" + tc + " " + ans + " " + ansCnt);
        }
    }
}
