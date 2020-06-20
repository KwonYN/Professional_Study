#include <cstdio>

int N, S;
int arr[100010];
int min_len;

int main()
{
	int l = 1, r = 1, sum, len;

	min_len = 987654321;
	scanf("%d %d", &N, &S);
	for(int i = 1; i <= N; i++) scanf("%d", &arr[i]); // N번
	sum = arr[1];

	while(l <= r && r <= N)
	{
		if(sum < S) sum += arr[++r];
		else
		{
			len = r - l + 1;
			if(min_len > len) min_len = len;
			if(l <= r) sum -= arr[l++];
		}
	}

	if(min_len == 987654321) printf("%d\n", 0);
	else printf("%d\n", min_len);
}
