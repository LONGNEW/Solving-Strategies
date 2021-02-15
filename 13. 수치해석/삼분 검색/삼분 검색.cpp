//
// Created by NEW on 2021-02-03

// f(x) 나타내는 식
double f(double x);
// [lo, hi] 구간에서 f(x)의 최대치를 갖는 x를 반환.
// 극대를 찾는과정.
double ternary(double lo, double hi){
    for (int i = 0; i < 100; i++){
        double a = (2 * lo + hi) / 3.0;
        double b = (lo + 2 * hi) / 3.0;
        if(f(a) > f(b)){
            // 극대를 지나서 순감소 하는 형태의 함수가 만들어 지게 됨.
            hi = b;
        } else{
            lo = a;
        }
    }
}