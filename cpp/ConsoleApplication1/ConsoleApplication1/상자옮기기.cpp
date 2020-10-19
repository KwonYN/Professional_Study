// 상자 옮기기
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100010)
#define WHMAX	(100010)

typedef long long ll;
typedef pair<int, int> pii;
int T, N;
pii box[NMAX];
pii d[NMAX];
int leng[NMAX], max_len;

bool cmp(pii b1, pii b2) {
	if(b1.first < b2.first) return true;
	if (b1.first == b2.first) {
		if(b1.second < b2.second) return true;
	}
	return false;
}

void input() {
	int w, h;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &w, &h);
		box[i] = { w, h };
	}
	sort(box + 1, box + N + 1, cmp);
	/*for (int i = 1; i <= N; i++) {
		printf("W = %d // H = %d\n", box[i].first, box[i].second);
	}
	printf("\n");*/
}

int bin_search(int s, int e, int target) {
	int m;
	while (s <= e) {
		m = (s + e) / 2;
		if (d[m].second == target) return m;
		if (d[m].second > target) e = m - 1;
		else s = m + 1;
	}
	return s;
}

void operation() {
	int len = 0;
	max_len = 0;
	d[++len] = { 1, box[1].second };
	for (int i = 2; i <= N; i++) {
		if (box[d[len].first].first < box[i].first) {
			if (d[len].second < box[i].second) {
				d[++len] = { i, box[i].second };
				leng[i] = len;
				max_len = max(max_len, len);
			}
			else {
				int idx = bin_search(1, len, box[i].second);
				d[idx] = { i, box[i].second };
				leng[i] = idx;
				max_len = max(max_len, idx);
			}
		}
		else {
			leng[i] = len;
		}
	}
	for (int i = 1; i <= len; i++) {
		printf("W:%d  H:%d\n", box[d[i].first].first, d[i].second);
	}
}

void output(int tc) {
	ll vol = (1LL<<61);
	for (int i = 1; i <= N; i++) {
		ll chk = 1LL*box[i].first*box[i].first*box[i].second;
		if (leng[i] == max_len) {
			if(vol > chk) vol = chk;
		}
	}
	printf("#%d %d %lld\n", tc, max_len, vol);
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
