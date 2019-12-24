#include<cstdio>

struct Area {
	int depth;
	int width;
};
Area top[5000];
Area bottom[5000];
int idx[40001];
int main() {
//	freopen("input.txt", "r", stdin);
	int n, l;
	int x_1, y_1, x_2, y_2;
	scanf("%d", &n);

	l = n / 2 - 1;

	scanf("%d %d", &x_1, &y_1);//clear buffer

	for (int i = 0; i < l; i++) {
		scanf("%d %d", &x_1, &y_1);
		scanf("%d %d", &x_2, &y_2);
		bottom[i] = { y_1, x_2 - x_1 };
		top[i] = { 0, x_2 - x_1 };
		idx[x_1] = i;
	}

	scanf("%d %d", &x_1, &y_1);// clear buffer
		
	int k;
	scanf("%d", &k);
	for (int i = 0; i < k;i++) {
		scanf("%d %d %d %d", &x_1, &y_1, &x_2, &y_2);
		int h = bottom[idx[x_1]].depth;
		top[idx[x_1]].depth = h;
		int x = idx[x_1] - 1;
		while (x >= 0 && top[x].depth < h) {
			if(bottom[x].depth < h) h = bottom[x].depth;
			top[x].depth = h;
			x -= 1;
		}
		h = bottom[idx[x_1]].depth;
		x = idx[x_1] + 1;
		while (x < l && top[x].depth < h) {
			if (bottom[x].depth < h) h = bottom[x].depth;
			top[x].depth = h;
			x += 1;
		}
	}
	int s = 0;
	for (int i = 0; i < l; i++) s += (bottom[i].depth - top[i].depth) * bottom[i].width;
	printf("%d\n", s);
}