import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;
 
public class Solution {
     
    static int N;
    static long ans;
     
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
 
        int T = Integer.parseInt(br.readLine());
 
        for (int t = 1; t <= T; t++) {
 
            st = new StringTokenizer(br.readLine());
 
            N = Integer.parseInt(st.nextToken());
             
            int car [] = new int [N+1];
             
            st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                int num = Integer.parseInt(st.nextToken());
                car[num] = i;
            }
             
            ans = 0;
             
            if(N == 1) {
                System.out.println("#"+ t+" "+0);
                continue;
            }
             
            long [][] dp = new long [N+1][2];
             
            // 정방향 [i][0]
            dp[1][0] = calc(1, car[1]);
            // 역방향 [i][1]
            dp[1][1] = 2000000000;
             
            dp[2][0] = dp[1][0] + calc(car[1], car[2]);
            dp[2][1] = calc(1,car[2]) + calc(car[2], car[1]);
             
            for (int i = 3; i <= N; i++) {
                dp[i][0] = Math.min( dp[i-1][0] + calc(car[i-1], car[i]), 
                                     dp[i-1][1] + calc(car[i-2], car[i]));
                dp[i][1] = Math.min( dp[i-2][0] + calc(car[i-2], car[i]) + calc(car[i], car[i-1]),
                                     dp[i-2][1] + calc(car[i-3], car[i]) + calc(car[i], car[i-1]));
            }
             
            ans = Math.min(dp[N][0], dp[N][1]);
            System.out.println("#" + t + " " + ans);
 
        }
    }
     
    static long calc(int a, int b){
         
        long big = Math.max(a, b);
        long small = Math.min(a, b);
         
        long r = big - small;
        long l = N - (big - small);
         
        return Math.min(r, l);
    }
}
