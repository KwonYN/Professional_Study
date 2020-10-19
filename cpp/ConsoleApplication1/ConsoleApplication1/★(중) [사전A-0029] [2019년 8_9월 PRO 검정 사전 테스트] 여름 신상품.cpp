// (중) [사전A-0029] [2019년 8~9월 PRO 검정 사전 테스트] 여름 신상품
/*
	모자 / 상의 / 하의 각 1개씩으로 이루어진 세트 상품
		-> 세트로만 판매됨!
		-> 상품코드는 모자(1), 상의(2), 하의(3)
	N개의 판매점 (1 ~ N까지 판매점 번호)

	1 x y k c
	[납품] : x~y 판매점에 k 코드 상품을 c개씩 더해줌
	1) x ~ y(x<=y) 사이에 포함되는 "모든 판매점"에
	   상품코드가 k인 상품을 c개씩 납품
	2) 1 <= c <= 100

	2 x c
	[판매] : x번 판매점에 c개 or (미만 case)가능한 세트 빼줌
	1) x번 판매점으로 c개 세트(1+2+3) 판매 요청 처리
	2) x번 판매점에서 c개 세트 상품을 판매할 수 있다면 c개 판매
	   c개 세트 만들 수 없다면 모든 세트만 판매(c개 미만)
	3) 1<= c <= 1천만

	3 x y
	[판매수량 조사] : 판매가 완료된 세트 수 sum
	1) x ~ y(x<=y) 판매점 누적 판매된 세트 수 조사
*/
#if 0
#pragma warning(diable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100000)	// 판매점 수
#define QMAX	(100000)	// 명령의 수

typedef long long ll;
struct COMMODITY { int clothes[4];  };	// 현재 세트 수, 모자, 상의, 하의
int T, N, Q;
COMMODITY dataa[NMAX+5];
ll tree[NMAX+5];		// 펜윅트리
ll acc_sales;

void init() {
	acc_sales = 0LL;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 4; j++) {
			dataa[i].clothes[j] = 0;
		}
		tree[i] = 0LL;
	}
}

void update(int shop1, int shop2, int commodity, int cnt) {
	for (int i = shop1; i <= shop2; i++) {
		dataa[i].clothes[commodity] += cnt;
		dataa[i].clothes[0] = min(dataa[i].clothes[1], min(dataa[i].clothes[2], dataa[i].clothes[3]));
	}
}

void sales(int shop1, int cnt) {
	int total_set = dataa[shop1].clothes[0];
	int val = (total_set < cnt) ? total_set : cnt;
	for (int i = 0; i <= 3; i++) {
		dataa[shop1].clothes[i] -= val;
	}
	while (shop1 <= N) {
		tree[shop1] += val;
		shop1 += (shop1 & -shop1);
	}
}

ll search_set(int s, int e) {
	ll sum1 = 0LL, sum2 = 0LL;
	while (s) {
		sum1 += tree[s];
		s -= (s & -s);
	}
	while (e) {
		sum2 += tree[e];
		e -= (e & -e);
	}
	return (sum2 - sum1);
}

void print_commodity(int q) {
	printf("\n\n★★★★★   Query : %d   ★★★★★\n", q);
	for (int i = 1; i <= N; i++) {
		ll val = search_set(i-1, i);
		printf("[%d] 세트 : 총 %lld\n", i, val);
		printf("--------------------------------------\n");
		printf("모자 : %d\n", dataa[i].clothes[1]);
		printf("상의 : %d\n", dataa[i].clothes[2]);
		printf("하의 : %d\n", dataa[i].clothes[3]);
		printf("(최소 : %d)\n", min(dataa[i].clothes[1], min(dataa[i].clothes[2], dataa[i].clothes[3])));
		printf("======================================\n");

	}
}

void input_() {
	int cmd, shop1, shop2, commodity, cnt;
	scanf("%d %d", &N, &Q);
	init();
	for (int i = 1; i <= Q; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {	// 납품
			scanf("%d %d %d %d", &shop1, &shop2, &commodity, &cnt);
			update(shop1, shop2, commodity, cnt);
		}
		else if (cmd == 2) { // 판매
			scanf("%d %d", &shop1, &cnt);
			sales(shop1, cnt);
		}
		else { // 판매수량 조사
			scanf("%d %d", &shop1, &shop2);
			acc_sales += search_set(shop1-1, shop2);
		}
		//print_commodity(i);
	}
}

void output(int tc) { printf("#%d %lld\n", tc, acc_sales); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//	if (tc > 1) return 0;
		input_();
		output(tc);
	}
	return 0;
}
#endif


// 다시 풀려고 하는데.. 구간 업데이트를 어떻게 해주어야 하는 것이지..
#if 0
#pragma warning(diable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(100000)	// 판매점 수
#define QMAX	(100000)	// 명령의 수

typedef long long ll;
struct COMMODITY { ll clothes[4];  };	// 현재 세트 수, 모자, 상의, 하의
int T, N, Q;
COMMODITY in[NMAX+5], out[NMAX+5];	// 펜윅트리 : 더함, 빼줌
ll tree[NMAX+5];					// 펜윅트리 : 판매수량
ll acc_sales;

void init() {
	acc_sales = 0LL;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 4; j++) {
			in[i].clothes[j] = out[i].clothes[j] =  0;
		}
		tree[i] = 0LL;
	}
}

void update(int at, int commodity, ll in_plus, ll out_minus) {
	while (at <= N) {
		in[at].clothes[commodity] += in_plus;
		out[at].clothes[commodity] += out_minus;
	}
}

