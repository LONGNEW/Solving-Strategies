//
// Created by NEW on 2021-02-06.
//

// 인접 리스트 표현.
vector<vector<int>> adj;
// 각 정점의 방문 여부를 나타냄.
vector<bool> visited;
void dfs(int here){
    cout << "DFS visits" << here << endl;
    visited[here] = true;
    // 모든 인접 정점을 순회.
    for(int i = 0; i < adj[here].size(); i++){
        int there = adj[here][i];
        // 아직 방문 한적이 없다면
        if (!visited[there])
            dfs(there);
    }
}
// 모든 정점을 방문한다.
void dfsAll(){
    // visited를 false로 초기화.
    visited = vector<bool>(adj.size(), false);
    // 모든 정점을 순회...
    for (int i = 0; i < adj.size(); ++i) {
        if (!visited[i])
            dfs(i);
    }
}