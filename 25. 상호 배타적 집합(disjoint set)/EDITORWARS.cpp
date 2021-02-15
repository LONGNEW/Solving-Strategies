//
// Created by NEW on 2021-02-14.
//

#include "vector"
using namespace std;

struct  BipartiteUnionFind{
    // parent[i] = i의 부모 노드, 루트라면 i, 동일할 것이다.
    // rank[i] = i가 루트인 경우, i를 루트로 하는 트리의 랭크
    // enemy[i] = i가 루트인 경우, 해당 집합과 적대 관계인 집합의 루트의 번호. (없으면 -1)
    // size[i] = i가 루트인 경우, 해당 집합의 크기.
    // 다 루트일 떄만 뭐가 있네 ㅋㅋㅋㅋㅋㅋㅋㅋㅋ
    vector<int> parent, rank, enemy, size;
    BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1){
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int u) {
        if(u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }
    // u가 속한 트리와 v가 속한 트리를 합친다.
    int merge(int u, int v){
        // u나 v가 공집합인 경우 나머지 하나를 반환.
        if(u == -1 || v == -1)
            return max(u, v);

        u = find(u);
        v = find(v);

        // 이미 u와 v가 같은 트리이면 걸러낸다.
        if(u == v) return u;

        // 우린 노드 v를 루트로 만들면서 이를 합치는데.
        // 이 높이가 u 보다 낮으면 이것을 합친 트리의 높이가 변화가 생긴다.
        // 이경우에 swap을 해서 바꿔주자.
        if(rank[u] > rank[v])
            swap(u, v);
        parent[u] = v;

        // 두 트리의 높이가 같다면 결과 트리의 높이를 1올려주자.
        if (rank[u] == rank[v])
            ++rank[v];

        parent[u] = v;
        size[v] += size[u];
        return v;
    }

};