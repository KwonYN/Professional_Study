import java.io.*;
import java.util.*;
 
public class Solution {
    static int N, K, T;
    static long Ans, Data[][], PairCnt;
    static long div = 1000000007;
 
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
 
        T = Integer.parseInt(st.nextToken());
        for (int testCase = 1; testCase <= T; testCase++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());
            Data = new long[N + 1][N + 1];
            Ans = 0;
            PairCnt = 0;
 
            if (K == 0) {
                Ans = 0;
            } else {
                func01();
 
                long target = 1;
                for (int i = 1; i <= (N * N) - 2; i++) {
                    target *= 2;
                    if (target >= div)
                        target %= div;
                }
                Ans = (PairCnt * target) % div;
            }
            System.out.println("#" + testCase + " " + Ans);
        }
        br.close();
    }
 
    public static void func01() {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                for (int ik = 0; ik <= K; ik++) {
                    // 각 i,j 위치에서 K 이내만큼 떨어져있는 칸이 몇칸인지 체크
                    if (ik + i > N)
                        break;
                    if (ik == 0) {
                        Data[i][j] += Math.min(N - j, K); // 오른쪽
                    } else {
                        Data[i][j] = Data[i][j] + Math.min(j - 1, K - ik) + Math.min(N - j, K - ik) + 1; // 왼쪽 + 오른쪽 +
                                                                                                            // 가운데
                    }
                    if (Data[i][j] >= div)
                        Data[i][j] %= div;
                }
 
                // 누적 합
                PairCnt += Data[i][j];
                if (PairCnt >= div)
                    PairCnt %= div;
            }
        }
    }
}
