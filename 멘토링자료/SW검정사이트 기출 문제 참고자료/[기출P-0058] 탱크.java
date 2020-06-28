import java.io.*;
import java.util.*;
 
public class Solution {
     
    static int T; //tc
    static int N; //탱크 개수
     
    static long[] idxTree; //인덱스 트리
    static int leaf; //인덱스 트리 leaf 노드 개수
     
    static long Answer;
 
    public static void main(String[] args) throws Exception {
        // TODO Auto-generated method stub
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        //File file = new File("res/sample_p0058");
        //FileReader fr = new FileReader(file);
        //BufferedReader br = new BufferedReader(fr);
                 
        PriorityQueue<Tank> pq = new PriorityQueue<Tank>(new Comparator<Tank>() {
 
            @Override
            public int compare(Tank arg0, Tank arg1) { //x 좌표기준 내림차순 
                if(arg0.x > arg1.x) return -1;
                    else if(arg0.x == arg1.x) return 0;
                    else return 1;
                }
                     
            });
         
        //indexed tree
        for(leaf=1; leaf<=1000000; leaf*=2);
        idxTree = new long[2*leaf];
         
        T = Integer.parseInt(br.readLine());
         
        for (int t=1; t<=T; t++){
             
            N = Integer.parseInt(br.readLine());
             
            //초기화 
            pq.clear();
            Answer=0L;
            Arrays.fill(idxTree, 0);
             
            StringTokenizer st;
            for(int i=0; i<N; i++){
                st = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                long c = Long.parseLong(st.nextToken());
                 
                pq.add(new Tank(a,b,c));
            }
             
             
            while(!pq.isEmpty()){
                Tank tank = pq.poll(); //x 좌표가 큰 탱크부터 뽑는다
                int idx = tank.y+leaf-1; // y 좌표 기준으로 idx 구하기
                update(idx, tank.point); // 값 넣어주고 인덱스 트리 갱신
                Answer += getScore(1,1,leaf,tank.y+1,leaf);
            }
             
            System.out.println("#" + t + " " + Answer);
        }
         
         
         
         
 
    }
     
     
    //인덱스트리 업데이트
    public static void update(int idx, long val){
         
        idxTree[idx] = val;
        int x=idx/2;
         
        while(x>0){
            idxTree[x]=idxTree[2*x]+idxTree[2*x+1];
            x=x/2;
        }
    }
     
    //인덱스트리 구간합 구하기 
    public static long getScore(int node, int start, int end, int left, int right){
        if(idxTree[node]==0) return 0;
        if(start > right || end < left) return 0;
        if(start >= left && end <= right) {
            return idxTree[node];
        }
        int mid=(start+end)/2;
        return getScore(node*2, start, mid, left, right) + getScore(node*2+1, mid+1, end, left, right);
    }
 
}
 
 
class Tank {
     
    int x;
    int y;
    long point;
     
    public Tank(int x, int y, long point){
        this.x=x;
        this.y=y;
        this.point=point;
    }
}
