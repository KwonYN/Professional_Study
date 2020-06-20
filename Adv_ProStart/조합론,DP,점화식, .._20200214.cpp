/************************/
/* [ 2020.02.14 day 5 ] */
/************************/

// (중) [교육A-0005] 조합 
// DP활용하여 조합(n C k)를 충족하는 배열 만들기!! (10억7로 나눈 나머지 저장)
#if 01
#define NMAX	5000
#define MOD		1000000007

#include <cstdio>

int Q, N, K;
int comb[NMAX+2][NMAX+2];

void make_combination()
{
	comb[1][0] = comb[1][1] = 1;
	for (int i = 2; i <= NMAX; i++)
	{
		for (int j = 1; j < i; j++)
		{
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j])%MOD;
		}
		comb[i][0] = comb[i][i] = 1;
	}
}

int main()
{
	make_combination();
	scanf("%d", &Q);
	for (int q = 1; q <= Q; q++)
	{
		scanf("%d %d", &N, &K);
		printf("#%d %d\n", q, comb[N][K]);
	}

	return 0;
}

#endif


//(중) [연습A-0033] 제품의 일련번호 1 
#if 01
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAX	3500000

int T, N;
string l, r;
int nl, nr;
int s, e;
char start = 'a';
int step;
char alpha[15];
int list[MAX];
int chk[15];
int cnt;

void make_string(int d)
{
	int idx;
	if (d >= N) return;
	for (int i = 0; i < N; i++)
	{
		if (chk[i]) continue;
		chk[i] = 1;
		idx = (int)(cnt++ / N);
		list[idx] += ((int)alpha[i] * (int)pow(10, d));
		make_string(d + 1);
		chk[i] = 0;
	}
}

void print_list()
{
	int idx = int(cnt / N);
	printf("print_list\n");
	for (int i = 0; i < idx; i++) printf("%d ", list[i]);
	printf("\n");
}

int main()
{
	ios::sync_with_stdio(false);
	
	for (int i = 0; i < 10; i++) alpha[i] = 'a' - i;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		cin >> l;
		cin >> r;
		nl = nr = 0;
		for (int i = N - 1; i >= 0; i--)
		{
			nl = nl + ((int)l[i] * (int)pow(10, N - i - 1));
			nr = nr + ((int)r[i] * (int)pow(10, N - i - 1));
		}
		cnt = 0;
		make_string(0);
		sort(list, list + (cnt/N));
		for (int i = 0; i < cnt / N; i++)
		{
			if (list[i] == nl) s = i;
			if (list[i] == nr) e = i;
		}
		step = e - s - 1;
		print_list();
		if (step < 0) step = 0;
		cout << "#" << tc << " " << step << endl;
	}
	return 0;
}

#endif

// Re
#if 01
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int T, N;
string l, r;
int fac[15];
int change2[130];
int ans;

int get_order(string str)
{
	int order = 0;
	int n = N;
	char change1[15];
	for (int j = 0; j < N; j++) change1[j] = 'a' + j;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (str[i] == change1[j])
			{
				//printf("i = %d, j = %d\n", i, j);
				order += j * fac[N - i - 1];
				//printf("order = %d\n", order);
				for (int k = j + 1; k < n; k++) change1[k - 1] = change1[k];
				n--;
				break;
			}
		}
	}
	//printf("===========\n");
	return order;
}

int main()
{
	ios::sync_with_stdio(false);
	int a, b;

	int num = 1;
	for (int i = 1; i < 10; i++)
	{
		num *= i;
		fac[i] = num;
	}
	for (int i = 'a'; i < 'j'; i++) change2[i] = i - 'a' + 1;

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		cin >> l;
		cin >> r;
		a = get_order(r);
		b = get_order(l);
		ans = abs(a-b) - 1;
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}

#endif




// [기출P-0006] 아름다운 비트문자열 
#if 01

#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define NMAX	(1000)
#define INF		(1ll<<60)

int T, N, K;
long long X;
long long comb[NMAX + 2][NMAX + 2];
int chk[1000];

void make_combination()
{
	comb[0][0] = 1;
	for (int i = 1; i <= NMAX; i++)	// 행 : 자릿수
	{
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; j++)	// 열 : 1의 개수
		{
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
			if (comb[i][j] > INF) comb[i][j] = INF + 1; // 주어지는 최대 순서 : 1<<60
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	//freopen("in.txt", "r", stdin);
	make_combination();
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> K >> X;
		cout << "#" << tc << " ";
		for (int i = 1; i <= N; i++)
		{
			if (comb[N - i][K] < X)
			{
				cout << "1";
				X -= comb[N - i][K--];
			}
			else cout << "0";
		}
		cout << endl;
	}

	return 0;
}

