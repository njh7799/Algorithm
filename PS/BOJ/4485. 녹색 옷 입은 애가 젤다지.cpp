#include<cstdio>
#include<cstring>
#include<queue>
#define min(a,b) (((a)<(b))?(a):(b))
using namespace std;
int a[125][125];
int d[125][125];
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
struct Point {
	int x;
	int y;
	bool operator==(const Point &rhs) const {
		return d[this->x][this->y] == d[rhs.x][rhs.y];
	}
	bool operator>(const Point& rhs) const {
		return d[this->x][this->y] > d[rhs.x][rhs.y];
	}
	bool operator<(const Point& rhs) const {
		return d[this->x][this->y] < d[rhs.x][rhs.y];
	}
};
void init() {
	for (int i = 0; i < 125; i++) {
		for (int j = 0; j < 125; j++) d[i][j] = 0x7fffffff;
	}
}
int main() {
	int n, tc = 1;
	while(scanf("%d", &n)) {
		if (!n) break;
		init();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
			}
		}

		//코스트가 낮은 길부터 처리해주기 위해 pq 사용
		priority_queue<Point, vector<Point>, greater<Point>> pq;
		pq.push({ 0,0 });
		d[0][0] = a[0][0];
		while (!pq.empty()) {
			Point crr = pq.top();
			pq.pop();
			for (int dir = 0; dir < 4; dir++) {
				int nx = crr.x + dx[dir];
				int ny = crr.y + dy[dir];
				if (nx >= 0 && nx < n && ny >= 0 && ny < n && d[crr.x][crr.y]+a[nx][ny]<d[nx][ny]) {
					d[nx][ny] = d[crr.x][crr.y] + a[nx][ny];
					pq.push({ nx, ny });
				}
			}
		}
		printf("Problem %d: %d\n", tc++, d[n - 1][n - 1]);
	}
}