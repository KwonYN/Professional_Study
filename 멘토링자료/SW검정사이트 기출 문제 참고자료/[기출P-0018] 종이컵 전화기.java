import java.io.*;
import java.util.*;
 
public class Solution {
     
    public static void main(String[] args) throws Exception {
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));       
        int T = Integer.parseInt(br.readLine().trim());
         
        for (int tc = 1; tc <= T; tc++) {
             
            StringTokenizer st = new StringTokenizer(br.readLine().trim());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
             
            int[][] A = new int[N+1][N+1];
            int[][] D = new int[N+1][N+1];
             
            for (int i = 0; i < M; i++) {
                st = new StringTokenizer(br.readLine().trim());
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                 
                A[a][b] = A[b][a]= 1;
                 
            }
             
            for (int i = 1; i < N; i++) {
                 
                for (int j = 1; j <= N-i; j++) {
                     
                    int s = j;
                    int e = j+i;
 
                    D[s][e] = 0;
 
                    if(D[s][e] < D[s+1][e]) D[s][e] = D[s+1][e];
                     
                    if(D[s][e] < D[s][e-1]) D[s][e] = D[s][e-1];
                     
                    if (A[s][e] == 1 && D[s][e] < D[s+1][e-1] + 1) {
                        D[s][e] = D[s+1][e-1] + 1;
                    }
                     
                    for(int k = s; k < e; k++){
                        if(D[s][e] < D[s][k] + D[k+1][e]) D[s][e] = D[s][k] + D[k+1][e];
                    }
                     
                }
                 
            }
             
            System.out.println("#"+tc+" "+D[1][N]);
             
        }
         
    }
     
}
