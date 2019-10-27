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

			// ������������ �����Ǿ� �����ϱ� �տ� �������� �� ����
			for (int k = 0; k < v[i][j].size(); k++) {
				if (farm[i][j] >= v[i][j][k]) {
					farm[i][j] -= v[i][j][k];
					v[i][j][k] += 1;
				}
				// �� ���� ������ �Ÿ� �����غ� , cnt �Լ��� �Ÿ� ���� ������ ����� ī����
				else {
					temp += v[i][j][k] / 2;
					cnt += 1;
				}
			}
			// �� ������ ������ ���̱�
			while (cnt--) v[i][j].pop_back();
			farm[i][j] += temp;
		}
	}
}

void fall() {

	// v �� ������ �ݴϴ�. push_back ���� �� �Ʊ� ������ �������� �������� �����Ϸ���
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			reverse(v[i][j].begin(), v[i][j].end());
		}
	}

	// �ѷ���
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

	// �ٽ� ������� �����ݴϴ�.
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			reverse(v[i][j].begin(), v[i][j].end());
		}
	}
}


//�ܿ� �׳� ��� �߰�
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

	//farm �ʱ�ȭ
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