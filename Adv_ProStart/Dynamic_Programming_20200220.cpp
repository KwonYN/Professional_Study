/************************/
/* [ 2020.02.20 day 9 ] */
/************************/

// 종이에 써가면서 다시 이해해보자! (DP의 활용 + 공간에 대한)

// DP[][]의 의미 제대로 선언(?)해서 사용 + 공간복잡도 줄이는 방법
// (중) [교육A-0012] 보석 털이 
#if 0

#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MMAX	(10000)
#define MAX(a, b)		( ( (a)  > (b) ) ? (a) : (b) )

int T, N, C[NMAX+5], W[NMAX+5], M;
//long long DP[NMAX+5][MMAX+5];	// DP[i][j] : 1 ~ i번 보석, 1 ~ j kg까지(이하)
long long DP[2][MMAX + 5];
long long D[MMAX+5];

void make_DP() {
	// 처음에 푼 풀이 (하지만 각 보석이 한 개밖에 없어서 이렇게는 못 품)
	/*long long max = 0;
	for (int i = 1; i <= M; i++) { // 모든 무게에 대해서
		for (int j = 1; j <= N; j++) { // 모든 보석에 대해서
			if (i < W[j]) continue;
			if (max < D[i - W[j]] + C[j]) {
				D[i] += D[i - W[j]] + C[j];
				max = D[i];
				P[i] = j;
				
			}
		}
	}
	return max;*/

	// DP[i][j] : 1 ~ i번 보석, 1 ~ j kg까지(이하)
	for (int i = 1; i <= N; i++) { // 모든 보석에 대해서
		for (int j = 0; j < W[i]; j++) { // if (j < W[i]) continue;
			//DP[i][j] = DP[i - 1][j];
			DP[i&1][j] = DP[(i - 1)&1][j];
		}
		for (int j = W[i]; j <= M; j++) { // 모든 무게에 대해서
			// DP[i][j] = MAX(DP[i - 1][j - W[i]] + C[i], DP[i-1][j]);
			// 1 ~ i-1까지의 보석들을 활용하여 만든 조합으로 그 다음 정해준다는 의미!
			// DP[i - 1][j - W[i]] + C[i] : i번째 보석을 사용하려면(합쳐서 j kg이 되야 하므로), j - W[i]에서의 최대값에 + C[i]
			// DP[i-1][j] : i번째 보석을 사용하지 않는다는 의미!
			DP[i&1][j] = MAX(DP[(i - 1)&1][j - W[i]] + C[i], DP[(i - 1)&1][j]);
		}
	}

	// 이건 무엇!?
	for (int i = 1; i <= N; i++) {
		for (int j = M; j >= W[i]; j--) {
			D[j] = MAX(D[j], D[j - W[i]] + C[i]);
		}
	}
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i <= M; i++) DP[0][i] = 0; // 초기화 필요 ㅋㅋ
		/*
				for (int j = 0; j < W[i]; j++) { // if (j < W[i]) continue;
					//DP[i][j] = DP[i - 1][j];
					DP[i&1][j] = DP[(i - 1)&1][j];
				}
				이 식 때문에
		}
		*/
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &C[i], &W[i]);
		}
		make_DP();
		//printf("#%d %lld\n", tc, DP[N][M]);
		printf("#%d %lld %lld\n", tc, DP[N&1][M], D[M]);
	}
	return 0;
}

#endif






// 다시 풀어보아야 할 문제 ( 3)의 방법으로! )
// (중상) [연습P-0022] LIS 2
/*
	최장 증가 부분 수열(Longest Increasing Subsequence)은
	어떤 수열의 부분 수열 중
	각 항이 이전 항에 비해 증가하는 부분 수열을 의미한다.
	예를 들어, 수열 (1, 8, 4, 12, 2, 14, 6)의 최장 증가 부분 수열은 (1, 8, 12, 14), (1, 4, 12, 14)가 있다.
	수열이 주어졌을 때, 해당 수열의 최장 증가 부분 수열의 길이를 알아내자.
*/
#if 0

#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(300000)

int T, N;
int A[NMAX+5], D[NMAX+5], P[NMAX+5];
int BIN[NMAX+5];
int max;	// 1)
int len;	// 2), 3)

