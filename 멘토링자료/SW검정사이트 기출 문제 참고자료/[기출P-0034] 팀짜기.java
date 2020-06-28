import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
 
// 팀짜기 
public class Solution {
     
    static int T, K, N, result;
    static ArrayList<ArrayList<Integer>> idxSet;
     
    public static void main(String[] args) throws IOException {
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        T = Integer.parseInt(br.readLine());
         
        for(int t = 0; t < T; t++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());
             
            idxSet = new ArrayList<ArrayList<Integer>>();
            for(int i =0; i<N; i++) {
                idxSet.add(new ArrayList<Integer>());
            }
             
            st = new StringTokenizer(br.readLine());
            for(int i =0; i<N; i++) {
                // 1 1 2 3 4 2 4 4 5
                // 1 : 0, 1
                // 2 : 2, 5
                // 3 : 3
                // 4 : 4,6,7
                // 5 : 8
                int num = Integer.parseInt(st.nextToken()) -1;
                idxSet.get(num).add(i);
            }
             
             
            // indexSet 정의 
            // 특정 숫자가 어디에 위치해 있는지를 나타내는 배열의 배열. 
             
            result = 0;
            // z 는 numberType, 어떤 숫자로 팀을 구성해 보겠다는 의미. 
            for(int z=0; z<N; z++) {
                ArrayList<Integer> idx = idxSet.get(z);
                 
                int tmp = 1;
                for(int i=0; i<idx.size(); i++) {
                    if(tmp >= idx.size()) break;   // 이 경우 index out of bound 나니깐... 
                     
                    // for문을 적게 될 게 하는 로직으로 해결. 
                    // 저장된 게 index의 배열. 이것으로 for 문을 적게 돌린다. 
                    for(int j=tmp; j<idx.size(); j++) {
                         
                        // idx.get(j) - idx.get(i)  : j번째 x가 속한 index - i번째 x가 속한 index 
                        // j - i : X 의 갯수 
                        // 1 2 3 1 3 1 1 2  라면..
                        // 1     1   1 1   만 신경쓰겠다는 로직. (idx.get(j) - idx.get(i) : 로 1과 1사이의 특정 숫자 사이의 갯수를 구하는 방법. 
                        int cnt = idx.get(j) - j - idx.get(i) + i;
                         
                         
                        // j - i + 1 : 특정 숫자의 갯수. 
                        // idx.get(j) - idx.get(i) + 1 : 전체 갯수. 
                        // cnt 는 제외시킬 갯수 
                        if(cnt > K) break;
                        else {
                            result = max(result, (idx.get(j)-idx.get(i)+1) - cnt);   // max 는 라이브러리 사용해도 된다. 
                            tmp++;  // 캐시 적재.  
                        }
                    }
                }
            }
             
            System.out.println("#" + (t+1)+ " " + result);
             
        }
        br.close();
         
    }
     
    static int max(int x, int y) {
        return x>y ? x:y;
    }
}
