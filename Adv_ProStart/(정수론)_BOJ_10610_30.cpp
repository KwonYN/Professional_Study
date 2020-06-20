// BOJ_10610_30

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int num[10], total, len;
string strn;	// 100,000개의 숫자로 구성되어 있음!
bool flag;

int main() {
	int tmp;
	flag = false;	total = 0;
	cin >> strn;
	len = strn.length();
	
	for(int i = 0; i < len; i++) {
		tmp = strn[i] - '0';
		//cout << "tmp : " << tmp << "\n";
		total += tmp;
		num[tmp]++;
	}
	if( !num[0] ) flag = true;

	if( !flag && !(total % 3) ) {
		int i = 9;
		while(i >= 0) {
			if(num[i] == 0) { i--; continue; }
			cout << i;  num[i]--;
		}
	}
	else cout << -1;
	cout << "\n";
	return 0;
}
