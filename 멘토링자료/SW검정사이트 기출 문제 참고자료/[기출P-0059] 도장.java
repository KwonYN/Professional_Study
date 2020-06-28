import java.io.*;
import java.util.*;
     
class Solution
{   
    static int T, N, M;
    static final int INF = 987654321;
    static int[][] map, stamp;
    public static void main(String[] args) throws Exception
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
               
            int ans = 0, x1 = 0, y1 = 0;
            map = new int[N][M];            
            for(int i=0; i<N; i++)
            {
                String str = br.readLine();                
                for(int j=0; j<M; j++)
                {
                    if(str.charAt(j) == '#')
                    {
                        if(ans == 0)
                        {
                            x1 = i;
                            y1 = j;
                        }
                        map[i][j] = 1;
                        ans++;                        
                    }
                }
            }
              
            if(ans <= 1)
            {
                System.out.println("#" + tc + " " + ans);
                continue;
            }
   
            for(int i=x1; i<N; i++)
            {
                for(int j=0; j<M; j++)
                {
                    if(i == x1 && j == y1)
                        continue;
                    if(map[i][j] == 1)
                        ans = Math.min(ans, count(x1, y1, i-x1, j-y1));
                }
            }  
            System.out.println("#" + tc + " " + ans);
        }
    }
     
    static int count(int x1, int y1, int dx, int dy) 
    {
        int ret = 0;
        stamp = new int[N][M];
        for(int i=x1; i<N; i++) 
        {
            for(int j=0; j<M; j++) 
            {
                if(map[i][j] == 1) // 현재 위치가 #인 경우
                {
                    if(stamp[i][j] == 0) // 아직 도장이 안찍힌 경우 : 이미 현재 위치에 도장이 찍혔다면 이전에 #이 카운트 되었으므로 통과
                    {
                        int ax = i+dx, ay = j+dy; // 다음 위치
                        int bx = i-dx, by = j-dy; // 이전 위치
                        if(ax < N && ay >= 0 && ay < M && map[ax][ay] == 1) // 현재 위치의 #이 다음 위치에 찍혔다면
                        {
                            ret++; // 현재 위치에 1번 도장 #이 있음
                            stamp[i][j] = stamp[ax][ay] = 1; // 현재 위치와 다음 위치는 도장이 찍힌걸로 갱신
                        }
                        else // 현재 위치의 #이 다음 위치에 찍히지 않았다면
                        {
                            if(bx >= 0 && by >= 0 && by < M && map[bx][by] == 1) // 이전 위치에 #이 있으면
                            {
                                ret++; // 이전 위치에 1번 도장 #이 있음
                                stamp[i][j] = 1;
                            }
                            else // 이전 위치에도 #이 없고, 다음 위치에도 #이 없다면 현재 위치가 #일수 없음
                            {
                                return INF;
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }
}
