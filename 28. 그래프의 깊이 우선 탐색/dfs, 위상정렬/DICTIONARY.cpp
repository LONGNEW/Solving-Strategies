//
// Created by NEW on 2021-02-07.
//

// 알페ㅏ벳의 각 글자에 대한 인접 행렬 표현
// 간선(i, j)는 i가 j보다 사전순으로 앞에 존재한다는 의미.
vector<vector<int>> adj;
vector<int> seen, order;
void dfs(int here){
    seen[here] = 1;
    //모든 알파벳에 대한 dfs를 수행.
    for(int there = 0; there < adj.size(); ++there)
        // 간선이 존재하고, 아직 visit 하지 않았다면.
        if(adj[here][there] && !seen[there])
            dfs(there);
    // 연결된 모든 지점에 대해 dfs를 수행했다면.
    // order 벡터에 집어넣고 마지막에 이 벡터를 뒤집어서 위상정렬 한다.
    order.push_back(here);
}
vector<int> topologicalSort(){
    // 노드의 수만큼.
    int m = adj.size();
    seen = vector<int>(m, 0);
    order.clear();

    for (int i = 0; i < m; ++i)
        // 각 노드를 visit 하지 않았으면 dfs를 수행하기.
        if(!seen[i])
            dfs(i);
    reverse(order.begin(), order.end());
    // 그래프가 DAG(사이클이 없는 그래프)가 아니라면, 사이클이 존재한다면.
    // 역방향 간선이 존재한다.
    for(int i = 0; i < m; i++)
        for (int j = i + 1; j < m; ++j)
            // 현재 정렬되어 있는 순서가 i -> j 로 가는 순서니까
            // 이의 반대인 j -> i로 가는 간선이 존재하는지 확인한다.
            if (adj[order[j]][order[i]])
                // 사이클이 존재한다면 빈 벡터를 반환.
                return vector<int>();
    return order;
}
void makeGraph(const vector<string>& words){
    // 모든 알파벳이ㅔ 대한 인접 행렬을 만들었다.
    adj = vector<vector<int>>(26, vector<int>(26, 0));
    for (int j = 1; j < words.size(); ++j) {
        int i = j - 1, len = min(words[i].size(), words[j].size());
        // word[i]가 word[j] 앞에 오는 이유를 찾자.
        for(int k = 0; k < len; ++k){
            if(words[i][k] != words[j][k]){
                int a = words[i][k] - 'a';
                int b = words[j][k] - 'a';
                adj[a][b] = 1;
                break;
            }
        }
    }
}