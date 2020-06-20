// BOJ_12904_A와 B
/*
	두 문자열 S와 T가 주어졌을 때, S를 T로 바꾸는 게임.
	문자열을 바꿀 때는 다음과 같은 두 가지 연산만 가능.
	1) 문자열의 뒤에 A를 추가
	2) 문자열을 뒤집고 뒤에 B를 추가
	=> S를 T로 만들 수 있는지 없는지 알아내는 프로그램을 작성

	=> ★ T는 이미 만들어진 결과. 그렇기에 T에서 시작하여 거꾸로 간다면, S를 구할 수 있지 않을까!?!?!?!? ★
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string S, T; // S의 길이 < T의 길이
int s_len, t_len;
bool flag;

string str_reverse(string &str, int &len) {
	char tmp[1010] = { '\0' };
	for(int i = 0; i < len; i++) tmp[i] = str[i];
	for(int i = len - 1; i >= 0; i--) {
		str[len - i - 1] = tmp[i];
	}
	str[len] = '\0';
	return str;
}

bool cmp_str(string &str1, string &str2, int &len1, int &len2) {
	if(len1 != len2) return false;
	len1 = len2 = 0;
	while(str1[len1] && str2[len2]) {
		if(str1[len1++] != str2[len2++]) return false;
	}
	return true;	
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);	cout.tie(NULL);
	cin >> S;		cin >> T;
	s_len = S.length();	t_len = T.length();	flag = false;
	while(true) {
		if(s_len > t_len) break;
		else if(s_len == t_len) if(cmp_str(S, T, s_len, t_len)) { flag = true; break; }
		if(T[--t_len] == 'B') {
			T = str_reverse(T, t_len);
		}
	}
	cout << flag << "\n"; // 만들 수 있으면 true, 아니면 false
	return 0;
}
