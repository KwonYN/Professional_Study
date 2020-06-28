import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;
 
public class Solution {
    public static int N, M, A, B, score, result, arr[];
    public static boolean checked[];
    public static void main(String[] args) throws Exception {
        // [기출P-0032] 사격장 => union-find(disjoint-set) => fail
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
         
        int T = Integer.parseInt(br.readLine());
        for (int tc = 1; tc <= T; tc++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
 
            checked = new boolean[N+1];
            arr = new int[N+2];
            for (int i = 1; i <= N+1; i++) {
                arr[i] = i;
            }
             
            result = 0;
            for (int i = 1; i <= M; i++) {
                score = 0;
                st = new StringTokenizer(br.readLine());
                A = Integer.parseInt(st.nextToken());
                B = Integer.parseInt(st.nextToken());
             
                A = find(A);
                while(A <= B) {
                    score++;
                    union(A, A+1);
                    A = find(A);
                }
                 
                if(i % 2 == 0) result -= score;
                else result += score;
            }
             
            bw.write("#" + tc + " " + result + "\n");
            bw.flush();
        }
    }
     
    private static void union(int a, int b) {
        arr[find(a)] = find(b);
    }
     
    private static int find(int a) {
        if(arr[a] == a) return a;
        else return arr[a] = find(arr[a]);
    }
}
