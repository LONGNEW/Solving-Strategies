//
// Created by NEW on 2021-02-11.
//
#include "vector"
using namespace std;


const int INT_MAX = numeric_limits<int>::max();
struct RMQ{
    // 배열의 길이
    int n;
    // 각 구간의 최소치.
    vector<int> rangeMin;
    RMQ(const vector<int>& array){
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n - 1, 1);
    }

    //node 가 array[left, right]배열을 표현.
    // node를 루트로 하는 서브트리를 초기화, 이 구간의 최소치를 반환.
    int init(const vector<int>& array, int left, int right, int node){
        if (left == right)
            return rangeMin[node] = array[left];

        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return  rangeMin[node] = min(leftMin, rightMin);
    }

    // 구간의 최소치를 구하는 질의(query) 연산.
    // node가 표현하는 범위 array[nodeLeft, nodeRight]가 주어짐.
    // 이 범위와 array[left, right]의 교집합의 최소치를 구한다.
    int query(int left, int right, int node, int nodeLeft, int nodeRight){

        // 두 구간에 교집합이 존재하지 않으면(겹치지 않으면) 아주 큰 값을 반환.
        if (right < nodeLeft || left > nodeRight)
            return INT_MAX;

        // node가 표현하는 범위가 array[left, right]에 완전히 포함.
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];

        // 양쪽 구간을 나눠서 푼 뒤 결과를 합침.(그냥 최솟값 찾아서 리턴.)
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }

    int query(int left, int right){
        return query(left, right, 1, 0, n - 1);
    }

    // array[index] = newValue로 바뀌었을 때 node를 루트로 하는 구간 트리를 갱신. 노드가 표현하는 구간의 최소치를 반환.
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
        // index가 노드가 표현하는 구간과 상관 없는 경우엔 무시.
        if (index < nodeLeft || nodeRight > index)
            return rangeMin[node];

        // 트리의 리프까지 왔을 떄.
        if(nodeLeft == nodeRight)
            return rangeMin[node] = newValue;

        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
    }

    int update(int index, int newValue){
        return update(index, newValue, 1, 0, n - 1);
    }
};


