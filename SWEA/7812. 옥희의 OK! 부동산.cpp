#include <cstdio>
#include <cstdlib>

int solve(int n, int m, int* a) {
	int l = 0;
	int r = 0;
	int count = 0;
	int sum = a[0];
	while (r < n) {
		if (sum == m) { 
			count += 1;
			r += 1;
			sum += a[r];
		}
		else if (sum < m) {
			r += 1;
			if (r >= n) break;
			sum += a[r];
		}
		else if (sum > m) {
			sum -= a[l];
			l += 1;
		}
	}
	return count;
}
int main() {
//	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		int n, m;
		scanf("%d %d", &n, &m);
		int* a = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		int answer = solve(n, m, a);
		printf("#%d %d\n", tc, answer);
	}
	return 0;
}