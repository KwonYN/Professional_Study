import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
//(중상) [기출P-0068] 홀수짝수경로       
//20개 1.5초
//2≤N≤100,000, 1≤M≤300,000
//다익스트라
//All-Path(1, X)
//All-Path-No-Farther(1, X) : Ai+1 에서 X로 가는 최단경로가 Ai에서 X로 가는 최단 경로보다 더 길지 않아야 한다 
//홀 짝
public class Solution {
    static BufferedReader br;
    static BufferedWriter bw;
    static StringTokenizer st;
    static int TC;
    static int AnsOdd, AnsEven;
    static int N, M; //2≤N≤100,000, 1≤M≤300,000, w=1
    static int[][] D=new int[2][100001]; //경로의 홀수갯수, 짝수갯수를 담는다
    static int[] dist=new int[100001]; //거리, depth
    static final int INF = Integer.MAX_VALUE;
    static ArrayList<Integer>[] nodes;
    static PriorityQueue<int[]> pq = new PriorityQueue<>(new Comparator<int[]>() {
        public int compare(int[] a, int[] b) {
            if (a[1] < b[1]) return -1;
            else if (a[1] > b[1]) return 1;
            else return 0;
        }
    });
     
    public static void main(String[] args) throws Exception {
        //System.setIn(new FileInputStream(Solution.class.getResource("input2.txt").getPath()));
        br = new BufferedReader(new InputStreamReader(System.in));
        bw = new BufferedWriter(new OutputStreamWriter(System.out));
 
        TC=Integer.parseInt(br.readLine());
        for(int tc=1; tc<=TC; tc++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            nodes = new ArrayList[N+1];
            for(int i=1; i<=N; i++) nodes[i]=new ArrayList<Integer>();
             
            int a, b;
            for(int i=1; i<=M; i++) {
                st = new StringTokenizer(br.readLine());
                a = Integer.parseInt(st.nextToken());
                b = Integer.parseInt(st.nextToken());
                nodes[a].add(b);
                nodes[b].add(a);
            }
             
            all_path_no_farther(1);
             
            AnsOdd=AnsEven=0;
            for(int x=1; x<=N; x++) {
                AnsOdd +=D[0][x];
                AnsEven +=D[1][x];
                //System.out.println(" X : "+x+" : "+ dist[x]+" "+count[x]+": "+D[0][x]+" "+D[1][x]);
            }
            //System.out.println("#"+tc+" "+AnsOdd+" "+AnsEven);
            bw.write("#"+tc+" "+AnsOdd+" "+AnsEven+"\n");//홀짝
        }
        br.close();
        bw.flush();
        bw.close();
    }
    static void all_path_no_farther(int s) {
        pq.clear();
        Arrays.fill(D[0], 0);
        Arrays.fill(D[1], 0);
        Arrays.fill(dist, INF);
         
        D[0][s]=0; //j까지의 홀수경로 갯수, 최대 1개
        D[1][s]=1; //j까지의 짝수경로 갯수, 최대 1개
        dist[s]=0;
         
        pq.add(new int[] {s, 0, 0, 0});
        while(!pq.isEmpty()) {
            int[] cur=pq.poll();
            //System.out.println("pq.poll : "+cur[0]+" "+cur[1]+" "+cur[2]+" "+cur[3]);
            int u = cur[0];
            int cur_dist = cur[1];
 
            //홀수경로, 짝수경로는 최대 1개씩
            for(int v : nodes[u]) {
                //이미 v의 홀수경로가 채워져 있음 skip
                if ( (cur_dist+1) %2==1 && D[0][v] ==1 ) continue;
                //이미 v의 짝수경로가 채워져 있음 skip
                if ( (cur_dist+1) %2==0 && D[1][v] ==1 ) continue;
                 
                //원래 dist[v] > cur_dist+1 비교이지만, 1개 차이까지 허용하기 위해 비교문 변경
                if (dist[v] >= cur_dist) {
                    dist[v] = cur_dist+1;
                    if (dist[v]%2==0) {//짝수경로
                        D[1][v]++;
                    }else { //홀수경로
                        D[0][v]++;
                    }
                    pq.add(new int[] {v, dist[v], D[0][v], D[1][v]});
                    //System.out.println(" ----- pq.add : "+v +" "+dist[v] + " "+ D[0][v] + " "+ D[1][v] );
                }
                                 
            }
        }
    }
     
 
}
