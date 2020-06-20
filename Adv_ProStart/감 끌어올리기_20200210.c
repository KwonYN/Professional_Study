#pragma warning(disable: 4996)

#include <stdio.h>


// [연습A-0028] 나누기
#if 01

#define MAX	150

void input(void);
void DFS(int num, int sy, int sx, int ey, int ex);

void print_map(void);

int T, N;
int count0, count1;
int map[MAX][MAX];
int sum[MAX][MAX];

int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		input();
		print_map();
		DFS(N, N, N, 0, 0);
		printf("#%d %d %d\n", i, count0, count1);
	}

	return 0;
}

void input(void)
{
	int i, j;

	count0 = count1 = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &map[i][j]);
			sum[i][j] = map[i][j];
		}
		for (j = 2; j <= N; j++) sum[i][j] += sum[i][j-1];
	}
	for (j = 1; j <= N; j++)
	{
		for(i = 2; i <= N; i++) sum[i][j] += sum[i-1][j];
	}
}

void DFS(int num, int sy, int sx, int ey, int ex)
{
	int comp;

	printf("num = %d, sy = %d, sx = %d, ey = %d, ex = %d\n", num, sy, sx, ey, ex);
	getch();

	if (num <= 1)
	{
		if (map[sy][sx] == 1) count1++;
		else count0++;
		return;
	}

	comp = sum[sy][sx] - sum[ey][sx] - sum[sy][ex] + sum[ey][ex];
	printf("comp = %d\n", comp);
	getch();
	if (comp == num * num)
	{
		count1++;
		return;
	}
	else if (comp == 0)
	{
		count0++;
		return;
	}
	else
	{
		printf("<count0 = %d, count1 = %d>\n", count0, count1);
		getch();
		DFS(num / 2, sy / 2, sx / 2, ey, ex);
		DFS(num / 2, sy, sx / 2, ey+sy / 2, ex);
		DFS(num / 2, sy / 2, sx, ey, ex+sx / 2);
		DFS(num / 2, sy, sx, ey+sy / 2, ex+sx / 2);
	}
}


void print_map(void)
{
	int i, j;

	printf("map\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("=======\n");

	printf("sum\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
	printf("=======\n");
}

#endif


// [기출A-0013] 숫자 배치하기 
#if 01

void input(void);
void make_comb(int L, int max);

int T, N;
int score_board[15][15];
int max_score;
int list[15];
int chk[15];

int main(void)
{
	int i;

	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		input();
		make_comb(0, 0);
		printf("#%d %d\n", i, max_score);
	}

	return 0;
}

void input(void)
{
	int i, j;

	max_score = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) scanf("%d", &score_board[i][j]);
}

void make_comb(int L, int max)
{
	int i;

	if (L >= N)
	{
		if (max_score < max) max_score = max;
		return;
	}
	
	for (i = 1; i <= N; i++)
	{
		if (chk[i]) continue;
		chk[i] = 1;
		list[L] = i;
		make_comb(L + 1, max + score_board[i][L+1]);
		list[L] = 0;
		chk[i] = 0;
	}
}

#endif
/*
	< 이 문제의 시간 복잡도?? : N! >
	N개를 한 번씩만 사용하여 수열을 만든다!?
	(1st)N가지의 경우 * (2nd) N-1가지 * (3rd) N-2가지 * ... * (N th) 1가지
	=> N*(N-1)*(N-2)*...*2*1 == N!
*/



// [연습A-0013] 피크닉
# if 01

void input(void);
void DFS(int s, int start, int num);
int get_answer(void);
void init(void);

void print_existable(void);

int T, K, N, M;
int injub[1010][1010];
int injub2[1010][1010];
int cow[1010];	// 소의 첫 목초지 위치
int existable[1010];	// 길 수 있는 목초지
int chk[1010];

int main(void)
{
	int i, j;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		input();
		for (j = 1; j <= N; j++)
		{
			if (!cow[j]) continue;
			existable[j] += cow[j];
			chk[j] = 1;
			DFS(j, j, cow[j]);
			chk[j] = 0;
		}
		print_existable();
		printf("#%d %d\n", i, get_answer());
		init();
	}

	return 0;
}

void input(void)
{
	int i;
	int tmp_cow;
	int s, e;

	scanf("%d %d %d", &K, &N, &M);
	for (i = 1; i <= K; i++)
	{
		scanf("%d", &tmp_cow);
		cow[tmp_cow]++;	// tmp_cow 목초지에서 출발하는 소가 몇 마리인지?
	}
	for (i = 1; i <= M; i++)
	{
		scanf("%d %d", &s, &e);
		injub[s][e] = 1;
	}
}

