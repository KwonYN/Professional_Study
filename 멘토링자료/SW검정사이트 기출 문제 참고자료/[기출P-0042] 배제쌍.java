import java.io.*;
import java.util.*;
 
class Solution
{
    static int T, N, M, K;
    static long ans;
    static ArrayList<Edge> edge; // 간선들의 정보 저장
    static boolean[] visited; // 간선 사용불가 여부 체크 배열
    static int[][] baeje; // 배제쌍 저장 배열
    static int[] parent;    
    public static void main(String[] args) throws IOException 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        T = Integer.parseInt(st.nextToken());
        for(int tc=1; tc<=T; tc++)
        {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());
 
            parent = new int[N+1];          
            visited = new boolean[M+1];
            baeje = new int[K][2];
            edge = new ArrayList<Edge>();
            for(int i=1; i<=M; i++)
            {
                st = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                int c = Integer.parseInt(st.nextToken());
                edge.add(new Edge(a, b, c, i));
            }
             
            for(int i=0; i<K; i++)
            {
                st = new StringTokenizer(br.readLine());
                baeje[i][0] = Integer.parseInt(st.nextToken());
                baeje[i][1] = Integer.parseInt(st.nextToken());
            }           
 
            Collections.sort(edge, new CompEdge());     
            ans = Long.MAX_VALUE;
            dfs(0);     
            if(ans == Long.MAX_VALUE)
                ans = -1;
            System.out.println("#" + tc + " " + ans);
        }
    }
     
   static void dfs(int d) 
   {
        if(d == K) 
        {
            ans = Math.min(ans, Kruskal());
            return;
        }
        for(int i=0; i<2; i++)
        {
            boolean back = visited[baeje[d][i]];
            visited[baeje[d][i]] = true;
            dfs(d+1);
            visited[baeje[d][i]] = back;
        }
    }
     
    static long Kruskal() 
    {
        long ret = 0;
        int cnt = 0;
        for(int i=1; i<=N; i++) 
            parent[i] = i;
        for(int i=0; i<M; i++)
        {
            Edge here = edge.get(i);
            int a = find(here.a);
            int b = find(here.b);
            if((a != b) && !visited[here.idx])
            { 
                union(a, b);
                ret += here.cost; 
                if(++cnt == N-1)
                    return ret;
            }
        }       
        return Long.MAX_VALUE;
    }
     
    static void union(int u, int v)
    {
        parent[find(u)] = find(v);
    }
     
    static int find(int u)
    {
        if(u == parent[u]) 
            return u;
        return parent[u] = find(parent[u]);
    }
     
    static class Edge
    {
        int a, b, cost, idx;    
        Edge(int a, int b, int cost, int idx)
        {
            this.a = a;
            this.b = b;
            this.cost = cost;
            this.idx = idx;
        }
    }
 
    static class CompEdge implements Comparator<Edge>
    {
        public int compare(Edge o1, Edge o2)
        {
            return o1.cost - o2.cost;
        }
    }
}