// 3) 다시...
typedef struct { int value, index; }DATA;
DATA Data[NMAX*4];

bool cmp(const DATA &p1, const DATA &p2) {
	if (p1.value < p2.value)  return true;
	if (p1.value == p2.value) return p1.index > p2.index;
	return false;
}

void make_tree() {
	int maldan;
	for (maldan = 1; maldan <= N; maldan <<= 1);
	for (int i = 1; i < 2 * maldan; i++) Data[i] = { 0, 0 };

	stable_sort(Data, Data + N, cmp);
	for (int i = 1; i <= N; i++) Data[i + maldan - 1] = { A[i], i };
	for (int i = maldan - 1; i >= 1; i--) Data[i] = Data[i * 2] + Data[i * 2 + 1];
}

int search(int s, int e) {

}

void update(int idx, int len) {

}

// 2)
int bin_search(int s, int e, int target) {
	int m;

	while (s <= e) {
		m = (s + e) / 2;
		if (BIN[m] == target) return m;
		if (BIN[m] > target) e = m - 1;
		else s = m + 1;
	}
	return s;
}

int main()
{
	BIN[0] = 0x80000000;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//max = 0;	// 1)
		len = 0;	// 2)
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &A[i]);

			// 1) O(N^2)의 방법!
			/*
			D[i] = 1;	P[i] = -1;
			for (int j = i - 1; j >= 1; j--) {
				if (A[j] < A[i]) {
					if (D[i] < D[j] + 1) {
						D[i] = D[j] + 1;
						P[i] = j;
						if(max < D[i]) max = D[i];
					}
				}
			}
			*/

			
			// 2) N logN의 방법! : 또 다른 배열 + 바이너리 서치 필요
			int idx;
			if (BIN[len] < A[i]) {
				BIN[++len] = A[i];
				D[i] = len;
			}
			else {
				idx = bin_search(1, len, A[i]);
				D[i] = idx;
				BIN[idx] = A[i];
			}
		}
		// 3) N logN의 방법! : Indexed Tree
		make_tree();
		for (int i = 1; i <= N; i++) {
			len = search(1, Data[i].index - 1);
			D[Data[i].index] = len + 1;
			update(Data[i].index, len + 1);
		}

		//printf("#%d %d\n", tc, max);	// 1)
		//printf("#%d %d\n", tc, len);	// 2)
		printf("#%d %d\n", tc, );
	}
	return 0;
}

#endif






// 흠.. 어떻게 해야 함? 다시 ㄱㄱ
// (중상) [교육P-0019] Matrix Chain Multiplication 
/*
	행렬 곱셈에는 교환 법칙 AB=BA는 성립하지 않지만, 결합 법칙 (AB)C = A(BC)는 성립한다.
	결합 법칙에 의해 어떤 순서로 곱셈을 하는지에 따라 전체 연산 횟수가 달라진다.
*/
#if 0

#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX		(500)
#define INF		(987654321)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

int T, N;
int A[MAX+10];
int DP[MAX+10][MAX+10];	// i번째 행렬 ~ j번째 행렬 곱의 최소 연산 횟수를 담는/기록하는 배열!!

void init() {
	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) DP[i][j] = INF;
}

void count_Matrix_Chain_Multiplication() {
	for (int section = 1; section <= N; section++) {
		for (int s = 1; s <= N; s++) {
			if (s + section < 1) continue;
			if (s + section - 1 > N) break;
			for (int m = s; m < N; m++) {
				DP[s][s+section-1] = MIN(DP[s][m] + DP[m+1][s+section-1] + A[s]*A[m+1]*A[s+section-1], 
											 DP[s][s+section-1]);
			}
		}
	}
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		init();
		for (int i = 1; i <= N + 1; i++) scanf("%d", &A[i]);
		count_Matrix_Chain_Multiplication();
		printf("#%d %d\n", tc, DP[1][N]);
	}
	return 0;
}

#endif






// (중상) [기출P-0027] 기름 값 
/*
	각 도시에는 단 하나의 주유소. 각 주유소의 리터 당 기름 가격은 입력으로 주어진다.
	인접한 두 도시를 잇는 도로의 킬로미터 단위 길이도 입력으로 주어진다.
	1리터 당 1킬로미터를 주행.

*/
#if 0

#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(2000)
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )

