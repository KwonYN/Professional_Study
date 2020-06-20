#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	1000000
#define MMAX	10000

// N : 수의 개수, M : 수의 변경 횟수, K 구간의 합 구하는 횟수
int N, M, K;
long long int tree[NMAX*4];
int maldan;

void input()
{
	register int i;
	scanf("%d %d %d", &N, &M, &K);
	for(maldan = 1; maldan < N; maldan *= 2);
	for(i = 1; i < maldan<<1; i++) tree[i] = 0;
	for(i = 1; i <= N; i++) scanf("%lld", &tree[i+maldan-1]);
	for(i = maldan - 1; i >= 1; i--)
		tree[i] = tree[i<<1] + tree[(i<<1)|1];
}

void update(int idx, int new_val)
{
	idx = idx + maldan - 1;
	tree[idx] = new_val;
	while(idx > 1)
	{
		idx >>= 1;
		tree[idx] = tree[idx<<1] + tree[(idx<<1)|1];
	}
}

long long int search_sum(int s, int e)
{
	long long int ret = 0;
	s = s + maldan - 1;
	e = e + maldan - 1;
	while(s <= e)
	{
		if(s&1) ret += tree[s++];	// 왼쪽 자식: 홀수가 다른 부모
		if(!(e&1)) ret += tree[e--];	// 오른쪽 자식: 짝수가 다른 부모
		s >>= 1;	e >>= 1;
	}
	return ret;
}

void operation()
{
	register int i;
	int a, b, c;		
	for(i = 1; i <= M+K; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		if(a==1) update(b, c);
		else printf("%lld\n", search_sum(b, c));
	}
}

int main()
{
	input();
	operation();

	return 0;
}
