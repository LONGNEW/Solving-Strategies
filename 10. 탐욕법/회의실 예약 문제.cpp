//
// Created by NEW on 2021-02-19.
//

#include <algorithm>
#include "vector"
using namespace std;

// 회의 시간의 경우 [begin, end) 구간 동안 회의실을 사용.

int n;
int begin[100], end[100];
int schedule(){
    // 일찍 '끝나는' 순서로 정렬.
    vector<pair<int, int>> order;
    for (int i = 0; i < n; ++i) {
        order.push_back(make_pair(end[i], begin[i]));
    }
    sort(order.begin(), order.end());

    // 가지고 있어야 하는 변수들.
    // earliest : 다음 회의가 언제 부터 시작할 수 있는지 기록
    // selected : 지금까지 선택한 회의의 수
    int earliest = 0, selected = 0;

    for (int i = 0; i < order.size(); ++i) {
        int meetingBegin = order[i].second, meetingEnd = order[i].first;

        if (earliest <= meetingBegin){
            earliest = meetingEnd;
            ++selected;
        }
    }
    return selected;
}