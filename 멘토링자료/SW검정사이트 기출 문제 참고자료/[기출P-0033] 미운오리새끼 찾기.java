import java.io.*;
import java.util.*;
 
public class Solution {
    static int T, N;
    static int ans, duck, tmp;
    static int num[] = new int[1000000];
    static int left[] = new int[1000000];
    static int right[] = new int[1000000];
 
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;
         
        T = Integer.parseInt(br.readLine());
        for (int test_case = 1; test_case <= T; test_case++) {
            N = Integer.parseInt(br.readLine());
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                num[i] = Integer.parseInt(st.nextToken());
            }
             
            left[0] = num[0];
            for (int i = 1; i < N; i++) {
                left[i] = gcd(left[i-1], num[i]);
            }
             
            right[N-1] = num[N-1];
            for (int i = N-2; i >= 0; i--) {
                right[i] = gcd(right[i+1], num[i]);
            }
             
            ans = duck = tmp = 0;
            for (int i = 0; i < N; i++) {
                if (i == 0) {
                    tmp = right[1];
                }else if (i == N-1) {
                    tmp = left[N-2];
                }else {
                    tmp = gcd(left[i-1], right[i+1]);
                }
                 
                if (num[i] % tmp == 0) {
                    continue;
                }
                if (ans < tmp) {
                    ans = tmp;
                    duck = num[i];
                }
            }
             
            System.out.println("#"+test_case+" "+ans+" "+duck);
        }
    }
     
    static int gcd(int a, int b) {
        int tmp;
        while (b > 0) {
            tmp = b;
            b = a%b;
            a = tmp;
        }
        return a;
    }
     
}
