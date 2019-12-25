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
		if (!dq.empty() && i - dq.front().timer >= l) dq.pop_front(); // 윈도우 벗어 났으면 pop
		if (dq.empty()) dq.push_back({ k ,i }); // 덱이 비었으면 그냥 push
		else {
			while (!dq.empty() && k <= dq.back().value) dq.pop_back(); // 가장 최근에 들어온 값보다 큰 값들은 쓸모 없으니 다 제거
			dq.push_back({ k,i });// 필요 없는 값 다 지우고 뒤에 붙여줌
		}
		printf("%d ", dq.front().value);
	}
}