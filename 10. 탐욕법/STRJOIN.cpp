//
// Created by NEW on 2021-02-20.
//

#include <set>
#include "vector"
#include "algorithm"
using namespace std;

// 문자열들의 길이가 입력 될 떄 하나로 합치는 최소 비용을 반환.
int concat(const vector<int>& lengths){
    // 우선순위 큐를 선언.
    // 얘가 가장 짧을 길이인 문자열 2개를 가져다 줄꺼임.
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < lengths.size(); ++i) {
        pq.push(lengths[i]);
    }
    int ret = 0;
    // 원소가 하나 이상 이면 계속 반복한다.
    while (pq.size() > 1){
        // 가장 짧은 문자열 두 개를 찾기
        int min1 = pq.top(); pq.pop;
        int min2 = pq.top(); pq.pop;
        pq.push(min1 + min2);
        ret += min1 + min2;
    }
    return ret;
}