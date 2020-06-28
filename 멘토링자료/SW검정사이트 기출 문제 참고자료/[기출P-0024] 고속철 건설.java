import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;
 
 
public class Solution {
     
    static long[][] nodeXY;                     // 모든 점의 좌표정보
    static ArrayList<Point>[] group;                // 도 안의 모든 점
    static ArrayList<Point>[] grpConvex;        // 도 안의 convex점
    static ArrayList<Point>[] grpMaxMin;        // 도 안의 사각점
     
    static long X;                                  // convex hull 위한 sorting 기준점
    static long Y;                                  // (X,Y)
     
    static long a;                                  // 고속철도
    static long b;                                  // (a,b)와 (c,d) 직선
    static long c;
    static long d;
     
    private static class Point {                    // 점 좌표정보
        long x;
        long y;
        public Point(long x, long y) {
            this.x = x;
            this.y = y;
        }
    }
 
    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws Exception {
         
        //System.setIn( new FileInputStream("src/sds_sw_practice_1/ChooChooTrain"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine().trim(), "");
         
        int T = Integer.parseInt(st.nextToken());
         
        for (int t = 1; t <= T; t++) {
             
            st = new StringTokenizer(br.readLine().trim(), " ");
             
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());
             
            nodeXY = new long[N+1][2];
            ArrayList<Integer>[] adjList = new ArrayList[N+1];
             
            // 노드 입력
            for (int n = 1; n <= N; n++) {
                st = new StringTokenizer(br.readLine().trim(), " ");
                 
                nodeXY[n][0] = Long.parseLong(st.nextToken());
                nodeXY[n][1] = Long.parseLong(st.nextToken());
            }
             
            // 간선 입력
            for (int m = 1; m <= M; m++) {
                st = new StringTokenizer(br.readLine().trim(), " ");
                int from = Integer.parseInt(st.nextToken());
                int to = Integer.parseInt(st.nextToken());
                 
                if(adjList[from] == null) adjList[from] = new  ArrayList<Integer>();
                adjList[from].add(to);
                if(adjList[to] == null) adjList[to] = new  ArrayList<Integer>();
                adjList[to].add(from);
            }
             
             
            /*
             * 1. 도 나누기(bfs)
             */
            int[] discovered = new int[N+1];
            boolean runBFS = true;
            group = new ArrayList[5+1];
             
            int start=0;
            int groupID;
            int cnt =0;
            for (groupID = 1; groupID <= 5; groupID++) {
                for (int i = 1; i <= N; i++) {
                    if(discovered[i] == 0){
                        start = i;
                        group[groupID] = new ArrayList<Point>();
                        cnt++;
                        break;
                    }
                    if(i==N){
                        runBFS = false;
                    }
                }
                //bfs
                if(runBFS) bfs(adjList, discovered, start, groupID);
            }
             
            /*
             * 2. 도마다 볼록껍질 점 구하기 + 사각점 구하기
             */
            grpConvex = new ArrayList[cnt+1];
            for (int i = 1; i <= cnt; i++) {
                grpConvex[i] = new ArrayList<Point>();
            }
             
            grpMaxMin = new ArrayList[cnt+1];
            for (int i = 1; i <= cnt; i++) {
                grpMaxMin[i] = new ArrayList<Point>();
            }
             
             for (groupID = 1; groupID <= cnt; groupID++) {
                  
                 for(int i=1; i < group[groupID].size(); i++){
                     if(group[groupID].get(0).y > group[groupID].get(i).y || group[groupID].get(0).y == group[groupID].get(i).y && group[groupID].get(0).x > group[groupID].get(i).x) {
                         Point tmp = group[groupID].get(0);
                         group[groupID].add(0,group[groupID].get(i));
                         group[groupID].add(i,tmp);
                     }
                 }
                  
                 X = group[groupID].get(0).x;
                 Y = group[groupID].get(0).y;
                  
                 group[groupID].sort(new Comparator<Point>() {
                     @Override
                     public int compare(Point a, Point b) {
                         int v = ccwForConvexHull (new Point(X,Y), a, b);
                         if (v > 0) return -1;
                         if (v < 0) return 1;
                         return (int)((Math.abs(a.x-X) + a.y-Y) - (Math.abs(b.x-X) + b.y-Y));
                     }           
                 });
                  
                 List<Integer> list = new ArrayList<>();
                  
                 // 첫번째 점 입력
                 list.add(0);
                 grpConvex[groupID].add(group[groupID].get(0));
                 long xMin = grpConvex[groupID].get(0).x;
                 long xMax = grpConvex[groupID].get(0).x;
                 long yMin = grpConvex[groupID].get(0).y;
                 long yMax = grpConvex[groupID].get(0).y;
                  
                 //convex hull 구하기
                 for (int i = 1; i < group[groupID].size() ; i++) {
                     while (list.size() > 1 && ccwForConvexHull(group[groupID].get(list.get(list.size()-2)), group[groupID].get(list.get(list.size()-1)), group[groupID].get(i)) <= 0) {
                         grpConvex[groupID].remove(list.size()-1);
                         list.remove(list.size()-1);
                     }
                     list.add(i);
                     grpConvex[groupID].add(group[groupID].get(i));
                      
                     // 여기서 i-1번째까지 최대최소를 구하는 로직을 짬
                     // groupMaxMin의 
                     long x_1 = grpConvex[groupID].get(list.size()-1).x;
                     long y_1 = grpConvex[groupID].get(list.size()-1).y;
                     if(xMin > x_1) xMin = x_1;
                     if(xMax < x_1) xMax = x_1;
                     if(yMin > y_1) yMin = y_1;
                     if(yMax < y_1) yMax = y_1;
                      
                 }
                 // 제일 끝 점 조사
                 long x_1 = grpConvex[groupID].get(grpConvex[groupID].size()-1).x;
                 long y_1 = grpConvex[groupID].get(grpConvex[groupID].size()-1).y;
                 if(xMin > x_1) xMin = x_1;
                 if(xMax < x_1) xMax = x_1;
                 if(yMin > y_1) yMin = y_1;
                 if(yMax < y_1) yMax = y_1;
                  
                 // 사각점 만들기
                 grpMaxMin[groupID].add(new Point(xMin, yMin));//0번째는 좌하단점
                 grpMaxMin[groupID].add(new Point(xMax, yMin));//1번째는 우하단점
                 grpMaxMin[groupID].add(new Point(xMax, yMax));//2번째는 우상단점
                 grpMaxMin[groupID].add(new Point(xMin, yMax));//3번째는 좌상단점
                    
            }
              
             /*
              * 3. 고속철도마다 검사
              *     1) 사각점이 모두 한쪽에 있으면 통과
              *     2) 사각점을 둘둘로 나누거나 두점이상 겹치면 탈락
              *     3) 이 외(사각점을 셋하나로 나누면)는 더 검사해야함.  
              */
              
            int result = 0;
            // 고속철도 하나씩 검사
            for (int k = 1; k <= K; k++) {
                st = new StringTokenizer(br.readLine().trim(), " ");
                a = Long.parseLong(st.nextToken());
                b = Long.parseLong(st.nextToken());
                c = Long.parseLong(st.nextToken());
                d = Long.parseLong(st.nextToken());
                 
                boolean pass = true;
                for (int i = 1; i < grpConvex.length; i++) {
                     
                    int positive = 0;
                    int negative = 0;
                    int zero = 0;
                     
                    //1. 사각점으로 검사
                    for (Point recPoint : grpMaxMin[i]) {
                        switch (ccwForTrain(recPoint.x,recPoint.y)) {
                        case 1:
                            positive++;
                            break;
                        case -1:
                            negative++;
                            break;
                        case 0:
                            zero++;
                            break;
                        }
                    }
                     
                    if(positive == 4 || negative== 4){
                        //통과
                    }else if(positive == 2 || negative== 2 || zero >= 2){
                        //탈락
                        pass = false;
                        break;
                    }else{
                        //2. 직접조사
                        int check = ccwForTrain(grpConvex[i].get(0).x,grpConvex[i].get(0).y);
                        for (int m = 1; m < grpConvex[i].size(); m++) {
                            if(check != ccwForTrain(grpConvex[i].get(m).x,grpConvex[i].get(m).y) || check == 0){
                                pass = false;
                                break;
                            }
                        }
                    }
                     
                    if(!pass) break;
                     
                }
                 
                if(pass) result++;
                 
            }
             
            bw.write("#"+t+" "+result+"\n");
        }
         
        bw.flush();
        bw.close();
        br.close();
    }
 
    protected static void bfs(ArrayList<Integer>[] adjList, int[] discovered, int start, int groupID) {
        int node;
        Queue<Integer> queue = new LinkedList<Integer>();
         
        queue.add(start);
        discovered[start] = 1;
         
        while(queue.size() > 0){
            node = queue.poll();
             
            //방문~!
            group[groupID].add(new Point(nodeXY[node][0], nodeXY[node][1]));
             
            if(adjList[node] != null){
                for(int adjacent : adjList[node]){
                    if(discovered[adjacent] == 0){
                        queue.add(adjacent);
                        discovered[adjacent] = 1;
                    }
                }
            }
        }
    }
     
    static int ccwForConvexHull (Point a, Point b, Point c) {
        long v = (long) (c.y - a.y) * (b.x - a.x)  - (long) (c.x - a.x) * (b.y - a.y);
        if (v > 0) return 1;
        if (v < 0) return -1;
        return 0;
    }
 
    static int ccwForTrain(long x, long y){
        long result = (d-b)*(x-a) - (c-a)*(y-b);
        if(result > 0) return 1;
        else if(result < 0) return -1;
        else return 0;
    }
     
}
