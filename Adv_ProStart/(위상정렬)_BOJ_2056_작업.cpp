// ㅁㅊㄷ ㅁㅊㅇ
#include <iostream>
#include <algorithm>

using namespace std;
int N;
int time[10001];
int mx;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int t, n, t2;
		cin >> t >> n;
		for (int j = 0; j < n; j++) {
			cin >> t2;
			time[i] = max(time[i], time[t2]);
		}
		time[i] += t;
		mx = max(mx, time[i]);
	}
	cout << mx;
	return 0;
}


// 굉장히 나에게는 신기한.. 그러한 남의 코드... 한 번 봅시다!!
#include <cstdio>
#include <cctype>
class FastIO {
    int fd, bufsz;
    char *buf, *cur, *end;
public:
    FastIO(int _fd = 0, int _bufsz = 1 << 20) : fd(_fd), bufsz(_bufsz) {
        buf = cur = end = new char[bufsz];
    }
    ~FastIO() {
        delete[] buf;
    }
    bool readbuf() {
        cur = buf;
        end = buf + bufsz;
        while (true) {
            size_t res = fread(cur, sizeof(char), end - cur, stdin);
            if (res == 0) break;
            cur += res;
        }
        end = cur;
        cur = buf;
        return buf != end;
    }
    int readint() {
        while (true) {
            if (cur == end) readbuf();
            if (isdigit(*cur) || *cur == '-') break;
            ++cur;
        }
        bool sign = true;
        if (*cur == '-') {
            sign = false;
            ++cur;
        }
        int ret = 0;
        while (true) {
            if (cur == end && !readbuf()) break;
            if (!isdigit(*cur)) break;
            ret = ret * 10 + (*cur - '0');
            ++cur;
        }
        return sign ? ret : -ret;
    }
};

#include <algorithm>
using namespace std;
int a[10001];
int main() {
  FastIO fio;
  int n = fio.readint(), ans = 0;
  for (int i = 1; i <= n; ++i) {
    int t = fio.readint(), m = fio.readint(), y = 0;
    for (int j = 0; j < m; ++j) {
      int x = fio.readint();
      y = max(y, a[x]);
    }
    a[i] = y + t;
    ans = max(ans, a[i]);
  }
  printf("%d", ans);
  return 0;
}




// BOJ_2056_작업
#if 01
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define	MAX		(10000)

int N;
int workhour[MAX+10], indegree[MAX+10]; // indegree는 0으로,
vector<int> edges[MAX+10];				// edges.clear()로 초기화 해주어야 함!
int min_time[MAX+10];
queue<int> que;

int main() {
	//freopen("in.txt", "r", stdin);
	int cnt, node;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &workhour[i]);
		scanf("%d", &cnt);
		for (int j = 1; j <= cnt; j++) {
			scanf("%d", &node);
			edges[node].push_back(i);
			indegree[i]++;
		}
	}
	for (int i = 1; i <= N; i++) {
		min_time[i] = -1;
		if (!indegree[i]) { que.push(i); min_time[i] = workhour[i]; }
	}
	int maxx = -1;
	while (!que.empty()) {
		int out = que.front();	que.pop();
		for (int next : edges[out]) {
			indegree[next]--;
			min_time[next] = max(min_time[next], min_time[out] + workhour[next]);
			if (!indegree[next]) {
				if (maxx < min_time[next]) maxx = min_time[next];
				que.push(next);
			}
		}
	}
	printf("%d\n", maxx);
	return 0;
}
#endif






// 다른 ver.인데 똑같음.. 효율적이지 못함 ㅠㅠ
#pragma warning(disable: 4996)
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define	MAX		(10000)

int N;
int workhour[MAX+10], indegree[MAX+10]; // indegree는 0으로,
vector<int> edges[MAX+10];				// edges.clear()로 초기화 해주어야 함!
int min_time[MAX+10];
queue<int> que;

int main() {
	//freopen("in.txt", "r", stdin);
	int cnt, node;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &workhour[i]);
		scanf("%d", &cnt);
		for (int j = 1; j <= cnt; j++) {
			scanf("%d", &node);
			edges[node].push_back(i);
			indegree[i]++;
		}
	}
	for (int i = 1; i <= N; i++) {
		min_time[i] = -1;
		if (!indegree[i]) { que.push(i); min_time[i] = workhour[i]; }
	}
	int maxx = -1;
	while (!que.empty()) {
		int out = que.front();	que.pop();
        if (maxx < min_time[out]) maxx = min_time[out];
		for (int next : edges[out]) {
			indegree[next]--;
			min_time[next] = max(min_time[next], min_time[out] + workhour[next]);
			if (!indegree[next]) que.push(next);
		}
	}
	printf("%d\n", maxx);
	return 0;
}
