import java.util.*;
import java.io.*;
public class Solution {
    static int T, N;
    static long J,K, seq, ans;
    static int map[];
    static long vcnt[];
    static long visited[];
    public static void main(String[] argus) throws Exception {
        //System.setIn(new FileInputStream("모든쌍의최단경로.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int tc = 1; tc <= T; tc++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            st = new StringTokenizer(br.readLine());
            map = new int[N+1];
            visited = new long[N+1];
            vcnt = new long[N+1];
            for(int i=1; i <= N; i++) {
                int a = Integer.parseInt(st.nextToken());
                map[i] = a;
            }
            seq = 1;
             
            for(int i=1; i <=N; i++) {
                if(visited[i] ==0 ) {
                    cycle(i);
                }
            }
            ans = 0;
            for(int i=1; i <= N; i++)
                ans += (vcnt[i] * (vcnt[i]+1)) /2;
             
            bw.write("#"+tc+" ");
            bw.write(String.valueOf(ans));
            bw.write("\n");
            bw.flush();
        }
        bw.close();
    }
    static void cycle(int start) {      
        Stack<Integer> stack = new Stack<Integer>();
        long here = start;
        while(visited[(int) here] == 0) {
            stack.add((int) here); // 방문한 경로 스택에 저장
            visited[(int) here] = seq++; // 방문한 순번 저장
            here =  map[(int) here]; // 다음 정점으로 이동
        }       
         
        // 이번 호출에서 사이클이 이뤄진 경우
        if(visited[(int) here] >= visited[start]) {
            long size = (seq - visited[(int) here]); // 사이클을 이루는 정점수(사이클 크기)
            for(int i=0; i<size; i++) 
                vcnt[stack.pop()] = size - 1; // 사이클 내 정점의 방문 가능 정점수는 사이클 크기 - 1
        }       
         
        // 사이클이 아닌 정점(스택에 남아 있는 정점)의 방문 가능 정점수 계산   
        while(!stack.empty()) {
            int top = stack.pop();
            vcnt[top] = vcnt[(int) map[top]] + 1; // 다음 정점 방문 가능수 + 1
        }
         
         
    }
}
