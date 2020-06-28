import java.io.*;
import java.util.*;
  
public class Solution
{
    static int N;
    static Point pt[] = new Point[200];
    static int num;
    static Point S, E;
    static final int OOB = 1000000001;
     
    static class Point {
        int x, y;
        public List<Integer> line = new ArrayList<Integer>();
         
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
     
    public static int setpoint(int x, int y) {
        int i;
         
        for (i = 0; i < num; i++) {
            if (pt[i].x == x && pt[i].y == y) {
                break;
            }
        }
         
        if (num == i) {
            pt[i].x = x;
            pt[i].y = y;
            num++;
        }
         
        return i;
    }
     
    public static int intersect(Point a, Point b, Point c, Point d) {
         
        return ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0 ? 1 : 0;
    }
     
    public static int ccw(Point a, Point b, Point c) {
        long c1 = (long)(b.x - a.x) * (c.y - a.y);
        long c2 = (long)(c.x - a.x) * (b.y - a.y);
         
        return c1 > c2 ? 1 : c1 < c2 ? -1 : 0;
    }
     
    public static void main(String args[]) throws Exception {
 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         
        int T = Integer.parseInt(br.readLine().trim());
        int tc, i;
        StringTokenizer st;
         
        int x1, y1, x2, y2;
        int c, d, is, ie;
         
        for(tc = 1; tc <= T; tc++) {
            N = Integer.parseInt(br.readLine().trim());
            num = 0;
             
            for (i = 0; i < 2 * N; i++) {
                pt[i] = new Point(0,0);
            }
             
            for (i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine().trim());
                 
                x1 = Integer.parseInt(st.nextToken());
                y1 = Integer.parseInt(st.nextToken());
                x2 = Integer.parseInt(st.nextToken());
                y2 = Integer.parseInt(st.nextToken());
                 
                c = setpoint(x1, y1);
                d = setpoint(x2, y2);
                 
                pt[c].line.add(d);
                pt[d].line.add(c);      
            }
             
            Queue<Integer> que = new LinkedList<Integer>();
             
            for (i = 0; i < num; i++) {
                if (pt[i].line.size() == 1) {
                    que.add(i);
                }
            }
             
            while (!que.isEmpty()) {
                c = que.poll();
                 
                if (pt[c].line.isEmpty()) {
                    continue;
                }
                 
                d = pt[c].line.get(0);
                pt[c].line.remove(0);
                pt[d].line.remove((Integer)c);
                 
                if (pt[d].line.size() == 1) {
                    que.add(d);
                }               
            }
             
            st = new StringTokenizer(br.readLine().trim());
            S = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
             
            st = new StringTokenizer(br.readLine().trim());
            E = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
             
            is = ie = 0;
             
            for (i = 0; i < num; i++) {
                for(int j : pt[i].line) {               
                    is += intersect(pt[i], pt[j], S, new Point(OOB, S.y + 1));
                    ie += intersect(pt[i], pt[j], E, new Point(OOB, E.y + 1));
                }
            }
 
            System.out.printf("#%d %d\n", tc, is / 2 % 2 == ie / 2 % 2 ? 0 : 1);
        }
    }
}