int T, N, L;
int city[NMAX][2]; // [x][0] = x도시에서의 기름값 // [x][1] = x도시까지의 거리
int dist_sum[NMAX+5];		// idx도시까지의 거리 누적 합
int min_station[NMAX +5];	// idx번째 도시까지의 주유소 중 값이 싼 주유소가 있는 도시의 번호
int D[NMAX+5][NMAX+5];

void make_DP() {
	for (int section = 1; section < N; section++) {
		for (int s = 1; s <= N; s++) {
			if (s + section > N) break;
			for (int m = s; m <= s + section - 1; m++) {
				if (dist_sum[m] - dist_sum[s] > L || dist_sum[s + section] - dist_sum[m + 1] > L) continue;
				D[s][s + section] = D[s][m] + D[m+1][s+section];
			}
		}
	}
}

int main()
{
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		dist_sum[1] = 0;
		min_station[0] = 0;
		scanf("%d %d", &N, &L);
		for (int i = 1; i < N; i++) {
			scanf("%d %d", &city[i][0], &city[i+1][1]);
			dist_sum[i+1] += city[i+1][1];
			if (city[min_station[i - 1]][0] > city[i][0]) min_station[i] = i;
		}
		scanf("%d", &city[N][0]); // 어차피 주유 안해주기 때문에 그냥 입력만 받아줌!
		make_DP();
		printf("#%d %d\n", tc, D[1][N]);
	}
	return 0;
}

#endif
// Re..... 점화식 다시 구해보자!
#if 0

#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(2000)
#define LMAX	(50)

int T, N, L;
int Oil[NMAX+5];		// idx번 도시에서의 기름 비용
int Dist[NMAX+5];		// idx-1 -> idx번 도시 사이 거리
int D[NMAX+5][LMAX+5];	// idx번 도시에서 있는 상태. 그리고 그 때 남아있는 기름의 양 jdx

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {


		//  답은 0 ~ L사이까지의 D[N][i]의 최소값
	}
	return 0;
}

#endif 
/*
[문제]
좌우 방향의 일직선 상에 위치한 N개의 도시가 있다. 직선 상에서 인접한 두 도시 사이를 잇는 도로가 모두 있으며
길이는 다를 수 있다. 왼쪽 끝 도시에서 오른쪽 끝 도시로 자동차를 이용하여 이동하려고 한다.
처음에 자동차에는 기름이 없어서 기름을 넣고 출발하여야 한다. 각 도시에는 단 하나의 주유소가 있으며,
각 주유소의 리터 당 기름 가격은 입력으로 주어진다. 또, 인접한 두 도시를 잇는 도로의 킬로미터 단위 길이도 입력으로 주어진다.
사용할 자동차는 1리터 당 1킬로미터를 주행한다고 한다. 자동차의 기름통 용량은 L리터이다.

위의 그림은 N=4 인 예를 보이고 있다. 원은 도시이고, 원 안의 숫자는 그 도시에 있는 주유소의 리터당 기름 값이다.
선은 도로이며, 선 위의 숫자는 도로의 길이이다. 위의 예에서 L<15 인 경우
제일 왼쪽 도시에서 제일 오른쪽 도시로 이동이 불가능함을 알 수 있다. L=15 인 경우 최소 비용은 68이다.

위의 예에서 L=8 이라고 하면 최소 비용은 25임을 알 수 있다.
각 도시에 있는 주유소의 기름값과 도로들의 길이를 입력으로 받아
제일 왼쪽의 도시에서 제일 오른쪽의 도시로 이동하는 최소 비용을 출력하는 프로그램을 작성하라.

[입력]
첫째 줄에 테스트 케이스의 개수 T가 주어지고, 이후 차례로 T개 테스트 케이스가 주어진다.
각 케이스의 첫째 줄에는 도시의 개수를 나타내는 자연수 N과 기름통의 크기를 나타내는 L이 주어진다.
(2 ≤ N ≤ 2,000, 1 ≤ L ≤ 50) 다음 줄에는 기름 값, 도로 길이, 기름 값, 도로 길이의 순서로
도시의 기름 값들과 도로의 길이가 왼쪽부터 순서대로 주어진다.
(예제의 그림과 동일한 순서임) 도로의 길이는 1 이상 1,000 이하의 자연수이며, 기름 값은 1 이상 1,000 이하의 자연수이다.


[출력]
각각의 테스트 케이스에 대하여 #x (x는 1부터 시작하는 테스트 케이스의 번호)를 출력하고
공백을 하나 둔 다음 정답을 출력한다. 정답인 최소 비용은 하나의 자연수로 출력한다.
제일 왼쪽 도시에서 제일 오른쪽 도시로 이동이 불가능하면 -1을 출력한다.

[입출력 예]
(입력)
3
4 14
5 3 4 2 3 15 7
4 15
5 3 4 2 3 15 7
4 8
3 5 1 3 2 6 7

(출력)
#1 -1
#2 68
#3 25
*/




