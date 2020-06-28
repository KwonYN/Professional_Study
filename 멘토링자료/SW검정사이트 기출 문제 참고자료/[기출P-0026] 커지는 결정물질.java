import java.util.*;
import java.io.*;
 
public class Solution {
    static int T, N;
    static int vv, ll;
    static String Ans;
    static Mat[] M;
    static StringTokenizer st = null;
 
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());
        for(int ts=1; ts<=T; ts++) {
            N = Integer.parseInt(br.readLine());
            M = new Mat[N];
            for(int i=0; i<N; i++) {
                st = new StringTokenizer(br.readLine());
                M[i] = new Mat(i+1, Integer.parseInt(st.nextToken()),
                        Integer.parseInt(st.nextToken()),
                        Integer.parseInt(st.nextToken()),
                        Integer.parseInt(st.nextToken()),
                        Integer.parseInt(st.nextToken()));
            }
            Arrays.sort(M, 0, N, new Comparator<Mat>(){
                public int compare(Mat M1, Mat M2) { return M2.d - M1.d;}
            });
            for(int i=0; i<N-1; i++) {
                for(int j=i+1; j<N; j++) {
                    vv = M[i].v + M[j].v;
                    ll = Math.max( Math.abs( M[i].x - M[j].x ), Math.abs( M[i].y - M[j].y ) ) * 2 - ( M[i].s + M[j].s );
                    if( (long)M[i].ll * vv < (long)ll * M[i].vv ) continue; 
                    if( M[j].vv == 0 || ( (long)ll * M[j].vv < (long)M[j].ll * vv ) ){
                        M[j].vv = vv;
                        M[j].ll = ll; 
                    }
                }
            }
            Arrays.sort(M, 0, N, new Comparator<Mat>(){
                public int compare(Mat M1, Mat M2) {
                    long t1, t2;
                    t1 = (long)M1.ll * M2.vv;
                    t2 = (long)M2.ll * M1.vv;
                    if( t1 < t2 ) return -1;
                    if( t1==t2 && M1.d < M2.d ) return -1;                  
                    return 1;
                }
            });
            Ans = Integer.toString(M[0].id);
            for( int i=1; i<N; i++ ){
                Ans = Ans+" "+M[i].id;
            }
            System.out.println("#"+ts+" "+Ans);
        }
    }
    public static class Mat {
        int id, x, y, v, d, s, vv, ll;
        public Mat (int i1, int i2, int i3, int i4, int i5, int i6) {
            id = i1; x = i2; y = i3;
            s  = i4; v = i5; d = i6;
        }
    }
}
