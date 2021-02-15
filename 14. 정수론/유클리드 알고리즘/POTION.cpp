//
// Created by NEW on 2021-02-05.
//
#include <vector>
#include <algorithm>

vector<int> solveSimulation(const vector<int>& recipe, vector<int> put){
    vector<int> oa = put;
    int n = recipe.size();
    vector<int> ret(n);
    // 각 재료를 최소한 recipe 만큼 넣어야 함.
    for(int i = 0; i< n; i++){
        ret[i] = max(recipe[i] - put[i], 0);
        put[i] += ret[i];
    }
    // 비율이 맞도록 재료를 추가하자.
    int iter = 0;
    while (true){
        ++iter;
        bool ok = true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                // ㅑ 번째 재료에 의해 모든 재료는 put[i] / recipe[i] = x 배 이상은 넣어야 함.
                // ->> put[j] = recipe[j] * x
                // 얘를 올림으로 싸악 해주기 위해서 분자에 recipe[i] - 1을 한다.
                int requiired = (put[i] * recipe[j] + recipe[i] - 1) / recipe[i];

                if (requiired > put[j]) {
                    ret[j] += requiired - put[j];
                    put[j] = requiired;
                    ok = false;
                }
            }
        if (ok)
            break;
    }
}