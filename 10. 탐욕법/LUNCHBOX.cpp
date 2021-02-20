//
// Created by NEW on 2021-02-20.
//

#include <set>
#include "vector"
#include "algorithm"
using namespace std;

int n, e[MAX_N], m[MAX_N];
int heat(){
    // 어느 순서로 데워야 하는가?
    vector<pair<int, int>> order;
    for (int i = 0; i < n; ++i) {
        // 먹는 시간은 e[]에 들어있고.
        // 우리는 이 시간을 내림차순으로 정렬하고 싶다.
        // 그런데 sort를 이용하면 오름차순으로 정렬을 하니까 이를 이용해서
        // e[]값들에 - 를 붙여서 다시 꺼낼떄 -를 붙여 원 상태로 돌리도록 하자.
        order.push_back(make_pair(-e[i], i));
        // 저 의도가 아니라 그냥 idx만 찾을 의도 였네 ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
        // ㄲㅃ
    }
    int ret = 0, beginEat = 0;
    for (int i = 0; i < n; ++i) {
        int box = order[i].second;
        beginEat += m[box];
        ret = max(ret, beginEat + e[box]);
    }
}