//
// Created by NEW on 2021-02-14.
//
#include "vector"
using namespace std;

struct OptimizedDisjointSet{
    // rank 에는 해당 노드가 루트인 경우에 해당 트리의 높이를 저장한다.
    // 그리고 이 높이를 이용해서 높이가 낮은 쪽을 높은 트리의 서브트리로 포함되게 한다.
    vector<int> parent, rank;

    OptimizedDisjointSet(int n) : parent(n), rank(n, 1){
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // u 가 속한 트리의 루트의 번호를 반환.
    int find(int u) {
        if(u == parent[u])
            return u;
        // parent[u] 의 값을 업데이트 함으로써 바로 루트 노드를 찾을 수 있게 해준다.
        // DP의 연장선.
        return parent[u] = find(parent[u]);
    }

    // u가 속한 트리와 v가 속한 트리를 합친다.
    void merge(int u, int v){
        u = find(u);
        v = find(v);

        // 이미 u와 v가 같은 트리이면 걸러낸다.
        if(u == v) return;

        // 우린 노드 v를 루트로 만들면서 이를 합치는데.
        // 이 높이가 u 보다 낮으면 이것을 합친 트리의 높이가 변화가 생긴다.
        // 이경우에 swap을 해서 바꿔주자.
        if(rank[u] > rank[v])
            swap(u, v);
        parent[u] = v;

        // 두 트리의 높이가 같다면 결과 트리의 높이를 1올려주자.
        if (rank[u] == rank[v])
            ++rank[v];
    }
};