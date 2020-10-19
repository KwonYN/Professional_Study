// BOJ_2014_¼Ò¼öÀÇ °ö
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <algorithm>
using namespace std;
#define KMAX	(110)

int K, N, primeNum[KMAX];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d %d", &K, &N);
	for (int i = 1; i <= K; i++) {
		scanf("%d", &primeNum[i]);
	}
	return 0;
}
#endif
