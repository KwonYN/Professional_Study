import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
 
 
public class Solution {
    static int T; // testcase 수
    static int N; // 전체 선물의 수  (1 ≤ N ≤ 100,000)
    static int K; // 선택해야 하는 선물의 수  (1 ≤ K ≤ N)
    static PriorityQueue<Integer>[] gift = new PriorityQueue[101]; // 선물 배열, 무게를 index로 하고 선호도를 내림차순으로 pq add 함
    static float Ans; 
     
    /* Logic : N이 100,000이므로 O(nlogn)으로 플어야함
     * 검색하는 후보를 줄이기 위해, 분모가 같은 경우 분자를 크게 . 즉, 무게별 선호도가 큰 걸 priorityQueue에 저장
     * Answer를 찾을 때는 무게가 작은 거부터~ 같은 무게에서 선호도가 높은거 찾기 */
     
    public static void main(String[] args) throws Exception {       
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         
        T = Integer.parseInt(br.readLine());
         
        for(int t=1; t<=T; t++){
            StringTokenizer st = new StringTokenizer(br.readLine());
             
            N = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());
             
            for (int i = 0; i <= 100; i++) gift[i] = new PriorityQueue<Integer> (Collections.reverseOrder());
             
            //주어진 선물 정보 입력
            int f,w; // 1 ≤ f, w ≤ 100
             
            for(int i=0; i<N; i++){
                st = new StringTokenizer(br.readLine());
                f = Integer.parseInt(st.nextToken());
                w = Integer.parseInt(st.nextToken());   
                gift[w].add(f);//pq 초기화, 선호도 내림차순으로 넣어줄거임! 같은 무게 내에서는 가장 큰 선호도가 뽑힐 수 있도록
            }
             
             
            int pickW = 0;  int pickF = 0; //선택한 무게와 선호도
            int bestW = 0;  int bestF = 0; 
            float best = 0; float pick = 0; //best : 계산한 값 중에 최정의 F/W, pick : 현재 계산한 F/W
            float wSum = 0; float fSum = 0;
             
             
            //선물 K개 뽑기 시작 > K*100 탐색 
            for (int k = 0; k < K; k++) {
                best = 0;
                for (int i = 1; i <= 100; i++) {//무게는 오름차순으로 탐색, 무게그룹에서 선호도 높은거 하나 골라서 비교!
                    pickW = i;
                    if(gift[i].size() > 0) pickF = gift[i].peek(); // 해당 무게에서 선호도 가장 높은거
                    else continue;
                     
                    pick = (fSum + pickF)/(wSum + pickW);
                    if(best < pick) {
                        best = pick;
                        bestW = pickW;
                    }
                }
                wSum += bestW;
                fSum += gift[bestW].poll();
            }       
             
            Ans = fSum / wSum;
            System.out.print("#" + t + " ");
            System.out.printf("%.3f",Ans);
            System.out.println();
        }
    }
}
