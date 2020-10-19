#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(10010)
#define MMAX	(40010)
#define INTINF	(0x7fffffff)

typedef long long ll;
typedef pair<int, pair<int, int>> pipii;
typedef pair<ll, pair<int, int>> plpii;
int T, N, M, P, P_2;
vector<pipii> edges[NMAX];
pair<ll, int> dijk[NMAX];
const ll INF = (1LL << 61);

void init() {
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		dijk[i] = { INF, INTINF };
	}
	P_2 = P*2;
}

void input() {
	int a, b, c, d;
	scanf("%d %d %d", &N, &M, &P);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		edges[a].push_back({ c, {b, d} });
		edges[b].push_back({ c, {a, d} });
	}
}

void dijkstra() {
	priority_queue<plpii, vector<plpii>, greater<plpii>> pq;
	dijk[1] = { 0LL, 0 };		pq.push({ 0LL, {1, 0} });
	while (!pq.empty()) {
		plpii out = pq.top();		pq.pop();
		int cur = out.second.first;		// �� ������ ��
		ll dist = out.first;			// �� �������� ���� �ð�
		int climate = out.second.second;// �� ��忡���� �� ���� ��Ȳ
		if (cur == N) return;

		for (pipii n : edges[cur]) {
			int isTer = n.second.second;// 1 : �ͳ�, 0 : �Ϲ� ����
			int d = n.first;			// �� ������ ����
			int next = n.second.first;	// �� ������ ����Ǿ� �ִ� �ٸ� ���

			if (isTer) {	// �ͳ��� �� ��
				/*ll chk = dijk[cur].first + 1LL * d;
				if (dijk[next].first > chk) {
					dijk[next] = chk;
					pq.push({ chk, {next, (climate+d)%P_2} });
				}*/
			}
			else {	// �Ϲ� ���ζ��?
				int tmp1 = d/P;
				int tmp2 = d%P;
				if (!tmp1) {
					/*if (P - climate >= d) {
						ll chk = dijk[cur] + 1LL * d;
					}*/
				}
			}
		}
	}
}

void output(int tc) { printf("#%d %lld\n"), tc, dijk[N]; }

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		dijkstra();
		output(tc);
	}
}
#endif

// ?
#if 0
#pragma warning(disable: 4996)
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

int T, n, m, p;
vector <pair<pair<int, int>, int>> vc[10001];
ll dist[10001];

void dijkstra(int start) {
    priority_queue <pair<pair<ll, int>, int>> pq;
    dist[start] = 0;
    pq.push({ {0,start},1 });
    bool isWeatherClear;
    while (!pq.empty()) {
        auto x = pq.top(); pq.pop();
        int here = x.first.second;
        ll hereCost = -x.first.first;
        int isHereTunnel = x.second;
        if (dist[here] < hereCost)
            continue;
        // ���� iteration�� ���ϱ� ���� flag
        int weatherFlag = dist[here] / p;
        // ���� �ܰ迡�� ���� �����ϰ� ���� step (������ �������� �� residualStep��ŭ no extra cost�� �� �̵��� �� �ִ�)
        int residualStep = p - (dist[here] % p);
        // 0��°�� ¦����° ���� iteration�̶�� ������ ���� ������ <-> Ȧ����°�� �帰 ����
        if (!(weatherFlag & 1))
            isWeatherClear = true;
        else
            isWeatherClear = false;

        for (auto y : vc[here]) {
            int next = y.first.first;
            ll nextCost = (ll)y.first.second;
            int isNextTunnel = y.second;
            ll waitTime = 0, stopTime = 0;
            if (!isNextTunnel) {
                if (isWeatherClear) {
                    // ���� ������ ����, residualStep���� ���� ���� ���̰� �� ���, �⺻ residualStep��ŭ �����ϴϱ� waitTime�� p�� �����ְ�,

                    // (���� ���� ���̿��� residualStep ���̸� ���� �Ÿ�) �������� ���� �ð� ����
                    if (nextCost > residualStep) {
                        stopTime += ((nextCost - residualStep - 1) / p) * p;
                        if (residualStep)
                            waitTime += p;
                    }
                }
                else {
                    // ���� ������ �帮�� residualStep��ŭ ��ٷȴٰ� ����ؾ� ��
                    waitTime += residualStep;
                    stopTime += ((nextCost - 1) / p) * p;
                }
            }
            if (dist[next] > dist[here] + waitTime + stopTime + nextCost) {
                dist[next] = dist[here] + waitTime + stopTime + nextCost;
                pq.push({ {-dist[next], next}, isNextTunnel });
            }
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d%d", &n, &m, &p);
        for (int i = 1; i <= n; i++) {
            vc[i].clear();
            dist[i] = 1e18;
        }
        while (m--) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            vc[a].push_back({ {b, c}, d });
            vc[b].push_back({ {a, c}, d });
        }
        dijkstra(1);
        printf("#%d %lld\n", t, dist[n]);
    }
    return 0;
}
#endif

