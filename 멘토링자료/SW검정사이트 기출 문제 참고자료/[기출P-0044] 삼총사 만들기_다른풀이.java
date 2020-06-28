import java.io.*;
import java.util.*;
 
public class Solution {
    static int N, M, ans;
    static ArrayList<Integer>[] adjList, newList;
 
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
         
        int T = Integer.parseInt(br.readLine());
        for(int test_case=1; test_case<=T; test_case++){
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
             
            adjList = new ArrayList[N+1];
            newList = new ArrayList[N+1];
            for(int i=1; i<=N; i++){
                adjList[i] = new ArrayList<Integer>();
                newList[i] = new ArrayList<Integer>();
            }
             
            for(int i=1; i<=M; i++){
                st = new StringTokenizer(br.readLine());
                int s = Integer.parseInt(st.nextToken());
                int e = Integer.parseInt(st.nextToken());
                 
                adjList[s].add(e);
                adjList[e].add(s);
            }           
             
            int u, v, w, n, sFriend, eFriend, friendCnt;
            boolean isFriend = false;
            ans = 0;
             
            for(u=1; u<=N; u++){ //각 친구의 인접리스트를 통해 삼총사 후보 확인 및 새 인접리스트 친구 추가
                for(int j=0; j<adjList[u].size(); j++){
                    v = adjList[u].get(j);
                     
                    for(int k=j; k<adjList[u].size()-1; k++){
                        w = adjList[u].get(k+1);
                         
                        isFriend = false;
                        for(n=0; n<adjList[w].size(); n++){
                            if(adjList[w].get(n)==v){ //이미 친구관계 임
                                isFriend = true;
                                break;
                            }
                        }
                         
                        if(isFriend == false){ //친구관계가 아니면 새 인접리스트에 추가
                            sFriend = Math.min(v, w);
                            eFriend = Math.max(v, w);
                             
                            newList[sFriend].add(eFriend);
                             
                            friendCnt = 0;
                            for(int e : newList[sFriend]){
                                if(e == eFriend) friendCnt++;
                            }
                             
                            ans = Math.max(ans, friendCnt);
                        }
                    }
                     
                }
            }
             
            System.out.println("#" + test_case + " " + ans);
        } //end of test_case
    } //end of main 
}
