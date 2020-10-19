// (중상) [기출P-0055] 고양이
/*
	[문제 힌트] [기출P-0055] 고양이  ( SDS SW검정  2018.07.10 )
	고양이 문제는 다음과 같이 해결할 수 있습니다.
	본 문제는 트리 형태의 그래프에서 고양이가 있는 노드가 주어졌을 때, 
		두 마리의 고양이가 한 연결그래프에 있지 않도록 간선을 지우는 경우의 수를 구하는 문제이다.
	N이 30만이기 때문에 모든 경우의 수를 직접 계산하는 것은 불가능하고, 
		별도의 점화식을 통해 경우의 수를 구하는 방법을 생각해야 한다.
	본 문제는 그래프가 "트리 형태"라는 것이 힌트이다.
	그래프가 트리 형태이기 때문에 "간선 하나하나를 지우는 행위는 트리를 두 개의 부분 트리로 나누는 행위"이다. 
	따라서 일반 그래프처럼 "사이클이 발생해 우회경로를 고려해야 하는 변수가 존재하지 않"는다.
	입력으로 주어진 트리 형태의 그래프를 1번 노드를 루트노드로 하는 트리로 개편할 수 있다. 
	그리고 그렇게 만든 트리에서 "리프노드부터 시작하여 각 노드를 루트 노드로 하는 서브트리를 만들어" 
		"전체 문제에 대한 부분 문제의 정답을 차례대로 구해"나갈 수 있다.
	먼저 노드가 하나 있는 트리에서의 경우의 수는 1가지이다.
	다음으로 자식이 있는 경우, 
		자식과 부모를 잇는 간선을 사용하는 경우와 사용하지 않는 경우로 나눠볼 수 있다. 
	간선을 사용하지 않는 경우는 
		간단하게 자식과 부모가 완전히 독립적이게 되므로 완전곱셈의 경우의 수가 나오게 된다. 
	간선을 사용하는 경우에는 
		부모 자식에 연결된 그래프에 고양이가 있는 경우의 수와 없는 경우의 수의 관계를 고려하면 
		점화식을 구할 수 있다.
	이런 식으로 각 노드와 연결된 그래프에 고양이가 존재하는 경우와 존재하지 않는 경우로 구분하여 
		경우의 수를 구해주면 문제의 정답을 O(N)에 구할 수 있다.

제가 푼 방식을 대략 소개하자면 다음과 같습니다. 
1. 메모이제이션 정의 
   DP[i][0] : i번째 node와 i번째 node의 자식노드를 포함해 고양이가 한마리도 없는 경우의 수     
   DP[i][1] : i번째 node와 i번째 node의 자식노드를 포함해 고양이가 1마리가 있는 경우의 수 
2. 점화식 
   i번째 node에 고양이가 있는 경우와 고양이가 없는 경우로 나눌 수 있습니다. 
   i번째 node에 고양이가 있는 경우 
      DP[i][0] = 0 (이미 고양이가 있으므로 고양이가 없는 경우는 없음) 
      DP[i][1] = i의 자식노드중에 고양이가 없는 경우의 수 (이미 i번째 node에 고양이가 있으므로 i의 자식노드는 고양이가 없어야 함) 
   i번째 node에 고양이가 없는 경우 
      DP[i][0] = i의 자식노드 중에 고양이가 없는 경우의 수 
      DP[i][1] = i의 자식노드중에 고양이가 있는 자식노드 1개만 연결시킨 경우의 수(즉, 나머지 자식노드는 모두 연결되어 있지 않거나 고양이가 없는 경우만 연결)  
3. 초기화 
     i번째 node가 leaf 노드인 경우 DP[i][0]은 i번째 node에 고양이가 있으면 0, 고양이가 없으면 1 
                                             DP{i][1]은 i번째 node에 고양이가 있으면 1, 고양이가 없으면 0 

node 1번을 root라고 정의한다면  node 1을 시작으로 DFS를 통해서 위의 1~3번 과정을 계산하고 DFS가 완료된 후  
     최종정답 = DP[1][0] + DP[1][1] (root와 연결된 그래프에서 고양이가 한마리도 없는경우와 고양이가 한마리만 있는경우의 수의 합) 
이 됩니다. 
*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(300010)
#define ROOT	(1)
#define MOD		(1000000007LL)

typedef long long ll;		// 10억 * 10억이 나올 수도;;;;
int T, N;
int isCat[NMAX];
vector<int> edges[NMAX];
ll dp[NMAX][3];		// dp[i][0] : 현재의 i번째 노드에 고양이가 한 마리도 없는 경우
					// dp[i][1] : 현재의 i번째 노드에 고양이 한 마리만 있는 경우 (한 마리까지는 괜찮음!!)
					// => ROOT를 1이라고 한다면, 나중에 dp[1][0] + dp[1][1] 해주면 됨!
void input() {
	int a, b;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &isCat[i]);
		edges[i].clear();		// init
	}
	for(int i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
}

void dfs_get_dp(int node, int parent) {
	// init
	dp[node][1] = isCat[node];			// 고양이 있으면 dp[i][1] = 1 && isCat[i] = 1, 없으면 둘 다 0
	dp[node][0] = -1*(isCat[node]-1);	// 고양이 있으면 dp[i][0] = 0 && isCat[i] = 0, 없으면 둘 다 1
	
	for(int child : edges[node]) {
		if(child == parent) continue;
		dfs_get_dp(child, node);
		// ★점화식...!!!
		if(!isCat[node]) { // 이 노드에 고양이가 없다면!
			int tmp = dp[node][0];
			/*  1. < 현재 node가 고양이랑 연결되어 있지 않을 경우의 수 > : dp[node][0]
				1-1) 연결이 되어 있지 않다면,
				자식 노드가 고양이랑 연결되어 있지 않다면 ( dp[child][0] )
				연결시키든 끊어놓든 큰 상관이 없음.		  (      *2      )
				1-2)
				자식 노드가 고양이랑 연결되어 있다면	  ( dp[child][1] )
				끊어놓아야 함!							  (      *1      )
				
				1-3)
				고양이와 연결이 되어 있지 않아야 하기 때문에
				설령 이전에 자식들로 인해 dp[node][1]에 값이 있더라도 
				얘를 사용하면 고양이가 있는 것이 되어버림. 그래서 얘에 대해서는 고려 X!!!
			*/
			dp[node][0] = (dp[node][0]*(dp[child][0]*2 + dp[child][1]))%MOD;
			/*  2. < 현재 node가 고양이 단 한마리랑 연결되어 있을 경우의 수 > : dp[node][1] , dp[node][0]
				★ 현재 node에 고양이가 없다고 무조건 연결 안되겠지가 아니다!!
				   다른 자식 노드에 고양이가 있는데 이 자식과 연결되어 있다면, 고양이가 있는 것!!!!! ★
				2-1) 현재 이미 연결이 되어 있다면,
				자식 노드가 고양이랑 연결되어 있지 않다면 ( dp[child][0] )
				연결시키든 끊어놓든 큰 상관이 역시 없음	  (      *2      )
				2-2)
				자식 노드가 고양이랑 연결되어 있다면	  ( dp[child][1] )
				끊어놓아야 함!							  (      *1      )
				
				2-3) 연결이 되어 있지 않다면,
				하지만 이번 2-3)은 위의 1-3)과 다르다.
				1-3에서는 "아예 연결이 되지 않아야 함" 때문에 연결된 것을 고려해주지 않았지만,
				이번에는 하나는 연결될 수 있기 때문에
				이전 자식들로 인해 연결이 되어 있는 상태가 아니라면  ( dp[node][0] )
				이번에 연결해보는 과정이 추가된다!					 ( dp[child][1] )
			*/
			dp[node][1] = (dp[node][1]*(dp[child][0]*2 + dp[child][1]) + tmp*dp[child][1])%MOD;
            printf("%d->[%d(%s)] : %d / %d\n", child, node, isCat[node] ? "TRUE" : "FALSE", dp[node][0], dp[node][1]);
		}
		else {	// 그런데 고양이가 있으면!
			/*  1. < 현재 node가 고양이랑 연결되어 있지 않을 경우의 수 >
				이미 현재 node에 고양이가 있기 때문에
				고양이랑 연결되어 있지 않을 경우는 없다!!!
			*/
			dp[node][0] = 0LL;
			/*  2. < 현재 node에 고양이가 한 마리 연결되어 있을 경우의 수 >
				2-1) 현재 이미 연결이 되어 있다면,
				자식 노드가 고양이랑 연결되어 있지 않다면 ( dp[child][0] )
				연결시키든 끊어놓든 큰 상관이 없음		  (      *2      )
				2-2)
				자식 노드가 고양이랑 연결이 되어있다면	  ( dp[child][1] )
				연결을 끊어놓아야 함!					  (      *1      )
				
				2-3) 연결이 되어 있지 않다면,
				하지만 말이 되지 않는 것이 이 node 자체에 고양이가 있기 때문!
				그래서 자식(child)가 고양이를 가지고 있는 경우에는 절대 연결될 수 없음!
			*/
			dp[node][1] = (dp[node][1] * (dp[child][0]*2 + dp[child][1]))%MOD;
            printf("%d->[%d(%s)] : %d / %d\n", child, node, isCat[node] ? "TRUE" : "FALSE", dp[node][0], dp[node][1]);
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, (dp[ROOT][0] + dp[ROOT][1])%MOD); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		dfs_get_dp(ROOT, 0);
		output(tc);
	}
	return 0;
}
#endif


