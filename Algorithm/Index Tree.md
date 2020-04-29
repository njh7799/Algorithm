```cpp
#include <cstdio>
#include <vector>
#define N (1<<3)

using namespace std;

int indexTree[N * 2]; // 인덱스 트리
vector<int> initialData(N); // 초기 데이터 (입력 값)

// begin ~ end : 노드 범위
// left ~ right : 찾는 범위

int initTree(int node = 1, int begin = 0, int end = N - 1) {

	// 리프에 도달하면 리프 노드에 data 값을 넣어준다.
	if (begin == end) {
		return indexTree[node] = initialData[begin];
	}

	// 중간 값 설정
	int mid = (begin + end) / 2;

	// 상위 노드의 값은 두 하위 노드의 합과 같다.
	return indexTree[node] = initTree(node * 2, begin, mid) + initTree(node * 2 + 1, mid + 1, end);
}

int sum(int left, int right, int node = 1, int begin = 0, int end = N - 1) {

	// node의 범위가 목표 지점 안에 포함되어 있을 경우
	if (left <= begin && end <= right) {
		return indexTree[node];
	}

	// 현재 탐색 범위 (node의 범위)가 목표 지점을 완전히 벗어났을 경우
	if (end < left || right < begin) {
		return 0;
	}

	// 두 범위가 겹쳐져 있을 경우
	int mid = (begin + end) / 2;
	return sum(left, right, node * 2, begin, mid) + sum(left, right, node * 2 + 1, mid + 1, end);
}

void updateFromBottom(int node, int diff) {

	// 루트 노드까지 처리된 후 종료
	if (node == 0) {
		return;
	}
	indexTree[node] += diff;

	// 부모 노드로 이동
	updateFromBottom(node / 2, diff);
}

void updateFromTop(int index, int diff, int node=1, int begin=0, int end=N-1) {
	// index 가 node 의 범위 밖이면 update 하지 않는다.
	if (index < begin || end < index) return;

	// index 가 node 의 범위 안에 있기 때문에 update 한다.
	indexTree[node] += diff;

	// 리프 노드에 도달하면 중단한다.
	if (begin == end) return;
	int mid = (begin + end) / 2;
	updateFromTop(node * 2, begin, mid, index, diff);
	updateFromTop(node * 2 + 1, mid + 1, end, index, diff);
}

int main() {

	// 더미 데이터 초기화
	int n = 6;
	for (int i = 0; i < 6; i++) {
		initialData[i] = i + 1;
	}

	initTree();
	printf("리프 노드 리스트\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", indexTree[i + N]);
	}
	printf("\n\n");

	printf("인덱스 0에서 3까지의 합\n");
	printf("%d\n\n", sum(0, 3)); // 10

	printf("업데이트 전 루트 노드\n");
	printf("%d\n\n", indexTree[1]); // 21

	updateFromBottom(N + 7, 9);

	printf("업데이트 후 루트 노드\n");
	printf("%d\n\n", indexTree[1]); // 30

	updateFromTop(1, -9);

	printf("업데이트 후 루트 노드\n");
	printf("%d\n", indexTree[1]); // 21
}
```

 http://isukorea.com/blog/home/waylight3/216 

문제 :  https://www.acmicpc.net/problem/2517 

코드:

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX  500001
using namespace std;

int ranking[MAX];
int competent[MAX];
int ans[MAX];
int ind[MAX];
int tree[1<<20];
int indnode = (1 << 19) -1;
bool cmp(int a, int b) {
	return competent[a] < competent[b];
}

void update(int node) {
	while (node > 0) {
		tree[node] += 1;
		node /= 2;
	}
}

int getsum(int node, int begin, int end, int left, int right) {
	int mid = (begin + end) / 2;
	if (begin>right || end < begin) return 0;
	else if (begin >= left && end <= right) return tree[node];
	else return getsum(node * 2, begin, mid, left, right) + getsum(node * 2 + 1, mid + 1, end, left, right);
}



int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &competent[i]);
	for (int i = 1; i <= n; i++) {
		ranking[i] = i;
		ind[i] = i;
	}

	sort(ranking + 1, ranking + 1 + n, cmp);
	sort(ind + 1, ind + 1 + n, cmp);

	int stop = 1;

	for (int i = 1; i <= n; i++) {
		int index = ranking[i];
		int up = getsum(1, (1<<19), (1 << 20) - 1, indnode + 1, indnode + index - 1);
		update(indnode + index);
		ans[ind[i]] = ranking[i] - up;
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
}
```



[인덱스 트리](http://blog.naver.com/PostView.nhn?blogId=whtrb_study&logNo=220776497689&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView) vs [세크먼트 트리](http://blog.naver.com/PostView.nhn?blogId=whtrb_study&logNo=220776883103&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView)