import java.io.*;
import java.util.*;
 
public class Solution {
 
    static class Pos {
        int v, p;
        public Pos (int v, int p) {
            this.v = v;
            this.p = p;
        }
        @Override
        public String toString() {
            return String.format("{%d - %d}", v, p);
        }
    }
    static class CompAsc implements Comparator<Pos>
    {
        public int compare(Pos o1, Pos o2)
        {
            if (o1.v > o2.v) return 1;
            else if (o1.v < o2.v) return -1;
            return 0;
        }
    }
   
    static class CompDesc implements Comparator<Pos>
    {
        public int compare(Pos o1, Pos o2)
        {
            if (o1.v > o2.v) return -1;
            else if (o1.v < o2.v) return 1;
            return 0;
        }
    }
     
    static int N, K;
    static Pos[] arr;
    static int AnswerN;
     
    public static void main(String[] args) throws IOException {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        String[] temp = br.readLine().trim().split(" ");
        int T = Integer.parseInt(temp[0]);
         
        for(int test_case = 1; test_case <= T ; test_case++) {
            temp = br.readLine().trim().split(" ");
            N = Integer.parseInt(temp[0]);
            K = Integer.parseInt(temp[1]);
             
            arr = new Pos[N];
 
            temp = br.readLine().trim().split(" ");
            for(int i=0; i< N; i++) {
                int v = Integer.parseInt(temp[i]);
                arr[i] = new Pos(v, i);
            }
             
            AnswerN = 0;
            // 1인 경우는 최대값을 출력
            if(K==1) {
                for(int i=0; i< N; i++) {
                    AnswerN = Math.max(AnswerN, arr[i].v);
                }
                System.out.println("#"+test_case+" " + AnswerN);
                continue;
            }
 
            // 중앙값 판별을 위해 좌우 Queue 생성
            PriorityQueue<Pos> RQ = new PriorityQueue<>(new CompAsc());
            PriorityQueue<Pos> LQ = new PriorityQueue<>(new CompDesc());
            // K개를 유지하기 위한 좌우 count
            int rCnt=0;
            int lCnt=0;
             
            // 첫번째 값을 오늘쪽 Queue에 넣고 count 1 증가
            // 오른쪽 count 가 왼쪽보다 항상 1 커야 함
            RQ.add(arr[0]);
            rCnt++;
             
            // K개까지 양쪽 Queue에 넣고 각각 count 1 증가
            for(int i=1; i<K ;i++) {
                Pos mid = RQ.peek();
                if (arr[i].v > mid.v) { // 중앙값보다 크면 중앙값은 왼쪽큐로 이동, 신규는 오른쪽 큐에 추가
                    RQ.poll();
                    rCnt--;
 
                    LQ.add(mid);
                    lCnt++;
 
                    RQ.add(arr[i]);
                    rCnt++;
                } else { // 중앙값보다 작으면 왼쪽큐에 추가
                    LQ.add(arr[i]);
                    lCnt++;
                }
                // 오른쪽을 1개 많이 가져가므로 왼쪽이 크거나 같으면 오른쪽으로 이동
                if (lCnt >= rCnt) {
                    RQ.add(LQ.poll());
                    lCnt--;
                    rCnt++;
                }
            }
             
             
            // Queue에서 꺼낼때 K개 이전은 제거
            for(int i=K; i<N ;i++) {
                Pos mid = RQ.peek();
                while(mid.p < (i-K)) { // Queue에서 꺼낼때 K개 이전이면 제거하고 다음 값을 사용
                    RQ.poll();
                    mid = RQ.peek();
                }
                AnswerN = Math.max(AnswerN, mid.v); // 중앙값 중 최대값
 
                // K개 이전 값 제거
                // 삭제한 값 좌우 체크하여 count 1 감소
                if (mid.p <= (i-K)) { // 중앙값의 위치가 K개 이전이면 제거
                    RQ.poll(); 
                    rCnt--;
                    mid = RQ.peek();
                } else if (arr[i-K].v >= mid.v) {
                    rCnt--;
                } else {
                    lCnt--;
                }
                 
                // 신규로 추가하는 값 판별하고 좌우 count 증가 
                if (arr[i].v > mid.v) { // 중앙값보다 크면 오른쪽 큐 추가
                    if (mid.p >= (i-K)) { // 중앙값이 삭제 안 된 경우 왼쪽큐로 옮겨준다.
                        RQ.poll();
                        rCnt--;
                        LQ.add(mid);
                        lCnt++;
                    }
 
                    RQ.add(arr[i]);
                    rCnt++;
                } else { // 중앙값보다 작거나 같으면 왼쪽 큐 추가
                    LQ.add(arr[i]);
                    lCnt++;
                }
                // 좌우 균형 맞춤
                if (lCnt >= rCnt) {
                    Pos t = LQ.poll();
                    while(t.p < (i-K)) { // Queue에서 꺼낼때 삭제 마킹되었으면 제거하고 다음 값을 사용
                        t = LQ.poll();
                    }
                    lCnt--;
                    RQ.add(t);
                    rCnt++;
                }
            }
             
            // 마지막 중앙값
            Pos mid = RQ.peek();
            while(mid.p < (N-K)) { // Queue에서 꺼낼때 삭제 마킹되었으면 제거하고 다음 값을 사용
                RQ.poll();
                mid = RQ.peek();
            }
            AnswerN = Math.max(AnswerN, mid.v);
             
            System.out.println("#"+test_case+" " + AnswerN);
        }
    }
}
