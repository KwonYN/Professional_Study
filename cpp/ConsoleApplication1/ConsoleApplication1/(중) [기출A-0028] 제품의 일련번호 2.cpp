// (중) [기출A-0028] 제품의 일련번호 2
/*
	길이가 N일 때,
	X???...? (첫 자가 결정되었다면), 그 뒤의 ???...?은 총 (N-1)!
*/
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;

int T, N;	// N : 4 ~ 18
char input1[20], input2[20];
bool sunseo1[20], sunseo2[20];
long long factorial[20];	// 18! == 약 6,500조 < 21억^2

void init() {
	for (int i = 0; i < N; i++) sunseo1[i] = sunseo2[i] = false;
}

void input() {
	char tmp;		bool flag = false;
	scanf("%d", &N);
	init();
	scanf("%s %s", input1, input2);
	//printf("%s %s\n", input1, input2);
	for (int i = 0; input1[i] && input2[i]; i++) {	// swap(1 <= 2)
		if (input1[i] == input2[i]) continue;
		if (input1[i] < input2[i]) break;
		flag = true;			   break;
	}
	if (flag) {
		for (int i = 0; i < N; i++) {
			tmp = input1[i];
			input1[i] = input2[i];
			input2[i] = tmp;
		}
	}
	//printf("%s %s\n", input1, input2);
}

long long get_cnt() {
	long long order1 = 0LL, order2 = 0LL;
	int sunseo, cnt = 0;;
	for (int i = 0; i < N; i++) {
		sunseo = input1[i]-'a';
		cnt = 0;
		for (int j = 0; j < N; j++) {
			if (sunseo1[j]) continue;
			if (sunseo == j) {
				sunseo1[j] = true;
				order1 += (1LL * cnt * factorial[N - 1 - i]);
				break;
			}
			cnt++;
		}
	}
	for (int i = 0; i < N; i++) {
		sunseo = input2[i] - 'a';
		cnt = 0;
		for (int j = 0; j < N; j++) {
			if (sunseo2[j]) continue;
			if (sunseo == j) {
				sunseo2[j] = true;
				order2 += (1LL * cnt * factorial[N - 1 - i]);
				break;
			}
			cnt++;
		}
	}
	//printf("%lld %lld\n", order1, order2);
	return order2 - order1 - 1; // 두 문자열 사이에 끼어있는 개수!!
}

int main() {
	freopen("in.txt", "r", stdin);
	factorial[1] = 1;
	for (int i = 2; i <= 17; i++) factorial[i] = 1LL*i*factorial[i - 1];	// factorial init
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
		printf("#%d %lld\n", tc, get_cnt());
	}
	return 0;
}
#endif