void range_update(int l, int r, int commodity, ll cnt) {
	update(l, commodity, cnt, -cnt*(l-1));
	update(r+1, commodity, -cnt, cnt*r);
}

void sales(int shop, int cnt) {
	int val = (total_set < cnt) ? total_set : cnt;
	for (int i = 0; i <= 3; i++) {
		dataa[shop].clothes[i] -= val;
	}
	while (shop <= N) {
		tree[shop] += val;
		shop += (shop & -shop);
	}
}

ll search_set(int l, int r) {
	ll sum1 = 0LL, sum2 = 0LL;
	while (l) {
		sum1 += tree[l];
		l -= (l & -l);
	}
	while (r) {
		sum2 += tree[r];
		r -= (r & -r);
	}
	return (sum2 - sum1);
}

void input_() {
	int cmd, shop1, shop2, commodity, cnt;
	scanf("%d %d", &N, &Q);
	init();
	for (int i = 1; i <= Q; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {	// 납품
			scanf("%d %d %d %d", &shop1, &shop2, &commodity, &cnt);
			range_update(shop1, shop2, commodity, 1LL*cnt);
		}
		else if (cmd == 2) { // 판매
			scanf("%d %d", &shop1, &cnt);
			sales(shop1, cnt);
		}
		else { // 판매수량 조사
			scanf("%d %d", &shop1, &shop2);
			acc_sales += search_set(shop1-1, shop2);
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, acc_sales); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//	if (tc > 1) return 0;
		input_();
		output(tc);
	}
	return 0;
}
#endif


// 세그먼트 트리 Lazy Propagation?
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
#define NMAX	(100010)

typedef long long ll;
struct SHOP { int inventory_code[4], lazy[4]; };
int T, N, Q;
SHOP inventory[NMAX * 3];	// 세그먼트트리
ll tree[NMAX + 5];		// 펜윅트리
ll acc_sales;

void init_inventory(int s, int e, int idx) {
	for (int i = 0; i <= 3; i++) {
		inventory[idx].inventory_code[i] = 0;
		inventory[idx].lazy[i] = 0;
	}
	if (s == e) return;
	int m = (s + e) / 2;
	init_inventory(s, m, idx << 1);
	init_inventory(m + 1, e, (idx << 1) | 1);
}

void init() {
	acc_sales = 0LL;
	for (int i = 0; i <= N; i++) {
		tree[i] = 0LL;
	}
	init_inventory(1, N, 1);
}

void lazy_propagation(int s, int e, int idx, int code) {
	if (inventory[idx].lazy[code] != 0) {
		inventory[idx].inventory_code[code] += inventory[idx].lazy[code] * (e - s + 1);
		if (s != e) {
			inventory[idx << 1].lazy[code] += inventory[idx].lazy[code];
			inventory[(idx << 1) | 1].lazy[code] += inventory[idx].lazy[code];
		}
		inventory[idx].lazy[code] = 0;
	}
}

void update(int s, int e, int l, int r, int idx, int code, int val) {
	assert(1 <= s && e <= N);
	lazy_propagation(s, e, idx, code);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		inventory[idx].inventory_code[code] += (e - s + 1) * val;
		if (s != e) {
			inventory[idx << 1].lazy[code] += val;
			inventory[(idx << 1) | 1].lazy[code] += val;
		}
		return;
	}
	int m = (s + e) / 2;
	update(s, m, l, r, idx << 1, code, val);
	update(m + 1, e, l, r, (idx << 1) | 1, code, val);
	inventory[idx].inventory_code[code] =
		inventory[idx << 1].inventory_code[code]
		+ inventory[(idx << 1) | 1].inventory_code[code];
}

void update_fenwick(int idx, ll val) {
	while (idx <= N) {
		tree[idx] += val;
		idx += idx & -idx;
	}
}

void inventory_sales(int s, int e, int shop, int idx, int cnt) {
	for (int i = 1; i <= 3; i++) lazy_propagation(s, e, idx, i);
	if (shop < s || e < shop) return;
	if (s == e) {
		int val = cnt;
		for (int i = 1; i <= 3; i++) {
			val = min(val, inventory[idx].inventory_code[i]);
		}
		for (int i = 1; i <= 3; i++) {
			inventory[idx].inventory_code[i] -= val;
		}
		update_fenwick(s, 1LL * val);
		return;
	}
	int m = (s + e) / 2;
	inventory_sales(s, m, shop, idx << 1, cnt);
	inventory_sales(m + 1, e, shop, (idx << 1) | 1, cnt);
}

ll get_sum(int idx) {
	ll sum = 0LL;
	while (idx) {
		sum += tree[idx];
		idx -= idx & -idx;
	}
	return sum;
}

void input_() {
	int cmd, left, right, commodity, count;
	scanf("%d %d", &N, &Q);
	init();
	for (int i = 1; i <= Q; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {	// 납품
			scanf("%d %d %d %d", &left, &right, &commodity, &count);
			update(1, N, left, right, 1, commodity, count);
		}
		else if (cmd == 2) {	// 판매
			scanf("%d %d", &left, &count);
			inventory_sales(1, N, left, 1, count);
		}
		else {	// 판매수량 조사
			scanf("%d %d", &left, &right);
			acc_sales += (get_sum(right) - get_sum(left - 1));
		}
	}
}

void output(int tc) { printf("#%d %lld\n", tc, acc_sales); }

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
		output(tc);
	}
	return 0;
}
#endif