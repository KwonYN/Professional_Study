import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;
 
// (중상) [기출P-0046] 직사각형 체인
public class Solution {
    static int N;
    static int[][] map;
    static long[][] rect;
    static long[][] D;
    static final int MOD = 1000000007;
    public static void main(String[] args) throws Exception {
        // TODO Auto-generated method stub
        //System.setIn(new FileInputStream("input.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int T = Integer.parseInt(br.readLine());
                  
        for (int tc = 1; tc <=T; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken()); //  격자의 크기 N 이 주어진다 (2 ≤ N ≤ 1000). 
             
            map = new int[N+1][N+1];
            rect = new long[N+1][N+2];
            D = new long[N+1][N+1];
             
            for (int i=1; i<=N; i++) {
                st = new StringTokenizer(br.readLine());
                for (int j=1; j<=N; j++) {
                    /// 입출력
                    map[i][j] = Integer.parseInt(st.nextToken()); // N 개의 줄에 격자 교점에 적힌 숫자들 (1 이상 2N-2 이하의 정수)
                }                
            }          
                         
            // 1. 직사각형 체인을 구성하는 직사각형은 격자의 교점을 꼭짓점으로 가지며 변이 수평이나 수직인 것들이다.  
            // 2. 첫번째 직사각형은 격자의 제일 왼쪽 위 교점을 자신의 왼쪽 위 꼭짓점으로 가져야 한다. 
            // 3. 마지막 직사각형은 격자의 제일 오른쪽 아래 교점을 자신의 오른쪽 아래 꼭짓점으로 가져야 한다. 
            // 4. 직사각형 체인의 한 직사각형 A 다음에 직사각형 B가 온다면, A의 오른쪽 아래 꼭짓점과 B의 왼쪽 위 꼭짓점이 같아야 한다.
             
            long sum1, sum2;
            D[1][1] = rect[1][1] = 1;
             
            for (int i=1; i<=N; i++) {
                for (int j=1; j<=N; j++) {
                    if (i==1 && j==1)
                        continue;
                     
                    if (i+j-2 >= map[i][j]) {
                        if (i-map[i][j] >=1) 
                            sum1 = rect[i-map[i][j]-1][j+1];                        
                        else
                            sum1 = 0;
                         
                        if (j-map[i][j] >=1) 
                            sum2 = rect[i][j-map[i][j]];
                         
                        else
                            sum2 = rect[i-(map[i][j]-j+1)][1];                      
                         
                        D[i][j] = sum2 - sum1;
                         
                        if (D[i][j] < 0)
                            D[i][j] += MOD;
                        D[i][j] %=MOD;
                    }
                    rect[i][j] = rect[i-1][j+1] + D[i][j];
                    rect[i][j] %= MOD;
                }
            }
             
            // 모든 가능한 직사각형 체인의 개수를 출력
            bw.write("#" + tc + " " + D[N][N] + "\n");
            bw.flush();
        }
         
        bw.close();
    }
 
}
