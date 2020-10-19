// BOJ_19237_����
/*
	���� 1~M �ڿ��� ��ȣ�� �پ� �ְ�, ��� ��ȣ ���� �� �ٸ�
	������ �ٸ� ������ �ѾƳ����� ��
	1�� �� ���� ��
	N*N ���� �� M�� ĭ�� �� �� ������ �������
	�� ó�� ���� �ڽ��� ��ġ�� �ڽ��� ���� �Ѹ�

	�� �� 1�ʸ��� ��� �� ���ÿ� �����¿� ���� �̵� -> ����
	�� �� �̵����� ������ ��, ���� ĭ �� �ƹ� ���� ���� ĭ����
	�׷� ĭ�� ���ٸ� �ڽ��� ������ �ִ� ĭ����
	�׷� ĭ�� �� ���� ������ �ִٸ� �켱���� ����
		- �켱������ ���� �� �ٸ� �� ����
		- ���� ���� �����ִ� ���⿡ ���� �ٸ� �� ����
		- �� ó�� ���� �ִ� ������ �Է����� �־���
		  �� �� ��� �̵��� ������ �����ִ� ������ ��!
		- ��� �� �̵��� ��, ��ĭ�� ���� ���� �� �����ִٸ� 
		  ���� ���� ��ȣ�� ���� ��� �����ϰ� �� ����
*/
#if 0 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(20)
#define MMAX	(NMAX*NMAX)
#define KMAX	(1000)
#define TIME_MAX	(1000)
#define INF		(987654321)

struct NODE { int y, x; };
struct SHARK { int num;  NODE node; int dir; };
int N, M, K;
pair<int, int> sea[NMAX+5][NMAX+5];	// �ٴ�. �׵θ� üũ �� ���� ����. // ����, ��ȣ
queue<NODE> smell;
queue<SHARK> sharks;
int dy[5] = { 0, -1, 1, 0, 0 }, dx[5] = { 0, 0, 0, -1, 1 };//X�����¿�
int shark_first_dir[MMAX+5];	// ����� �ʱ� ����
NODE shark_first_loc[MMAX+5];	// ����� �ʱ� ��ġ
int priority_dir[MMAX+5][5][5]; // �����, �� ������, �켱���� ����
int time_limit;
bool flag = false;

void input() {
	int tmp;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &tmp);
			if (tmp) {
				shark_first_loc[tmp] = { i, j };
				sea[i][j] = { K, tmp };
				smell.push({ i, j });
			}
			else sea[i][j] = { 0, 0 };
		}
		sea[i][0] = sea[i][N + 1] = sea[0][i] = sea[N + 1][i] = { -1, -1 };	// �׵θ�
	}
	for (int i = 1; i <= M; i++) {
		scanf("%d", &shark_first_dir[i]);
	}
	for (int i = 1; i <= M; i++) {
		for (int d = 1; d <= 4; d++) {//i�� ����� �����¿�
			for (int pd = 1; pd <= 4; pd++) {// d������ �켱����
				scanf("%d", &priority_dir[i][d][pd]);
			}
		}
		sharks.push({ i, shark_first_loc[i], shark_first_dir[i] });
	}
}

void print_smell(int t) {
	printf("[time : %d]\n", t);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%d(%d)< ", sea[i][j].first, sea[i][j].second);
		}
		printf("\n");
	}
}

void sharks_move() {
	vector<pair<pair<NODE, int>, bool>> clean;	// ��ǥ, ����
	int chk[NMAX+5][NMAX+5];	// ��� �ִ��� ������?, ���� ��ȣ�� ��� ����
	// �̵� �ÿ� chk�� ���

	for (int i = 1; i <= N; i++) {
		//memset(chk[i], INF, sizeof(int) * (N+1));
		for (int j = 1; j <= N; j++) {
			chk[i][j] = INF;
			//printf("%d ", chk[i][j]);
		}
		//printf("\n");
	}

	int sy, sx, sd, ny, nx, nd, sharks_size, smell_size;
	bool isSmelled;
	time_limit = 0;
	while (true) {
		sharks_size = sharks.size();
		if (time_limit > TIME_MAX && sharks_size > 1) {
			flag = true;
			break;
		}
		else if (sharks_size == 1) break;

		/*
		print_smell(time_limit);
		printf("\n[time = %d]\n", time_limit);
		printf("�̵� ������ ��� : %d\n", sharks_size);
		*/

		// 1. �� �ʸ��� Ȯ��
		// 2. ����� �̵�
		while (sharks_size--) {
			// 2-1. ����� ����
			SHARK s = sharks.front();		sharks.pop();
			sy = s.node.y;		sx = s.node.x;
			sd = s.dir;
			isSmelled = true;
			// 2-2. ��� ��� üũ
			for (int d = 1; d <= 4; d++) {	// 2-2-1. ����X ��� Ž��
				nd = priority_dir[s.num][sd][d];
				/*
					s.num�� ���� sd ������ ������ �ִµ�
					�� ������ ������ ���� ��, s.num����� �켱���� ���� �������
				*/
				ny = sy + dy[nd];
				nx = sx + dx[nd];
				if (sea[ny][nx].first != 0) continue;	// �׵θ� or ����O

				// ������ ��� �� �� �ִ� ��Ȳ
				isSmelled = false;
				if (chk[ny][nx] == INF) {
					chk[ny][nx] = s.num;
					clean.push_back({ {{ny, nx}, nd }, true });	// �Ŀ� chk�迭 �ʱ�ȭ���ֱ� ����
				}
				else {
					chk[ny][nx] = min(chk[ny][nx], s.num);	// �� ���� ������ ��� ���(���⿡�� ���ŵǾ� �������� ��ȣ�� �Ѱܳ��� �Ǵ� �����!)
				}
				break;
			}
			if (isSmelled) {
				for (int d = 1; d <= 4; d++) {	// 2-2-2. ����O��� �ڱ� ���� ������
					nd = priority_dir[s.num][sd][d];
					ny = sy + dy[nd];
					nx = sx + dx[nd];
					if (sea[ny][nx].second == s.num) {
						chk[ny][nx] = s.num;
						clean.push_back({ {{ny, nx}, nd }, false });
						break;
					}
				}
			}
		}

		//printf("(clean_size) �̵� ������ ��� ���� : %d\n", clean.size());
		
		// 3. �� �̵��� ������ ������ ���� �Ѹ��� �� ���� ���ֱ�
		smell_size = smell.size();

		//printf("(smell_size) ���� �����ִ� ���� : %d\n", smell_size);
		

		while (smell_size--) {
			NODE s = smell.front();		smell.pop();
			//printf("%d %d\n", s.y, s.x);
			sea[s.y][s.x].first = sea[s.y][s.x].first - 1;
			if (sea[s.y][s.x].first == 0) sea[s.y][s.x].second = 0;
			else smell.push(s);
		}
		for (pair<pair<NODE, int>, bool> n : clean) {
			ny = n.first.first.y;		nx = n.first.first.x;
			sharks.push({ chk[ny][nx], n.first.first, n.first.second });
			sea[ny][nx] = { K, chk[ny][nx] };
			chk[ny][nx] = INF;
			if(n.second) smell.push({ ny, nx });
		}
		clean.clear();	// init

		//printf("=====================\n");

		time_limit++;
	}
}

void output() { printf("%d", flag ? -1 : time_limit); }

int main() {
	freopen("in.txt", "r", stdin);
	input();
	sharks_move();
	output();
	return 0;
}
#endif