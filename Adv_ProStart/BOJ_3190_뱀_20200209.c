#include <stdio.h>
#define KMAX	110
#define NMAX	110
#define LMAX	110
#define XMAX	10010

void input(void);
void move_snake(void);

typedef struct { int second; char dir; }COMMAND;
COMMAND c[LMAX];

int N, K, L;
int map[NMAX][NMAX];
int snake_y[KMAX], snake_x[KMAX];
int snake_len;
int dir_y[4] = {-1, 1, 0, 0};
int dir_x[4] = {0, 0, -1, 1};
int dir_L[4] = {2, 3, 1, 0};
int dir_D[4] = {3, 2, 0, 1};
int time;

int main(void)
{
	input();
	move_snake();
	printf("%d\n", time+1);

	return 0;
}

void input(void)
{
	int i;
	int tmp_y, tmp_x;

	time = 0, snake_len = 1;
	scanf("%d", &N);
	for(i = 0; i <= N+1; i++)	// wall
		map[0][i] = map[N+1][i] = map[i][0] = map[i][N+1] = -1;
	scanf("%d", &K);
	for(i = 0; i < K; i++)
	{
		scanf("%d %d", &tmp_y, &tmp_x);
		map[tmp_y][tmp_x] = 1;	// apple
	}
	scanf("%d", &L);
	for(i = 0; i < L; i++) scanf("%d %c", &c[i].second, &c[i].dir);
}

void move_snake(void)
{
	int sy = 1, sx = 1, sd = 3, stime = 0;
	snake_y[0] = sy, snake_x[0] = sx;
	map[sy][sx] = -1;
	int i;

	while(1)
	{
		/*
		int r, cc;
		printf("time = %d, snake_len = %d\n", time, snake_len);
		for(r = 1; r <= N; r++)
		{
			for(cc = 1; cc <= N; cc++)
			{
				printf("%d ", map[r][cc]);
			}
			printf("\n");
		}
		printf("\n");
		printf("snake_y\n");
		for(r = 0; r < snake_len; r++) printf("%d ", snake_y[r]);
		printf("\nsnake_x\n");
		for(r = 0; r < snake_len; r++) printf("%d ", snake_x[r]);
		printf("\n=====================\n\n");
		*/

		sy += dir_y[sd];
		sx += dir_x[sd];
		if(map[sy][sx] == -1) break;
		if(map[sy][sx] == 1)	// if apple?
		{
			snake_y[++snake_len-1] = sy;
			snake_x[snake_len-1] = sx;
		}
		else			// if not?
		{
			map[snake_y[0]][snake_x[0]] = 0;
			for(i = 0; i < snake_len-1; i++)
			{
				snake_y[i] = snake_y[i+1];
				snake_x[i] = snake_x[i+1];
			}
			snake_y[snake_len-1] = sy;
			snake_x[snake_len-1] = sx;
		}
		map[sy][sx] = -1;
		time++;
		if(stime < L && time == c[stime].second)
		{
			if(c[stime].dir == 'L') sd = dir_L[sd];
			else sd = dir_D[sd];
			stime++;
		}
	}
}
