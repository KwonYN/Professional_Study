//#include "day2.h"
//
//
//
//day2::day2()
//{
//}
//
//
//day2::~day2()
//{
//}



//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(diable: 4996)

//#include <iostream>
//using namespace std;

#include <cstdio>

// (중상) [교육P-0013] 나무 
#if 0
#include <cstdio>

#define MAX	100010

int T, n, m;
int tree[MAX];
int Li[MAX], Ri[MAX];
int gugan[MAX];
int beauty_max;

void input()
{
	int l, r;

	scanf("%d %d", &n, &m);
	printf("n = %d, m = %d\n", n, m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &l, &r);
		printf("l = %d, r = %d\n", l, r);
		for (int j = l; j <= r; j++) gugan[j]++;
	}
}

void print_tree()
{
	printf("print_tree\n");
	for (int i = 1; i <= n; i++) printf("%d ", gugan[i]);
	printf("\n");
}

void init()
{
	for (int i = 0; i <= n; i++) gugan[i] = 0;
}
int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	printf("T = %d\n", T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		print_tree();
		printf("#%d\n%d\n", tc, beauty_max);
		for (int i = 1; i <= n; i++) printf("%d ", tree[i]);
		printf("\n");
		init();
	}

	return 0;
}

#endif



// (중상) [교육P-0016] 동굴 
/*
2
6 6
3
3
3
3
3
3
14 5
1
3
4
2
2
4
3
4
3
3
3
2
3
3
*/
// re
# if 0

#include <cstdio>

int T, N, H;
int pole[200010];
int h1[500010], h2[500010];
int result[500010];
int min_result, cnt;

void input()
{
	min_result = 987654321, cnt = 0;
	scanf("%d %d", &N, &H);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &pole[i]);
		//scanf("%d", &num);
		//if (i & 1) pole[i] = num; // 석순
		//else pole[i] = H - num + 1; // 종유석
	}
}

void operation()
{
	int max1 = 0, max2 = 0;
	int res1 = 0, res2 = 0;
	for (int i = 1; i <= N; i += 2)
	{
		if (pole[i] > max1) max1 = pole[i];
		h1[pole[i]]++;
	}
	//result[max1] = res1 = h1[max1];
	for (int i = max1; i >= 1; i--)
	{
		res1 += h1[i];
		result[i] += res1;
	}

	for (int i = 2; i <= N; i += 2)
	{
		if (pole[i] > max2) max2 = pole[i];
		h2[pole[i]]++;
	}
	/*result[H - max2 + 1] += h2[max2];
	res2 = h2[max2];*/
	for (int i = max2; i >= 1; i--)
	{
		res2 += h2[i];
		result[H - i + 1] += res2;
	}
}

void get_ans(void)
{
	for (int i = 1; i <= H; i++) if (min_result > result[i]) min_result = result[i];
	for (int i = 1; i <= H; i++) if (result[i] == min_result) cnt++;
}

void init()
{
	for (int i = 0; i <= H; i++) h1[i] = h2[i] = result[i] = 0;
}

void print_result()
{
	printf("print_result\n");
	for (int i = 1; i <= H; i++) printf("%d ", result[i]);
	printf("\n");
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		operation();
		get_ans();
		//print_result();
		printf("#%d %d %d\n", tc, min_result, cnt);
		init();
	}

	return 0;
}

#endif




// (중) [연습A-0026] 지은이가 지은 집 
#if 0
#define TOP 10000000

#include <cstdio>
#include <algorithm>

int T, X, N;
int chk1[TOP+10];
int chk2[TOP+10];
int tool[TOP+10];
char *result[2] = { "yes", "danger" };
int flag;
int max_num;
int L1, L2;

void input()
{
	int num;

	max_num = 0;
	flag = 1;
	L1 = L2 = 0;
	scanf("%d", &X);
	X *= TOP;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &num);// &tool[i]);
		chk1[num]++; // 주어진 수
		if(X > num && X - num <= TOP) chk2[X - num]++; // 주어질 것으로 기대되는 수
		if (max_num < num) max_num = num;

		if (X - num >= 0 && X - num <= TOP && chk2[X - num])
		{
			tool[num]++;
			tool[X - num]++;
		}
	}
}

void operation()
{
	for (int i = 1; ; i++)
	{
		if (tool[i])
		{
			L1 = i;	L2 = X - i;
			flag = 0;
			//printf("i = %d\n", i);
			//printf("tool[i] = %d\n", tool[i]);
			return;
		}
	}
}

void init()
{
	for (int i = 0; i <= max_num; i++) chk1[i] = chk2[i] = tool[i] = 0;
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		operation();
		//printf("L1 = %d, L2 = %d\n", L1, L2);
		printf("#%d %s %d %d\n", tc, result[flag], L1, L2);
		init();
	}

	return 0;
}

