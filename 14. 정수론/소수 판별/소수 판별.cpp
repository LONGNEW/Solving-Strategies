//
// Created by NEW on 2021-02-04.
//

#include <cmath>

bool isPrime(int n){
    //소수 판별 시 언제나 예외는 1과 2다.
    // 1은 소수가 아니고, 2는 유일한 짝수 소수이다.
    if (n <= 1) return false;
    if (n == 2) return true;

    // 2를 제외한 모든 짝수는 소수가 아니다.
    if (n % 2 == 0) return false;
    // 3이상의 모든 홀수로 나눠보기
    //현재 하는 방법은 n 이 a * b 합성수로 나타낼 수 있을 때.
    // 특정 숫자와 다른 숫자의 곱으로 나타낼 수 있는지를 보려 하는 것이다.
    // 소수라면 1과 자기자신 밖에 없어서 다른 곱이 생기지 않는다.
    int sqrtn = int(sqrt(n));
    for (int div = 3; div <= sqrtn; div += 2){
        if(n % div == 0) return false;
    }
    return true;
}