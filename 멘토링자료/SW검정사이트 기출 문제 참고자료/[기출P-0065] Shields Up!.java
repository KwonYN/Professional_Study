import java.io.*;
import java.util.*;
   
class Solution
{   
    static int T, N, M;
    static int[][] map;
    static int dx[] = {0, 0, -1, 1};
    static int dy[] = {-1, 1, 0, 0};
    public static void main(String[] args) throws Exception
    { 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine().trim());
        for(int tc=1; tc<=T; tc++)
        {         
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());           
            map = new int[N+2][M+2];            
            for(int i=1; i<=N; i++) 
            {
                String tmp = br.readLine();            
                for(int j=1; j<=M; j++) 
                    map[i][j] = tmp.charAt(j-1) - 48; 
            }
             
            PriorityQueue<Shield> pq = new PriorityQueue<Shield>(new CompShield());
            for(int i=1; i<=N; i++)
            {
                for(int j=1; j<=M; j++)
                {
                    if(map[i][j] > 0)
                    {
                        for(int k=0; k<4; k++)
                        {
                            if(map[i+dx[k]][j+dy[k]] == 0)
                            {
                                pq.add(new Shield(i, j, map[i][j])); // 주변에 하나라도 0이 있으면 우선순위큐에 추가
                                map[i][j] = -1;
                                break; // 해당 지점은 한번만 넣어줘야 하므로 break
                            }
                        }
                    }
                } 
            }           
             
            int ans = 0;
            while(!pq.isEmpty())
            {
                Shield here = pq.poll();
                ans += here.h;
                for(int i=0; i<4; i++)
                {        
                    int nextX = here.x + dx[i];
                    int nextY = here.y + dy[i];
                    if(map[nextX][nextY] > 0) 
                    { 
                        pq.add(new Shield(nextX, nextY, here.h + map[nextX][nextY]));   
                        map[nextX][nextY] = -1;
                    }
                }
            } 
            System.out.println("#" + tc + " " + ans);
        }
    }    
    static class Shield
    {
        int x, y, h; // x좌표, y 좌표, 침공당하는 시간
        Shield(int x, int y, int h)
        {
            this.x = x;
            this.y = y;
            this.h = h;
        }       
    }    
    static class CompShield implements Comparator<Shield>  
    {
        public int compare(Shield o1, Shield o2) 
        {
            return o1.h - o2.h; // 침공당하는 시간 오름차순 정렬
        }
    }
}
