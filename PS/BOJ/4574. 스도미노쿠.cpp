#include<cstdio>
#include<algorithm>
using namespace std;
int row[10];
int column[10];
int tile[10];
bool domino[10][10];
int sudoku[9][9];
int cnt;
int tc = 0;
int dx[2] = { 1,0 };
int dy[2] = { 0,1 };
bool flag = false;

void print() {
	printf("Puzzle %d\n", tc);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			printf("%d", sudoku[i][j]);
		printf("\n");
	}
}

void reset() {
	flag = false;
	cnt = 9;
	for (int i = 0; i < 10; i++) {
		row[i] = 0;
		column[i] = 0;
		tile[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			domino[i][j] = 0;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sudoku[i][j] = 0;
		}
	}
}

int tilenum(int x, int y) {
	if (y < 0) {
		x -= 3;
		y += 9;
	}
	return (x / 3) * 3 + y / 3;
}

bool permit(int x, int y, int k) {
	return !(row[x] & (1 << k)) && !(column[y] & (1 << k)) && !(tile[tilenum(x, y)] & (1 << k));
}

void add(int x, int y, int num) {
	sudoku[x][y] = num;
	row[x] += (1 << num);
	column[y] += (1 << num);
	tile[tilenum(x, y)] += (1 << num);
}

void diff(int x, int y, int num) {
	sudoku[x][y] = 0;
	row[x] -= (1 << num);
	column[y] -= (1 << num);
	tile[tilenum(x, y)] -= (1 << num);
}

void adddomino(int x_1, int y_1, int x_2, int y_2, int num, int num2) {
	add(x_1, y_1, num);
	add(x_2, y_2, num2);
	if (num > num2) swap(num, num2);
	domino[num][num2] = true;
	cnt += 2;
}

void diffdomino(int x_1, int y_1, int x_2, int y_2, int num, int num2) {
	diff(x_1, y_1, num);
	diff(x_2, y_2, num2);
	if (num > num2) swap(num, num2);
	domino[num][num2] = false;
	cnt -= 2;
}

void dfs(int t) {
	if (flag) return;//출력 한번 했으면 return;
	if (t == 81) {
		if (cnt == 81) {
			print();
			flag = true;
		}
		return;
	}
	int x = t / 9;
	int y = t % 9;

	//직전 타일이 비어있으면 return;
	if (x % 3 == 2 && y % 3 == 0 && t > 18 && tile[tilenum(x, y - 1)] < ((1 << 10) - (1 << 1))) return;

	//이미 차 있으면 다음으로
	if (sudoku[x][y]) dfs(t + 1);


	else {
		//방향은 왼쪽과 아래 두가지 경우만 고려
		for (int dir = 0; dir < 2; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 9 && ny < 9) {

				if (sudoku[nx][ny]) continue;

				//두칸짜리 연속된 공간이 있을 때
				else {
					int fuckyou = 1;
					for (int i = 1; i < 9; i++) {
						for (int j = i + 1; j < 10; j++) {
							if (!domino[i][j]) {
								// x,y is i nx,ny is j
								if (permit(x, y, i) && permit(nx, ny, j)) {
									adddomino(x, y, nx, ny, i, j);
									dfs(t + 1);
									diffdomino(x, y, nx, ny, i, j);
								}

								// x,y is j nx,ny is i
								if (permit(x, y, j) && permit(nx, ny, i)) {
									adddomino(x, y, nx, ny, j, i);
									dfs(t + 1);
									diffdomino(x, y, nx, ny, j, i);
								}
							}
						}
					}
				}
			}
		}
	}
}


int main() {
	int n;
	//	freopen("input.txt", "r", stdin);
	while (scanf("%d", &n)) {
		if (!n) break;
		tc += 1;
		reset();
		for (int i = 0; i < n; i++) {
			int num, num2;
			char s[3], s2[3];
			scanf("%d %s %d %s", &num, s, &num2, s2);
			int x_1 = s[0] - 'A', x_2 = s2[0] - 'A';
			int y_1 = s[1] - '1', y_2 = s2[1] - '1';
			adddomino(x_1, y_1, x_2, y_2, num, num2);
		}
		for (int i = 1; i <= 9; i++) {
			char s[3];
			scanf("%s", s);
			sudoku[(s[0] - 'A')][(s[1] - '1')] = i;
			row[(s[0] - 'A')] += 1 << i;
			column[(s[1] - '1')] += 1 << i;
			tile[tilenum(s[0] - 'A', s[1] - '1')] += 1 << i;
		}
		dfs(0);
	}
}