// BOJ_1238_��Ƽ
/*
	������ �л����� ��Ƽ�� �����ϱ� ���� 
		�ɾ�� �ٽ� �׵��� ������ ���ƿ;� �Ѵ�.
	������ �� �л����� ���� �������� �ִ� �ð��� ���� ���⸦ ���Ѵ�.
	�� ���ε��� �ܹ����̱� ������
		�Ƹ� �׵��� ���� ���� ���� �ٸ����� �𸥴�.
	N���� �л��� �� ���� ���µ�
		���� ���� �ð��� �Һ��ϴ� �л��� �������� ���Ͽ���.
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(1010)
#define MMAX	(10010)
#define INF		(0x7fffffff)

typedef pair<int, int> pii;
int N, M, X;
vector<pii> edges[NMAX], reverse_edges[NMAX];
int dist1[NMAX], dist2[NMAX];

int main() {
	freopen("in.txt", "r", stdin);
	int a, b, c;
	// 1. �Է�
	scanf("%d %d %d", &N, &M, &X);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		// �ܹ��� ����
		edges[a].push_back({ c, b });			// X���� ���ư� ��!
		reverse_edges[b].push_back({ c, a });	// X�� �� ��
	}
	// 2. �Ÿ� ���ϱ�
	for (int i = 1; i <= N; i++) dist1[i] = dist2 [i] = INF;	// init
	// 2-1. ������ �� -> X : reverse_edges
	priority_queue<pii, vector<pii>, greater<pii>> pq1;
	pq1.push({ 0, X });		dist1[X] = 0;
	while (!pq1.empty()) {
		pii cur = pq1.top();		pq1.pop();
		for (pii next : reverse_edges[cur.second]) {
			if (dist1[next.second] > dist1[cur.second] + next.first) {
				dist1[next.second] = dist1[cur.second] + next.first;
				pq1.push({ dist1[next.second], next.second });
			}
		}
	}
	// 2-2. X -> �ǵ��ư��� : edges
	priority_queue<pii, vector<pii>, greater<pii>> pq2;
	pq2.push({ 0, X });		dist2[X] = 0;
	while (!pq2.empty()) {
		pii cur = pq2.top();		pq2.pop();
		for (pii next : edges[cur.second]) {
			if (dist2[next.second] > dist2[cur.second] + next.first) {
				dist2[next.second] = dist2[cur.second] + next.first;
				pq2.push({ dist2[next.second], next.second });
			}
		}
	}
	// 3. ���
	int max_stu = 0;
	for (int i = 1; i <= N; i++) {
		//printf("[%d]->[%d] : %d\n", i, X, dist1[i]);
		//printf("[%d]->[%d] : %d\n", X, i, dist2[i]);
		if (dist1[i] + dist2[i] > max_stu) max_stu = dist1[i] + dist2[i];
		//printf("%d\n", max_stu);
		//printf("=======================\n");
	}
	printf("%d\n", max_stu);
	return 0;
}
#endif