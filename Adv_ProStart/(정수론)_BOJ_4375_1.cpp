#include <cstdio>
#include <algorithm>
using namespace std;

int n, digit, comp;

int main() {
	while(true) {
		int ret = scanf("%d", &n);    // 2와 5로 나누어 떨어지지 않는 정수
		if(ret != 1) break;
		comp = digit = 1;
		while( (comp % n) ){
			digit++;    comp = (10 * comp + 1) % n;
		} 
		printf("%d\n", digit);
	}

}
