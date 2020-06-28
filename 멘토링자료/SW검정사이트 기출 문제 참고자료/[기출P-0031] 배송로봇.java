
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
 
import java.io.*;
import java.util.*;
 
public class Solution {
     
    static int r, n, answer;
    static int[] s = new int[10];
    static int[] p1 = new int[10];
    static int[] p2 = new int[10];
    static int[] t1 = new int[10];
    static int[] t2 = new int[10];
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int T = Integer.parseInt(br.readLine().trim());
        double T1 = System.currentTimeMillis();
        for(int t=0; t<T; t++) {
            st = new StringTokenizer(br.readLine().trim());
            r = Integer.parseInt(st.nextToken());
            n = Integer.parseInt(st.nextToken());
            answer = -1;
            for(int i=0; i<n; i++) 
                        {
                st = new StringTokenizer(br.readLine().trim());
                p1[i] = Integer.parseInt(st.nextToken()); // 발송지
                p2[i] = Integer.parseInt(st.nextToken()); // 목적지
                t1[i] = Integer.parseInt(st.nextToken()); // 발송시간
                t2[i] = Integer.parseInt(st.nextToken()); // 도착요구시간
                s[i] = 0;
            }
            backTrack(r, 0);
            System.out.println("#"+(t+1)+" "+answer);
        }
        br.close();
        double T2 = System.currentTimeMillis();
        //System.out.println((T2-T1)/1000);
    }
     
    static void backTrack(int pos, int time) 
    {
        if(answer != -1 && time >= answer) return;
 
        if(isFinished()) {
            answer = time;
            return;
        }
 
        for(int i=0; i<n; i++) 
        {
            if(s[i] == 2) continue;
             
            if(s[i] == 0) // 아직 안싣었을때는 출발지가 목적지임
            {
                if(!oneStoneTwoBirds(pos, p1[i], time)) // 출발지가 목적지임
                {
                    s[i] = 1;
                    backTrack(p1[i], max(t1[i], time + abs(pos - p1[i])));
                    s[i] = 0; //i는 배달 완료
                }
            } 
            else
            {
                if(abs(p2[i] - pos) + time > t2[i]) return;
                 
                if(!oneStoneTwoBirds(pos, p2[i], time)) 
                {
                    s[i] = 2; // 배송이 완료된 상태
 
                    backTrack(p2[i], time + abs(pos - p2[i]));
                    s[i] = 1; //로봇에 적재된 상태
                }
            }
        }
    }
     
    static boolean oneStoneTwoBirds(int pos, int des, int time) 
    { 
        //가는길에 주을 수 있거나 줄 수 있는지 확인.
        if(pos > des) 
        {
            int tmp = pos;
            pos = des;
            des = tmp;
        }
         
        for(int i=0; i<n; i++) 
        {
            if(s[i] == 1 && p2[i] < des && p2[i] > pos) return true;
            if(s[i] == 0 && p1[i] < des && p1[i] > pos && ((abs(pos - p1[i])+time) >= t1[i])) 
                return true;
        }
        return false;
    }
     
    static boolean isFinished() {
        for(int i=0; i<n; i++)
            if(s[i] != 2) return false;
        return true;
    }
     
    static int max(int x, int y) {
        return (x > y) ? x : y;
    }
     
    static int abs(int z) {
        return (z > 0) ? z : -z;
    }
     
     
     
}
 