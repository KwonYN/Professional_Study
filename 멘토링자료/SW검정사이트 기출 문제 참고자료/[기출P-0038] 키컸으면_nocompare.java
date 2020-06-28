import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class Solution {
    private static final int S = 1024 * 1024;
    private static int h[][];
    private static int tree[] = new int[2 * S];
    private static int N;
 
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb;
        StringTokenizer st;
 
        int T = Integer.parseInt(br.readLine().trim());
        int Q;
        int answer[];
        int query[][];
        for (int t = 1; t <= T; t++) {
            for (int i = 0; i < 2 * S; i++) {
                tree[i] = 0;
            }
            st = new StringTokenizer(br.readLine().trim());
            sb = new StringBuilder();
 
            N = Integer.parseInt(st.nextToken());
            Q = Integer.parseInt(st.nextToken());
 
            h = new int[N][2];
            st = new StringTokenizer(br.readLine().trim());
            for (int i = 0; i < N; i++) {
                h[i][0] = i;
                h[i][1] = Integer.parseInt(st.nextToken()) - 1;
                update(S + i, 1);
            }
 
            Arrays.sort(h, (int[] o1, int[] o2) -> {
                return o1[1] - o2[1];
            });
 
            query = new int[Q][4];
            answer = new int[Q];
            for (int i = 0; i < Q; i++) {
                st = new StringTokenizer(br.readLine().trim());
 
                query[i][0] = i;
                query[i][1] = Integer.parseInt(st.nextToken()) - 1;
                query[i][2] = Integer.parseInt(st.nextToken()) - 1;
                query[i][3] = Integer.parseInt(st.nextToken());
            }
            Arrays.sort(query, (int[] o1, int[] o2) -> {
                return o1[3] - o2[3];
            });
 
            int c = 0;
            for (int i = 0; i < Q; i++) {
                for (int j = c; j < N; j++) {
                    if (h[j][1] < query[i][3]) {
                        update(S + h[j][0], -1);
                    } else {
                        c = j;
                        break;
                    }
                }
                answer[query[i][0]] = sum(S + query[i][1], S + query[i][2]);
            }
 
            for (int i = 0; i < Q; i++) {
                sb.append(answer[i]);
                sb.append(" ");
            }
            System.out.println("#" + t + " " + sb.toString().trim());
        }
    }
 
    private static int sum(int i, int j) {
        int sum = 0;
        int l = i;
        int r = j;
        while (l < r) {
            if ((l & 1) == 1) {
                sum += tree[l];
                l++;
            }
            if ((r & 1) == 0) {
                sum += tree[r];
                r--;
            }
            l /= 2;
            r /= 2;
        }
        if (l == r)
            sum += tree[l];
 
        return sum;
    }
 
    private static void update(int index, int d) {
        int p = index;
        while (p > 0) {
            tree[p] += d;
            if (tree[p] < 0) {
                tree[p] = 0;
            }
            p /= 2;
        }
    }
}
