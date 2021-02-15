//
// Created by NEW on 2021-02-04.
//

#include <cmath>

vector<int> factorSimple(int n){
    vector<int> ret;

    int sqrtn = int(sqrt(n));
    // 소수들만을 가지고 나누기를 한다.
    for(int div = 2; div <= sqrtn; ++div){
        // 소인수로 동일한 소수가 여러번 나올 수 있기 때문에
        // while문이 필요하다.
        while(n % div == 0){
            n /= div;
            ret.push_back(div);
        }
    }
    if (n > 1) ret.push_back(n);
    return ret;
}