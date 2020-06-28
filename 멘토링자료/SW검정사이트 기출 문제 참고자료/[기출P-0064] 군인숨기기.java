import java.io.*;
import java.util.*;
 
public class Solution {
    public static int T;
    public static int N;
    public static int[] H = new int[10001];
    public static int[] C = new int[10001];
    public static int Answer;
     
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
         
        T = Integer.parseInt(br.readLine());
        for (int test_case = 1; test_case <= T; test_case++) {
            for (int i = 1; i <= 10000; i++)  C[i] = 0;
             
            N = Integer.parseInt(br.readLine());
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                H[i] = Integer.parseInt(st.nextToken());
            }
             
            Answer = 0;
 
            C[1] = 1;
            for (int i = 1; i <= N; i++) {
                int s = 0;
                for (int j = 1; j <= H[i]; j++) {
                    s += C[j];
                    if (s >= 1000000007) s -= 1000000007;
                    C[j] = s;
                     
                    if (N == i) { 
                        Answer += C[j];
                        if (Answer >= 1000000007) Answer -= 1000000007;
                    }
                }
            }
            bw.write("#" + test_case + " " + Answer + "\n");
        }
        bw.flush();
        bw.close();
    }
}
