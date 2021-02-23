//
// Created by NEW on 2021-02-07.
//

#include <set>
#include "vector"
#include "algorithm"
using namespace std;

vector<vector<int>> adj;
// 결과 로 얻어지는 circuit을 뒤집으면 오일러 서킷이 된다.
void getEulerCircuit(int here, vector<int>& circuit){
    for (int there = 0; there < adj[here].size(); ++there) {
        while (adj[here][there] > 0){
            // visit 대신에 그냥 존재하는 간선들을 없애버리는
            // 아주 상남자적 코드;;;
            adj[here][there]--;
            adj[there][here]--;
            getEulerCircuit(there, circuit);
        }
    }
    circuit.push_back(here);
}