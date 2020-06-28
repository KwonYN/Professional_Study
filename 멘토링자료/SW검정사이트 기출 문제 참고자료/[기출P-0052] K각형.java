import java.io.*;
import java.util.*;
  
class Solution
{
    static int T, N;
    static Point p;
    static Point[] po0, po;
    static long[][][] dp;
    static long[] ans;
    public static void main(String[] args) throws Exception 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++)
        {
            N = Integer.parseInt(br.readLine());
            po0 = new Point[N];
            po = new Point[N];
            for(int i=0; i<N; i++)
            {
                StringTokenizer st = new StringTokenizer(br.readLine());
                po0[i] = new Point();
                po0[i].x = Long.parseLong(st.nextToken());
                po0[i].y = Long.parseLong(st.nextToken());
            }    
            Arrays.sort(po0, new CompPointY());            
            ans = new long[N+1];
            Arrays.fill(ans, Long.MAX_VALUE);           
            for(int i=0; i<N-2; i++)
            {               
                p = po0[i];  
                po = po0.clone();
                Arrays.sort(po, i+1, N, new CompPoint()); 
                  
                dp = new long[N][N][N+1];
                for(int j=0; j<N; j++)
                    for(int k=0; k<N; k++)
                        Arrays.fill(dp[j][k], -1);
                  
                for(int j=i+1; j<N-1; j++)
                {
                    for(int k=j+1; k<N; k++)
                    {
                        dp[j][k][3] = Math.abs(ccw(po[i], po[j], po[k]));
                        ans[3] = Math.min(ans[3], dp[j][k][3]);
                        for(int l=i+1; l<j; l++)
                        {
                            if(ccw(po[l], po[j], po[k]) > 0)
                            {
                                for(int m=4; m<=N-i; m++)
                                {
                                    if(dp[l][j][m-1] == -1)
                                        break;
                                       
                                    if(dp[j][k][m] == -1 || dp[j][k][m] > dp[l][j][m-1] + dp[j][k][3])
                                    {
                                        dp[j][k][m] = dp[l][j][m-1] + dp[j][k][3];
                                        ans[m] = Math.min(ans[m], dp[j][k][m]);
                                    }
                                }
                            }
                        }
                    }
                }
            }           
            System.out.print("#" + tc);
            for(int i=3; i<=N; i++)
            {
                if(ans[i] == Long.MAX_VALUE)
                    ans[i] = 0;
                System.out.print(" " + (ans[i]/2) + ((ans[i]%2 == 0)? ".0" : ".5"));         
            }
            System.out.println();
        }
    }   
    static class Point 
    {
        long x, y;
    }   
    static long ccw(Point p1, Point p2, Point p3)
    {
        return (p1.x*p2.y + p2.x*p3.y + p3.x*p1.y) - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y);
    }   
    static class CompPoint implements Comparator<Point>
    {
        public int compare(Point a, Point b) 
        {
            if(ccw(p, a, b) < 0)
                return 1;
            else
                return -1;
        }
    } 
    static class CompPointY implements Comparator<Point>
    {
        public int compare(Point a, Point b) 
        {
            return (int)(a.y - b.y);
        }
    } 
}
