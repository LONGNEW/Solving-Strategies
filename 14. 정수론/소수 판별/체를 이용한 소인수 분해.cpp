//
// Created by NEW on 2021-02-04.
//

#include <cmath>

int n;
// i의 가장 작은 소인수를 저장한다.
int minFactor[MAX_N];
//에라토스테네스의 체를 수행하며 가장 작은 소인수도 저장한다.
void eratosthenes2(){
    //1은 항상 예외처리.
    minFactor[0] = minFactor[1] = -1;
    for ( int i = 1; i <= n; i++)
        // minFactor의 초기화는 자기자신으로 하도록하자.
        minFactor[i] = i;

    int sqrtn = int(sqrt(n));
    for(int i = 2; i <= sqrtn; i++){
        // 가장 작은 소수를 이용해 체를 쓰면서.
        // 아까는 소수를 판별하는 bool을 바꿨지만
        // 현재는 가장 작은 소수의 배수임을 알리는 방법.
        if (minFactor[i] == i)
            for (int j = i * i; j <= n; j += i)
                if(minFactor[j] == j)
                    minFactor[j] = i;
    }
}

vector<int> factor(int n){
    vector<int> ret;
    // n이 1이 될 때까지 가장 작은 소인수로 나누기를 반복.
    while (n > 1){
        ret.push_back(minFactor[n])
        n /= minFactor[n]
    }
    return ret;
}