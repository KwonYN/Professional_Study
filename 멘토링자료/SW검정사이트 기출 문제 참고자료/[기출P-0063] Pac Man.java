import java.io.*;
import java.util.*;
 
class Solution
{
    static int T, N, M, sx, sy, ex, ey, cidx, INF = 987654321;
    static boolean[][] map;
    static int[] cx, cy;
    static int[] dx = {0, 1, 0, -1};
    static int[] dy = {-1, 0, 1, 0};
    public static void main(String[] args) throws Exception 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());            
            map = new boolean[N+2][M+2]; // 외곽을 false로 둘러싸기 위해서 N+2, M+2로 생성   
            cx = new int[4]; // 고스트들의 x위치
            cy = new int[4]; // 고스트들의 y위치
            cidx = 0; // 고스트의 숫자
            for(int i=1; i<=N; i++)
            {
                String str = br.readLine();
                for(int j=1; j<=M; j++)
                {
                    char ch = str.charAt(j-1);
                    if(ch != '#')
                    {
                        map[i][j] = true;
                        if(ch == 'S') // 팩맨 시작위치
                        {
                            sx = i;
                            sy = j;
                        }
                        if(ch == 'E') // 종료위치
                        {
                            ex = i;
                            ey = j;
                        }
                        if(ch == 'C') // 고스트 시작위치
                        {
                            cx[cidx] = i;
                            cy[cidx++] = j;
                        }                       
                    }
                }
            }            
            int pacman = bfs(sx, sy); // 팩맨 최단거리
            for(int i=0; i<cidx; i++)
            {
                int ghost = bfs(cx[i], cy[i]); // 고스트 최단거리
                if(pacman >= ghost && pacman%2 == ghost%2) // 고스트 최단거리가 작거나 같으면서 홀짝이 같으면 만난다.
                {
                    pacman = -1;
                    break;
                }
            }
            if(pacman == INF) // 팩맨이 종료위치에 도달할 수 없는 경우
                pacman = -1;
            System.out.println("#" + tc + " " + pacman);
        }
    }
 
    static int bfs(int x, int y)
    {
        int ret = INF;
        boolean[][] discovered = new boolean[N+2][M+2];
        Queue<Integer> qx = new LinkedList<Integer>();
        Queue<Integer> qy = new LinkedList<Integer>();
        Queue<Integer> dist = new LinkedList<Integer>();
        qx.add(x); 
        qy.add(y); 
        dist.add(0); 
        discovered[x][y] = true;
        while(!qx.isEmpty()) 
        {
            int here_x = qx.poll();
            int here_y = qy.poll();
            int here_dist = dist.poll();
            if(here_x == ex && here_y == ey)
            {
                ret = here_dist;
                break;
            }
            for(int i=0; i<4; i++) 
            {
                int next_x = here_x + dx[i];
                int next_y = here_y + dy[i];
                int next_dist = here_dist + 1;
                if(!discovered[next_x][next_y] && map[next_x][next_y]) 
                { 
                    qx.add(next_x); 
                    qy.add(next_y); 
                    dist.add(next_dist);
                    discovered[next_x][next_y] = true;                  
                }
            }
        }
        return ret;
    }
}
