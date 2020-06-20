// ★★★(중상) [기출P-0041] K-Heap 슈퍼이벤트 
// Indexed Tree를 응용한 문제!!
#if 01

#include <cstdio>
#define NMAX	100000
#define QMAX	300000

int T, Q;
int card_tree[NMAX*4];
int maldan;

void add_card(int n)
{
	int idx = maldan + n - 1;
	card_tree[idx]++;
	while (idx > 1)
	{
		idx /= 2;
		//card_tree[idx] = card_tree[idx<<1] + card_tree[(idx<<1)|1];
		card_tree[idx]++;
	}
}

void del_card(int n)
{
	int idx = maldan + n - 1;
	card_tree[idx]--;
	while (idx > 1)
	{
		idx /= 2;
		//card_tree[idx] = card_tree[idx<<1] + card_tree[(idx<<1)|1];
		card_tree[idx]--;
	}
}

int find_dangchum(int order)
{
	int idx = 1;
	int result;

	while (idx < maldan)
	{
		if (card_tree[idx<<1] >= order)
		{
			idx <<= 1;
			//if (card_tree[idx] != order) order -= card_tree[idx];
		}
		else
		{
			idx <<= 1;
			order -= card_tree[idx];
			idx |= 1;
		}
	}
	result = idx - maldan + 1;
	del_card(result);
	return result;
}

void input()
{
	int a, XK;

	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++)
	{
		scanf("%d %d", &a, &XK);
		if (a == 1) add_card(XK);
		else printf("%d ", find_dangchum(XK));
	}
}

void init()
{
	for (int i = 1; i < 2 * maldan; i++) card_tree[i] = 0;
}

int main()
{
	scanf("%d", &T);
	for (maldan = 1; maldan < NMAX; maldan *= 2);
	for (int tc = 1; tc <= T; tc++)
	{
		printf("#%d ", tc);
		input();
		init();
		printf("\n");
	}

	return 0;
}

#endif
