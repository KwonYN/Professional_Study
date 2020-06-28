import java.io.*;
import java.util.*;
 
class Solution 
{
    static int T, N, M;
    static long[][] dist;
    static int[] color;
    static ArrayList<Edge>[] map;
    static long INF = Long.MAX_VALUE;   
    public static void main(String[] args) throws Exception 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));       
        T = Integer.parseInt(br.readLine());    
        for(int tc = 1; tc <= T; tc++) 
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());           
            dist = new long[4][N+1]; // 0: 적색/청색, 1: 적색, 2: 청색, 3: 없음 
            for(int i=0; i<4; i++)
                Arrays.fill(dist[i], INF); 
             
            String str = br.readLine();
            color = new int[N+1];
            for(int i=0; i<N; i++)
            {
                if(str.charAt(i) == 'W')
                    color[i+1] = 0;
                else if(str.charAt(i) == 'R')
                    color[i+1] = 1;
                else if(str.charAt(i) == 'B')
                    color[i+1] = 2;
                else
                    color[i+1] = 3;
            }
 
            map = new ArrayList[N+1]; 
            for(int i=1; i<=N; i++)
                map[i] = new ArrayList<Edge>();
             
            for(int i=0; i<M; i++) 
            {
                st = new StringTokenizer(br.readLine());
                int s = Integer.parseInt(st.nextToken());
                int e = Integer.parseInt(st.nextToken());
                long c = Long.parseLong(st.nextToken());    
                map[s].add(new Edge(0, e, c));              
            }
             
            System.out.println("#" + tc + " " + dijkstra(1));
        }
    }
     
    static long dijkstra(int s) 
    {
        dist[0][s] = 0;
        PriorityQueue<Edge> pq = new PriorityQueue<Edge>(M, new CompEdge());
        pq.add(new Edge(0, s, 0));
        while(!pq.isEmpty()) 
        {
            int pass = pq.peek().pass; // 현재 통행증 보유 상태
            int here = pq.peek().end;
            long cost = pq.peek().cost;
            pq.poll();          
                         
            if(here == N) // 최초로 목적지에 도착하면 최소 비용임
                return cost;
             
            if(dist[pass][here] < cost) 
                continue;
             
            int nextpass = -1;
            if(color[here] == 0)
                nextpass = 0;
            else if(color[here] == 3)
                nextpass = pass;
            else if(color[here] == 1 && (pass == 0 || pass == 1))
                nextpass = pass + 2;
            else if(color[here] == 2 && (pass == 0 || pass == 2))
                  nextpass = pass + 1;
             
            if(nextpass < 0)
                continue;
    
            for(int i=0; i<map[here].size(); i++) 
            {        
                int there = map[here].get(i).end;
                long nextCost = map[here].get(i).cost;
                if(dist[nextpass][there] > cost + nextCost)
                { 
                    dist[nextpass][there] = cost + nextCost;
                    pq.add(new Edge(nextpass, there, dist[nextpass][there]));
                }
            }
        }       
        return -1;
    }
     
    static class Edge 
    {
        int pass;
        int end;
        long cost;
        Edge(int pass, int end, long cost) 
        {
            this.pass = pass;
            this.end = end; 
            this.cost = cost;
        }
    }
     
    static class CompEdge implements Comparator<Edge> 
    {
        public int compare(Edge o1, Edge o2) 
        {
            return (int)(o1.cost - o2.cost);
        }
    }
}
