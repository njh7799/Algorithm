#include<cstdio>
#define abs(a) (((a) > 0) ? (a):(-(a)))
struct Point {
	int x;
	int y;
};
Point p[100000];
int d[100000];

int findDist(Point from, Point to) {
	return abs(from.x - to.x) + abs(from.y - to.y);
}
int main() {
	int mini = 0x7fffffff;
	int sumDistance = 0;
	//	freopen("input.txt", "r", stdin);
	int n, inx, iny;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &inx, &iny);
		p[i] = { inx,iny };
	}
	for (int i = 0; i < n - 1; i++) {
		d[i] = findDist(p[i], p[i + 1]);
		sumDistance += d[i];
	}
	for (int i = 1; i < n - 1; i++) {
		int crrDist = sumDistance - d[i - 1] - d[i] + findDist(p[i - 1], p[i + 1]);
		if (crrDist < mini) mini = crrDist;
	}
	printf("%d", mini);
}