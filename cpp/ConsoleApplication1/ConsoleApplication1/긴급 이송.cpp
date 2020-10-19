// ��� �̼�
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(3010)
#define INF		(1LL<<62)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> ppiii;
typedef pair<ll, int> pli;
typedef pair<pli, pii> pplipii;
int T, N, M, K, S, F;
vector<pii> edges[NMAX];
vector<ppiii> reverse_edges[NMAX];
ll tme[NMAX][5], result_time;
int cst[NMAX][5], result_cost;

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		reverse_edges[i].clear();
		for (int j = 0; j < 4; j++) {
			tme[i][j] = INF;
			cst[i][j] = 55;
		}
	}
	result_time = INF;	result_cost = 55;
}

void input() {
	int a, b, c, d;
	scanf("%d %d %d %d %d", &N, &M, &K, &S, &F);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		edges[a].push_back({ c, b });
		reverse_edges[b].push_back({ {c, d}, a });
		/*	a -> b
			c : �ɸ��� �ð�
			d : ���� �� ���� ��� */
	}
}

void operation() {
	// { { �ð�, ��� }, { ���� Ƚ��, ��� } }
	priority_queue<pplipii, vector<pplipii>, greater<pplipii>> pq;
	pq.push({ {0LL, S}, {0, 0} });
	tme[S][0] = 0LL;	cst[S][0] = 0;
	while (!pq.empty()) {
		pplipii cur = pq.top();		pq.pop();
		ll t = cur.first.first;			// ���� ���� �ð�
		int cur_node = cur.first.second;// ���� ���
		int count = cur.second.first;	// ���� ���� Ƚ��
		int cost = cur.second.second;	// ���� ���� ���
		if (cur_node == F) {
			result_time = t;
			result_cost = cost;
			break;
		}

		// ��� ���� ���ϰ� ����
		for (pii nex : edges[cur_node]) {
			int tt = nex.first;			// �������� ���� �ð�
			int nex_node = nex.second;	// ���� ���

			ll chk = t + 1LL*tt;
			if (tme[nex_node][0] > chk) {
				tme[nex_node][0] = chk;
				if (cst[nex_node][0] > cost) cst[nex_node][0] = cost;
				pq.push({ {chk, nex_node}, {0, cost} });
			}
			else if (cst[nex_node][0] > cost) {
				cst[nex_node][0] = cost;
				pq.push({ {chk, nex_node}, {0, cost} });
			}
		}
		if (count < 3) {	// 3������ �������� ���������� �� ��
			// ��� �����ϰ� ����
			for (ppiii nex : reverse_edges[cur_node]) {
				int tt = nex.first.first;	// �������� ���� �ð�
				int c = nex.first.second;	// �������� ���� ���
				int nex_node = nex.second;	// ���� ���

				int chk_cost = cost + c;
				if (chk_cost > K) continue;	// ������ �Ѿ�� �� ��
				
				ll chk_time = t + 1LL * tt;
				if (tme[nex_node][count+1] > chk_time) {
					tme[nex_node][count+1] = chk_time;
					if (cst[nex_node][count+1] > chk_cost) cst[nex_node][count+1] = chk_cost;
					pq.push({ {chk_time, nex_node}, {count+1, chk_cost} });
				}
				else if (cst[nex_node][count+1] > chk_cost) {
					cst[nex_node][count+1] = chk_cost;
					pq.push({ {chk_time, nex_node}, {count+1, chk_cost} });
				}
			}
		}
	}
}

void output(int tc) {
	printf("#%d ", tc);
	if (result_time == INF) printf("-1\n");
	else printf("%lld %d\n", result_time, result_cost);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
	}
	return 0;
}
#endif