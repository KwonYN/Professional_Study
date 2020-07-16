// (�߻�) [����P-0067] ���� ū �ִ� ���
/*
	����(E)�� �� ������? : (N-1)*N/2 < 13000 < 2^14 
	���ͽ�Ʈ��? : E*logE = �� N^2

	��....
	������� �������� ���������� �ʴٴ� ���� ��� ���̽��� �������־�� �ϴ� ���ε�
	��� ���-������ �� ������ �ִܰŸ��� �����ִ� �˰�����
		�ٷ� �÷��̵�-���� �˰���..!!
	������ �ð����⵵�� N^3�� ���� �����Ѵٸ�,
		N�� ũ�Ⱑ 500�̰�, ���ɰ� �� 20�� ������
		�־��� ��� 1.25�� * 20 == 25�� == 25��...
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(500)	// N^3 == 1.25��;;

typedef long long ll;
int T, N;
int deleted[NMAX+5];
ll pre_edges[NMAX+5][NMAX+5], edges[NMAX+5][NMAX+5];
const ll INF = 0x7fffffffffffffffLL;

void input() {
	long long w;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &deleted[i]);	// �ᱹ ��� ��/������ ������ ��
	}
	for (int i = 1; i < N; i++) {
		for (int j = i + 1; j <= N; j++) {
			scanf("%lld", &w);
			if (w == 0LL) w = INF;
			pre_edges[i][j] = pre_edges[j][i] = w;
		}
	}
}

void pre_process(int start) {
	int s, e;
	for (int i = start; i <= N; i++) {
		s = deleted[i];
		for (int j = start; j <= N; j++) {
			e = deleted[j];
			edges[i][j] = pre_edges[s][e];
			//printf("%lld ", edges[i][j]);
		}
		//printf("\n");
	}
}

void print_edges(int start) {
	printf("\ndeleted : %d\n", deleted[start]);
	printf("print_edges\n");
	for (int i = start; i <= N; i++) {
		for (int j = start; j <= N; j++) {
			printf("%lld ", edges[i][j]);
		}
		printf("\n");
	}
	printf("�� ");
}

void floyd_warshall(int tc) {
	ll max_min_path;
	printf("#%d", tc);
	for (int k = 1; k <= N; k++) {
		// �ʱ�ȭ
		pre_process(k);
		// �÷��̵� ���� : ��� �� �ִܰŸ� ���ϱ�
		for (int i = k; i <= N; i++) {
			if (edges[i][k] == INF) continue;
			for (int j = k; j <= N; j++) {
				if (edges[k][j] == INF) continue;
				if (i == j) continue;
				edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
			}
		}
		print_edges(k);
		// ���� ū �ִܰ�� ���ϱ�
		max_min_path = -1;
		for (int i = k; i <= N; i++) {
			for (int j = k; j <= N; j++) {
				if (edges[i][j] == INF) continue;
				max_min_path = max(max_min_path, edges[i][j]);
			}
		}
		printf(" %lld", max_min_path);
	}
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		floyd_warshall(tc);
	}
	return 0;
}
#endif


#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(500)	// N^3 == 1.25��;;

typedef long long ll;
int T, N;
int deleted[NMAX+5];
ll pre_edges[NMAX+5][NMAX+5], edges[NMAX+5][NMAX+5];
const ll INF = 0x7fffffffffffffffLL;
ll max_min_path[NMAX+5];

void input() {
	long long w;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &deleted[i]);	// �ᱹ ��� ��/������ ������ ��
	}
	for (int i = 1; i < N; i++) {
		for (int j = i + 1; j <= N; j++) {
			scanf("%lld", &w);
			if (w == 0LL) w = INF;
			pre_edges[i][j] = pre_edges[j][i] = w;
		}
	}
}

void pre_process() {
	int s, e;
	for (int i = 1; i <= N; i++) {
		s = deleted[N+1-i];
		for (int j = 1; j <= N; j++) {
			e = deleted[N+1-j];
			edges[i][j] = pre_edges[s][e];
		}
		max_min_path[i] = -1LL;	// �ʱ�ȭ
	}
}

void floyd_warshall() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			if (edges[i][k] == INF) continue;
			for (int j = 1; j <= N; j++) {
				if (edges[k][j] == INF) continue;
				if (i == j) continue;
				edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
			}
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= k; j++) {
				if (edges[i][j] == INF) continue;
				max_min_path[k] = max(max_min_path[k], edges[i][j]);
			}
		}
	}
}

void output(int tc) { 
	printf("#%d", tc);
	for (int i = N; i >= 1; i--) {
		printf(" %lld", max_min_path[i]);
	}
	printf("\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		pre_process();
		floyd_warshall();
		output(tc);
	}
	return 0;
}
#endif


