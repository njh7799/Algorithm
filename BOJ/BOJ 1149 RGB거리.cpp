#include<cstdio>
#define MIN(a,b) (((a)<(b))?(a):(b))
int n;
int RGB[1001][3];
int d[1001][3];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d %d %d", &RGB[i][0], &RGB[i][1], &RGB[i][2]);
	d[0][0] = RGB[0][0];
	d[0][1] = RGB[0][1];
	d[0][2] = RGB[0][2];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			d[i][j] = MIN(d[i - 1][(j + 1) % 3], d[i - 1][(j + 2) % 3]) + RGB[i][j];
		}
	}
	printf("%d", MIN(MIN(d[n - 1][0], d[n - 1][1]), d[n - 1][2]));
}