// (�߻�) [����P-0070] ���൹ ���� 
// �������� : https://m.blog.naver.com/ndb796/221236874984
/*
	(����)
	�� ���൹���� �����ؼ� ���ἱ�� ���� ������ ��,
	���� ������ ���� ���� ���� ������ ���� �Ǵ� ���� �ݺ��ؼ�
		(���� �׸����� ���� ���൹���� ������ ���൹�� �����̴� ���� ����)
	���� ���൹�� ���ƿ� �� �ִ� ���� ����.
	=> �� �� ����~~��� �����غ���!! ����Ŭ�� ���ٴ� �Ҹ��̴�!!
*/
#if 0
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define MMAX	(200010)

typedef long long ll;
typedef pair<int, pair<int, int>> pipii;
typedef pair<pair<int, int>, pair<int, int>> ppiipii;
int T, N, M, K;
int indegree[NMAX], order, result[NMAX];
vector<pipii> edges[NMAX];
ll total_score;
ppiipii save[MMAX];
bool isPicked[NMAX];

void print_indegree() {
	int cnt = 0;
	printf("print_indegree\n");
	for (int i = 1; i <= N; i++) {
		cnt += indegree[i];
		printf("%d ", indegree[i]);
	}
	printf("\n");
	printf("indegree ���� �� �� == cnt ? : %s\n", (cnt == M) ? "True" : "False");
}

void init() {
	total_score = 0LL;		order = 0;
	for (int i = 1; i <= N; i++) {
		edges[i].clear();
		indegree[i] = result[i] = 0;
		isPicked[i] = false;
	}
}

void input() {
	int a, b, p, q, save_cnt = 0;
	scanf("%d %d %d", &N, &M, &K);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &a, &b, &p, &q);
		if (p > q) {
			edges[a].push_back({ p, {b, q} });
			indegree[b]++;
		}
		else if (p < q) {
			edges[b].push_back({ q, {a, p} });
			indegree[a]++;
		}
		else {
			save[++save_cnt] = { {a, p}, {b, q} };
		}
	}
	bool flag;
	for (int i = 1; i <= save_cnt; i++) {
		ppiipii tmp = save[i];
		a = tmp.first.first;
		b = tmp.second.first;
		p = tmp.first.second;
		q = tmp.second.second;
		flag = true;
		for (pipii edge : edges[a]) {
			if (edge.second.first == b) {
				flag = false;
				edges[a].push_back({ p, { b, q } });
				indegree[b]++;
				break;
			}
		}
		if (flag) {
			edges[b].push_back({ q, { a, p } });
			indegree[a]++;
		}
	}
}

void pick_joyak() {
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) {
			pq.push(i);
			isPicked[i] = true;
		}
	}
	while (!pq.empty()) {
		int out = pq.top();		pq.pop();
		result[++order] = out;
		//printf("%d ", out);
		//if (order == N) printf("���⿡�� ��!\n");
		for (pipii edge : edges[out]) {
			total_score += 1LL * edge.first;
			if (--indegree[edge.second.first] == 0) {
				pq.push(edge.second.first);
				isPicked[edge.second.first] = true;
			}
		}
	}
	//printf("\n");
	for (int i = 1; i <= N; i++) {
		if (!isPicked[i]) result[++order] = i;
	}
}

void print_result() {
	printf("N = %d\n", N);
	printf("�ڡڡڡڡڡڡڡ�order = %d�ڡڡڡڡڡ�\n", order);
	printf("print_result\n");
	printf("[%d]\n", K);
	for (int i = 1; i <= N; i++) {
		if (i == K) printf("��%d�� ", result[i]);
		else printf("%d ", result[i]);
	}
	printf("\n");
}

void output(int tc) { printf("#%d %lld %d\n", tc, total_score, result[K]); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		//print_indegree();
		pick_joyak();
		//print_result();
		output(tc);
	}
	return 0;
}
#endif