//
// Created by NEW on 2021-02-04.
//

#include <cmath>

int n;
bool isPrime[MAX_N + 1];
// 아래의 함수를 수행하고 나면 위의 bool 값의 배열에 소수인지 아닌지를 확인할 수 있게 됨.
void eratosthenes(){
    memset(isPrime, 1, sizeof (isPrime));
    // 1은 항상 예외처리.
    isPrime[0] = isPrime[1] = false;

    int sqrtn = sqrt(n);
    for(int i = 2; i < sqrtn; i++){
        if (isPrime[i])
            // i번쨰 숫자를 확인 할 떄.
            // 맨 처음 만나는 2, 3, ... 의 경우엔 소수이다.
            // 워... 그리고 i * i 에서 시작을 해도 된다.
            // 작은 숫자에서 모든 경우를 확인 하고 그 다음으로 넘어갔을 떄.
            // 아 어차피 구구단 하면서 지나갔다고 보면 된다.
            // 만약 현재 i 가 5라서 25에서 부터 시작을 하려 한다.
            // 2일 때 10을 지우고, 3일 때 15 지우고, 어차피 얘네도 2, 3, 4 단에 존재하니까... 지워버리는 것
            for(int j = i * i; j <= n; j += i)
                // 여기선 반복문이 n까지 수행되어서 모든 소수들을 찾는다.
                // 위의 조건은 sqrt(n) 까지만 수행해서 시간 복잡도를 줄인다.
                isPrime[j] = false;
    }
}
