import java.io.*;
import java.util.*;
 
public class Solution {
     
    public static int T;
    public static int N;
    public static int[] deck = new int[100000];
    public static int Answer;
     
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
         
        T = Integer.parseInt(br.readLine());
        for (int test_case = 1; test_case <= T; test_case++) {
            N = Integer.parseInt(br.readLine());
             
            Answer = 0;
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                int num = -1 * Integer.parseInt(st.nextToken());
                int ix = Arrays.binarySearch(deck, 0, Answer, num);
                deck[ix*-1-1] = num;
                if (Answer == ix*-1-1) Answer++;
            }
             
            bw.write("#" + test_case + " " + Answer + "\n");
        }
        bw.flush();
        bw.close();
    }
}
