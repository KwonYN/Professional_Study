// (중상) [모의P-0002] 답글의 수
/*

*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX	(50000)

typedef long long ll;
int T, M, total_cnt, idx_num;
vector<int> edges[NMAX];
int left[NMAX + 5], right[NMAX];
int tree[NMAX << 1 + 5];
ll total_sum;

void init() {
	for (int i = 0; i <= total_cnt; i++) {
		edges[i].clear();
		left[i] = right[i] = 0;
	}
}

void get_tree_idx(int node) {	// dfs
	left[node] = idx_num++;
	//printf("left[%d] = %d\n", node, idx_num - 1);
	for (int next : edges[node]) get_tree_idx(next);
	right[node] = idx_num - 1;
	//printf("right[%d] = %d\n", node, idx_num - 1);
}

int update(int s, int e, int tree_idx) { // init & update
	if (s == e) {
		if (s == 0) return tree[tree_idx] = 0;
		return tree[tree_idx] = 1;
	}
	int m = (s + e) / 2;
	int a = update(s, m, tree_idx << 1);
	int b = update(m + 1, e, (tree_idx << 1) | 1);
	/*printf("[%d]\n", tree_idx);
	printf("s = %d, e = %d\n", s, e);
	printf("a = %d, b = %d => a+b = %d\n", a, b, a + b);*/
	return tree[tree_idx] = a + b;
}

int get_child_cnt(int s, int e, int l, int r, int tree_idx) {
	if (r < s || e < l) return 0;
	/*if (s == e) {
		if (left[s] == right[s]) return 0;
	}*/
	if (l <= s && e <= r) {
		//printf("seg_tree[%d] = %d\n", tree_idx, seg_tree[tree_idx]);
		return tree[tree_idx];
	}
	int m = (s + e) / 2;
	int a = get_child_cnt(s, m, l, r, tree_idx << 1);
	int b = get_child_cnt(m + 1, e, l, r, (tree_idx << 1) | 1);
	/*printf("[%d]\n", tree_idx);
	printf("s = %d, e = %d\n", s, e);
	printf("l = %d, r = %d\n", l, r);
	printf("a = %d, b = %d => a+b = %d\n", a, b, a + b);
	printf("============================\n");*/
	return a + b;
}

void input() {
	int command, n;
	total_sum = 0LL;	total_cnt = 0;
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &command, &n);
		if (command == 1) {
			edges[n].push_back(++total_cnt);
		}
		else if (command == 2) {
			edges[n].clear();
		}
		else {
			idx_num = 0;
			get_tree_idx(0);
			update(left[0], right[0], 1);
			printf("total_sum_pre = %lld\n", total_sum);
			//printf("l = %d, r = %d\n", left[n], right[n]);
			total_sum += (get_child_cnt(left[0], right[0], left[n], right[n], 1) * 1LL) - 1;
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_sum); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		output(tc);
		init();
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
#define NMAX	(1<<16)

typedef long long ll;
int T, M, total_cnt, idx_num;
vector<int> edges[NMAX];
int left[NMAX + 5], right[NMAX];
int tree[NMAX << 1 + 5];
bool deleted[NMAX];
ll total_sum;

void init() {
	for (int i = 1; i <= total_cnt; i++) {
		edges[i].clear();
		left[i] = right[i] = 0;
		deleted[i] = false;
	}
}

void dfs(int node) {
	left[node] = idx_num++;
	//printf("\n%d ▶", node);
	//for (int next : edges[node]) printf(" %d", next);
	for (int next : edges[node]) {
		if (deleted[next]) continue;
		dfs(next);
	}
	right[node] = idx_num - 1;
}

void tree_init(int s, int e, int tree_idx) {
	tree[tree_idx] = 0;
	if (s == e) {
		if (s != 0) tree[tree_idx] = 1;
		return;
	}
	int m = (s + e) / 2;
	tree_init(s, m, tree_idx << 1);
	tree_init(m + 1, e, (tree_idx << 1) | 1);
}

int make_tree(int s, int e, int tree_idx) {
	if (s == e) return tree[tree_idx];
	int m = (s + e) / 2;
	return tree[tree_idx] = make_tree(s, m, tree_idx << 1)
		+ make_tree(m + 1, e, (tree_idx << 1) | 1);
}

int get_child_cnt(int s, int e, int l, int r, int tree_idx) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return tree[tree_idx];
	int m = (s + e) / 2;
	return get_child_cnt(s, m, l, r, tree_idx << 1)
		+ get_child_cnt(m + 1, e, l, r, (tree_idx << 1) | 1);
}

