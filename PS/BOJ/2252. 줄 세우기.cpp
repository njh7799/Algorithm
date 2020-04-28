#include<iostream>
#include<queue>
#define MAX 32000

using namespace std;

int searchZeroInDegreeNode(int topological[]) {
	for (int i = 1; i <= MAX ; i++) {
		if (topological[i] != 0) {
			continue;
		}
		topological[i] = -1;
		return i;
	}
	return 0;
}

int main() {
	int n, m;
	cin >> n >> m;
	queue<int> q[MAX+1];
	int topological[MAX+1] = {};
	for (int i = 0; i < m; i++) {
		int to;
		int from;
		cin >> to >> from;
		q[to].push(from);
		topological[from] += 1;
	}
	for (int i = 0; i < n;i++) {
		int targetNode = searchZeroInDegreeNode(topological);
		cout << targetNode << ' ';
		while (!q[targetNode].empty()) {
			int to = q[targetNode].front();
			q[targetNode].pop();#include<iostream>
#include<queue>
#define MAX 32000

using namespace std;

int searchZeroInDegreeNode(int topological[]) {
	for (int i = 1; i <= MAX ; i++) {
		if (topological[i] != 0) {
			continue;
		}
		topological[i] = -1;
		return i;
	}
	return 0;
}

int main() {
	int n, m;
	cin >> n >> m;
	queue<int> q[MAX+1];
	int topological[MAX+1] = {};
	for (int i = 0; i < m; i++) {
		int to;
		int from;
		cin >> to >> from;
		q[to].push(from);
		topological[from] += 1;
	}
	for (int i = 0; i < n;i++) {
		int targetNode = searchZeroInDegreeNode(topological);
		cout << targetNode << ' ';
		while (!q[targetNode].empty()) {
			int to = q[targetNode].front();
			q[targetNode].pop();
			topological[to] -= 1;
		}
	}
}
			topological[to] -= 1;
		}
	}
}