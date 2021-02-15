//
// Created by NEW on 2021-02-03.
//

#include "UVa_OJ_10385.h"
#include <vector>
#include <algorithm>
using namespace std;

double t;
vector<double> runSpeed, cycleSpeed;

// 달리기 구간의 길이가 run 일 때 i번 선수가 걸리는 시간, 차이를 가장 크게 만들려고 하는 중.
double time(int i, double run){
    double cycle = t - run;
    return run / runSpeed[i] + cycle / cycleSpeed[i];
}

// 달리기 구간 길이가 r일 떄의, othres(r) - cheater(r)을 반환 한다.
double diff(double r){
    int n = runSpeed.size();
    double cheater = time(n - 1, r);
    double others = time(0, r);
    //나머지 선수들 중 가장 잘한 사람 기록 넣을 거면 max를 했어야지 왜 min을 한데?
    // 선형함수중 최소치를 나타내서 오목함수를 그린다.
    // min이 이 최소치를 나타내는 것으로 보임.
    for(int i = 1; i< n - 1; ++i){
        others = min(others,time(i, r));
    }
    return others - cheater;
}
// diff 함수의 극대점(최대치의 위치)을 삼분 검색으로 계산.
double maxDifference(){
    double lo = 0, hi = t;
    for(int i = 0; i < 100; i++){
        double a = (2 * lo + hi) / 3;
        double b = (lo + 2 * hi) / 3;

        if(diff(a) > diff(b)){
            hi = b;
        } else{
            lo = a;
        }
    }
    return (lo + hi) / 2;
}