#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct Point {
	int x;
	int y;
};

Point delta[8] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1} };
int n, m, k;
int a[11][11], farm[11][11];
vector<int> v[11][11];

void springsummer() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int temp = 0;
			int cnt = 0;

			// 오름차순으로 정열되어 있으니까 앞에 나무부터 밥 먹임
			for (int k = 0; k < v[i][j].size(); k++) {
				if (farm[i][j] >= v[i][j][k]) {
					farm[i][j] -= v[i][j][k];
					v[i][j][k] += 1;
				}
				// 밥 없는 나무들 거름 만들준비 , cnt 함수에 거름 없는 나무가 몇개인지 카운팅
				else {
					temp += v[i][j][k] / 2;
					cnt += 1;
				}
			}
			// 밥 못먹은 나무들 죽이기
			while (cnt--) v[i][j].pop_back();
			farm[i][j] += temp;
		}
	}
}

void fall() {

	// v 를 뒤집어 줍니다. push_back 했을 때 아기 나무가 마지막에 들어오도록 정렬하려고
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			reverse(v[i][j].begin(), v[i][j].end());
		}
	}

	// 뿌려요
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int stop = 1;
			for (int k = 0; k < v[i][j].size(); k++) {
				if (v[i][j][k] % 5 == 0) {
					for (int t = 0; t < 8; t++) {
						int nx = i + delta[t].x;
						int ny = j + delta[t].y;
						if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
							v[nx][ny].push_back(1);
						}
					}
				}
			}
		}
	}

	// 다시 원래대로 돌려줍니다.
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			reverse(v[i][j].begin(), v[i][j].end());
		}
	}
}


//겨울 그냥 양분 추가
void winter() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			farm[i][j] += a[i][j];
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
		}
	}

	//farm 초기화
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			farm[i][j] = 5;
		}
	}

	int x, y, t;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &x, &y, &t);
		v[x][y].push_back(t);
	}



	while (k--) {
		springsummer();
		fall();
		winter();
	}

	int sum = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			sum += v[i][j].size();
		}
	}
	printf("%d\n", sum);

}