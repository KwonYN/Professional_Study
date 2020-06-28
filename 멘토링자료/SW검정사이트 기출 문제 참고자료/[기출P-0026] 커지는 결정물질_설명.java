import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;
 
public class Solution {
    public static void main(String[] args) throws Exception{
        //System.setIn(new FileInputStream("MaterialEvaporation_input.txt"));
         
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         
        int T = Integer.parseInt(br.readLine());
         
        for(int test_case = 1;test_case<=T; test_case++){
            int N = Integer.parseInt(br.readLine());
             
            Material[] input = new Material[N];             // Material 객체 입력 데이터 저장
                         
            Material last_Material = new Material();
             
            /*
             * 1. 입력 데이터(Material 정보) 저장
             */
            for(int i=0;i<N;i++){
                StringTokenizer st = new StringTokenizer(br.readLine());
                 
                Material m = new Material();
                m.no = i+1;
                m.x = Integer.parseInt(st.nextToken())*2;
                m.y = Integer.parseInt(st.nextToken())*2;
                m.size = Integer.parseInt(st.nextToken());
                m.speed = Integer.parseInt(st.nextToken())*2;
                m.density = Integer.parseInt(st.nextToken());
                m.delSec = Double.MAX_VALUE;
                 
                input[i] = m;
                //inputList.add(m);
                 
                if(i==0 || last_Material.density < m.density){
                    last_Material = m;
                }
            }
             
            Arrays.sort(input, new Comparator<Material>() {
                public int compare(Material o1, Material o2) {
                    if(o1.density <o2.density){
                        return 1;
                    } else{
                        return -1;
                    }
                }
            });
             
            /*for(int i=0;i<input.length;i++){
                System.out.print(input[i].no + ", ");
            }
            System.out.println();*/
             
             
            for(int i=1; i<input.length;i++){
                 
                double minSec = Double.MAX_VALUE;
                for(int j=0;j<i;j++){
                    double sizeSum = input[i].size+input[j].size;
                    double speedSum = input[i].speed + input[j].speed;
                     
                    double nowSec;
                     
                    // 부동소수점 연산 오류 방지를 위해 MAX 값인 1,000,000,000을 곱해줌
                    double secX = (Math.abs(input[i].x - input[j].x)-sizeSum) * 1000000000 / speedSum;
                    double secY = (Math.abs(input[i].y - input[j].y)-sizeSum) * 1000000000 / speedSum;
                     
                    if(input[i].x==input[j].x){
                        nowSec = secY;
                    } else if(input[i].y == input[j].y){
                        nowSec = secX;
                    } else {
                        nowSec = Math.max(secX, secY);
                    }
                     
                    if(nowSec < minSec && nowSec <= input[j].delSec){
                        minSec = nowSec;
                    }
                }
                 
                input[i].delSec = minSec;
            }
             
        /*  for(int i=0;i<input.length;i++){
                System.out.print(input[i].delSec + ", ");
            }
            System.out.println();*/
             
            Arrays.sort(input, new Comparator<Material>() {
                public int compare(Material o1, Material o2) {
                    if(o1.delSec <o2.delSec){
                        return -1;
                    } else if(o1.delSec > o2.delSec){
                        return 1;
                    } else {
                        if(o1.density < o2.density){
                            return -1;
                        } else {
                            return 1;
                        }
                    }
                }
            });
             
             
            StringBuffer sb = new StringBuffer();
            sb.append("#" + test_case);
             
            for(int i=0; i<input.length;i++){
                sb.append(" " + input[i].no);
            }
             
 
            System.out.println(sb.toString());
             
             
        }
         
        br.close();
    }
}
 
class Material{
    public int no;          // 객체별 번호
    public double x;            // X 좌표
    public double y;            // Y 좌표
    public double size;     // 초기 크기
    public double speed;        // 속도
    public double density;  // 밀도
    public double delSec;       // 충돌 시간
}
