// BOJ_1837_암호제작
/*
	엣지 케이스를 주의하자!!!
	TC를 만들거나 적용해볼 때는 변수 조건의 최소값, 최대값, 0개나 1개, 엄청 넘치게 넣어보는 습관이 중요!
*/
#if 01
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define KMAX    (1000000)

string P;
int K, len, r;
int sosu[KMAX], sosu_cnt;
bool eratos[KMAX+10], quality;

bool get_quotient(int n) {
    int num = 0;
    for (int i = 0; i < len; i++) {
        num = (num * 10 + (P[i] - '0')) % n;
    }
    return (num == 0);
}

int main() {
    freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);
    eratos[0] = eratos[1] = true;      sosu_cnt = 0;
    for (int i = 2; i <= KMAX; i++) {
        if (eratos[i]) continue;    // eratos[i] == false인 값이
        sosu[++sosu_cnt] = i;       // sosu[sosu_cnt]에 들어감!
        for (int j = i + i; j <= KMAX; j += i) eratos[j] = true;
    }
    cin >> P;               cin >> K;       
    len = P.length();       quality = true;
    for (int i = 1; i <= sosu_cnt; i++) {
        if (sosu[i] >= K) break;
        else if (get_quotient(sosu[i])) {
            r = sosu[i];
            quality = false;
            break;
        }
    }
    if (quality) cout << "GOOD" << "\n";
    else cout << "BAD " << r << "\n";
    return 0;
}
#endif




// BOJ_1837_암호제작
#if 01
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX		(1000000)

string P;
int K;
int eratos[MAX + 10], sosu[MAX], sosu_cnt;
int len, r;
bool quality;

bool get_quotient(int n) {
	int num = 0;
	for (int i = 0; i < len; i++) {
		num = num * 10 + (P[i]-'0');
		num %= n;
	}
	if (!num) return true;
	return false;
}

int main() {
	freopen("in.txt", "r", stdin);
	quality = false;
	eratos[0] = eratos[1] = 1;		sosu_cnt = 0;
	for (int i = 2; i <= MAX; i++)
	{
		if (eratos[i]) continue;
		sosu[++sosu_cnt] = i;
		for (int j = 2 * i; j <= MAX; j += i) eratos[j]++;
	}
	cin >> P; cin >> K;				len = P.length();
	for (int i = 1; i <= sosu_cnt; i++) {
		if (sosu[i] < K) {
			if (get_quotient(sosu[i])) {
				r = sosu[i];
				break;
			}
		}
		else { quality = true; break;  }
	}
	if (quality) cout << "GOOD" << "\n";
	else cout << "BAD " << r << "\n";
	return 0;
}
#endif
