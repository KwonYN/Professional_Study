import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
 
class Solution {
     
    static int N, L;
    static int PQ[];
    static int K[] = new int[]{0, 153, 197, 239, 268, 294, 317, 321, 309, 275, 243, 202, 151, 119, 76, 43, 21, 17, 13, 11};
     
    static int R[][];
    static int Answer;
 
    public static void work(int i, int j) {
        int sum = 0;
        int max = 0;
         
        for (int k = j; k >= i; k--) {
            if (k < N + 1) {
                sum = sum + PQ[k] * K[j - k < 19 ? j - k : 19];
            }
             
            if (R[i - 1][k] + sum > max) {
                max = R[i - 1][k] + sum;
            }
        }
        R[i][j] = max;
    }
     
    public static void main(String args[]) throws Exception {
 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
        int T = Integer.parseInt(br.readLine().trim());
        StringTokenizer st, st2;
         
        int test_case, i, j;
         
        for(test_case = 1; test_case <= T; test_case++) {
            st = new StringTokenizer(br.readLine().trim());
             
            N = Integer.parseInt(st.nextToken());
            L = Integer.parseInt(st.nextToken());
             
            PQ = new int[N + 1];
            R = new int[L + 1][N + 20];
             
            st = new StringTokenizer(br.readLine().trim());
            st2 = new StringTokenizer(br.readLine().trim());
             
            for (i = 1; i <= N; i++) {
                PQ[i] = Integer.parseInt(st.nextToken()) * Integer.parseInt(st2.nextToken());
            }
             
            for (i = 1; i <= L; i++) {  // i: 1 ~ L 작업일 사용 횟수
                for (j = i + 1; j <= N + 19; j++) {  // j: i+1 ~ N+19 일째 작업
                    work(i, j);
                }
            }
             
            Answer = 0;
            for (i = 2; i <= N + 19; i++) {
                Answer = Math.max(Answer, R[L][i]);
            }
             
            System.out.printf("#%d %.2f\n", test_case, Answer / 100.);
        }
    }
}
