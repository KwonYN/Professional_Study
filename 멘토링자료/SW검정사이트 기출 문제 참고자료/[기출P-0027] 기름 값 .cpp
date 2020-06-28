#include <cstdio>
#define MAX_N 2000
#define MAX_L 50
#define INF 2000000000
 
int cache[MAX_N+1][MAX_L+1];
 
int min(const int&a, const int&b) {return (a<b) ? a:b;}
 
int main(){
    int TC, iCase, N, L, i, j;
    int cost, dist;
    bool flag;
     
    scanf("%d", &TC);
     
    for(iCase =1; iCase <=TC; ++iCase){
        scanf("%d %d %d", &N, &L, &cost);
        flag = true;
        for(j=1; j<=L; ++j) cache[0][j] = cache[0][j-1] + cost;
        for(i=1; i<N; ++i){
            scanf("%d %d", &dist, &cost);
            if(L < dist) flag= false;
            if(!flag) continue;
            cache[i][0] = cache[i-1][dist];
            for(j=1; j<=L; ++j){
                if(j+dist>L) cache[i][j] = INF;
                else cache[i][j] = cache[i-1][j+dist];
                cache[i][j] = min(cache[i][j], cache[i][j-1]+cost);
            }
        }
        if(flag) cost = cache[N-1][0];
        else cost= -1;
        printf("#%d %d\n", iCase, cost);
    }
    return 0;
     
     
     
}
