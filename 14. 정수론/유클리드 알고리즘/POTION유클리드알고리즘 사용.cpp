//
// Created by NEW on 2021-02-05.
//

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}
// 분수 a / b 보다 같거나 큰 최소의 자연수를 반환.
// 올림이랑 동일한 알고리즘인데.
// a + b / b 하면 그 다음 값도 동일하게 소수(점이) 존재하는 수가 되니까.
// a + b - 1 / b 해가지고 중간값으로 만드는 거 같다. 사실 위에거 해도 괜찮을 거 같다.
int ceil(int a, int b){
    return (a + b - 1) / b
}
vector<int> solve(const vector<int>& recipe, const vector<int>& put){
    int n = recipe.size();
    // 모든 레시피의 최대공약수 b 구하기.
    int b = recipe[0];
    for (int i = 0; i < n; i++){
        b = gcd(b, recipe[i]);
    }
    // 만들려는 약의 최소한 1배는 만들어야 하니까 a는 b로 초기화 해줌.
    int a = b;
    // X를 직접 구하지 말고 ceil( put[i] * b, recipe[i])의 최대값을 구하자.
    for (int i = 0; i < n; ++i)
        a = max(a, ceil(put[i] * b, recipe[i]));
    // 이를 통해 우리는 비율 a / b 를 구할 수 있게 되었다.
    vector<int> ret(n);
    for (int i = 0; i < n; ++i)
        // 레시피의 비율대로 만든다.
        // 그리고 입력 받은 put 값을 빼주면
        // 추가해야하는 양을 구할 수 있다.
        ret[i] = recipe[i] * a / b - put[i];
    return ret;
}
