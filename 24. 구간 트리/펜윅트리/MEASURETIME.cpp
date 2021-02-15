//
// Created by NEW on 2021-02-13.
//

#include "vector"
using namespace std;

struct FenwickTree {
    vector<int> Tree;
    FenwickTree(int n) : Tree(n + 1) {}

    int sum(int pos){
        ++pos;
        int ret = 0;
        while(pos > 0){
            ret += Tree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }

    void add(int pos, int val){
        ++pos;
        while (pos < Tree.size()){
            Tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};

// 펜윅트리를 이용하는데. 현재 까지 숫자가 출현한 횟수를 기록한다.
long long countMoves(const vector<int>& A){
    FenwickTree tree(1000000);
    long long ret = 0;

    for (int i = 0; i < A.size(); ++i) {
        // A[i] 번째 숫자보다 작은 놈들의 출현횟수는 필요없고.
        // 그것보다 큰 놈들의 출현 횟수를 찾는다.
        // 999999 번째 까지의 숫자들의 출현 횟수 모두를 더해서.
        // 자기보다 작은 놈드르이 출현 횟수르르 뺌으로써 정답을 구함.
        ret += tree.sum(999999) - tree.sum(A[i]);
        tree.add(A[i], 1);
    }
    return ret;
}