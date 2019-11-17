#include<cstdio>
#include<vector>
using namespace std;
char s[50][51];
int n, m;
struct Point {
	int x;
	int y;
};

bool isValidRow(int x, int y) {
	if (!(x == 0 || s[x - 1][y] == '#')) return false;
	for (int i = 1; i <= 2; i++) {
		if (x + i >= n) return false;
		if (s[x + i][y] == '#') return false;
	}
	return true;
}
bool isValidColumn(int x, int y) {
	if (!(y == 0 || s[x][y - 1] == '#')) return false;
	for (int j = 1; j <= 2; j++) {
		if (y + j >= m) return false;
		if (s[x][y + j] == '#') return false;
	}
	return true;
}

int main() {
	//	freopen("input.txt", "r", stdin);
	vector<Point> v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%s", s[i]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '#') continue;
			if (!isValidRow(i, j) && !isValidColumn(i, j)) continue;
			v.push_back({ i + 1,j + 1 });
		}
	}
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++) printf("%d %d\n", v[i].x, v[i].y);
}