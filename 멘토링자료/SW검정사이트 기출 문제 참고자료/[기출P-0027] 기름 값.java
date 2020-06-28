import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;
 
public class Solution {
     
    static int N, L;
     
    static int dist, cost;
    static int[][] dp;
 
    public static void main(String[] args) throws Exception {
        //System.setIn(new FileInputStream("sample_input.txt"));
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
         
        int T = Integer.parseInt(br.readLine());
         
        for(int index = 1; index <= T; index++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            L = Integer.parseInt(st.nextToken());
             
            int solution = findSolution(br);
             
            bw.write("#" + index + " " + solution +"\n");
            bw.flush();
        }
         
        bw.close();
        br.close();
    }
     
    private static int findSolution(BufferedReader br) throws Exception {
        StringTokenizer st = new StringTokenizer(br.readLine());
        int cost = Integer.parseInt(st.nextToken());
         
        dp = new int[N + 1][L + 1];
         
        for(int index = 1; index <= L; index++) {
            dp[1][index] = cost * index;
        }
         
        for(int index = 2; index <= N; index++) {
            dist = Integer.parseInt(st.nextToken());
            cost = Integer.parseInt(st.nextToken());
             
            //예외 처리, 기름통보다 큰 거리가 있을 경우 이동 불가능
            if(dist > L) {
                return -1;
            }
             
            //DP배열 채우기
            dp[index][0] = dp[index - 1][dist];
            for(int j = 1; j <= L; j++) {
                if(j + dist <= L) {
                    dp[index][j] = Math.min(dp[index - 1][j + dist], dp[index][j - 1] + cost);
                } else {
                    dp[index][j] = dp[index][j - 1] + cost;
                }
            }
        }
        return dp[N][0];
    }
}