// 다시 풀어보자....................
// (중상) [교육P-0028] LCS - special judge
/*
	LCS(최장 공통 부분수열, Longest Common Subsequence)란,
	두 수열이 있을 때 두 수열의 공통 부분수열 중 가장 긴 공통 부분수열을 의미한다.
	두 문자열이 주어졌을 때, 두 문자열의 LCS를 구하는 프로그램을 작성하시오.

	[입력]
	입력은 여러 개의 테스트케이스로 이루어져 있다.
	입력의 첫째 줄에는 테스트케이스의 수 T가 주어지고, 이후 차례로 각 테스트케이스가 주어진다. (1 ≤ T ≤ 15)
	각 테스트케이스의 첫째 줄과 둘째 줄에 두 문자열이 주어진다. 문자열은 알파벳 대문자로만 이루어져 있으며,
	길이가 1,000을 넘지 않는다.


	[출력]
	각 테스트케이스 마다 줄의 시작에 “#x”를 출력한다.
	이 때, x는 1부터 시작하는 테스트케이스의 번호다. 같은 줄에 주어진 두 문자열의 LCS를 출력한다.
	만약 답이 여러 가지인 경우 아무거나 하나 출력한다. LCS의 길이가 0인 경우는 입력으로 주어지지 않는다.

	[입출력 예]
	(입력)
	1
	ABCBDAB
	BDCABA

	(출력)
	#1 BCBA
*/
#if 0

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
#define SMAX	(1000)
#define MAX(a, b)	( ( (a) > (b) ) ? (a) : (b) )

int T;
string str1, str2;
int len1, len2;
char result[SMAX+10];
int D[SMAX+5][SMAX+5];
// D[i][j] : str1의 i 위치(1 ~ i까지의 최장공통수열 길이), str2의 j 위치(1 ~ j까지의 최장공통수열 길이)
// if ( str1[i] == str2[j] ) => D[i][j] = D[i-1][j-1] + 1;
// if ( str1[i] != str2[j] ) => D[i][j] = max ( D[i-1][j], D[i][j-1] );
int P[SMAX+5][SMAX+5];
// P[i][j] : D[][]가 최장길이를 기록하는 배열이라면,
//			 P[][]는 그 때 어떤 값을 참조하여 길이를 구했는지를 표시해주는 배열

