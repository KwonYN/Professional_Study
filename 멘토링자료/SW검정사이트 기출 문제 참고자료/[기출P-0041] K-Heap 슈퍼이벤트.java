import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
 
public class Solution {
//Solution
    //static PriorityQueue<Integer> pq;
    static LinkedList<Integer> llarray;
    static int[] tree;
    static int Array_size;
 
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        //BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int T,Q, action, get_number; //, pollnum;
        StringTokenizer st;
         
        T = Integer.parseInt(br.readLine()); //테케
                 
        Array_size = 2;
        while(Array_size <= 100000) {  //  테케안에서 케이스마다 사이즈 조절하니 시간 더걸림....걍 크게 하나 선언하고 쓰는게 좋은듯.
            Array_size *= 2;           // 들어올수 있는 숫자크기 100000 MAX 를 넣을수 있게 완전 2진트리 구조를 가지는 크기
        }
         
        //System.out.println("Array_size : " + Array_size);
         
        tree = new int[Array_size * 2];
         
        for (int t = 1; t <= T; t++) {
             
            Arrays.fill(tree, 0);
            StringBuilder ans = new StringBuilder();
            ans.append("#").append(t);
            Q = Integer.parseInt(br.readLine()); //행위수
             
            for(int i = 1 ; i <= Q ; i++) {
                st = new StringTokenizer(br.readLine());
                action = Integer.parseInt(st.nextToken());     //행위 1 뽑기, 2발표 (1≤X≤100,000)
                get_number = Integer.parseInt(st.nextToken()); //뽑은 혹은 발표 번호 K (1≤K≤참가자수(X(1))) 
                 
                if(action == 1) {
                     
                    tree_add(get_number); //트리에다가 넣기
                     
                }else if(action == 2) {
                     
                    ans.append(" ").append(tree_search(get_number)); //트리에서 찾아오기
                     
                }else {
                    //없겠지....
                }
                 
            }//FOR Q 행위
             
            System.out.println(ans.toString());
             
        }//테케
         
         
    }//main
     
    //아래의 넣고 찾는 부분 확실하게 이해 필요함.
    //
    static void tree_add(int gn) {
         
        int index;
        index = gn + Array_size -1;  //트리구조 이해필요.
        //System.out.println("Array_size : " + tree.length + ", gn : " + gn + " , start index : " + index);
         
        while(index >= 1) {
             
             
            tree[index]++;
            index /= 2;
             
            //arraycheck
//          System.out.print("index : " + index + ", tree :");
//          for(int tt=0;tt<tree.length;tt++) {
//              System.out.print(" " + tree[tt] );
//          }
//          System.out.println("");
             
        }
         
    }
     
    static int tree_search(int qnum) {
         
        //System.out.print("index : " + index + ", tree :");
//      for(int tt=0;tt<tree.length;tt++) {
//          System.out.print(" " + tree[tt] );
//      }
        //System.out.println("");
         
         
        int index = 1;//0은 빈노드(안쓰는거), 1이root
        //System.out.println("1 qnum : " + qnum + " , index : " + index);
        while(index < Array_size) {
            tree[index]--;  //root노드부터 하나씩 미리빼면서 감.  선택된 번호 빼야되니 미리 빼고 내려감.
            //System.out.println("CIF tree[index*2]  : " + tree[index*2]  + " , qnum : " + qnum + " , index : " + index);
            if(tree[index*2] >= qnum) { //뽑아야하는 순번이 왼쪽노드에 있을경우...
                 
                index *= 2;
                //System.out.println("2 qnum : " + qnum + " , index : " + index);
            }else { //왼쪽에없으면 오른쪽에 있것지?  뽑은수가 없는 경우는 없음.....몇번째 카드니...
                //System.out.println("3 qnum : " + qnum + " , index : " + index);
                qnum -= tree[index * 2]; //왼쪽자식노드에서 누적값만큼 뺀다.
                index = index * 2 + 1; //오른쪽 자식노드로 이동
             
            }
             
        }
         
        tree[index]--; //마지막노드 도착 카드반납...위에서부터 빼와서 다시 안올라가도됨....강사님이 갈키줌...
         
        return index - Array_size + 1;
    }
     
 
}
