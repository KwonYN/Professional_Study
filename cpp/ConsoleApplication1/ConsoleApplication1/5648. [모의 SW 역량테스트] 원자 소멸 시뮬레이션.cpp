// 5648. [���� SW �����׽�Ʈ] ���� �Ҹ� �ùķ��̼�
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX	(4000)

struct NODE { int y, x; };
struct ATOM { NODE node; int dir, energy; };
int T, N;
int dy[4] = { 1, -1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };
queue<ATOM> atom;
int sum_energy;
pair<int, int> chk[MAX+5][MAX+5];	// ������, ����

void init() {
	sum_energy = 0;
	atom = queue<ATOM>();	// �ʱ�ȭ
}

void input() {
	int x, y, d, e;
	init();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d %d", &x, &y, &d, &e);
		x += 1000, y += 1000;
		x *= 2, y *= 2;	// ������ �� 0 ~ 4000�� ��!!
		atom.push({ { y, x }, d, e });
	}
}

void collide_atom() {
	int ny, nx, d, e, atom_size, max_time = MAX;
	while ( max_time-- && atom.size() ) {
		vector<ATOM> clean;
		atom_size = atom.size();
		while (atom_size--) {
			ATOM a = atom.front();		atom.pop();
			d = a.dir;
			ny = a.node.y + dy[d];
			nx = a.node.x + dx[d];
			e = a.energy;
			if (ny < 0 || ny > MAX || nx < 0 || nx > MAX) continue;
			chk[ny][nx].first += a.energy;
			if (chk[ny][nx].second++ == 0) clean.push_back({ { ny, nx }, d, e });
		}
		for (ATOM at : clean) {
			ny = at.node.y;		nx = at.node.x;
			if (chk[ny][nx].second > 1) sum_energy += chk[ny][nx].first;
			else atom.push(at);
			chk[ny][nx] = { 0, 0 };
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, sum_energy); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		collide_atom();
		output(tc);
	}
	return 0;
}
#endif

// ���� �ڵ�
#if 0
#include <stdio.h>
#define MAXM	(4200)
#define MAXW	(1100)

typedef struct { int y, x, d, e, boundary; }WONJA;
WONJA wonja[MAXW];

void Input(void);
void Operation(void);
void Renew_chk(void);
void Init(void);
void Print_chk(void);

int T, N;
int chk[MAXM][MAXM];
int dy[4] = { 1, -1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int b_cnt;
int total_energy;

int main(void)
{
	int i;

	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		Operation();
		printf("#%d %d\n", i, total_energy);
		Init();
	}

	return 0;
}

void Input(void)
{
	int i;
	int yy, xx, dd, ee;

	total_energy = 0;	// �� ���� ������
	b_cnt = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d %d %d", &xx, &yy, &dd, &ee);
		xx += 1000;		yy += 1000;
		xx *= 2;		yy *= 2;
		wonja[i] = (WONJA){ yy, xx, dd, ee, 0 };
	}
}

void Operation(void)
{
	int t = 0, i;
	int ny, nx, d;

	// ��� �� ������ ��� ������ �ִ� �ð����� �����ϰų�,
	// �������� ������ ���ڵ��� ������ ���� ����, �� ��� ���ڰ� �������� �������� �� ����!
	while ((++t <= 4000) || (b_cnt < N))
	{	// ���ڵ� �� Ȯ���غ�
		for (i = 1; i <= N; i++)
		{
			if (wonja[i].boundary) continue; // �� Ȯ���غ�����, �³װ� Ȯ���� �ʿ䰡 ���� ���¸� �ٷ� �ǳʶ�
			d = wonja[i].d;
			ny = wonja[i].y + dy[d];	nx = wonja[i].x + dx[d];	// ������ ���ο� �̵� ��ġ!
			// ���� ������ �Ѿ��, �� ���� �� ���� ������ ���ٸ� boundary ����ٴ� �÷���
			// (�̴� �״� �÷��׿� ����! ==> ������ �̵���Ű�� ���� ���̱� ����!)
			if (ny < 0 || ny > 4000 || nx < 0 || nx > 4000)
			{
				wonja[i].boundary = 1;
				b_cnt++;
				continue;
			}
			wonja[i].y = ny;	wonja[i].x = nx;
			chk[ny][nx]++;
		}
		Renew_chk();
		//printf("b_cnt = %d\n", b_cnt);
		//printf("[%d] total_energy = %d\n", t, total_energy);
		//Print_chk();
		//getch();
	}
}

void Renew_chk(void)
{
	int i, k, yy, xx;

	for (i = 1; i <= N; i++)
	{
		if (wonja[i].boundary) continue;
		yy = wonja[i].y;	xx = wonja[i].x;
		if (chk[yy][xx] > 1)
		{
			for (k = 1; k <= N; k++)
			{
				if (wonja[k].boundary) continue;
				if ((wonja[k].y == yy) && (wonja[k].x == xx))
				{
					wonja[k].boundary = 1;
					b_cnt++;
					total_energy += wonja[k].e;
				}
			}
		}
		chk[yy][xx] = 0;
	}
}

void Init(void)
{
	int i;

	for (i = 0; i <= N + 1; i++)
	{
		wonja[i] = (WONJA){ 0, 0, 0, 0, 0 };
	}
}

void Print_chk(void)
{
	int i, j;
	//printf("Print_chk\n");
	for (i = 0; i <= 4000; i++)
	{
		for (j = 0; j <= 4000; j++)
		{
			if (chk[i][j]) printf("y = %d, x = %d\n", i, j);
		}
	}
}
#endif