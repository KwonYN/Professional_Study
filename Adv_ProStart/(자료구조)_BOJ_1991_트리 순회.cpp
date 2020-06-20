// BOJ_1991_트리 순회
/*
	전위 순회(preorder traversal) : 루트 - 왼 - 오
	중위 순회(inorder traversal)  : 왼 - 루트 - 오
	후위 순회(postorder traversal): 왼 - 오 - 루트
*/

#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX	(26)

int N;
pair<char, char> edges_pre[MAX+5];//, edges_in[MAX+5], edges_pst[MAX+5];

void preorder_traversal(char node) {
	if(node == '.') return;
	printf("%c", node);
	preorder_traversal(edges_pre[(int)(node-'A')].first);
	preorder_traversal(edges_pre[(int)(node-'A')].second);
}


void inorder_traversal(char node) {
	if(node == '.') return;
	inorder_traversal(edges_pre[(int)(node-'A')].first);
	printf("%c", node);
	inorder_traversal(edges_pre[(int)(node-'A')].second);
}

void postorder_traversal(char node) {
	if(node == '.') return;
	postorder_traversal(edges_pre[(int)(node-'A')].first);
	postorder_traversal(edges_pre[(int)(node-'A')].second);
	printf("%c", node);
}

int main()
{
	char a, b, c;
	scanf("%d", &N);
	for(int i = 0; i < N; i++) {
		scanf(" %c %c %c", &a, &b, &c);
		edges_pre[(int)(a-'A')] = {b, c};
	}
	preorder_traversal('A');
	printf("\n");
	inorder_traversal('A');
	printf("\n");
	postorder_traversal('A');
	printf("\n");
	return 0;
}
