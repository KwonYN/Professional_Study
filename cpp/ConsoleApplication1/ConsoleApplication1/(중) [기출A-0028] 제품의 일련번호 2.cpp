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

void input() {
	char tmp;		bool flag = false;
	scanf("%d", &N);
	scanf("%s %s", input1, input2);
	printf("%s %s\n", input1, input2);
	for (int i = 0; input1[i] && input2[i]; i++) {
		if (input1[i] == input2[i]) continue;
		if (input1[i] < input2[i]) break;
		if (input1[i] > input2[i]) {
			flag = true;
			break;
		}
	}
	if (flag) {
		for (int i = 0; i < N; i++) {
			tmp = input1[i];
			input1[i] = input2[i];
			input2[i] = tmp;
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input();
	}
	return 0;
}
#endif