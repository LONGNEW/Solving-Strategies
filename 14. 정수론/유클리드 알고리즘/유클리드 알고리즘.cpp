//
// Created by NEW on 2021-02-05.
//

//과거의 알고리즘은 두 수 p, q의 공약수 집합이 p-q, q의 공약수 집합과 같다는 것을 이용했다.
int gcd(int p, int q){
    if(p < q) swap(p);
    if (q == 0) return p;
    return gcd(p - q, q);
}

// 그러나 이것은 더 최적화를 할 수 있다. p - q 대신에 p % q 로 만들어진 나머지를 이용하자.
// 그리고 나머지를 취할 때는 p < q 에 대한 처리가 필요없다.
// p % q = p 이므로 다음 재귀 호출이 자동적으로 gcd(q, p)가 이루어진다.
int gcd(int p, int q){
    if(q == 0) return p;
    return gcd(p % q, q);
}