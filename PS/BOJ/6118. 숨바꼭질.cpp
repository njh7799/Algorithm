#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

vector<int> v[20001];
bool visit[20001];
int main() {
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	queue<int> q;
	q.push(1);
	int dist = -1;
	int target = 1;
	visit[1] = true;
	int mini, qsize;
	while (!q.empty()) {
		dist += 1;
		qsize = q.size();
		mini = 0x7fffffff;
		for (int i = 0; i < qsize; i++) {
			int crr = q.front();
			q.pop();
			mini = mini < crr ? mini : crr;
			for (int k = 0; k < v[crr].size(); k++) {
				if (!visit[v[crr][k]]) {
					target = v[crr][k];
					q.push(target);
					visit[target] = true;
				}
			}
		}
	}
	printf("%d %d %d\n", mini, dist, qsize);
}