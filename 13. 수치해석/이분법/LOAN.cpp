//
// Created by NEW on 2021-02-02.
//

#include "LOAN.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// amount원을 연 이율 rates 퍼센트로 duration월 간 한 달에 monthlyPayment로 상환.
double balance(double amount, int duration, double rates, double monthlyPayment){
    double balance = amount;
    for(int i = 0; i < duration; ++i){
        // 한 달에 대출 잔금(amount)은
        // amount + amount * (P/12)%(퍼센트) 늘기 때문에
        // 퍼센트를 나타내려고 100으로 나눈거 같다.
        balance *= (1.0 + (rates / 12.0) / 100);
        balance -= monthlyPayment;
    }
    return balance;
}
// 그렇다면 amount원을 duration달 안에 갚으려면 얼마나 내야 하나.
double payment(double amount, int duration, double rates){
    //여기선 무엇을 해야 하는가 방정식을 풀어야 한다.
    // 정의역 즉 x값이 될수 있는 것들은? 몇 개월이 걸리는 가를 표시.
    // ******* 한 달에 얼마를 갚는 가를 보는 것이다.*****
    // 한달에 최대한으로 지불하면? 원금을 다 갚아버리는 것. 그래서 hi는 저렇게 나온다.
    // 1. lo원씩 갚으면 못 갚는다.
    // 2. hi원씩 갚으면 duration개월 안에 갚을 수 있다.
    double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100.0);
    for (int i = 0; i < 100; ++i){
        //이분법을 해서 답을 찾는 과정. 중간값을 찾자.
        double mid = (lo + hi) / 2.0;

        if(balance(amount, duration, rates, mid) <= 0){
            // 매 달 mid 만큼 지불해서 모두 상환을 했을 경우 hi를 낮춘다.
            hi = mid;
        }else{
            // 상환이 불가능 하면 매 달 지불하는 금액을 늘려야 하나 lo를 바꿈.
            lo = mid;
        }
    }
    // 마지막엔 hi가 상환이 가능한 거니까 hi를 리턴.
    return hi;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

}
