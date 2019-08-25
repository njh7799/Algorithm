// BOJ 17406 �迭 ������4
// ��ó: https://www.acmicpc.net/problem/17406

#include<cstdio>
#include<algorithm>
using namespace std;
int A[50][50];
int a[50][50];
int rot[6][3];
int order[6];

//�� ���� �����̴� �Լ�
void move(int r, int c, int s) {
	r = r - 1;
	c = c - 1;
	int temp = a[r - s][c - s];
	for (int i = -s; i < s; i++) a[r + i][c - s] = a[r + i + 1][c - s];
	for (int i = -s; i < s; i++) a[r + s][c + i] = a[r + s][c + i + 1];
	for (int i = s; i > -s; i--) a[r + i][c + s] = a[r + i - 1][c + s];
	for (int i = s; i > -s; i--) a[r - s][c + i] = a[r - s][c + i - 1];
	a[r - s][c - s + 1] = temp;
}

// �迭 �ʱ�ȭ
void setarray() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			a[i][j] = A[i][j];
		}
	}
}


// �ּڰ��� ���
int cal(int n, int m) {
	int mini = 1 << 20;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m; j++) {
			sum += a[i][j];
		}
		mini = mini < sum ? mini : sum;
	}
	return mini;
}

int main() {
	int globalmin = 0x7fffffff;
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 3; j++) scanf("%d", &rot[i][j]);
	}
	for (int i = 0; i < k; i++) {
		order[i] = i;
	}
	do {
		setarray();
		for (int i = 0; i < k; i++) {
			int r = rot[order[i]][0];
			int c = rot[order[i]][1];
			int s = rot[order[i]][2];
			for (int j = 1; j <= s; j++) move(r, c, j);
		}
		int localmin = cal(n, m);
		if (localmin < globalmin) globalmin = localmin;
	} while (next_permutation(order, order + k));
	printf("%d", globalmin);
}