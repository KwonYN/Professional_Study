// 통과된 코드
// : AB, CD 배열을 long long으로 잡아줘서 바로 통과...
// 게다가 typedef long long ll; 로 선언을 해줬으면서, get_cnt 함수 내에서 long long ll;이라는 변수를 선언해주는 바람에.. 밑 밑에 코드 통과 못했었음 ㅠㅠ

// BOJ_7453_합이 0인 네 정수
/*
	=> 배열의 크기 n : 1 ~ 4000
	   4000 ^ 4는 1600만^2... 너무 크다 ( 시간 복잠도 O(N^4) )
*/

#include <iostream>
#include <algorithm>
using namespace std;
#define MAX	(4010)

int n;
int A[MAX], B[MAX], C[MAX], D[MAX];
int AB[MAX*MAX], CD[MAX*MAX];
long long total_cnt;
int idx;

void input()
{
	cin >> n;
	for(int i = 0; i < n; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];
}

void print_ABCD()
{
	for(int i = 0; i < n; i++)
	{
		cout << A[i] << " " << B[i] << " " << C[i] << " " << D[i] << endl;
	}
}

void div_case()
{
	idx = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			AB[idx] = A[i] + B[j];
			CD[idx++] = C[i] + D[j];
		}
	}
	sort(AB, AB+idx);
	sort(CD, CD+idx);
	//cout << "idx :  " << idx << endl;
}

void print_AC()
{
	for(int i = 0; i < idx; i++)
	{
		cout << AB[i] << " " << CD[i] << endl;
	}
}


void get_cnt()
{
	total_cnt = 0ll;
	int l = 0;	// AB 시작 인덱스
	int r = idx - 1;// CD 시작 인덱스
	long long ll, rr; // 같은 수 몇 개나??
	int l_tmp;

	while((l < idx) && (r >= 0))
	{
		if(0 == AB[l] + CD[r])
		{
			l_tmp = l;
			ll = rr = 0;
			while((0 == AB[l] + CD[r]) && (l < idx))
			{
				l++; ll++;
			}
			while((0 == AB[l_tmp] + CD[r]) && (r >= 0))
			{
				r--; rr++;
			}
			total_cnt += (rr * ll);
			//printf("total_cnt = %d\n", total_cnt);
		}
		else if(0 > AB[l] + CD[r]) l++;
		else r--;
	}
	//cout << "idx :  " << idx << endl;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	input();
	//print_ABCD();
	div_case();
	//print_AC();
	get_cnt();
	cout << total_cnt << endl;

	return 0;
}





// 이진탐색으로 풀 것
// BOJ_7453_합이 0인 네 정수
/*
	=> 배열의 크기 n : 1 ~ 4000
	   4000 ^ 4는 1600만^2... 너무 크다 ( 시간 복잠도 O(N^4) )
*/

#include <iostream>
#include <algorithm>
using namespace std;
#define MAX	(4010)

int n;
int A[MAX], B[MAX], C[MAX], D[MAX];
int AB[MAX*MAX], CD[MAX*MAX];
long long total_cnt;
int idx;

void input()
{
	cin >> n;
	for(int i = 0; i < n; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];
}

void print_ABCD()
{
	for(int i = 0; i < n; i++)
	{
		cout << A[i] << " " << B[i] << " " << C[i] << " " << D[i] << endl;
	}
}

void div_case()
{
	idx = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			AB[idx] = A[i] + B[j];
			CD[idx++] = C[i] + D[j];
		}
	}
	sort(AB, AB+idx);
	sort(CD, CD+idx);
}

void print_AC()
{
	for(int i = 0; i < idx; i++)
	{
		cout << AB[i] << " " << CD[i] << endl;
	}
}


void get_cnt()
{
	total_cnt = 0;
	int l = 0;	// AB 시작 인덱스
	int r = idx - 1;// CD 시작 인덱스
	long long ll, rr; // 같은 수 몇 개나??
	int l_tmp;

	while((l < idx) && (r >= 0))
	{
		if(0 == AB[l] + CD[r])
		{
			l_tmp = l;
			ll = rr = 0;
			while((0 == AB[l] + CD[r]) && (l < idx))
			{
				l++; ll++;
			}
			while((0 == AB[l_tmp] + CD[r]) && (r >= 0))
			{
				r--; rr++;
			}
			total_cnt += (rr * ll);
			//printf("total_cnt = %d\n", total_cnt);
		}
		else if(0 > AB[l] + CD[r]) l++;
		else r--;
	}
}


void get_cnt()
{
	total_cnt = 0ll;
	int s = 0, e = idx - 1, m;
	
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	input();
	//print_ABCD();
	div_case();
	//print_AC();
	get_cnt();
	cout << total_cnt << endl;

	return 0;
}




// 2중 for문
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX	4010

int N;
int A[MAX], B[MAX], C[MAX], D[MAX];
int AB[MAX*MAX], CD[MAX*MAX];
int idx;

void input()
{
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
	{
		scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
	}
}

void div()
{
	idx = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			AB[idx] = A[i] + B[j];
			CD[idx++] = C[i] + D[j];
			//if((i == N-1) && (j == N-1)) printf("%d\n", i*N+j);
		}
	}
	sort(AB, AB + idx);
	sort(CD, CD + idx);
}

long long int answer()
{
	long long int ans = 0;
	int s = 0, e = idx - 1;
	int sum;
	int ss, ee;
	int s_idx;

	while((s < idx) && (0 <= e))
	{
		sum = AB[s] + CD[e];
		if(sum == 0)
		{
			s_idx= s;
			ss = ee = 0;

			/*
			// s+1나 e-1이 배열 범위를 벗어날 수도 있음;;
			while(AB[s] == AB[s+1])
			{
				s++;
				ss++;
			}
			while(CD[e] == CD[e-1])
			{
				e--;
				ee++;
			}
			*/

			while(AB[s] + CD[e] == 0)
			{
				if(s >= idx) break;
				ss++;	s++;
			}
			while(AB[s_idx] + CD[e] == 0)
			{
				if(e < 0) break;
				ee++;	e--;
			}
			ans += (ss * ee);
			//s++; e--;
		}
		else if(sum < 0) s++;
		else e--;
	}

	return ans;	// 4000^4 만큼을 담아야 할 수도 있기 때문!
}

/*
void print_input()
{
	printf("  A   B   C   D\n");
	for(int i = 0; i < N; i++) printf("%3d %3d %3d %3d\n", A[i], B[i], C[i], D[i]);
	printf("  AB   CD\n");
	for(int i = 0; i < N * N; i++) printf("%4d %4d\n", AB[i], CD[i]);
}
*/

int main()
{
	input();
	div();
	//print_input();
	printf("%lld\n", answer());

	return 0;
}
