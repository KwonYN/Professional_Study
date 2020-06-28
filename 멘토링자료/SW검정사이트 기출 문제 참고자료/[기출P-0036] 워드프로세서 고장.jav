import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
 
public class Solution {
     static int K;
     static int D[][];
     static int MAX_VALUE = (int) 1e9 + 1;
 
    public static void main(String[] args) throws Exception{
 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());
 
        for (int tc = 1; tc <= T; tc++) {
 
            K = Integer.parseInt(br.readLine().trim());
 
            String sentence = br.readLine().trim();
            int L = sentence.length();
 
 
            String words[] = new String[K + 1];
 
            for (int i = 1; i <= K; i++) {
                words[i] = br.readLine().trim();
            }
 
            if (K == 1 && sentence.equals(words[1])) {
                System.out.println("#" + tc + " " + 1);
                continue;
            }
 
            D = new int[L + 1][K + 1];
 
            for (int i = 1; i <= L; i++) {
                for (int j = 1; j <= K; j++) {
                    D[i][j] = MAX_VALUE;
                }
            }
 
 
            for (int i = 1; i <= L; i++) {
                String fraction = sentence.substring(0, i);
                for (int j = 1; j <= K; j++) {
                    String targetWord = words[j];
                    if (fraction.length() >= targetWord.length() && fraction.endsWith(targetWord)) {
                        int front = fraction.length() - targetWord.length();
                        D[i][j] = Math.min(D[i][j], getMinValue(front, j) + 1);
                    }
                }
            }
 
            int ans = MAX_VALUE; 
            for (int i = 1; i <= K; i++) {
                ans = Math.min(D[L][i], ans);
            }
 
            System.out.println("#" + tc +" "+ (ans == MAX_VALUE ? -1: ans));
 
        }
 
    }
 
    private static int getMinValue(int front, int j) {
        int min = MAX_VALUE;
        for (int i = 1; i <= K; i++) {
            if (i != j) {
                min = Math.min(D[front][i], min);
            }
        }
        return min;
    }
 
}
