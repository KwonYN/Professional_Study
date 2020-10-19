// Hackerrank_Abstract Classes - Polymorphism
// 나 혼자 제멋대로 해본 ver.
#if 0
#pragma warning(disable: 4996)
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
#define NMAX	(500010)
#define MMAX	(1010)

struct CACHE {
	CACHE *prev, *next;
	int key, value;
	CAHCE() {}
	CAHCE(int k, int v) { 
		this->key = k;	this->value = v;
		this->prev = this->next = (CACHE*)0x0;
	}
}
int N, M, cache_size;
CACHE *head, *tail;
CACHE cache[NMAX];

void solve() {
	char* cmd;		int a, b;
	cache_size = 0;		head = tail = (CAHCE*) 0x0; 
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++) {
		scanf("%s", cmd);
		string str = cmd;
		if(str.compare("set") == 0) {
			scanf("%d %d", &a, &b);
			if(cache_size < M) {
				cache[i] = new CACHE(a, b);
				head = &cache[i];
				if(++cache_size == 1) {
					tail = &cache[i];
				}
				else {
					head->next = &cache[i-1];
					head->next->prev = head;
					cache[cache_size-1].next = &cache[cache_size];
					cache[cache_size].prev = &cache[cache_size-1];
				}
			}
			else {
				cache_size--;
				CACHE *tmp = tail;
				tail = tail->prev;
				tail->next = (CACHE*)0x0;
				delete tmp;cache[i] = new CACHE(a, b);
				head = &cache[i];
				if(++cache_size == 1) {
					tail = &cache[i];
				}
				else {
					head->next = &cache[i-1];
					head->next->prev = head;
					cache[cache_size-1].next = &cache[cache_size];
					cache[cache_size].prev = &cache[cache_size-1];
				}
			}
		}
		else {
			bool end_flag = false;
			scanf("%d", &a);
			for(CACHE* i = head; i; i = i->next) {
				if(i->key == a) {
					printf("%d\n", i->value);
					end_flag = true;
					break;
				}
			}
			if(!end_flag) printf("-1\n");
		}
	}
	delete[] cache;
}

int main() {
	solve();
	return 0;
}
#endif


// 문제에서 코드 복붙 후 남은 부분 구현 ver.
/*
	[접근제한자]
	private		: 외부에서 접근이 불가능
	protected	: 외부에서 접근이 불가능하나 파생 클래스에서는 접근이 가능
	public		: 어디서나 접근이 가능
	
	https://blog.hexabrain.net/173 - 너무 좋은 소스..!!!ㄷㄷ
*/
#if 01
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 	// protected : 외부에서는 접근이 불가능하나, 파생클래스에서는 접근이 가능!!!
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function
};

// Inheritance : Cache 클래스를 상속받아 LRUCache 클래스를 만듬
//				 이 안에서 추상메소드를 구현!
class LRUCache: public Cache {
	
	LRUCache(int capa) {
		this->cp = capa;
	}
	void set(int k, int v) {
		NODE * new_node;
		if(mp.empty()) {
			new_node = new NODE(k, v);
			this->tail = this->head = new_node;
			mp.insert({k, new_node});
			return;
		}
		;
	}
	
	int get(int k) {
		;
	}
}

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
#endif