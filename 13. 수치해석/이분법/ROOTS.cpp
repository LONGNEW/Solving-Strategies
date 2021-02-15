//
// Created by NEW on 2021-02-02.
//

#include "ROOTS.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// 미분을 위한 함수
vector<double> differentiate(const vector<double>& poly);
// 1차, 2차 방정식 풀이를 위한 함수
vector<double> solveNaive(const vector<double>& poly);
// f(x0)의 값을 반환하는 함수.
double evaluate(const vector<double>& poly, double x0);
//왜 방정식의 해의 절대 값은 L이하여야 할까?
const double L = 25;

vector<double> solve(const vector<double>& poly){
    int n = poly.size() - 1;

    if (n <= 2)
        return solveNaive(poly);

    vector<double> derivative = differentiate(poly);
    vector<double> sols = solve(derivative);
    sols.insert(sols.begin(), -L -1);
    sols.insert(sols.end(), L + 1);
    vector<double> ret;

    for (int i = 0; i + 1 < sols.size(); ++i){
        //왜 i + 1과 i를 비교하는 건가 했는데 당연하다.
        // 우리는 미분을 하고 난 후의 값들을 sols 벡터에 저장을 했다.
        // 즉 연속되는 이 극 값들은 하나가 양이었다면 하나는 음인 순서로 저장되어 있다.
        // 그래서 i, i + 1 사이에는 f(x)가 0이 되는 근을 가지고 있을 수 있다는 것이다.
        double x1 = sols[i], x2 = sols[i + 1];
        double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);

        if (y1 * y2 > 0)
            continue;

        // 불변 조건 f(x1) <= 0 <= f(x2)
        if (y1 > y2){
            swap(y1, y2); swap(x1, x2);
        }
        for (int iter = 0; iter < 100; ++iter){
            // 이분법을 수행하는 것으로 중간 위치를 찾아야 한다.
            double mx = (x1 + x2) / 2;
            // mid_x를 이용해서 f(x)값이 양수인지 음수인지 확인
            double my = evaluate(poly, mx);

            // my가 음수에 존재.
            if(y1 * my > 0){
                // 음수일 때는 이전에 음수인 것을 변경해 줘야함.
                x1 = mx;
                y1 = my;
            } else{
                // 양수일 떄는 그 반대.
                x2 = mx;
                y2 = my;
            }
        }
        ret.push_back((x1 + x2) / 2);
    }
    sort(ret.begin(), ret.end());

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


}

