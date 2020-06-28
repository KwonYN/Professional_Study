// (중) [사전A-0033] [2019년 12월 PRO 검정 사전 테스트] 스마트 팩토리
/*
	공장에서는 26가지(A~Z) 부품 생산 가능
	하루에 "N개의 부품"을 "순차적으로 처리" 가능
	"M개의 라인"이 있고, 모든 라인이 "동시에 작동 시작하고 마감"
	각 라인의 "처리 속도는 같으"며 모든 "부품 만드는 시간 동일"
	엔지니어의 개입 없으면 모든 부품이 불량품이 됨!
	"K명의 엔지니어"
	각 엔지니어들은 한 종류의 부품만을 책임지고 담당
	투입된 시점 ~ 퇴근 담당 부품의 불량률 0%로 만들 수 있음
	한 번 투입되면 공장 끝날 때까지 일할 수 있지만,
		한 번 일한 엔지니어는 같은 날 다시 일하지 않음
	두 명의 엔지니어가 동시에 일할 수 없음
		→ 다른 엔지니어 투입시키고 싶으면, 그 라인 한 명 퇴근시켜야
		→ 퇴근한 엔지니어는 다음 날 다시 출근 ㅋ
	엔지니어 투입하여 생산할 수 있는 정상부품 최대 개수!?!?


*/
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX	(5000)
#define MMAX	(100)

int T, N, M, K;
int engineer[6];
int sum_alpha[27][NMAX+5];

void init() {
	for (int i = 1; i <= 26; i++) {
		for (int j = 1; j <= N; j++) {
			sum_alpha[i][j] = 0;
		}
	}
}

int char_to_int(char ch) {	// A : 1, B : 2, ... , Z : 26
	return (int)(ch - 'A') + 1;
}

void input_() {
	char k_tmp[6], input_tmp[NMAX+5];
	scanf("%d %d %d", &N, &M, &K);
	init();
	scanf("%s", k_tmp+1);
	for (int i = 1; i <= K; i++) engineer[i] = char_to_int(k_tmp[i]);
	for (int i = 1; i <= M; i++) {
		scanf("%s", input_tmp+1);
		for (int j = 1; j <= N; j++) {
			sum_alpha[char_to_int(input_tmp[j])][j]++;
		}
	}
	for (int j = 2; j <= N; j++) { // j시점 까지의 알파벳 개수 누적합
		for (int i = 1; i <= 26; i++) {
			sum_alpha[i][j] += sum_alpha[i][j-1];
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		input_();
	}
	return 0;
}
#endif