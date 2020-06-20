// BOJ_5639_이진 검색 트리
/*
    세 가지 조건을 만족하는 이진 트리
    노드의 왼쪽 서브트리에 있는 모든 노드의 키는 노드의 키보다 작다.
    노드의 오른쪽 서브트리에 있는 모든 노드의 키는 노드의 키보다 크다.
    왼쪽, 오른쪽 서브트리도 이진 검색 트리이다.
    전위 순회 (루트-왼쪽-오른쪽): 루트를 방문. 왼쪽 서브트리, 오른쪽 서브 트리를 순서대로 방문하면서 노드의 키를 출력.
    후위 순회 (왼쪽-오른쪽-루트): 왼쪽 서브트리, 오른쪽 서브트리, 루트 노드 순서대로 키를 출력.
    후위 순회한 결과를 구하는 프로그램? (양의 정수가 주어짐!!)
*/

#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX	(10000)

int bin_tree[MAX*4];

void leftrightroot(int idx) {
	if(!bin_tree[idx]) return;
	leftrightroot(idx*2);
	leftrightroot(idx*2+1);
	printf("%d\n", bin_tree[idx]);
}

void update(int node, int idx) {
	if(!bin_tree[idx]) { bin_tree[idx] = node; return; }
	if(bin_tree[idx] > node) update(node, idx*2);
	else update(node, idx*2 + 1);
}

int main() {
	// 전위 순회 입력 받음
	int num;
	scanf("%d", &bin_tree[1]);
	while(true) {
		int ret = scanf("%d", &num);
		if(ret != 1) break;
		update(num, 1);
	}
	// 후위 순회로 프린트
	leftrightroot(1);
	
	return 0;
}