void DFS(int s, int start, int num)
{
	int i;

	for (i = 1; i <= N; i++)
	{
		if (!injub[s][i] || injub2[start][i] || chk[i]) continue;
		injub2[start][i] = 1;
		chk[i] = 1;
		existable[i] += num;
		DFS(i, start, num);
		chk[i] = 0;
	}
}

void print_existable(void)
{
	int i;

	for (i = 1; i <= N; i++) printf("%d ", existable[i]);
	printf("\n");
}

int get_answer(void)
{
	int i, ans = 0;

	for (i = 1; i <= N; i++) if (existable[i] == K) ans++;
	return ans;
}

void init(void)
{
	int i, j;

	for (i = 1; i <= N; i++)
	{
		cow[i] = 0;
		existable[i] = 0;
		for (j = 1; j <= N; j++) injub[i][j] = injub2[i][j] = 0;
	}
}
/*
2
2 4 5
2
3
1 2
1 4
2 3
3 4
2 4
2 4 4
2
3
1 2
1 4
2 3
3 4
*/
#endif


// [기출A-0009] 정예병사
#if 01

#define NMAX	100010

void input(void);
void operation(void);

void print_defense(void);

int T, N;
int count;
int defense[NMAX];
int def_min;

int main(void)
{
	freopen("in.txt", "r", stdin);
	int t;
	scanf("%d", &T);
	for (t = 1; t <= T; t++)
	{
		input();
		operation();
		//print_defense();
		printf("#%d %d\n", t, count);
	}

	return 0;
}

void input(void)
{
	int i;
	int tmp_atk, tmp_def;

	count = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &tmp_atk, &tmp_def);	// i번 병사의 공격력, 방어력 순위
		// 공격력 순위가 tmp_atk인 병사는 i번 병사이고, 방어력 순위는 tmp_def 
		defense[tmp_atk] = tmp_def;
	}
}

void operation(void)
{
	int i;

	def_min = defense[1];
	for (i = 1; i <= N; i++)
	{
		if (def_min >= defense[i])
		{
			def_min = defense[i];
			count++;
		}
	}
}

void print_defense(void)
{
	int i;

	printf("atk\n");
	for (i = 1; i <= N; i++) printf("%d ", i);
	printf("\n");
	printf("def\n");
	for (i = 1; i <= N; i++) printf("%d ", defense[i]);
	printf("\n");
}

/*
void operation(void)
{
	int i, j;
	int comp, comp2, def_comp;
	int cnt, min = 987654321;

	for (i = 1; i <= N; i++)
	{
		comp = attack[i]; // 공격력이 i위인 병사의 번호
		cnt = 0;
		def_comp = defense[comp];	// 공격력이 i위인 병사의 수비력 순위
		if (def_comp > min) continue;
		for (j = 1; j < i; j++)
		{
			comp2 = defense[ attack[j] ]; // j번 병사의 수비력 순위
			if (comp2 < def_comp) break;
			if (min > comp2) min = comp2;
			cnt++;
		}
		if (cnt == i - 1) count++;
	}
}
*/
#endif



// [사전A-0024] 바코드
#if 01

#define SMAX	3010
#define LCODE	0
#define GCODE	1

void input(void);
	
int T;
char in_barcode[SMAX];
int len;
int count;
char *group_C[10] =
{
	"1110010",
	"1100110",
	"1101100",
	"1000010",
	"1011100",
	"1001110",
	"1010000",
	"1000100",
	"1001000",
	"1110100"
};
// A그룹의 숫자에 따라!! (그 숫자는 이 배열의 요소 번호)
char *group_BA[10] =
{
	"LLLLLL",
	"LLGLGG",
	"LLGGLG",
	"LLGGGL",
	"LGLLGG",
	"LGGLLG",
	"LGGGLL",
	"LGLGLG",
	"LGLGGL",
	"LGGLGL"
};

char *group_BLG[10][2] =
{
	{"0001101", "0100111"},
	{"0011001", "0110011"},
	{"0010011", "0011011"},
	{"0111101", "0100001"},
	{"0100011", "0011101"},
	{"0110001", "0111001"},
	{"0101111", "0000101"},
	{"0111011", "0010001"},
	{"0110111", "0001001"},
	{"0001011", "0010111"}

};


int main(void)
{
	int t;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (t = 1; t <= T; t++)
	{
		input();

		printf("#%d %d ", t, count);
	}

	return 0;
}

void input(void)
{
	count = 0;
	scanf("%s", in_barcode);
}

#endif
