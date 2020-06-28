import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class Solution {
 
    static final int DEPTHMAX = 15;
    static int N,Q;
     
    static int[][] parent;
     
    static int[] heightMax;
    static int[] depth;
     
    static ArrayList<Integer>[] sonList;
     
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
         
        int T = Integer.parseInt(st.nextToken());
        int p, h;
        int groupSize;
        int x1,x2;
        for (int test=1; test<=T;test++) {
             st = new StringTokenizer(br.readLine());
             N = Integer.parseInt(st.nextToken());
             Q = Integer.parseInt(st.nextToken());
              
             parent = new int[N+1][DEPTHMAX+1];
             heightMax = new int[N+1];
             sonList = new ArrayList[N+1];
             depth = new int[N+1];
              
             for (int i=1; i<=N; i++) sonList[i] = new ArrayList<>();
              
             for (int i=1; i<=N; i++) {
                 st = new StringTokenizer(br.readLine());
                 p = Integer.parseInt(st.nextToken());
                 h = Integer.parseInt(st.nextToken());
                  
                 parent[i][0] = p; //2^0 번째 조상
                 heightMax[i] = h;
                  
                 if (p !=0) sonList[p].add(i);
             }
             
             dfsCheck(1, 0, 1);
              
             //parent 갱신
             for (int n=1; n<=DEPTHMAX; n++) {
                 for (int i=1; i<=N; i++) {
                     parent[i][n] = parent[parent[i][n-1]][n-1];
                 }
             }
             // 자료 제작 끝
              
             bw.write("#" + test);
             for (int qu = 1; qu<=Q; qu++) {
                 st = new StringTokenizer(br.readLine());
                 groupSize = Integer.parseInt(st.nextToken());
                 x1 = Integer.parseInt(st.nextToken());
                 for (int count=2; count<=groupSize; count++) {
                    x2 = Integer.parseInt(st.nextToken());
                    x1 = lca(x1,x2);
                 } 
                 bw.write(" " + heightMax[x1]);
             }
             bw.write("\n");
        }//test end
        bw.flush();
 
    }//main end
     
    static void dfsCheck(int index, int maxHeight, int currDepth) { //index 현재 위치, maxHeight 조상님들의 최대값 
        depth[index] = currDepth;
        heightMax[index] = Math.max(heightMax[index], maxHeight);
         
        for (int next : sonList[index]) {
            if (depth[next] ==0) dfsCheck(next, heightMax[index], currDepth+1);
        }
    }
     
    static int lca(int a, int b) {
         
         
        if (depth[a] > depth[b]) { //a를 올려줘야함 
            for (int k = DEPTHMAX; k>=0; k--) {
                if (a!=b && depth[parent[a][k]] >= depth[b]) a = parent[a][k];
            }
        }else if (depth[a] < depth[b]) { //b를 올려줘야함 
            for (int k = DEPTHMAX; k>=0; k--) {
                if (a!=b && depth[parent[b][k]] >= depth[a]) b = parent[b][k];
            }
        }
         
        for (int k=DEPTHMAX; k>=0; k--) {
            if (a!=b && parent[a][k] != parent[b][k]) { //같아지기 직전까지 올려준다
                a= parent[a][k];
                b=parent[b][k];
            }
        }
         
        if (a== b) return a; 
        else return parent[a][0]; //하나 더 올려주기
    }
 
}