#endif




// [기출A-0028] 제품의 일련번호 2 
#if 01

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int T, N;
string l, r;
long long fac[20];

void make_factorial(int n)
{
	fac[1] = 1;
	for (int i = 2; i < n; i++) fac[i] = i * fac[i - 1];
}

long long get_order(string str)
{
	long long order = 0;
	int n = N;
	char change1[20];
	for (int j = 0; j < N; j++) change1[j] = 'a' + j;

	for (int i = 0; i < N; i++)
	{
		for(int j = 0; j < change1[i])
		for (int j = 0; j < n; j++)
		{
			if (str[i] == change1[j])
			{
				//printf("i = %d, j = %d\n", i, j);
				order += j * fac[N - i - 1];
				//printf("order = %d\n", order);
				for (int k = j + 1; k < n; k++) change1[k - 1] = change1[k];
				n--;
				break;
			}
		}
	}
	//printf("===========\n");
	return order;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	long long a, b;

	make_factorial(18);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> l >> r;
		a = get_order(r);		b = get_order(l);
		cout << "#" << tc << " " << (abs(a - b) - 1) << endl;
	}

	return 0;
}

#endif
// 참고할 것!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
#include <iostream>
#include <cstring>

using namespace std;

long long  factorial[18] = { 1, };
bool check_a[18], check_b[18];

void fill_factorial() {
	for (int i = 1; i < 18; i++)
		factorial[i] = factorial[i - 1] * i;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	fill_factorial();
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(check_a, false, sizeof(check_a));
		memset(check_b, false, sizeof(check_b));
		int N;
		char a[18], b[18];
		cin >> N >> a >> b;

		long long a_num = 0, b_num = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < a[i] - 'a'; j++) {
				if (!check_a[j])
					a_num += factorial[N - i - 1];
			}
			check_a[a[i] - 'a'] = true;

			for (int j = 0; j < b[i] - 'a'; j++) {
				if (!check_b[j])
					b_num += factorial[N - i - 1];
			}
			check_b[b[i] - 'a'] = true;
		}

		long long ans = (a_num < b_num) ? b_num - a_num - 1 : a_num - b_num - 1;
		cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}

*/

/*
#include <stdio.h>
int T,N;
char S[20],E[20];
long long fac[19];
long long getSN(char str[])
{
	long long ret = 0;
	int used[20];
	for(int i=0;i<N;i++) used[i]=1;
	for(int i=0;i<N;i++)
	{
		int prev_cnt=0;
		int digit = str[i]-'a';
		for(int j=0;j<digit;j++)
			prev_cnt += used[j];
		ret += fac[N-i-1]*prev_cnt;
		used[digit]=0;
	}
	return ret;
}
long long abs(long long a){return (a<0)?-a:a;}
int main()
{
	fac[0]=1;
	for(int i=1;i<=18;i++) fac[i] = fac[i-1]*i;
	scanf("%d",&T);
	for(int tc=1;tc<=T;tc++)
	{
		scanf("%d%s%s",&N,S,E);
		printf("#%d %lld\n",tc,abs(getSN(E)-getSN(S))-1);
	}
}

*/



// (중) [연습A-0031] 최대 힙 : 손 못 댐..
// + DP의 개념까지!! <- 점화식을 통해!! (규칙 찾기!)
// ( (2^높이)-2 ) C ( 2^(H-1==N)-1 ) * DP[H-1] * DP[H-1]
#if 01

#include <cstdio>
#define MOD		(100000123)

typedef long long ll;

int T, N;
int n[15];
int input_no;
ll heap_case[1<<12][1<<12];
ll D[15];

void print_n() { for (int i = 1; i <= 11; i++) printf("%d ", n[i]); }

void make_heap_case()
{
	heap_case[0][0] = 1ll;
	for (int i = 1; i < 1 << 12; i++) // 파스칼 삼각형
	{
		heap_case[i][0] = 1ll;
		for (int j = 1; j <= i; j++)
		{
			heap_case[i][j] = (heap_case[i - 1][j - 1] + heap_case[i - 1][j]) % MOD;
		}
	}

	D[0] = 1;		D[1] = 2;
	for (int i = 2; i < 12; i++)	// 각 N에 대한 답을 기록 및 저장해놓는 배열
	{
		int cnt = (1 << (i + 1)) - 2;
		// 점화식...;
		D[i] = ((( heap_case[cnt][cnt / 2] * D[i - 1] ) % MOD) * D[i - 1]) % MOD;
	}
}