// 아카춘 코드인데, 음... 100% 이해가지는 않아서...
#if 0
#include <stdio.h>
#include <time.h>
#define NMAX 300010
typedef long long ll;
#define MOD 1000000007
int TC,N;
ll D[NMAX][3], ans;
int P[NMAX*2], T[NMAX], E[NMAX*2][2], dg[NMAX], ord[NMAX], R[NMAX];
int Q[NMAX*2];
struct Queue{
     
    int front,rear,size;
    Queue(){
        size = front = rear = 0;
    }
    void push(int a)
    {
        Q[rear++] = a;
        size++;
    }
    int pop()
    {
        int ret = Q[front++];
        size--;
        return ret;
    }
};
int main() 
{
    scanf("%d",&TC);
    for(int tc = 1; tc <= TC ; tc++)
    {
        ans = 0;
        scanf("%d",&N);
        if(N<1||N>300000) printf("Nerr[%d]\n",N);
        //printf("N[%d] ",N);
        for(int i = 1,c ; i <= N ; i++)
        {
            scanf("%d",&c);
            if(c<0||c>1) printf("Cerr[%d]\n",c);
            D[i][2] = 0;
            D[i][1] = c;
            D[i][0] = (c==0)?1:0;
            R[i] = T[i] = P[i] = -1;
            dg[i] = 0;
             
        }
        for(int i = 1 ; i < N ; i++)
        {
            scanf("%d%d",&E[i][0],&E[i][1]);
             
            if(E[i][0] < 1 || E[i][0]>N) printf("E0 err[%d]\n",E[i][0]);
            if(E[i][1] < 1 || E[i][1]>N) printf("E1 err[%d]\n",E[i][1]);
            P[i] = T[E[i][0]];T[E[i][0]] = i;
            E[i+N-1][0] = E[i][1];E[i+N-1][1] = E[i][0];
            P[i+N-1] = T[E[i+N-1][0]];T[E[i+N-1][0]] = i+N-1;
            dg[E[i][0]]++;dg[E[i][1]]++;
             
        }
        Queue que;
        for(int i = 1 ; i <= N ; i++) if(dg[i] < 2) que.push(i);
         
        int idx = 0;
        while(que.size>0)
        {
            int node = que.pop();
            ord[idx++] = node;
            dg[node]--;
            for(int i = T[node] ; i != -1 ; i = P[i])
            {
                int nnode = E[i][1];
                if(dg[nnode] > 0) 
                {
                    R[node] = nnode;
                    dg[nnode]--;
                    if(dg[nnode] == 1) que.push(nnode);
                    break;
                }
            }
        }
         
        for(int i = 0,pnode,node ; i < N-1 ; i++)
        {
            node = ord[i];
            pnode = R[node];
            ll sum = 0;
            for(int j = 0 ; j < 3 ; j++) sum = (sum+D[node][j])%MOD;
            D[pnode][1] = ((D[pnode][1]*sum)%MOD + (D[pnode][1]*D[node][0])%MOD + (D[pnode][0]*D[node][1])%MOD)%MOD;
            D[pnode][0] = ((D[pnode][0]*sum)%MOD + (D[pnode][0]*D[node][0])%MOD)%MOD;
        }
        ans = 0;
        for(int i = 0 ; i < 2 ; i++) ans = (ans+D[ord[N-1]][i])%MOD;
        printf("#%d %lld\n",tc,ans);
    }
    //printf("[%.3lf]",(double)clock()/CLOCKS_PER_SEC);
}
#endif