//
// Created by NEW on 2021-02-04.
//

#include "PASS486.h"

//Ten Million이 범위의 최대.
const int TM = 1000 * 1000 * 10;

//minFactor = i의 가장 작은 소인수.
int minFactor[TM + 1];

// minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는지.
int minFactorPower[TM + 1];

//factors[i] = i가 가진 약수의 수.
int factors[TM + 1];

void getFactorsSmart(){
    factors[1] = 1;
    for(int n = 2; n <= TM; ++n){
        if (minFactor[n] == n){
            minFactorPower[n] = 1;
            factors[n] = 2;
        } else{
            // 소수가 아니면,
            // 약수의 수를 응용해 약수의 수를 찾자.
            int p = minFactor[n];
            int m = n / p;

            // 재귀 느낌으로 n 을 이루는 가장 작은 소인수로 나눠서 m을 만듬.
            // 계속 이렇게 구하면 m의 약수의 개수 구하는데 이거를
            if (p != minFactor[m])
                minFactorPower[n] = 1;
            else
                minFactorPower[n] = minFactorPower[m] + 1;

            int a = minFactorPower[n];
            factors[n] = (factors[m] / a) * (a + 1);
        }
    }
}