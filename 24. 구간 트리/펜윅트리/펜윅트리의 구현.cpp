//
// Created by NEW on 2021-02-13.
//
#include "vector"
using namespace std;

// 가상의 배열 A[]의 부분합을 빠르게 구현할 수 있도록 함.
// 초기화 시에는 모든 값들이 0이라고 생각한다.
// 구간의 전체 합이 아닌 부분적인 합을 구하기 때문에 한 번에 구할 수가 없다.
// 구간 합을 구하는 sum 연산,
// 배열의 원소를 저장하는 add 연산을 만들어 준다.
struct FenwickTree {
    vector<int> Tree;
    FenwickTree(int n) : Tree(n + 1) {}

    // A[0 ~ pos] 까지의 부분 합을 구한다.
    int sum(int pos){
        // 트리 내부의 배열은 1부터 시작한다.
        // 외부에서 pos를 입력 받을 떄는 이와 달리 0부터 시작하기 때문에.
        // pos + 1을 해주어야 한다.
        ++pos;
        int ret = 0;
        while(pos > 0){
//             각 트리의 idx 마다 구 구간의 부분 합을 저장 하고 있다.
//             if pos == 7 일 때
//             우리가 더해야 하는 구간들은 7, 6, 4 이다.
//             그렇다면 이것을 어떻게 줄여야 하는가?
//             7 -> 111(2), 6 -> 110(2), 4 -> 100(2)
//             가장 마지막 비트를 지우면서 줄어 들어야 한다.
            ret += Tree[pos];
            // 가장 마지막 비트를 지우려면?
            // pos & (pos - 1) 이렇게 AND 연산을 수행 해 준다.
            // AND 연산을 수행하면 마지막 비트를 지운 값이 나오기 때문에 이를
            // pos에 담아주자.
            pos &= (pos - 1);
        }
        return ret;
    }
    // A[pos] 에 val을 더한다.
    void add(int pos, int val){
        // 위와 동일하게 idx 값을 1더해 주어야 한다.
        ++pos;
        // 부분합의 경우에 겹치는 부분들이 존재한다.
        while (pos < Tree.size()){
            Tree[pos] += val;
            // 만약 현재 추가하려는 pos가 5일 때.
            // 5 -> 6 -> 8 -> 16 순서대로 이 값들에도 추가를 해줘야 한다.
            // 이것은 어떻게 찾아야 하는가?
            // 5 -> 101(2), 6 -> 110(2), 8 -> 1000(2), 16 -> 10000(2)
            // 이 친구들의 연관성은 가장 마지막 비트에 존재하는 1을 더해 준것이다.
            pos += (pos & -pos);
            // -pos를 할 경우에 이는
            // ~(NOT)pos + 1을 한 것과 동일 한 값으로 pos에 대한 2의 보수를
            // 구한 것이다
            // 5의 경우엔 이진수 2의 칸이 비어있다 . 이를 채우기 위한 1이 2의 보수.
            // 6의 경우엔 이진수 8의 칸으로 올라가야 한다. 이를 채우기 위한 2가 2의 보수.
            // 8의 경우엔 이진수 16의 칸으로, 이를 채우기 위한 8이 2의 보수가 된다.
            // 그리하여 위의 연산을 수행한다.
        }
    }
};