void input() {
	int command, n;
	total_sum = 0LL;	total_cnt = 0;
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &command, &n);
		if (command == 1) {
			edges[n].push_back(++total_cnt);
		}
		else if (command == 2) {
			edges[n].clear();
			deleted[n] = true;
		}
		else {
			idx_num = 0;
			dfs(0);
			tree_init(left[0], right[0], 1);
			make_tree(left[0], right[0], 1);
			//printf("total_sum : (이전)%lld ▶ ", total_sum);
			total_sum += ((get_child_cnt(left[0], right[0], left[n], right[n], 1) * 1LL) - 1LL);
			//printf("%lld\n", total_sum);
			//printf("======\n");
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_sum); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		output(tc);
		init();
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
#define NMAX	(1<<16)

typedef long long ll;
int T, M, total_cnt, idx_num;
vector<int> edges[NMAX];
int left[NMAX + 5], right[NMAX];
int tree[NMAX << 1 + 5];
bool deleted[NMAX];
ll total_sum;

void init() {
	for (int i = 1; i <= total_cnt; i++) {
		edges[i].clear();
		left[i] = right[i] = 0;
		deleted[i] = false;
	}
}

void dfs(int node) {
	left[node] = idx_num++;
	//printf("\n%d ▶", node);
	//for (int next : edges[node]) printf(" %d", next);
	for (int next : edges[node]) {
		if (deleted[next]) continue;
		dfs(next);
	}
	right[node] = idx_num - 1;
}

void tree_init(int s, int e, int tree_idx) {
	tree[tree_idx] = 0;
	if (s == e) {
		if (s != 0) tree[tree_idx] = 1;
		return;
	}
	int m = (s + e) / 2;
	tree_init(s, m, tree_idx << 1);
	tree_init(m + 1, e, (tree_idx << 1) | 1);
}

int make_tree(int s, int e, int tree_idx) {
	if (s == e) return tree[tree_idx];
	int m = (s + e) / 2;
	return tree[tree_idx] = make_tree(s, m, tree_idx << 1)
		+ make_tree(m + 1, e, (tree_idx << 1) | 1);
}

int get_child_cnt(int s, int e, int l, int r, int tree_idx) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return tree[tree_idx];
	int m = (s + e) / 2;
	return get_child_cnt(s, m, l, r, tree_idx << 1)
		+ get_child_cnt(m + 1, e, l, r, (tree_idx << 1) | 1);
}

void input() {
	int command, n;
	total_sum = 0LL;	total_cnt = 0;
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &command, &n);
		if (command == 1) {
			edges[n].push_back(++total_cnt);
		}
		else if (command == 2) {
			edges[n].clear();
			deleted[n] = true;
		}
		else {
			idx_num = 0;
			dfs(0);
			//tree_init(left[0], right[0], 1);
			//make_tree(left[0], right[0], 1);
			//printf("total_sum : (이전)%lld ▶ ", tota_sum);
			//total_sum += ((get_child_cnt(left[0], right[0], left[n], right[n], 1) * 1LL) - 1LL);
			total_sum += ((right[n] - left[n]) * 1LL);
			//printf("%lld\n", total_sum);
			//printf("======\n");
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_sum); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		output(tc);
		init();
	}
	return 0;
}
#endif


// Last Try
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
		left[i] = right[i] = 0;
	}
}

void input() {
	int command, X;
	node_cnt = node_order = 0;
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &command, &X);
		cmd_set[i][0] = command;
		cmd_set[i][1] = X;
		if (command == 1) edges[X].push_back(++node_cnt);
	}
}

void dfs(int node) {	// get node index for tree
	left[node] = node_order++;
	for (int next : edges[node]) dfs(next);
	right[node] = node_order - 1;
}

int make_tree(int s, int e, int tree_idx) {	// initiate tree
	if (s == e) {
		leaf_node_idx[s] = tree_idx;
		return tree[tree_idx] = 0;
	}
	int m = (s + e) / 2;
	return tree[tree_idx] = make_tree(s, m, tree_idx << 1) + make_tree(m + 1, e, (tree_idx << 1) | 1);
}

void update_node(int tree_idx) {
	while (tree_idx >= 0) {
		tree[tree_idx]++;
		tree_idx >>= 1;
	}
}

void delete_node(int s, int e, int l, int r, int tree_idx) {
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		tree[tree_idx] = 0;
	}
	if (s == e) return;
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
	int command, X;
	dfs(0);
	make_tree(left[0], right[0], 1);
	total_sum = 0LL;
	for (int i = 1; i <= M; i++) {
		command = cmd_set[i][0];		X = cmd_set[i][1];
		if (command == 1) {
			update_node(leaf_node_idx[X]);
		}
		else if (command == 2) {
			delete_node(left[0], right[0], left[X], right[X], 1);
		}
		else {
			total_sum += (get_child_cnt(left[0], right[0], left[X], right[X], 1) * 1LL - 1LL);
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, total_sum); }

int main() {
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


// 조금 더 보완하여서!!
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
	while (tree_idx >= 1) {
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
