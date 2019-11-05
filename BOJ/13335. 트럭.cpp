#include<cstdio>
#include<queue>
using namespace std;
struct Truck {
	int time;
	int weight;
};

int main() {
	queue<int> wait;
	queue<Truck> bridge;
	int n, w, l, a;
	scanf("%d %d %d", &n, &w, &l);
	for (int i = 0; i < n; i++) scanf("%d", &a), wait.push(a);
	int t = 0;
	int total = 0;
	for (t = 1;; t++) {
		if (!bridge.empty() && t - bridge.front().time >= w) total -= bridge.front().weight, bridge.pop();
		if (!wait.empty() && total + wait.front() <= l && bridge.size() <= w) total += wait.front(), bridge.push({ t,wait.front() }), wait.pop();
		if (wait.empty() && bridge.empty()) break;
	}
	printf("%d", t);
}