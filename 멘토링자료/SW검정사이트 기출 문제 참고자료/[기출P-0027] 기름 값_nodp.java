import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
 
public class Solution {
    static int T, N, L;
    static int dist;
    static int Ans[];
    static int Answer;
     
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine().trim()); 
         
        StringTokenizer st;
        for(int TC=1; TC <= T; TC++){
            st = new StringTokenizer (br.readLine().trim());
            N = Integer.parseInt(st.nextToken());
            L = Integer.parseInt(st.nextToken());
             
            Ans = new int [2000001];
            Answer = 0;
             
            for(int i=0;i<2000001;i++){
                Ans[i]=Integer.MAX_VALUE;
            }
             
            st = new StringTokenizer (br.readLine().trim());
             
            int idx=1;
            int oilprice=0;
             
            for(int i=1; i<N; i++){
                oilprice=Integer.parseInt(st.nextToken());
                dist = Integer.parseInt(st.nextToken());
                 
                if(dist > L){
                    Answer = -1; break;
                }else{
                    if(i==1){
                        for(int j=idx; j<idx+L; j++){
                            Ans[j]=oilprice;                            
                        }
                    }else{
                        for(int j=idx; j<idx+L; j++){
                            Ans[j]=Math.min(Ans[j],oilprice);
                        }
                    }
                    idx = idx + dist;
                }
            }
            int target = Integer.parseInt(st.nextToken());
             
            if(Answer==-1) System.out.println("#"+TC+" "+Answer);
            else{
                for(int i=1; i<idx; i++){
                    Answer = Answer + Ans[i];
                }
                System.out.println("#"+TC+" "+Answer);
            }
        }
    }
}
