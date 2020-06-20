/************************/
/* [ 2020.02.13 day 4 ] */
/************************/

// 기약분수 나타내기!
#if 01

#include <cstdio>

int a, b;

void input()
{
	scanf("%d %d", &a, &b);
}

int gcd(int a, int b)
{
	if (b == 0) return a;
	else return gcd(b, a%b);
}

//int gcd_while(int a, int b)
//{
//	int A = a, B = b, r;
//	while (b)
//	{
//		r = A % B;
//		A = B;
//		B = r;
//	}
//	return A;
//}

int main()
{
	input();
	printf("%d와 %d의 최대공약수는? : %d\n", a, b, gcd(a, b));

	return 0;
}

#endif
// 최대공약수 이 함수는 최대 100번까지 돈다고 함!!
// 시간 크게 생각하지 않고 사용해도 된다고 하네!!
/*
int gcd(int a, int b)
{ 
	if (b == 0) return a;
	else return gcd(b, a%b);
}
*/



// (중) [교육A-0004] 금괴 
#if 01

#include <cstdio>

int T;
int M, N; // M명의 친구, N개의 금괴 -> 정확히 같은 크기로 나누자! (N/M개씩)
int min_cost;

int gcd(int a, int b)
{
	if (b == 0) return a;
	else return gcd(b, a%b);
}

//bool check(int ni, int m)
//{
//	if ( gcd(ni, m) != m ) return true;
//	return false;
//}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		min_cost = 0;
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= M; i++) if (gcd(N*i, M) != M) min_cost++;

		printf("#%d %d\n", tc, min_cost);
	}

	return 0;
}

#endif




// (중상) [교육P-0005] 확장 유클리드 호제법 - 호클리드 유제법
#if 01

#include <cstdio>

int gcd(int a, int b)
{
	if (b == 0) return a;
	else return gcd(b, a%b);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int x, y, z, g;
		int flag = 0;
		int s1 = 1, t1 = 0, r1;
		int s2 = 0, t2 = 1, r2, q2;
		int tmp;
		scanf("%d %d %d", &x, &y, &z);
		tmp = gcd(x, y);
		g = gcd(tmp, z);
		if (g != tmp)
		{
			printf("#%d %d\n", tc, -1);
			continue;
		}
		x /= g, y /= g, z /= g;
		r1 = x, r2 = y;
		while (r2 != 1)
		{
			tmp = r2;
			q2 = r1 / r2;
			r2 = r1 % r2; r1 = tmp;
			tmp = s2;
			s2 = s1 - s2 * q2;	s1 = tmp;
			tmp = t2;
			t2 = t1 - t2 * q2;	t1 = tmp;
			if (r2 == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0 && z > r2)
		{
			r2 = z / r2;
			s2 *= r2;
			t2 *= r2;
		}
		printf("#%d ", tc);
		if (flag) printf("%d\n", -1);
		else printf("%d %d\n", s2, t2);
	}
	return 0;
}

#endif




// (중) [연습A-0022] 소수경로 : 에라토스테네스의 체 + 오랜만에 BFS
#if 01

#include <cstdio>
#define MAX	10000

int eratos[MAX+10];
int quu[MAX*20];
int wp, rp;
int sosu[1500];
int sosu_cnt;

//void print_eratos()
//{
//	for (int i = 1; i <= 100; i++) printf("%d ", eratos[i]);
//}

bool get_diff_digit(int a, int b)
{
	//printf("a = %d, b = %d\n", a, b);
	int digit = 0;

	for (int i = 0; i < 4; i++)
	{
		if ( (a % 10) != (b % 10) ) digit++;
		a /= 10, b /= 10;
	}
	//printf("digit = %d\n", digit);
	if (digit == 1) return true;
	return false;
}

int get_step(int s, int e)
{
	int visited[MAX + 10] = {0, };

	wp = rp = 0;
	quu[wp++] = s;
	visited[s] = 1;

	while (wp > rp)
	{
		s = quu[rp++];
		if (s == e) break;
		for (int i = 1; i <= sosu_cnt; i++)
		{
			if (!visited[sosu[i]])
			{
				if (get_diff_digit(sosu[i], s))
				{
					quu[wp++] = sosu[i];
					visited[sosu[i]] = visited[s] + 1;
				}
			}
		}
	}
	return visited[s] - 1;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int T, A, B;
	sosu_cnt = 0;
	eratos[0] = eratos[1] = 1;

	scanf("%d", &T);
	for (int i = 2; i < MAX; i++) // eratos 배열에 0인 값이 바로 소수!
	{
		if ( eratos[i] ) continue;
		if(i >= 1000) sosu[++sosu_cnt] = i;
		for (int j = 2*i; j < MAX; j += i) eratos[j]++;
	}
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &A, &B);
		printf("#%d %d\n", tc, get_step(A, B));
	}
	//print_eratos();

	return 0;
}


#endif




// (중상) [교육P-0015] 파이합 
#if 01

#include <cstdio>
#define MAX	1000000

int T, L, R;
int pi[MAX + 10];
long long int pi_sum[MAX + 10];

int main()
{
	pi_sum[1] = 1;
	for (int i = 1; i <= MAX; i++) pi[i] = i;
	for (int i = 2; i <= MAX; i++)
	{
		if (i == pi[i])
		{
			for (int j = i; j <= MAX; j += i) pi[j] = pi[j] - pi[j] / i;
		}
		pi_sum[i] = pi_sum[i - 1] + pi[i];
	}
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &L, &R);
		printf("#%d %lld\n", tc, pi_sum[R] - pi_sum[L-1]);
	}
	return 0;
}

#endif




// (중상) [교육P-0034] 당황한 암호학자 
#if 01

#include <cstdio>
#include <string>
using namespace std;
#define MAX	1000000

int T, L, p;
string K;
int flag;
char *result[2] = { "GOOD", "BAD" };
int sosu[MAX];
int sosu_cnt;
int isPrime[MAX];

int main()
{
	//freopen("in.txt", "r", stdin);
	for (int i = 1; i <= MAX; i++) isPrime[i] = 1;
	sosu_cnt = isPrime[0] = isPrime[1] = 1;
	for (int i = 2; i <= MAX; i++)	 // eratos 배열에 0인 값이 바로 소수!
	{
		if (isPrime[i] == 1)
		{
			for (int j = 2 * i; j <= MAX; j += i) isPrime[j] = 0;
			sosu[++sosu_cnt] = i;
		}
	}
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%s", K);
		scanf("%d", &L);
		printf("K = %s, L = %d\n", K, L);
		flag = 0;	p = L + 1;

		// K에 대해서 어떻게 나눠주나??
		// 가장 큰 자리수부터 한 자리씩 꺼내가면서 L로 모듈려서 해줌!! 그러면서 끝까지!
		// 그럼 나눠 떨어지는지 결국에는 볼 수 있음.
		// (L보다 이하의 소수에 대해서 다!)

		printf("#%d %s", tc, result[flag]);
		if (flag) printf(" %d", p);
		printf("\n");
	}

	return 0;
}

#endif
