#include<cstdio>

long long d[61][31]; // memo

//DP top-down
long long dfs(int half, int full) {

	if (d[half][full]) return d[half][full];

	if (!half && !full) d[half][full] = 1;
	if (half) d[half][full] += dfs(half - 1, full);
	if (full) d[half][full] += dfs(half + 1, full - 1);
	return d[half][full];
}

int main() {
	int n;
	while (scanf("%d", &n)) {
		if (!n) break;
		printf("%lld\n", dfs(0, n));
	}
}