#endif

// re
#if 0
#define TOP 10000000

#include <cstdio>
#include <algorithm>
using namespace std;

int T, X, N;
int chk[1000000 + 10];
char *result[2] = { "yes", "danger" };
int flag;
int max_num;
int L1, L2;

void input()
{
	max_num = 0;
	flag = 1;
	L1 = L2 = 0;
	scanf("%d", &X);
	X *= TOP;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &chk[i]);
		if (X >= chk[i]) max_num = chk[i];
	}
	sort(chk + 0, chk + N);
}

void operation()
{
	for (int i = 0; i < N; i++)
	{
		L1 = chk[i], L2 = X - chk[i];
		if (L2 > max_num) continue;
		for (int j = N - 1; j > i; j--)
		{
			if (chk[j] == L2)
			{
				flag = 0;
				break;
			}
			else if (chk[j] < L2) break;
		}
		if (!flag) break;
	}
}

void init()
{
	for (int i = 0; i < N; i++) chk[i] = 0;
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		operation();
		printf("#%d %s ", tc, result[flag]);
		if(!flag) printf("%d %d", L1, L2);
		printf("\n");
		init();
	}
}

#endif



// (중상) [교육P-0020] 달리기 
#if 0

int T, N;
int A[100010];
int B[100010];
long long cnt;

void input()
{
	cnt = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
}

void merge_sort(int s, int e)
{
	int l, r, tmp;
	int m = (s + e) / 2;

	if (s >= e) return;

	merge_sort(s, m);
	merge_sort(m + 1, e);

	l = s, r = m + 1, tmp = s;
	while (l <= m || r <= e)
	{
		/*if (A[l] >= A[r]) B[tmp++] = A[l++];
		else
		{
			B[tmp++] = A[r++];
			cnt += m - l + 1;
		}*/
		if ( (r > e) || ( (l <= m) && (A[l] >= A[r]) ) ) B[tmp++] = A[l++];
		else
		{
			B[tmp++] = A[r++];
			cnt += m - l + 1;
		}
	}
	for (int i = s; i <= e; i++) A[i] = B[i];
	//while (l <= m) B[tmp++] = A[l++];
	//while (r <= e) B[tmp++] = A[r++];
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		merge_sort(1, N);

		printf("#%d %lld\n", tc, cnt);
	}

	return 0;
}

#endif



// (중) [연습A-0001] 카드선택 
#if 01
#include <cstdio>
#define MAX	150000

int T, N, K; // N개의 카드 - 각 카드에 모두 다른 정수, 몇 개 골라 정수 K가 되는 경우 몇 가지?
// 5 <= N <= 34
// -10억 <= 각 카드에 젹혀있는 값 <= 10억
// -10억 <= K <= 10억
// 카드 하나도 고르지 않는 경우도,,, 카드 고르는 순서 상관 없음
int cnt;
int cardl[20], cardr[20];
int l, r;
int ll, rr;
long long listl[MAX], listr[MAX];

void input()
{
	int num;

	l = r = 0;
	ll = rr = 0;
	scanf("%d %d", &N, &K);
	int m = N / 2;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &num);
		cardl[++l] = num;
	}
	for (int i = m + 1; i <= N; i++)
	{
		scanf("%d", &num);
		cardr[++r] = num;
	}
	printf("l\n");
	for (int i = 1; i <= N / 2; i++) printf("%d ", cardl[i]);
	printf("\n");
	printf("r\n");
	for (int i = N / 2 + 1; i <= N; i++) printf("%d ", cardr[i]);
	printf("\n");
}

void make_combl(int L, int s, long long sum)
{
	if (L >= l)
	{
		return;
	}

	for (int i = s; i <= l; i++)
	{
		listl[++ll] = sum + cardl[i];
		make_combl(L + 1, i + 1, listl[ll]);
	}
}

void make_combr(int L, int s, long long sum)
{
	if (L >= r)
	{
		return;
	}

	for (int i = s; i <= r; i++)
	{
		listr[++rr] = sum + cardr[i];
		make_combl(L + 1, i + 1, listr[rr]);
	}
}

void print_list()
{
	printf("<print_list>\n");
	printf("listsl\n");
	for (int i = 1; i <= ll; i++) printf("%lld ", listl[i]);
	printf("\n");
	printf("listr\n");
	for (int i = 1; i <= rr; i++) printf("%lld ", listr[i]);
	printf("\n");
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		make_combl(0, 1, 0);
		make_combr(0, 1, 0);
		print_list();
		printf("#%d %d\n", tc, cnt);
	}

	return 0;
}

#endif
