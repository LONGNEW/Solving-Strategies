//
// Created by NEW on 2021-02-19.
//

#include <set>
#include "vector"
#include "algorithm"
using namespace std;

int order(const vector<int>& russian, const vector<int>& korean){
    int n = russian.size(), wins = 0;
    // 남아있는 선수들의 레이팅.
    // 이진 검색 트리에 넣어서.
    // 선수들의 추가 삭제 연산을 빠르게 하려는 듯.
    // 선수들의 점수도 더 빨리 찾을 수 있음.
    multiset<int> ratings(korean.begin(), korean.end());

    for (int rus = 0; rus < n; ++rus) {
        // 가장 레이팅이 높은 한국 선수가 이길수 없으면,
        // 가장 레이팅 낮은 애와 경기 시킴.
        if(*ratings.rbegin() < russian[rus])
            ratings.erase(ratings.begin());
        // 그 외의 경우는 이길 수 있는 선수 중 가장 레이팅 낮은 애와 경기 붙임
        else{
            ratings.erase(ratings.lower_bound(russian[rus]));
            ++wins;
        }
    }
    return wins;
}