// ���� Ʋ����..(���� �ڵ�...) ���� �ٲ㺸��!!;;; Re�ؾ���!
#if 0
#pragma warning(disable: 4996)
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define NMAX    (10010)
using namespace std;

typedef long long ll;
typedef pair<ll, pair<int, int>> plpii;
typedef pair<pair<int, int>, int> ppiii;
int T, N, M, P;
vector <ppiii> vc[NMAX];
ll dist[NMAX];
const ll INF = (1LL<<61);

void init() {
    for (int i = 1; i <= N; i++) {
        vc[i].clear();
        dist[i] = INF;
    }
}

void input() {
    int a, b, c, d;
    scanf("%d%d%d", &N, &M, &P);
    init();
    while (M--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        vc[a].push_back({ {b, c}, d });
        vc[b].push_back({ {a, c}, d });
    }
}

void dijkstra(int start) {
    priority_queue <plpii, vector<plpii>, greater<plpii>> pq;
    dist[start] = 0;
    pq.push({ 0LL, {start, 1} });
    bool isWeatherClear;
    while (!pq.empty()) {
        auto x = pq.top(); pq.pop();
        int here = x.second.first;          // �� ��忡 �������
        ll hereCost = x.first;              // ���� �ð�
        int isHereTunnel = x.second.second;
        if (dist[here] < hereCost)
            continue;
        // ���� iteration�� ���ϱ� ���� flag
        ll weatherFlag = dist[here] / (1LL*P);
        // ���� �ܰ迡�� ���� �����ϰ� ���� step (������ �������� �� residualStep��ŭ no extra cost�� �� �̵��� �� �ִ�)
        ll residualStep = dist[here] % (1LL*P);
        // 0��°�� ¦����° ���� iteration�̶�� ������ ���� ������ <-> Ȧ����°�� �帰 ����
        if (!(weatherFlag & 1))
            isWeatherClear = true;  // ���� ����
        else
            isWeatherClear = false; // �帰 ����

        for (auto y : vc[here]) {
            int next = y.first.first;           // ���� ���
            ll nextCost = (ll)y.first.second;   // �� ������ �Ÿ�
            int isNextTunnel = y.second;        // �� ������ �ͳ�?
            ll waitTime = 0, stopTime = 0;
            if (!isNextTunnel) {    // �Ϲ� ���ζ��,
                if (isWeatherClear) {  
                    // ���� ������ ����, residualStep���� ���� ���� ���̰� �� ���,
                    // �⺻ residualStep��ŭ �����ϴϱ� waitTime�� p�� �����ְ�,

                    // (���� ���� ���̿��� residualStep ���̸� ���� �Ÿ�) �������� ���� �ð� ����
                    if (nextCost > weatherFlag*P) {
                        stopTime += ((nextCost - residualStep - 1) / P) * P;
                        if (residualStep)
                            waitTime += P;
                    }
                }
                else {
                    // ���� ������ �帮�� residualStep��ŭ ��ٷȴٰ� ����ؾ� ��
                    waitTime += residualStep;
                    stopTime += ((nextCost - 1) / P) * P;
                }
            }
            if (dist[next] > dist[here] + waitTime + stopTime + nextCost) {
                dist[next] = dist[here] + waitTime + stopTime + nextCost;
                pq.push({ dist[next] ,{next, isNextTunnel} });
            }
        }
    }
}

void output(int tc) { printf("#%d %lld\n", tc, dist[N]); }

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        input();
        dijkstra(1);
        output(tc);
    }
    return 0;
}
#endif