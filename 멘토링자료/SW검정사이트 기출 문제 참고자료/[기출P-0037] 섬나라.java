import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
 
//섬나라
public class Solution {
 
    static int N, M, A[][], Q, q1[], P[], C[], nums[][], MAX, cnt, ans[];
    static List<Pos>[] dPos;
    static int[] dx = {-1,1,0,0}, dy = {0,0,-1,1};
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        StringBuilder sb;
        int T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++){
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            A = new int[N][M]; //현재 섬 상태
            P = new int[N*M+1]; //집합 번호(1부터)
            C = new int[100001];
            nums = new int[N][M];
            dPos = new List[100001]; 
            for(int i=0; i<100001; i++){
                dPos[i] = new ArrayList<>();
            }
            int c = 1;
            MAX = 0;
            for(int i=0; i<N; i++){
                st = new StringTokenizer(br.readLine());
                for(int j=0; j<M; j++){
                    A[i][j] = Integer.parseInt(st.nextToken());
                    MAX = Math.max(MAX, A[i][j]);
                    nums[i][j] = c++; //위치별로 숫자 부여
                    dPos[A[i][j]].add(new Pos(i, j)); //숫자들의 원래 위치 저장
                }
            }
            Q = Integer.parseInt(br.readLine()); //파괴명령 수
            q1 = new int[Q+1]; //파괴될 숫자들
            ans = new int[Q+1];
            st = new StringTokenizer(br.readLine());
            for(int i=1; i<=Q; i++){
                q1[i] = Integer.parseInt(st.nextToken());
                if(C[q1[i]]==0) { //같은 숫자 중복해서 파괴할 경우 앞에 것만 처리하기 위함
                    C[q1[i]] = i; //해당 숫자가 언제 파괴되는지
                }
            }
             
            //파괴되지 않는 숫자부터 합쳐놓기
            cnt = 0;
            for(int i=1; i<=MAX; i++){
                if(C[i]==0) {
                    merge(i);
                }
            }
            for(int i=Q; i>0; i--){
                ans[i] = cnt;
                if(C[q1[i]] == i) { //같은 숫자 중복 파괴시 맨 앞에 것만 처리하기 위함
                    merge(q1[i]);
                }
            }
             
            sb = new StringBuilder();
            for(int i=1; i<=Q; i++){
                sb.append(" "+ans[i]);
            }
            bw.write("#"+tc+sb.toString()+"\n");
        }
        br.close();
        bw.close();
    }
         
    static void merge(int n) { //숫자n 근처 합침
        for(Pos cur:dPos[n]){
            P[nums[cur.x][cur.y]] = nums[cur.x][cur.y]; //집합 번호는 자기자신으로 초기화
            cnt++;
            for(int d=0; d<4; d++){
                int px = cur.x+dx[d];
                int py = cur.y+dy[d];
                if(px<0||px>=N||py<0||py>=M) continue;
                if(P[nums[px][py]]==0) continue; //아직 추가되지 않은 숫자면 pass
                int aRoot = find(nums[cur.x][cur.y]);
                int bRoot = find(nums[px][py]);
                if(aRoot!=bRoot){
                    P[aRoot] = bRoot;
                    cnt--;
                }
            }
        }
    }
 
    static void union(int a, int b) {
        int aRoot = find(a);
        int bRoot = find(b);
        P[bRoot] = aRoot;
    }
     
    static int find(int num) {
        if(num == P[num]) return num;
        return P[num] = find(P[num]);
    }
 
}
class Pos{
    int x, y;
    Pos(int x, int y){
        this.x = x;
        this.y = y;
    }
}
