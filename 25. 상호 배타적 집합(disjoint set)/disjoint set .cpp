//
// Created by NEW on 2021-02-14.
//
#include "vector"
using namespace std;

struct NaiveDisjointSet{
    vector<int> parent;

    NaiveDisjointSet(int n) : parent(n){
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // u 가 속한 트리의 루트의 번호를 반환.
    // const 를 넣음으로써 리턴 값을 상수로 고정한다.
    // 다른 수정이 불가능 하게 만들어버림
    int find(int u) const {
        if(u == parent[u])
            return u;
        return find(parent[u]);
    }

    // u가 속한 트리와 v가 속한 트리를 합친다.
    void merge(int u, int v){
        u = find(u);
        v = find(v);

        // 이미 u와 v가 같은 트리이면 걸러낸다.
        if(u == v) return;
        parent[u] = v;
    }
};
