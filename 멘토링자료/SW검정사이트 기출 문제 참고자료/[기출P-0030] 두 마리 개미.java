import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;
 
public class Solution {
 
 static long[][] ant1, ant2;
 
 static class Point{
  long x;
  long y;
  public Point(long x, long y) {
   super();
   this.x = x;
   this.y = y;
  }
   
 }
  
 static int ccw(Point A, Point B, Point C) {
  long result = A.x*B.y + B.x*C.y + C.x*A.y - A.y*B.x - B.y*C.x - C.y*A.x;
 // return result>0? 1 : result <0 ? -1 : 1;
     if(result > 0){
        return 1;
     }else if(result ==0){
        return 0;
     }else return -1;
  
 }
  
 static int result;
static StringBuilder sb = new StringBuilder();  
    public static void main(String[] args) throws IOException {
      
 
  BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
  BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
  int T = Integer.parseInt(br.readLine());
 
  StringTokenizer st;
  for (int t = 1; t <= T; t++) {
   st = new StringTokenizer(br.readLine());
   int N = Integer.parseInt(st.nextToken());
   int M = Integer.parseInt(st.nextToken());
 
   ant1 = new long[N+1][2];
   ant2 = new long[M+1][2];
   result = 0;
    
   st = new StringTokenizer(br.readLine());
   for (int i = 1; i <= N; i++) {
    ant1[i][0] = Integer.parseInt(st.nextToken());
    ant1[i][1] = Integer.parseInt(st.nextToken());
   }
 
   st = new StringTokenizer(br.readLine());
   for (int i = 1; i <= M; i++) {
    ant2[i][0] = Integer.parseInt(st.nextToken());
    ant2[i][1] = Integer.parseInt(st.nextToken());
   }/// 입력받기
  
 
   int i = 1;
   int j = 1;
   boolean flag = false;
   while(i < N && j <M ) {
        
    Point A1 = new Point(ant1[i][0],ant1[i][1]);
    Point A2 = new Point(ant1[i+1][0],ant1[i+1][1]);
          
    Point B1 = new Point(ant2[j][0],ant2[j][1]);
    Point B2 = new Point(ant2[j+1][0],ant2[j+1][1]);
     
    int case1 = ccw(A1,A2,B1);
    int case2 = ccw(A1,A2,B2);
    int case3 = ccw(B1,B2,A1);
    int case4 = ccw(B1,B2,A2);
     
   
     
    //2. 스치거나 아예 같은 성분인 경우
    if(case1*case2==0 && case3*case4==0 ) {
        if(ant1[i+1][0] < ant2[j][0]){
            i++;
        }else if(ant2[j+1][0] < ant1[i][0]){
            j++;
        }else if(ant1[i+1][0] == ant2[j][0]){
            i+=2;
        }else if(ant2[j+1][0] == ant1[i][0]){
            j+=2;
        }else{
             sb.append("#" + t + " " + -1 + "\n");
            flag = true;
             break;
        }
    }
     
    //3. 교차하는 경우
    else if(case1*case2 < 0 && case3*case4 <0) {
     result++;
        if(ant1[i+1][0] > ant2[j+1][0]){
            j++;
        }else if(ant1[i+1][0] < ant2[j+1][0]){
            i++;
        }
    }
        
        
       else if(case1*case2<0 && case3*case4==0){
        result++;
           i+=2;
       }
        
        
        
       else if(case1*case2==0 && case3*case4<0){
        result++;
           j+=2;
       }
    //4. 교차 안하는 경우
       else {
           if(ant1[i+1][0] > ant2[j+1][0]){
            j++;
           }else if(ant1[i+1][0] < ant2[j+1][0]){
            i++;   
           }
    }
     
   }
  if(!flag)
   sb.append("#" + t+ " " + result + "\n");
    
  }
System.out.println(sb.toString());
 }
}
