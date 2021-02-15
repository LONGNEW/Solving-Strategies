//
// Created by NEW on 2021-02-02.
//

#include "RATIO.h"
#include "LOAN.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 최대 게임의 수는 20억
long long L = 2000000000;
int ratio(long long b, long long a){
    return (a * 100) / b;
}
int neededGames(long long games, long long won){
    //이분법을 실행할 것임.
    // 20억 연승을 해도 1%가 오르지 않는 다면 이 경우는 불가능 함.
    if(ratio(games, won) == ratio(games + L, won + L)){
        return -1;
    }
    long long lo = 0, hi = L;
    // 반복문 불변식:
    //1. lo게임은 이겨도 1%증가하지 않는다.
    //2. hi 게임 승리시에는 1%증가한다.
    while (lo + 1 < hi){
        long long mid = (lo + hi) / 2;
        if(ratio(games, won) == ratio(games + mid, won + mid)){
            lo = mid;
        } else{
            hi = mid;
        }
    }
    // 모든 경우가 반복되고 난 후에 1%가 증가하는 최소의 경우는 hi에 존재한다. lo 와 hi가
    // 엇갈리며 끝나는데 이러면 값이 같은 경우에 끝난다고 볼 수 있다. 즉 lo도 정답이 되긴 하지만,
    // 헷갈린다. hi에 원래 부터 1%증가하면 값을 넣도록 했으니 hi를 리턴하자.
    return hi;
}
// 그렇다면 수학적으로는 어떻게 풀까?
//우리가 원하는 값은 [((M + x) / (N + x)) * 100 >= R] 이런 값을 구해야 한다.
//이를 수식으로 풀어내자.
//(M + x) * 100 >= R(N + x)
//(100x - Rx) >= RN - 100M
//x >= (RN - 100M) / (100 - R)
//최소의 정수는 오른쪽 분수를 올림한 값이며, 최소 연승 수가 된다.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

}