import java.io.*;
import java.util.*;
 
class Solution
{
    static int T, N, MAX = 1000000001;
    static Player[] pl;
    public static void main(String[] args) throws Exception 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken()); // 선수의 수
            pl = new Player[N+2]; 
            int minD = MAX;
            for(int i=1; i<=N; i++)
            {
                st = new StringTokenizer(br.readLine());
                int s = Integer.parseInt(st.nextToken());
                int d = Integer.parseInt(st.nextToken());
                pl[i] = new Player(s, d);
                minD = Math.min(minD, d);
            }
            pl[0] = new Player(1, MAX);
            pl[N+1] = new Player(MAX, MAX); // 한번에 계산을 완료하기 위해 슈팅, 드리블 최대능력치 선수를 N+1번째로 추가 
            Arrays.sort(pl, 1, N+1, new CompShoot()); // 슈팅 능력 순으로 오름차순 정렬
             
            long ans = 0;
            int minDribble = pl[0].dribble; // 직전까지의 드리블 능력 최소치
            for(int i=1; i<=N+1; i++) // 훑고 지나가기 탐색
            {
                long dx = pl[i].shoot - pl[i-1].shoot;
                long dy = minDribble - 1;
                ans += dx * dy; // 가능한 감독 능력치 갯수(사각형의 넓이)
                minDribble = Math.min(minDribble, pl[i].dribble);
            }
            System.out.println("#" + tc + " " + ans);           
        }
    }
    static class Player
    {
        int shoot, dribble;
        Player(int s, int d)
        {
            shoot = s;
            dribble = d;
        }
    }
    static class CompShoot implements Comparator<Player>
    {
        public int compare(Player o1, Player o2)
        {
            return o1.shoot - o2.shoot;
        }
    }
}
