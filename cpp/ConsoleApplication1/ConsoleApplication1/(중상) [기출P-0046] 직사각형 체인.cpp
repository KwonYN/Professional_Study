// (�߻�) [����P-0046] ���簢�� ü��
/*
	������ ������,
	�� ���������� ���� ���̰� 0 �̰ų� ���� ���̰� 0 �� �͵�
	Ư���� ���簢������ ���������,
	����, ���� ���̰� ��� 0 �� ����
	���簢������ ������� �ʴ´ٴ� ���̴�.

	������ ������ �Է� �޾�
	��� ������ ���簢�� ü���� ������ ����ϴ� ���α׷�

	�� ���� Ǯ�� ��
	1000 * 1000�̱� ������ ����� ��Ž���� �� �� ���� ������?
	But, �������� ����� % 10��7�� ���ִ� ������ ����
		 �Ϲ����� ��Ž���δ� �ð��ʰ��� �� ������ ����ǰ�,
		 ��û�� ����ġ�� �Ǵ� ���ٸ� Ǯ�̰� �ʿ��� ����.
	1 1 1		0(1) 1 1
	1 1 1	->	1    2 3
	1 1 1		1    3 6

	1 1 1		0(1) 1 1
	1 2 2	->	1    1 2
	1 2 1		1    2 4
	�̷��� ���� �׷����鼭 ��Ģ���� ã�ư�!

	2 3 4 5 ... (N+1)
	3 4 5 6 ... (N+2)
	4 5  . .
	5 6  .   .
	. .        .
	. .          .
	. .            .
	(N+1) (N+2)  ... (N+N)
	��
	(1,2) (2,1)				=> 1, -1
	(1,3) (2,2) (3,1)		=> 2, 0, -2
	(1,4) (2,3) (3,2) (4,1) => 3, 1, -1, -3
	...
	(1,N) . . . . . .  (N,1)=> (N-1), (N-3), ... , (1-N)
	(2,N) . . . . . .  (N,2)=> (N-2), (N-4), ... , (2-N)
	(N,N)					=> (0)
	��
	1) �׹������� �����.
	2) chain[i][j]�� ��
	  �� y��ǥ : 0 ~ chain[i][j], x��ǥ : chain[i][j] ~ 0
	     �� chain[i-y][j-x]�� �����ִ� ���� ������
		   (��, i-y �Ǵ� j-x�� < 1�� ��쿡�� X)
		   (�׸��� �Ź� %MOD�� ��������!)
	3) (N, N)���� 2)�� ����
	4) �ڿ����� chain[N][N]�� �� cnt�� ���̰� ��!
	=> (2N-2)*N^2 �ִ�� �� 2000 * 10��..!!

	���� �� ��������, �ð� ���⵵�� �ذ��ؾ� ��!!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(1000)
#define MOD		(1000000007)

int T, N, chain[NMAX+5][NMAX+5], path_cnt[NMAX+5][NMAX+5];

void input() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &chain[i][j]);
			path_cnt[i][j] = 0;
		}
	}
	path_cnt[1][1] = 1;
}

void get_path_cnt() { // ��Ʈ��ŷ(dfs)�ε� ������ �� ����!
	int x, dx;
	for (int s = 3; s <= N+1; s++) {
		for (int y = 1; y < s; y++) {
			x = s - y;
			//printf("(%d,%d) ", y, x);
			for (int dy = 0; dy <= chain[y][x]; dy++) {
				dx = chain[y][x] - dy;
				if (y - dy < 1 || x - dx < 1) continue;
				path_cnt[y][x] = (path_cnt[y][x] + path_cnt[y-dy][x-dx])%MOD;
			}
		}
		//printf("\n");
	}
	for (int s = N + 2; s <= 2 * N; s++) {
		for (int y = s - N; y <= N; y++) {
			x = s - y;
			//printf("(%d,%d) ", y, x);
			for (int dy = 0; dy <= chain[y][x]; dy++) {
				dx = chain[y][x] - dy;
				if (y - dy < 1 || x - dx < 1) continue;
				path_cnt[y][x] = (path_cnt[y][x] + path_cnt[y - dy][x - dx]) % MOD;
			}
		}
		//printf("\n");
	}
}

void output(int tc) { printf("#%d %d\n", tc, path_cnt[N][N]); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		get_path_cnt();
		output(tc);
	}
	return 0;
}
#endif