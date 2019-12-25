#include<cstdio>
#include<queue>
using namespace std;
struct E {
	int value;
	int timer;
};

int main() {
//	freopen("input.txt", "r", stdin);
	deque<E> dq;
	int n, l, k;
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) {
		scanf("%d", &k);
		if (!dq.empty() && i - dq.front().timer >= l) dq.pop_front(); // ������ ���� ������ pop
		if (dq.empty()) dq.push_back({ k ,i }); // ���� ������� �׳� push
		else {
			while (!dq.empty() && k <= dq.back().value) dq.pop_back(); // ���� �ֱٿ� ���� ������ ū ������ ���� ������ �� ����
			dq.push_back({ k,i });// �ʿ� ���� �� �� ����� �ڿ� �ٿ���
		}
		printf("%d ", dq.front().value);
	}
}