#include<iostream>
#include<queue>
using namespace std;
struct Point {
	int x;
	int y;
};

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
char s[12][7];
bool check[12][6];
bool flag;

void reset() {
	flag = false;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			check[i][j] = 0;
		}
	}
}
void puyo() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (s[i][j] != '.' && !check[i][j]) {
				char c = s[i][j];
				queue<Point> q;
				queue<Point> pu;
				q.push({ i,j });
				pu.push({ i,j });
				check[i][j] = true;
				while (!q.empty()) {
					Point crr = q.front();
					q.pop();
					for (int dir = 0; dir < 4; dir++) {
						int nx = crr.x + dx[dir];
						int ny = crr.y + dy[dir];
						if (nx >= 0 && nx < 12 && ny >= 0 && ny < 6 && s[nx][ny] == c && !check[nx][ny]) {
							q.push({ nx,ny });
							check[nx][ny] = true;
							pu.push({ nx,ny });
						}
					}
				}
				if (pu.size() >= 4) {
					flag = true;
					while (!pu.empty()) {
						s[pu.front().x][pu.front().y] = '.';
						pu.pop();
					}
				}
				else while (!pu.empty()) pu.pop();
			}
		}
	}
}
void gravity() {
	for (int j = 0; j < 6; j++) {
		int floor = 11;
		for (int i = 11; i >= 0; i--) {
			if (s[i][j] != '.') {
				if (i == floor) floor -= 1;
				else {
					s[floor][j] = s[i][j];
					s[i][j] = '.';
					floor -= 1;
				}
			}
		}
	}
}

int main() {
	int cnt = 0;
	for (int i = 0; i < 12; i++) cin >> s[i];
	while (1) {
		reset();
		puyo();
		if (flag) cnt += 1;
		if (!flag) break;
		gravity();
	}
	printf("%d\n", cnt);
}