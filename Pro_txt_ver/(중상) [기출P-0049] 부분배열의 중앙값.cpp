// (중상) [기출P-0049] 부분배열의 중앙값
// 시간초과
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)

typedef pair<int, int> pii;
int T, N, K, arr[NMAX];
pii sorted_arr[NMAX];
int fenwick_tree[NMAX], tree_idx[NMAX], reverse_idx[NMAX];
int max_median, median_cnt;
bool chk[NMAX];

void input() {
	scanf("%d %d", &N, &K);
	median_cnt = (K+1)/2;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		sorted_arr[i] = { arr[i], i };
	}
	sort(sorted_arr+1, sorted_arr+N+1);	//  value 기준 오름차순 정렬!
}

void init_tree() {
	max_median = 0;
	for(int i = 1; i <= N; i++) {
		fenwick_tree[i] = 0;
		tree_idx[sorted_arr[i].second] = i;
		reverse_idx[i] = sorted_arr[i].second;
		chk[i] = false;
	}
}

void update_tree(int idx) {
	idx = tree_idx[idx];
	chk[idx] = true;
	while(idx <= N) {
		fenwick_tree[idx]++;
		idx += idx & -idx;
	}
}

void delete_tree(int idx) {
	idx = tree_idx[idx];
	chk[idx] = false;
	while(idx <= N) {
		fenwick_tree[idx]--;
		idx += idx & -idx;
	}
}

void set_data() {
	init_tree();
	for(int i = 1; i <= K; i++) {
		update_tree(i);
	}
}

int get_cnt(int idx) {
	int cnt_sum = 0;
	while(idx) {
		cnt_sum += fenwick_tree[idx];
		idx -= idx & -idx;
	}
	return cnt_sum;
}

int get_median_idx(int s, int e) {	// bin_search
	int m = (s+e)/2;
	int cnt;
	while(s <= e){
		cnt = get_cnt(m);
		if(cnt == median_cnt && chk[m]) return arr[reverse_idx[m]];
		else if(cnt < median_cnt) s = m+1;
		else e = m-1;
	}
}

void get_median() {
	for(int i = 1; i < N-K+1; i++) {
		int median = get_median_idx(1, N);
		max_median = max(max_median, median);
		int will_deleted = i;
		delete_tree(will_deleted);
		int will_added = i+K;
		update_tree(will_added);
	}
}

void output(int tc) { printf("#%d %d\n", tc, max_median); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		set_data();
		get_median();
		output(tc);
	}
	return 0;
}
#endif


// Re...ㅠㅠ
# if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)

typedef pair<int, int> pii;
int T, N, K, arr[NMAX];
pii sorted_arr[NMAX];
int seg_tree[NMAX*3], leaf_node[NMAX];
int max_median, median_cnt;

void input() {
	max_median = 0;
	scanf("%d %d", &N, &K);
	median_cnt = (K+1)/2;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		sorted_arr[i] = { arr[i], i };
	}
	sort(sorted_arr+1, sorted_arr+N+1);	// arr의 value 기준 오름차순 정렬
}

void init_tree(int s, int e, int idx) {
	seg_tree[idx] = 0;
	if(s == e) {
		leaf_node[sorted_arr[s].second] = idx;			//	s는 arr의 index
		return;
	}
	int m = (s+e)/2;
	init_tree(s, m, idx<<1);
	init_tree(m+1, e, (idx<<1)|1);
}

void update_tree(int idx) {
	idx = leaf_node[idx];
	while(idx) {
		seg_tree[idx]++;
		idx >>= 1;
	}
}

void delete_tree(int idx) {
	idx = leaf_node[idx];
	while(idx) {
		seg_tree[idx]--;
		idx >>= 1;
	}
}

int get_median(int s, int e, int idx, int cnt) {
	if(s == e) {
		return sorted_arr[s].first;
	}
	int m = (s+e)/2;
	if(seg_tree[(idx<<1)] >= cnt) get_median(s, m, (idx<<1), cnt);
	else get_median(m+1, e, (idx<<1)|1, cnt-seg_tree[(idx<<1)]);
}

void set_tree() {
	init_tree(1, N, 1);
	for(int i = 1; i <= K; i++) {
		update_tree(i);	// i는 arr의 index
	}
	max_median = max(max_median, get_median(1, N, 1, median_cnt));
}

void get_max_median() {
	for(int i = 1; i < N-K+1; i++) {
		int left = i;
		int right = i+K;		// 이들 역시 모두 arr의 index
		delete_tree(left);
		update_tree(right);
		max_median = max(max_median, get_median(1, N, 1, median_cnt));
	}
}

void output(int tc) { printf("#%d %d\n", tc, max_median); }

int main() {
	scanf("%d", &T);
	for(int tc = 1; tc <= T; tc++) {
		input();
		set_tree();
		get_max_median();
		output(tc);
	}
	return 0;
}
#endif