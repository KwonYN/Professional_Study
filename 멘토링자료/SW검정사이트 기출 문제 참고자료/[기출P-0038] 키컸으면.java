import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;
  
  
public class Solution {
   
 static int T, N, Q;
 static int[][] man;
 static int[][] query;
 static int[] tree;
 static int[] ans; 
   
 public static void main(String[] args) throws IOException {
  BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
  BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
  StringTokenizer st;
    
  T = Integer.parseInt(br.readLine().trim());
    
  for (int t = 1; t <=T ; t++){
     
   st = new StringTokenizer(br.readLine().trim());
   N = Integer.parseInt(st.nextToken());
   Q = Integer.parseInt(st.nextToken());
     
   man = new int[N+1][2]; //0은 키 1은 인덱스
   query = new int[Q+1][4]; // 0키 1은 a 2는 b 3은 인덱스
   tree = new int[N+1];
   ans = new int[Q+1];
     
   st = new StringTokenizer(br.readLine().trim());
   for(int i = 1; i <= N ; i++){
    man[i][0] = Integer.parseInt(st.nextToken());
    man[i][1] = i;
   }
   for(int i = 1; i <= Q; i++){
    st = new StringTokenizer(br.readLine().trim());    
    query[i][1] = Integer.parseInt(st.nextToken());
    query[i][2] = Integer.parseInt(st.nextToken());
    query[i][0] = Integer.parseInt(st.nextToken());
    query[i][3] = i;
   }
     
   Arrays.sort(man, 1, N+1, new Comparator<int[]>(){
  
    public int compare(int[] o1, int[] o2) {
     return o2[0] - o1[0];
    }
      
   });
     
   Arrays.sort(query, 1, Q+1, new Comparator<int[]>(){
  
    public int compare(int[] o1, int[] o2) {
     return o2[0] - o1[0];
    }    
   });
     
   int j = 1;
     
   for(int i = 1; i <= Q; i++){
    //기준키보다 큰 man 1로 업데이트
    while(j<=N && man[j][0] > query[i][0]){
     update(man[j++][1], 1);
       }
       
    ans[query[i][3]] = sum(query[i][2]) - sum(query[i][1] -1);
   }
   bw.write("#"+ t);
   for (int i = 1; i <=Q; i++){
    bw.write(" " + ans[i]);
   }
   bw.flush();
   System.out.println();
     
  }
  
  bw.close();
 }
   
 static void update (int i, int val){
  while(i<=N){
   tree[i] += val;
   i += (i&-i);
  }
 }
   
 static int sum(int i){
  int result = 0;
  while(i > 0){
   result += tree[i];
   i -= (i&-i);
  }
  return result;
 }
   
  
}
