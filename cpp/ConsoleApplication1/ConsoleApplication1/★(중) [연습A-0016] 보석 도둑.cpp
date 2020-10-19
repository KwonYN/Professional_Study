// (��)[����A - 0016] ���� ����
/*
	
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define NKMAX	(300000)

typedef long long ll;
typedef pair<int, int> pii;
pii jewerly[NKMAX+5]; // ���� ����, ���� ����
int T, N, K, bag[NKMAX+5]; // ���� ���� �ɷ�
ll result_val;

void input() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N;) scanf("%d %d", &jewerly[i].first, &jewerly[i].second);
	for (int i = 0; i < K; i++) scanf("%d", &bag[i]);
}

void steal_jewerly() {
	priority_queue<int, vector<int>, greater<int>> pq;
	sort(jewerly, jewerly + N);	// ���� ��������
	sort(bag, bag + K);			// ���� ���� �ɷ� ��������
	result_val = 0LL;
	for (int i = 1; i < K; i++) {
		for (int j = 0; j < N; j++) {
			if (jewerly[j].first <= bag[i]) pq.push(jewerly[j].second);
			else break;
		}
		int val = -1;
		while (!pq.empty()) {
			int boseok = pq.top();		pq.pop();
			if(val < )
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, result_val); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		steal_jewerly();
		output(tc);
	}
	return 0;
}
#endif


#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(300000)

typedef pair<int, int> pii;
typedef long long ll;
int T, N, K;
pii jewerly[NMAX + 5];
int bag[NMAX + 5];
ll sum_price;

void input() {
	sum_price = 0LL;	// �ʱ�ȭ
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &jewerly[i].first, &jewerly[i].second);
	}
	for (int i = 0; i < K; i++) {
		scanf("%d", &bag[i]);
	}
}

void operation() {
	int pq_idx = 0;
	// pq������ jewerly[]�� price�� ���� ū ���� pop�� �� �ֵ���!! == max heap
	priority_queue<int, vector<int>, less<int>> pq;
	// ���� �������� �������� ����
	sort(bag, bag + K);
	sort(jewerly, jewerly + N);
	for (int i = 0; i < K; i++) printf("%d ", bag[i]);
	printf("\n");
	for (int i = 0; i < N; i++) printf("%d ", jewerly[i].first);
	printf("\n");
	for (int i = 0; i < K; i++) {
		while (pq_idx < N && jewerly[pq_idx].first <= bag[i]) {
			pq.push(jewerly[pq_idx++].second);
		}
		if (!pq.empty()) {
			sum_price += (1LL * pq.top());
			pq.pop();
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, sum_price); }

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