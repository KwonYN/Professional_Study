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
		int cur = out.second.first;		// 이 노드까지 옴
		ll dist = out.first;			// 이 노드까지의 누적 시간
		int climate = out.second.second;// 이 노드에서의 현 날씨 상황
		if (cur == N) return;

		for (pipii n : edges[cur]) {
			int isTer = n.second.second;// 1 : 터널, 0 : 일반 도로
			int d = n.first;			// 그 간선의 길이
			int next = n.second.first;	// 그 간선에 연결되어 있는 다른 노드

			if (isTer) {	// 터널은 걍 감
				/*ll chk = dijk[cur].first + 1LL * d;
				if (dijk[next].first > chk) {
					dijk[next] = chk;
					pq.push({ chk, {next, (climate+d)%P_2} });
				}*/
			}
			else {	// 일반 도로라면?
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
        // 날씨 iteration을 구하기 위한 flag
        int weatherFlag = dist[here] / p;
        // 이전 단계에서 차를 운전하고 남은 step (날씨가 맑을때는 이 residualStep만큼 no extra cost로 더 이동할 수 있다)
        int residualStep = p - (dist[here] % p);
        // 0번째나 짝수번째 날씨 iteration이라면 날씨가 맑은 상태임 <-> 홀수번째면 흐린 날씨
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
                    // 현재 날씨가 맑고, residualStep보다 다음 도로 길이가 더 길면, 기본 residualStep만큼 가야하니까 waitTime에 p를 더해주고,

                    // (다음 도로 길이에서 residualStep 길이를 빼준 거리) 기준으로 쉬는 시간 연산
                    if (nextCost > residualStep) {
                        stopTime += ((nextCost - residualStep - 1) / p) * p;
                        if (residualStep)
                            waitTime += p;
                    }
                }
                else {
                    // 현재 날씨가 흐리면 residualStep만큼 기다렸다가 출발해야 함
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

// 답이 틀린데..(위에 코드...) 내가 바꿔보자!!;;; Re해야함!
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
        int here = x.second.first;          // 이 노드에 오기까지
        ll hereCost = x.first;              // 누적 시간
        int isHereTunnel = x.second.second;
        if (dist[here] < hereCost)
            continue;
        // 날씨 iteration을 구하기 위한 flag
        ll weatherFlag = dist[here] / (1LL*P);
        // 이전 단계에서 차를 운전하고 남은 step (날씨가 맑을때는 이 residualStep만큼 no extra cost로 더 이동할 수 있다)
        ll residualStep = dist[here] % (1LL*P);
        // 0번째나 짝수번째 날씨 iteration이라면 날씨가 맑은 상태임 <-> 홀수번째면 흐린 날씨
        if (!(weatherFlag & 1))
            isWeatherClear = true;  // 맑은 날씨
        else
            isWeatherClear = false; // 흐린 날씨

        for (auto y : vc[here]) {
            int next = y.first.first;           // 다음 노드
            ll nextCost = (ll)y.first.second;   // 그 간선의 거리
            int isNextTunnel = y.second;        // 그 간선은 터널?
            ll waitTime = 0, stopTime = 0;
            if (!isNextTunnel) {    // 일반 도로라면,
                if (isWeatherClear) {  
                    // 현재 날씨가 맑고, residualStep보다 다음 도로 길이가 더 길면,
                    // 기본 residualStep만큼 가야하니까 waitTime에 p를 더해주고,

                    // (다음 도로 길이에서 residualStep 길이를 빼준 거리) 기준으로 쉬는 시간 연산
                    if (nextCost > weatherFlag*P) {
                        stopTime += ((nextCost - residualStep - 1) / P) * P;
                        if (residualStep)
                            waitTime += P;
                    }
                }
                else {
                    // 현재 날씨가 흐리면 residualStep만큼 기다렸다가 출발해야 함
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