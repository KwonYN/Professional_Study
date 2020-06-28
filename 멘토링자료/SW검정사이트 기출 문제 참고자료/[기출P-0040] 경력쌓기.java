import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
 
public class Solution {
 
    static int T, N, M;
    static StringTokenizer st; 
    static int[] salary, cnt;
    static ArrayList<Integer>[] connect;
    static long m = 1000000007;
    static long[] memo;
     
    public static void main(String[] args) throws Exception {
        // TODO Auto-generated method stub
 
        //System.setIn(new FileInputStream("p0040.txt"));
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out)); 
    
 
        T = Integer.parseInt(br.readLine());
         
        for(int Tc = 1; Tc <= T; Tc ++){
             
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
             
            // 직장별 상담소 연결 방향. 월급 큰 순
            connect = new ArrayList[N+1];       
            //직장 별 월급
            salary = new int[N+1];
             
            st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                salary[i] = Integer.parseInt(st.nextToken());
                connect[i] = new ArrayList();                   
            }
             
            // 상담소 연결고리.  
            cnt = new int[N+1]; // 다른 상담소에서 들어오는 경우의 수.
            Arrays.fill(cnt, 0);
             
            // 각 직장별 이전직장에서 올 수 있는 가짓수 저장 값.
            memo = new long[N+1];
            Arrays.fill(memo,0);
             
            for (int i = 1; i <= M; i++) {
              st = new StringTokenizer(br.readLine());              
              int a = Integer.parseInt(st.nextToken());
              int b = Integer.parseInt(st.nextToken());
               
              int a_sal = salary[a];
              int b_sal = salary[b]; 
               
              //직장 a 와  b 를 비교해서 월급이 작은쪽에서 큰쪽으로 가도록 함. 
              //월급 같은 경우는 고려하지 않음.
              if( a_sal < b_sal){
                 connect[a].add(b);
                 cnt[b]++;  // a에서  b 로 가므로 
              } else if(a_sal > b_sal){   
                 connect[b].add(a);
                 cnt[a]++;  // b에서  a 로 가므로.
              }   
            }
             
            //다른 직장에서 나의 직장으로 올 수 없는 경우 ( cnt = 0 ) 인 것 부터 수행해나감.
            PriorityQueue<Integer> q = new PriorityQueue<Integer>();
            for (int i = 1; i <= N; i++) {
              if(cnt[i] == 0){
                  q.add(i);
              }
            }
             
            // 모든 직장 다 돌은 경우
            long Ans = 0;
            while(q.isEmpty() == false){
               int from_company = q.poll();
                
               // from 직장부터 to 직장으로 갈 수 있는 직장 순서 돌음.
               for (int i = 0; i < connect[from_company].size(); i++) {
                   int to_company = connect[from_company].get(i);
                   long mod1 = 0; long mod2 = 0;
                      
                   mod1 = (memo[from_company]+1) % m;  //from직장까지 올 수 있는 경우의 수와 from직장에서 to직장으로 이동하는 상담소 1을 더한감.
                   mod2 = memo[to_company] % m;        //to직장까지 올 수 있었던 이전  from직장 값들 
                        
                   memo[to_company] = (mod1 + mod2) % m;   //현재까지 to 직장의 경우의 수 에  from 직장의 경우의 수 더함.
                       
                   cnt[to_company]--;  // from 직장에서 to 직장왔으므로, to직장 올 수 있는 가짓 수가 1번 줄어듬.
                   if(cnt[to_company] == 0){  // from 직장에서 to직장으로 더이상 올 수 없는 경우.
                        
                       Ans += (memo[to_company] % m);
                       Ans = Ans % m;
                        
                      // to 직장에서 이동할 수 있는 다른(to의  to) 직장 있는 경우는 이동, to직장을  from 직장으로 넣어주기
                      if (connect[to_company].size() != 0){
                          q.add(to_company); // 현재 직장에서 다음 직장으로 이동. 
                      }
                   }
               }
            }
             
            bw.write("#" + Tc + " " + Ans );
            bw.newLine();
            bw.flush();
        } // test end 
        br.close();
             
         
    } // end main
 
} // end class
