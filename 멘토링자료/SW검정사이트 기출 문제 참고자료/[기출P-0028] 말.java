import java.io.*;
import java.util.*;
 
//public class preP_0028 { // 말
public class Solution { // 말
    static BufferedReader br;
    static StringTokenizer st;
     
    static int T;
    static int N; 
    static int K; 
     
    static int A[][] = new int[20][2]; // A
    static int B[][] = new int[20][2]; // B
 
    static int C[][] = new int[3001][3001]; // 경우의 수 들을 미리 저장해 둘 배열
     
    static ArrayList<Point> PNT = new ArrayList<>();
     
    static long ANS;
     
    static class Point implements Comparable<Point>{
        int X;
        int Y;
         
        public Point(int x, int y) {
            this.X = x;
            this.Y = y;
        }
 
        @Override
        public int compareTo(Point that) {
            // TODO Auto-generated method stub
            if(this.X > that.X) {
                return 1;
            } else if(this.X < that.X) {
                return -1;
            } else {
                if(this.Y > that.Y) {
                    return 1;
                } else if(this.Y < that.Y) {
                    return -1;
                } else {
                    return 0;
                }               
            }
        }
    }
     
    public static void main(String args[]) throws Exception {
//      System.setIn(new FileInputStream("sample_input.txt"));
        br = new BufferedReader(new InputStreamReader(System.in));
        st = new StringTokenizer(br.readLine());
        T = Integer.parseInt(st.nextToken());
         
        // 움직일 수 있는 경우의 수를 매번 계산하기 힘드니까 미리 계산해둔다.
        for(int i = 1; i <= 3000; i++) {
            for(int j = 1; j <= 3000; j++) {
                if(i == 1 && j == 1) {
                    C[i][j] = 1;
                } else {
                    C[i][j] = (C[i][j] + C[i - 1][j] + C[i][j - 1]) % 1000000007;
                }
            }
        }
 
        for(int t = 1; t <= T; t++) {
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());   
            K = Integer.parseInt(st.nextToken());
             
            for(int k = 1; k <= K; k++) {
                st = new StringTokenizer(br.readLine());
                A[k][0] = Integer.parseInt(st.nextToken());
                A[k][1] = Integer.parseInt(st.nextToken());
                 
                B[k][0] = Integer.parseInt(st.nextToken());
                B[k][1] = Integer.parseInt(st.nextToken());
            }
             
            ANS = C[N][N]; // (1, 1) 에서 (N, N) 까지 가는 전체 경로의 수
             
            // K 가 1 인 경우에는 A1~B1 에 대한 경우의 수를 전체에서 빼면 된다.
            // K 가 2 인 경우에는 1. A1~B1, A2~B2 에 대한 경우의 수를 전체에서 빼고 2. A1~B1과 A2~B2 의 교집합 만큼을 더해줘야(보정) 한다.
            // K 가 n 인 경우에는 1. 각각의 경우의 수 제거 2. 두 경우의 교집합 추가 3. 세 경우의 교집합 제거 ... n. n 경우의 교집합을 순번에 맞게 추가 또는 제거 한다.
             
            int SIGN = 1;  
            for(int k = 1; k <= K; k++) {
                PNT.clear(); 
                SIGN = SIGN * (-1); // 최초 각각에 대한 경우의 수는 전체에서 빼야 하고, 이후에 추가 제거 추가 제거 순서를 거쳐야 하므로 Signal 변수에 -1을 곱하는 것으로 관리함  
                 
                Srch(k, 1, SIGN); 
            }
             
            System.out.print("#");
            System.out.print(t);
            System.out.print(" ");
            System.out.println(ANS);
        }
    }
 
    private static void Srch(int k, int l, int s) { // k, location, sign 
        // TODO Auto-generated method stub
        if(PNT.size() == k * 2) { // 최초 1개 조합(A 와 B 각 1개씩), 이후 2개조합, 3개조합, ..., n개 조합의 A B 를 사용할 것이다.
             
            ArrayList<Point> LIST = new ArrayList<>(); // 계산용 list 를 별도로 사용한다.
            LIST.addAll(PNT); 
            Collections.sort(LIST); // ~ 정렬을 사용해야 하므로 기존 Point list 는 사용하기 불편함
             
            int X = 1; // 시작점 X
            int Y = 1; // 시작점 Y
             
            long TMP = 1; // (X, Y) 에서 (NX, NY) 로 가기까지의 경우의 수
             
            boolean CHK = true;
             
            for(int i = 0; i < LIST.size(); i++) {
                int NX = LIST.get(i).X;
                int NY = LIST.get(i).Y;
                 
                if(NX >= X && NY >= Y) { // (NX, NY) 가 (X, Y) 의 오른쪽 아래에 있으면 -> (X, Y) 에서 (NX, NY) 으로 이동할 수 있으면 
                    TMP = (TMP * C[NX - X + 1][NY - Y + 1]) % 1000000007; // 가로 (NX - X + 1), 세로 (NY - Y + 1) 만큼의 배열을 움직일 수 있는 경우의 수 만큼을 곱한다. 
                    // (X1, Y1) ~ (X2, Y2), (X2, Y2) ~ (X3, Y3)... 등은 모두 개별적으로 움직이는 독립조건이므로 각각의 경우의 수를 곱한다.
                } else { // (X, Y) 에서 (NX, NY) 으로 이동할 수 없으면 (2개 조합 이후의 상황에서 발생) 
                    TMP = 0; // 2개 조합 간의 교집합은 없다고 볼 수 있다.
                    CHK = false;
                    break;
                }
                 
                X = NX;
                Y = NY;
            }
             
            if(CHK = true) { // 가장 마지막 An~Bn 까지 도달했다면, 종점인 (N, N) 으로 이동한다.
                TMP = (TMP * C[N - X + 1][N - Y + 1]) % 1000000007;
                ANS = (ANS + (s * TMP)) % 1000000007;
                 
                if(ANS < 0) {
                    ANS = ANS + 1000000007;
                }
            }
             
        } else {
             
            for(int i = l; i <= K; i++) {
                PNT.add(new Point(A[i][0], A[i][1]));
                PNT.add(new Point(B[i][0], B[i][1]));
                 
                Srch(k, i + 1, s);
                 
                PNT.remove(PNT.size() - 1);
                PNT.remove(PNT.size() - 1);
            }
             
        }
         
    }
}
