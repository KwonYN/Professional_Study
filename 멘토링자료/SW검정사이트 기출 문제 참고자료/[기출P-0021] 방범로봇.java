
import java.io.*;
import java.util.*;
 
//public class preP_0021 { // 방범로봇
public class Solution { // 방범로봇
    static BufferedReader br;
    static StringTokenizer st;
     
    static int T;
    static int N; // 3 <= N <= 100,000
    static int M; // 2 <= M <= 300,000
    static int Q; // 1 <= Q <= 20
    static long K; // 0 <= K <= 1000000000000000000
     
    static int MAX[][] = new int[100001][2]; // 홀짝 케이스에 대해 현재지점에서 가야 하는 가장 번호가 큰 통로의 번호
    static int MAP[][] = new int[100001][2]; // 홀짝 케이스에 대해 현재지점에서 가야 하는 가장 번호가 큰 통로의 목적지
     
    static long VISIT[][] = new long[100001][2];
 
    static int S, E, I;
     
    static long ANS;
     
    public static void main(String args[]) throws Exception {
        br = new BufferedReader(new InputStreamReader(System.in));
        st = new StringTokenizer(br.readLine());
        T = Integer.parseInt(st.nextToken());
         
        for(int t = 1; t <= T; t++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            Q = Integer.parseInt(st.nextToken());
             
            for(int n = 1; n <= N; n++) {
                MAP[n][0] = MAP[n][1] = n; // 이동할 수 있는 통로가 없다면 제자리에 머문다고 했으므로 기본적으로 자기자신을 가리켜놓음
                MAX[n][0] = MAX[n][1] = 0; // 이동할 수 있는 통로는 큰 번호가 기준이므로 최초 0으로 세팅
            }
             
            for(int m = 1; m <= M; m++) {
                st = new StringTokenizer(br.readLine());
                S = Integer.parseInt(st.nextToken());
                E = Integer.parseInt(st.nextToken());
                I = Integer.parseInt(st.nextToken());
                 
                if(MAX[S][I % 2] < I) { // S에 연결된 더 큰 통로 번호가 찾아졌다면
                    MAP[S][I % 2] = E; // S에서 홀/짝인 시점에 갈 수 있는 목적지는 E 로 고정된다. 
                    MAX[S][I % 2] = I;
                }
                 
                if(MAX[E][I % 2] < I) { // E에 연결된 더 큰 통로 번호가 찾아졌다면
                    MAP[E][I % 2] = S; // E에서 홀/짝인 시점에 갈 수 있는 목적지는 S 로 고정된다.
                    MAX[E][I % 2] = I;
                }
            }
             
            // 위의 작업을 통해 해당 그래프는 홀/짝 인 각각의 상황에서 
            // 한 정점이 하나의 방향성 있는 간선을 가지는 그래프가 됨을 알 수 있다.
             
            ArrayList<Integer> A = new ArrayList<>(); // 정답저장용
            for(int q = 1; q <= Q; q++) {
                st = new StringTokenizer(br.readLine());
                S = Integer.parseInt(st.nextToken());
                K = Long.parseLong(st.nextToken());
                 
                for(int n = 1; n <= N; n++) {
                    VISIT[n][0] = VISIT[n][1] = 0;
                }
                 
                // K 가 최대 10^18 으로 상당히 큰 수이지만,
                // N 이 최대 100000 이고 홀/짝 포함하면 200000 이므로, 2N < K 이면 순환구조를 타기 시작할 될 것이므로 횟수를 계산하면 한번 탐색에 2N 정도가 될 것이고
                // Q 가 최대 20 이므로 
                // DFS 형태의 그래프탐색으로 비벼볼 만 하다.
                E = Srch(S, K, 1, 1); // S에서 시작, K만큼을 이동할 예정, 최초 통로를 이동하는데 걸리는 시간 1분, 최초 홀수 통로를 탐색 
                A.add(E);
            }
             
            System.out.print("#");
            System.out.print(t);
            for(int a : A) {
                System.out.print(" ");
                System.out.print(a);
            }
            System.out.println();
        }
    }
 
    private static int Srch(int s, long k, int t, int oe) { // 시작지점, 잔여 이동시간, 누적 이동시간, odd/even
        // TODO Auto-generated method stub
        int RTN = 0;
         
        if(k == 0) { // K 만큼을 모두 움직였다면
            RTN = s; // (직전 DFS에서 도달한, 현재의)시작지점이 도착지점이 된다.
        } else { // 아직 이동시간이 남았다면
            VISIT[s][oe] = t; // 현재 시작시점의 홀/짝 시점에 누적이동시간을 입력한다.
            int e = MAP[s][oe]; // 도착점을 찾아서
             
            if(VISIT[e][(oe + 1) % 2] != 0) { // 도착지점이 방문을 한 곳이라면, 순환구조가 발생했다는 의미이므로 이동시간에서 순환만큼을 무시할 수 있다.  
                k = k % ((t + 1) - VISIT[e][(oe + 1) % 2]); // 누적 이동시간에서 최초 해당지점 도착시간만큼을 빼면 이후 계산된시간만큼 계속 순환함
            }   
             
            if(k == 0) { // 위의 계산을 통해 k 가 0 이 되면 현재지점이 도착지점이 되며 
                RTN = s;
            } else { // 잔여 이동시간이 남은 경우 계속 탐색을 한다.
                RTN = Srch(e, k - 1, t + 1, (oe + 1) % 2);
            }
        }
         
        return RTN;
    }
}