void init() {
	for (int i = 0; i <= len1; i++) {
		D[i][0] = 0;
		for (int j = 0; j <= len2; j++) P[i][j] = 0;
	}
	for (int i = 0; i <= len2; i++) D[0][i] = 0;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> str1;			cin >> str2;
		len1 = str1.length();	len2 = str2.length();
		init();

		// DP
		for (int i = 0; i < len1; i++) {
			for (int j = 0; j < len2; j++) {
				if (str1[i] == str2[j]) {		// P = 1 : 길이 늘어남
					D[i+1][j+1] = D[i][j] + 1;
					P[i+1][j+1] = 1;
				}
				else {
					if (D[i][j+1] >= D[i+1][j]) {	// P = 2 : str2에서
						P[i+1][j+1] = 2;
						D[i+1][j+1] = D[i][j+1];
					}
					else {							// P = 3 : str1에서
						P[i+1][j+1] = 3;
						D[i+1][j+1] = D[i][j+1];
					}
				}
			}
		}

		printf("print D\n");
		for (int i = 0; i <= len1; i++) {
			for (int j = 0; j <= len2; j++) {
				printf("%d ", D[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("print P\n");
		for (int i = 0; i <= len1; i++) {
			for (int j = 0; j <= len2; j++) {
				printf("%d ", P[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		// for Print
		int y = len1, x = len2, leng = 0;
		while ( (y != 0) && (x != 0)) {
			if (P[y][x] == 1) {
				result[leng++] = str1[y-1];
				printf("y-1 = %d\n", y - 1);
				y -= 1;		x -= 1;
			}
			else if (P[y][x] == 2) x -= 1;
			else if (P[y][x] == 3) y -= 1;
			printf("y = %d, x = %d\n", y, x);
		}
		
		// real Print
		cout << "#" << tc << " ";
		for (int i = leng - 1; i >= 0; i--) cout << result[i];
		cout << endl;
	}
	return 0;
}

#endif 




// (중상) [기출P-0035] 주차 타워 
/*
	주차 타워에 차가 N 대 주차되어 있다. 차들은 1부터 N까지 번호가 붙어 있다
	체인을 왼쪽이나 오른쪽으로 회전하는 칸 수를 비용으로 생각하자.

	주차 타워의 상태를 입력으로 받아 번호 순서에
	최대 1의 오차를 허용하는 조건으로 차를 꺼내는 최소 비용을 계산하는 프로그램을 작성하라.

	[입력]
	입력 파일의 제일 첫째 줄에는 파일에 포함된 케이스의 수 T가 주어진다.
	케이스의 첫 줄에 주차할 수 있는 칸의 개수 N이 주어진다. (1≤N≤1,000,000)
	다음 줄에 N개의 차 번호의 순서가 주어진다. 그 순서대로 원형 체인에 위치하고 있다는 의미이다.
	순서에서 첫 번째로 주어진 번호의 차가 꺼낼 수 있는 위치(1층)에 존재한다.


	[출력]
	각 테스트 케이스의 답을 순서대로 표준출력으로 출력하며,
	각 케이스마다 줄의 시작에 “#x”를 출력하여야 한다. 이때 x는 케이스의 번호이며 1부터 시작한다.
	같은 줄에 공백을 하나 두고 가능한 최소비용을 출력한다.

	[입출력 예]
	(입력)
	3         <- 3 test cases in total
	4         <- 1st case
	4 2 1 3
	4         <- 2nd case
	3 4 1 2
	5         <- 3rd case
	3 5 4 1 2

	(출력)
	#1 4
	#2 4
	#3 6
*/
#if 0

#include <cstdio>
#include <algorithm>
using namespace std;
#define MIN(a, b)	( ( (a) < (b) ) ? (a) : (b) )
#define ABS(a)		( ( (a) < 0 ) ? -(a) : (a) )
#define NMAX	(1000000)

int T, N;	// N 최대 100만
int out_order[NMAX+10];
int D[NMAX+10][3];
int P[NMAX+10];
// D[i][j] : i번에 주차되어야 하는 차는 i-1, i, i+1번째에 주차될 수 있음!
// j = 0이라면, i번째인 경우
// j = 1이라면, i - 1번째인 경우
// j = 2라면, i + 1번째인 경우!
/*
	@@ 1 ~ 3개 차 단위로 보자!!
	
	D[i][0] : i번째 주차되어야 하는 차를 i번째에!!
	 == D[i-1][0] : i-1번째 주차되어야 하는 차량을 제때 뽑거나

		+ D[i-1][1] : i-1번째 주차되어야 하는 차량이 i-2에 주차되는 경우
					(그렇다면 무조건 i-2번째 주차되어야 하는 차량이 i-1에 주차됨)

	D[i][1] : 
	 == D[i-2][0]
		+ D[][]
*/
// => D[i][0] = MIN( D[i-1][0] + dist(i-1, i), D[i-1][1] + dist(i-2, i) );
//	  D[i][1] = MIN( D[i-2][0] + dist(i-2, i) + dist(i, i-1)), D[i-2][1] + dist(i-3, i) + dist(i, i-1);

int dist(int a, int b) {
	int distance = ABS(P[a] - P[b]);
	if (distance > N / 2) distance = ABS(N - distance);
	return distance;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &out_order[i]); // i번째에 out_order[i] 차량이 있다
			P[out_order[i]] = i;		// 나중에 거리 구할 때 필요!!
		}


		printf("#%d %d\n", tc, MIN(D[N][0], D[N][1]));
	}
	return 0;
}

#endif 
