// (중상) [모의P-0002] 답글의 수_ver.2
/*
	명령의 내용 중 이미 삭제된 글에 답글을 달거나,
	삭제된 글의 답글 수를 요청하거나,
	이미 삭제된 글을 또 삭제하는 명령은 주어지지 않는다.
*/
// 잘못..ㅠ
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MMAX	(100010)

typedef long long ll;
typedef pair<int, int> pii;
int T, M, add_no;
pii query[MMAX];
vector<int> reply[MMAX];
pii numbering[MMAX];
ll fenwick_tree[MMAX];
int num;
ll result_cnt;

void init() {
	for (int i = 0; i <= add_no; i++) {
		reply[i].clear();
		numbering[i] = { 0, 0 };
		fenwick_tree[i] = 0;
	}
	add_no = num = result_cnt = 0;
}

void input_() {
	int q, n;
	scanf("%d", &M);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &q, &n);
		query[i] = { q, n };
		if (q == 1) {
			reply[n].push_back(++add_no);
		}
	}
}

void dfs_numbering(int n) {
	numbering[n].first = num++;
	for (int no : reply[n]) {
		dfs_numbering(no);
	}
	numbering[n].second = num-1;
	//printf("[%d] %d -> %d\n",n, numbering[n].first, numbering[n].second);
}

void update(int idx, int val) {
	while (idx <= add_no) {
		fenwick_tree[idx] += val;
		idx += idx & -idx;
	}
}

int get_sum(int idx) {
	int sum = 0;
	while (idx) {
		sum += fenwick_tree[idx];
		idx -= idx & -idx;
	}
	return sum;
}

void get_result() {
	int order = 0;
	for (int i = 1; i <= M; i++) {
		pii q = query[i];
		//printf("%d %d\n", q.first, q.second);
		if (q.first == 1) {
			++order;
			update(numbering[order].first, 1);
			//printf("[%d] %d -> %d\n", q.second, numbering[q.second].first, numbering[q.second].second);
		}
		else if (q.first == 2) {
			update(numbering[q.second].first, -1);
		}
		else if (q.first == 3) {
			result_cnt += get_sum(numbering[q.second].second) - get_sum(numbering[q.second].first);
		}
	}
}

void output(int tc) { printf("#%d %d\n", tc, result_cnt); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();			// O(M)
		dfs_numbering(0);	// O(M)
		get_result();		// O(M*logM) ... ?
		output(tc);
	}
	return 0;
}
#endif

#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MMAX	(100010)

typedef long long ll;
typedef pair<int, int> pii;
int T, M;
pii query[MMAX];
vector<int> node[MMAX];
int add_node, numbering, in[MMAX], out[MMAX];
int seg_tree[MMAX*3], leaf_node[MMAX];
ll result_cnt;

void init() {
	for (int i = 0; i <= add_node; i++) {
		node[i].clear();
	}
	add_node = numbering = 0;
	result_cnt = 0LL;
}

void input() {
	int q, n;
	scanf("%d", &M);
	init();
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &q, &n);
		if (q == 1) {
			node[n].push_back(++add_node);
			query[i] = { q, add_node };
		}
		else query[i] = { q, n };
	}
}

void dfs_numbering(int no) {
	in[no] = numbering++;
	for (int n : node[no]) dfs_numbering(n);
	out[no] = numbering - 1;
}

void init_tree(int s, int e, int tree_idx) {
	seg_tree[tree_idx] = 0;
	if (s == e) {
		leaf_node[s] = tree_idx;
		return;
	}
	int m = (s + e) / 2;
	init_tree(s, m, tree_idx << 1);
	init_tree(m + 1, e, (tree_idx << 1) | 1);
}

void update_tree(int tree_idx) {
	while (tree_idx) {
		seg_tree[tree_idx]++;
		tree_idx >>= 1;
	}
}

void delete_tree(int s, int e, int l, int r, int tree_idx) {
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		int tmp = seg_tree[tree_idx];
		while (tree_idx) {
			seg_tree[tree_idx] -= tmp;
			tree_idx >>= 1;
		}
		return;
	}
	int m = (s + e) / 2;
	delete_tree(s, m, l, r, tree_idx << 1);
	delete_tree(m + 1, e, l, r, (tree_idx << 1) | 1);
}