int main()
{
	int num = 1;
	n[1] = 1;
	for (int i = 1; i <= 11; i++)
	{
		num *= 2;
		n[i] += num + n[i-1];
	}
	//print_n();
	make_heap_case();
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		printf("#%d %lld\n", tc, D[N]);
	}
	return 0;
}

#endif

// 최대힙 참고 (참고로 이거 24/25임...;; Need to ReTry)
#if 01

#include <cstdio>
#define MAX(a, b)	( ( (a) > (b) ) ? (a) : (b) )

int T, N, z;
int arr[10010];
int max_lv;
int lv_list[15] = { 0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 10000 };
int lv, loc;

void input()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
	for (int i = 1; i < 15; i++)
	{
		if (lv_list[i - 1] < N && lv_list[i] <= N)
		{
			max_lv = i;
			break;
		}
	}
}

void print_arr()
{
	printf("print_arr\n");
	for (int i = 1; i <= N; i++) printf("%d ", arr[i]);
	printf("\n");
}

void operation()
{
	int l, r, tmp;
	arr[N] = -(1 << 30);
	arr[1] = arr[N--];
	z = 1;
	lv = 0;

	int i = 1;
	while (i < N)
	{
		l = i * 2, r = i * 2 + 1;
		if (l > N) break;
		if (arr[i] > MAX(arr[l], arr[r])) break;
		else if (arr[i] < arr[l] && arr[l] > arr[r])
		{
			tmp = arr[i];
			arr[i] = arr[l];
			arr[l] = tmp;
			i = z = l;
		}
		else if (arr[i] < arr[r] && arr[r] > arr[l])
		{
			tmp = arr[i];
			arr[i] = arr[r];
			arr[r] = tmp;
			i = z = r;
		}
		lv++;
	}
	loc = z - lv_list[lv];
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		operation();
		printf("#%d %d %d\n", tc, lv, loc);
	}
	return 0;
}

#endif




// (중상) [기출P-0053] 공주의 결혼식 
#if 01

#include <cstdio>
#define MAX	(1000)

int T, W, B;
double wedding[MAX+2][MAX+2];

void cele_wedding(int w, int b)
{
	wedding[w][b] = 1.0;
}

void init(int w, int b) { for (int i = 0; i <= w; i++) for (int j = 0; j <= b; j++) wedding[i][j] = 0; }

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &W, &B);
		cele_wedding(W, B);
		printf("#%d %f %f %f\n", tc, wedding[1][0], wedding[0][1], wedding[0][0]);
		init(W, B);
	}

	return 0;
}
#endif
/*
#include <iostream>
using namespace std;
double P[1002][1002][3], T;
int main() {
	P[0][0][0] = 0;    P[0][0][1] = 0;    P[0][0][2] = 1;
	P[0][1][0] = 0;    P[0][1][1] = 1;    P[0][1][2] = 0;
	P[1][0][0] = 1;    P[1][0][1] = 0;    P[1][0][2] = 0;
	P[1][1][0] = 0; P[1][1][1] = 0; P[1][1][2] = 1;
	for (int i = 0; i <= 1000; i++) {
		P[i][0][0] = 1, P[i][0][1] = 0, P[i][0][2] = 0, \
			P[0][i][0] = 0, P[0][i][1] = 1, P[0][i][2] = 0;
	}
	for (int i = 2; i <= 1000; i++) {
		for (int j = 0; j < 3; j++) {
			P[1][i][j] = (double)(i - 1) / (1 + i)*P[1][i - 1][j] + (double)2 * i / (1 + i) / i * P[0][i - 1][j];
			P[i][1][j] = (double)(i - 1) / (1 + i)*P[i - 1][1][j] + (double)2 * i / (1 + i) / i * P[i - 1][0][j];
		}
	}
	for (int i = 2; i <= 1000; i++) {
		for (int j = 2; j <= 1000; j++) {
			for (int k = 0; k < 3; k++) {
				P[i][j][k] = (double)i*(i - 1) / (i + j) / (i + j - 1)*P[i - 1][j][k] + \
					(double)j*(j - 1) / (i + j) / (i + j - 1)*P[i][j - 1][k] + \
					(double)2 * i*j / (i + j) / (i + j - 1)*P[i - 1][j - 1][k];
			}
		}
	}
	cout << fixed;
	cout.precision(8);
	cin >> T;
	for (int t = 0; t < T; t++) {
		int a, b;
		cin >> a >> b;
		cout << "#" << t + 1 << ' ' << P[a][b][0] << ' ' << P[a][b][1] << ' ' << P[a][b][2] << '\n';
	}
}
*/




// [기출P - 0011] 그림책
#if 01

#include <cstdio>

int main()
{

	return 0;
}

#endif



//
#if 0

#include <cstdio>

int main()
{

	return 0;
}

#endif
