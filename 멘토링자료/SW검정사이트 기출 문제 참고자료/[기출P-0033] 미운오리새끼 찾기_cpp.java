#include <cstdio>
#define MN 1000001
int a[MN], l[MN], T;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int i, g, r, n, k, ans;
    scanf("%d", &T);
    for(int tc = 1; tc <= T; tc++) {
        ans = -1;
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%d", a + i);
            l[i + 1] = gcd(a[i], l[i]);
        }
        for (i = n - 1, r = 0; i >= 0; i--) {
            g = gcd(l[i], r);
            r = gcd(r, a[i]);
            if (a[i] % g && g > ans) ans = g, k = a[i];
        }
        if(ans == -1) ans = k = 0;
        printf("#%d %d %d\n", tc, ans, k);
    }
}
