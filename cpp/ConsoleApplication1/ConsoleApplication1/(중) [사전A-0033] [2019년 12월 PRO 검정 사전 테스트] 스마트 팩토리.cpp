// (��) [����A-0033] [2019�� 12�� PRO ���� ���� �׽�Ʈ] ����Ʈ ���丮
/*
	���忡���� 26����(A~Z) ��ǰ ���� ����
	�Ϸ翡 "N���� ��ǰ"�� "���������� ó��" ����
	"M���� ����"�� �ְ�, ��� ������ "���ÿ� �۵� �����ϰ� ����"
	�� ������ "ó�� �ӵ��� ����"�� ��� "��ǰ ����� �ð� ����"
	�����Ͼ��� ���� ������ ��� ��ǰ�� �ҷ�ǰ�� ��!
	"K���� �����Ͼ�"
	�� �����Ͼ���� �� ������ ��ǰ���� å������ ���
	���Ե� ���� ~ ��� ��� ��ǰ�� �ҷ��� 0%�� ���� �� ����
	�� �� ���ԵǸ� ���� ���� ������ ���� �� ������,
		�� �� ���� �����Ͼ�� ���� �� �ٽ� ������ ����
	�� ���� �����Ͼ ���ÿ� ���� �� ����
		�� �ٸ� �����Ͼ� ���Խ�Ű�� ������, �� ���� �� �� ��ٽ��Ѿ�
		�� ����� �����Ͼ�� ���� �� �ٽ� ��� ��
	�����Ͼ� �����Ͽ� ������ �� �ִ� �����ǰ �ִ� ����!?!?


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
	for (int j = 2; j <= N; j++) { // j���� ������ ���ĺ� ���� ������
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