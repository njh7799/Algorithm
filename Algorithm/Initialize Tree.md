# 트리 초기화 시키기

## 조건

- 간선 리스트가 주어진다.
- 루트 노드가 주어진다.

## 목표

자신의 부모 노드를 가르키는 `parent` 배열과 깊이를 의미하는 `depth` 배열을 완성한다.

## 원리

루트 노드부터 인접한 노드를 BFS 탐색하여 `parent` 및 `depth` 배열을 채워 놓는다.

## 코드

```cpp
#include <cstdio>
#include <queue>
#define MAX 1000000
using namespace std;

int main(){
    queue<int> list[MAX+1];
    int* parent = (int*)malloc(sizeof(int)*(MAX+1)); 
    int* depth = (int*)malloc(sizeof(int)*(MAX+1)); 
    
    // 간선 리스트를 입력 받는다
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        list[a].push(b);
        list[b].push(a);
    }

	queue<int> q;
	q.push(1); // 루트 노드가 1이라고 가정
    
    // BFS 탐색 시작
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
        // crr 노드의 자식들을 탐색한다. 
        // 이 때 연결된 모든 엣지를 확인하기 때문에 부모 child에 부모노드가 들어가는 경우도 하나 생긴다.
        // 이는 뒤에서 예외처리할 것이다.
		while (!list[curr].empty()) {
            int child = list[curr].front();
            list[curr].pop();
            
            // parent[child]에 값이 있다는 것은 이미 부모 노드와 연결 되었다는 뜻이다.
            // 이 경우가 위에서 예고한 케이스이다.
            if (parent[child]) {
                continue;
            };
            q.push(child);
            parent[child] = curr;
            depth[child] = depth[curr] + 1;
		}
	}
}

```

