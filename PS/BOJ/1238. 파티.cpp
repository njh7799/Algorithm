#include<cstdio>
#include<queue>
#include<vector>
#define INFI 0x7fffffff
using namespace std;

struct Point {
	int node;
	int dist;

	bool operator ==(const Point& rhs) const {
		return this->dist == rhs.dist;
	}
	bool operator <(const Point& rhs) const {
		return this->dist < rhs.dist;
	}
	bool operator >(const Point& rhs) const {
		return this->dist > rhs.dist;
	}
};

int main() {
	vector<Point> w[1001];
	vector<Point> w2[1001];
	int forward[1001] = {}; // X로 가는 거리
	int backward[1001] = {}; // 집으로 돌아가는 거리
	int n, m, x;
	int p, q, t;
	scanf("%d %d %d", &n, &m, &x);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &p, &q, &t);
		w[p].push_back({ q,t });
		w2[q].push_back({ p,t });
	}
	for (int i = 1; i <= n; i++) forward[i] = backward[i] = INFI;
	priority_queue<Point, vector<Point>, greater<Point>> fpq;
	priority_queue<Point, vector<Point>, greater<Point>> bpq;

	//x까지 가는 거리
	fpq.push({ x, 0 });
	forward[x] = 0;
	while (!fpq.empty()) {
		Point crr = fpq.top();
		fpq.pop();
		int node = crr.node;
		int dist = crr.dist;
		for (int i = 0; i < w2[node].size(); i++) {
			if (forward[node] + w2[node][i].dist < forward[w2[node][i].node]) {
				forward[w2[node][i].node] = forward[node] + w2[node][i].dist;
				fpq.push(w2[node][i]);
			}
		}
	}

	//집으로 돌아가는 거리
	bpq.push({ x, 0 });
	backward[x] = 0;
	while (!bpq.empty()) {
		Point crr = bpq.top();
		bpq.pop();
		int node = crr.node;
		int dist = crr.dist;
		for (int i = 0; i < w[node].size(); i++) {
			if (backward[node] + w[node][i].dist < backward[w[node][i].node]) {
				backward[w[node][i].node] = backward[node] + w[node][i].dist;
				bpq.push(w[node][i]);
			}
		}
	}

	int maxi = -(1 << 20);
	for (int i = 1; i <= n; i++) maxi = maxi > forward[i] + backward[i] ? maxi : forward[i] + backward[i];
	printf("%d\n", maxi);
}