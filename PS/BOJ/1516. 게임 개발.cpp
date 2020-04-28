#include<cstdio>
#include<queue>
using namespace std;

int minTime[501];
int time[501];
int indegree[501];
queue<int> v[501];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &time[i]);

		while (1) {
			int input;
			scanf("%d", &input);
			if (input == -1) {
				minTime[i] = time[i];
				break;
			}
			v[input].push(i);
			indegree[i]++;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (indegree[j]) {
				continue;
			}
			while (!v[j].empty()) {
				int to = v[j].front();
				v[j].pop();
				indegree[to] -= 1;
				if (minTime[j] + time[to] <= minTime[to]) {
					continue;
				}
				minTime[to] = minTime[j] + time[to];
			}
			indegree[j] = -1;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d\n", minTime[i]);
	}
}