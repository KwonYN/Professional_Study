// (��) [����A-0040] ��ž
/*
	�� ���� ���� ��
	������ ���԰� �پ�
	���� �� �Ҹ�Ǵ� ������� ���ᷮ�� �پ�
	���ø��� ���̿� ����Ͽ� �Ҹ�Ǵ� ���ᷮ�� ����
	�־����� ����
		�� ���� ���� & 10cm���÷� ���� �� �Ҹ�Ǵ� ���ᷮ
	N�� �� ��� �׾� �������� ���� �� �ִ� �ּ����� ����Ҹ� ��!?
	0 + 1000*100 + 2000*100 + ... + 99��9õ*100
		= 1000*(1+2+...+999)*100
		= (1000^2 / 2 ) * 10�� > int ����

	�� ���� Ǯ�� ��
	1. DFS
		- 1000*1000
*/

// dfs ver. : �ð��ʰ� ������
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)

struct ELEMENT { int height, fuel; };
int T, N;
ELEMENT element[NMAX+5];
bool chk[NMAX+5];
long long result, INF = 0x7fffffffffffffff;

void init() {
	result = INF;
	for (int i = 1; i <= N; i++) chk[i] = false;
}

void input() {
	int h, f;
	scanf("%d", &N);
	init();
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &h, &f);
		element[i] = { h, f };
	}
}

void dfs(int d, int h, long long s) {
	if (result <= s) return;
	if (d >= N) {
		if (result > s) result = s;
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (chk[i]) continue;
		chk[i] = true;
		dfs(d + 1, h + element[i].height, s + 1LL * (h/10) * element[i].fuel);
		chk[i] = false;
	}
}

void output(int tc) { printf("#%d %lld\n", tc, result); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		dfs(0, 0, 0);
		output(tc);
	}
	return 0;
}
#endif

/*
	�����ߴ� / ��� �Ǽ��ߴ� ��!?!?
	=> 1000���� �� ������ 1+2+...+999+1000�� �ƴ϶�
	   1*2*...*999*1000���� ��!!!

	   => N�� 1000�̴�
	      N^2 ���Ϸ� Ǯ �� ���� ��!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)

struct ELEMENT { int fuel, height; };
int T, N;
ELEMENT element[NMAX+5];

void input() {
	int h, f;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &h, &f);
		element[i] = { f/10, h };
	}
	sort(element, element+N);	// �������� ����
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
	}
	return 0;
}
#endif

