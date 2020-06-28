import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
 
/**
 * 
 * 키워드 : 
 *
 */
public class Solution {
 
    static int ans, N, M;
    static ArrayList<Integer>[] arr;
    static Map<Integer, Integer>[] map;
 
    public static void main(String[] args) throws Exception {
//      System.setIn(new FileInputStream("practice/P-0044/input.txt"));
//      System.setIn(new FileInputStream("practice/P-0044/sample_input.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
 
        int T = Integer.parseInt(br.readLine());
        for (int tc = 1; tc <= T; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
 
            arr = new ArrayList[N + 1];
            map = new HashMap[N + 1];
            ans = 0;
            for (int i = 0; i <= N; i++) {
                arr[i] = new ArrayList<Integer>();
                map[i] = new HashMap<Integer, Integer>();
            }
 
            for (int i = 1; i <= M; i++) {
                st = new StringTokenizer(br.readLine());
                int f = Integer.parseInt(st.nextToken());
                int t = Integer.parseInt(st.nextToken());
 
                arr[f].add(t);
                arr[t].add(f);
            }
 
            proc();
            bw.write("#" + tc + " " + ans);
            bw.newLine();
            bw.flush();
        }
        bw.close();
        br.close();
    }
 
    //모든점 c에 연결된 a, b에 대하여
    //모든 쌍 (a,b)를 구한후
    //각 (a, b)가 연결되지 않은 경우 c의 갯수를 +1
    static void proc() {
        for (int i=1; i <= N; i++) {
            for (int j=0 ; j<arr[i].size() ; j++) {
                int a = arr[i].get(j);
                for (int k=j+1 ; k<arr[i].size() ; k++) {
                    int b = arr[i].get(k);
                    if (a == b) {
                        continue;
                    } else {
                        int count = 0;
                        if( !arr[a].contains(b) ) {
                            if( a>b ) {
                                count = count(a, b);
                            } else {
                                count = count(b, a);
                            }
                        }
                        ans = Math.max(ans, count);
                    }
                }
            }
        }
    }
     
    public static int count(int a, int b){
        int cnt = 0;
        if (map[a].containsKey(b)) {
            cnt = map[a].get(b);
        }
        map[a].put(b, ++cnt);
        return cnt;
    }
}