int get_sum(int s, int e, int l, int r, int tree_idx) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return seg_tree[tree_idx];
	int m = (s + e) / 2;
	return get_sum(s, m, l, r, tree_idx << 1) 
		 + get_sum(m + 1, e, l, r, (tree_idx << 1)| 1);
}

void operation_query() {
	init_tree(in[0], out[0], 1);
	for (int i = 1; i <= M; i++) {
		pii q = query[i];
		if (q.first == 1) {
			update_tree(leaf_node[in[q.second]]);
		}
		else if (q.first == 2) {
			delete_tree(in[0], out[0], in[q.second], out[q.second], 1);
		}
		else {
			result_cnt += (1LL* get_sum(in[0], out[0], in[q.second], out[q.second], 1) - 1LL);
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, result_cnt); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		dfs_numbering(0);
		operation_query();
		output(tc);
	}
	return 0;
}
#endif

// 이전에 풀었던 정답 코드
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NODE_MAX	(1<<16)

typedef long long ll;
int T, M, node_cnt;
vector<int> edges[NODE_MAX];
int cmd_set[NODE_MAX << 1][2];
int left[NODE_MAX], right[NODE_MAX], node_order;
int tree[NODE_MAX << 1], leaf_node_idx[NODE_MAX];
ll total_sum;

void init() {
	for (int i = 0; i <= node_cnt; i++) {
		edges[i].clear();
		left[i] = right[i] = leaf_node_idx[i] = 0;
	}
}

void input() {
	int command, X;
	node_cnt = node_order = 0;
	total_sum = 0LL;
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &command, &X);
		cmd_set[i][0] = command;
		if (command == 1) {
			edges[X].push_back(++node_cnt);
			cmd_set[i][1] = node_cnt;
		}
		else cmd_set[i][1] = X;
	}
}

void dfs(int node) {	// get node index for tree
	left[node] = node_order++;
	for (int next : edges[node]) dfs(next);
	right[node] = node_order - 1;
}

void make_tree(int s, int e, int tree_idx) {	// initiate tree
	tree[tree_idx] = 0;
	if (s == e) {
		leaf_node_idx[s] = tree_idx;
		//printf("tree_idx = %d\n", tree_idx);
		return;
	}
	int m = (s + e) / 2;
	make_tree(s, m, tree_idx << 1);
	make_tree(m + 1, e, (tree_idx << 1) | 1);
}

void update_node(int tree_idx) {
	while (tree_idx) {
		tree[tree_idx]++;
		tree_idx >>= 1;
	}
}

void delete_node(int s, int e, int l, int r, int tree_idx) {
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		int tmp = tree[tree_idx];
		while (tree_idx >= 1) {
			tree[tree_idx] -= tmp;
			tree_idx >>= 1;
		}
		return;
	}
	int m = (s + e) / 2;
	delete_node(s, m, l, r, tree_idx << 1);
	delete_node(m + 1, e, l, r, (tree_idx << 1) | 1);
}

int get_child_cnt(int s, int e, int l, int r, int tree_idx) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return tree[tree_idx];
	int m = (s + e) / 2;
	return get_child_cnt(s, m, l, r, tree_idx << 1) + get_child_cnt(m + 1, e, l, r, (tree_idx << 1) | 1);
}

void operation() {
	int command, n;
	dfs(0);
	make_tree(left[0], right[0], 1);
	for (int i = 1; i <= M; i++) {
		command = cmd_set[i][0];		n = cmd_set[i][1];
		if (command == 1) {
			update_node(leaf_node_idx[left[n]]);
		}
		else if (command == 2) {
			delete_node(left[0], right[0], left[n], right[n], 1);
		}
		else {
			//printf("X:%d [ left:%d ~~ right:%d ]  ", n, left[n], right[n]);
			//printf("total_sum : %lld ▶ ", total_sum);
			/*for(int i = 1; i <= node_cnt; i++) printf(" %2d", i);
			printf("\n");
			for(int i = 1; i <= node_cnt; i++) printf(" %2d", tree[leaf_node_idx[i]]);
			printf("\n");*/
			total_sum += (get_child_cnt(left[0], right[0], left[n], right[n], 1) * 1LL - 1LL);
			//printf("%lld\n", total_sum);
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_sum); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		operation();
		output(tc);
		init();
	}
	return 0;
}
#endif