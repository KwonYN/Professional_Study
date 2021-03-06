import java.io.*;
import java.util.*;
 
class Solution
{
    static int T, N;
    static final long INF = 987654321000000000L;
    static long[][] map, map2;
    public static void main(String[] args) throws Exception 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        T = Integer.parseInt(br.readLine().trim());
        for(int tc=1; tc<=T; tc++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
             
            st = new StringTokenizer(br.readLine());
            int[] del = new int[N];
            for(int i=0; i<N; i++)
                del[i] = Integer.parseInt(st.nextToken()); // 정점이 지워지는 순서
             
            map = new long[N+1][N+1];
            for(int i=1; i<N; i++)
            {
                st = new StringTokenizer(br.readLine());
                for(int j=i+1; j<=N; j++)
                {
                    long a = Long.parseLong(st.nextToken());
                    if(a == 0) // 두 정점이 연결되지 않은 경우
                         a = INF;
                     map[i][j] = map[j][i] = a;
                }
            }
             
            map2 = new long[N+1][N+1]; // 정점이 추가되는 순서로 리라벨링하여 map2 생성
            for(int i=1; i<=N; i++)
            {
                int a = del[N-i];
                for(int j=1; j<=N; j++)
                {
                    int b = del[N-j];
                    map2[i][j] = map[a][b];
                }
            }           
             
            // 플로이드-워셜로 모든쌍 최단거리 구하기
            long[] ans = new long[N+1];
            for(int k=1; k<=N; k++)
            {               
                for(int i=1; i<=N; i++)
                { 
                    if(map2[i][k] == INF)
                        continue;
                    for(int j=1; j<=N; j++)
                        map2[i][j] = Math.min(map2[i][j], map2[i][k] + map2[k][j]);                     
                }
                 
                // 정점 추가될때마다 가장 큰 최단 경로 구하기 
                long nMax = 0;
                for(int i=1; i<=k; i++)
                    for(int j=1; j<=k; j++)
                        if(map2[i][j] < INF)
                            nMax = Math.max(nMax, map2[i][j]);
                ans[k] = nMax;
            }
             
            bw.write("#" + tc + " ");
            for(int i=N; i>0; i--)
                bw.write(ans[i] + " ");
            bw.write("\n");
            bw.flush();
        }
        bw.close();
    }
}
