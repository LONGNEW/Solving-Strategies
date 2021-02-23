//
// Created by NEW on 2021-02-23.
//

#include <set>
#include <string>
#include "vector"
#include "algorithm"
using namespace std;

vector<vector<int>> adj;
// graph[i][j] = i로 시작해서 j로 끝나는 단어의 목록.
vector<string> graph[26][26];
// 차수를 저장해놓는 배열이다.
// indegree[i] = i로 시작하는 단어의 수
// outdegree[i] = i로 끝나는 단어의 수
vector<int> indegree, outdegree;
void makeGraph(const vector<string>& words){
    // 전역 변수 초기화
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j)
            graph[i][j].clear();

    adj = vector<vector<int>>(26, vector<int>(26, 0));
    indegree = outdegree = vector<int>(26, 0);
    // 입력 받은 단어들을 그래프에 추가
    for (int i = 0; i < words.size(); ++i) {
        int a = words[i][0] - 'a';
        int b = words[i][words[i].size() - 1] - 'a';
        graph[a][b].push_back(words[i]);
        adj[a][b]++;
        outdegree[a]++;
        indegree[b]++;
    }
}
void getEulerCircuit(int here, vector<int>& circuit){
    for (int there = 0; there < adj.size(); ++there)
        while (adj[here][there] > 0){
            // 유방향 그래프이기 때문에
            // 가는 거 하나만 간선을 없앤다.
            // 근데 어차피 adj에 간선은 하나씩만 저장 되는거 아닌가??
            adj[here][there]--;
            getEulerCircuit(there, circuit);
        }
    circuit.push_back(here);
}
vector<int> getEulerTrailOrCircuit(){
    vector<int> circuit;
    // 우선 트레일을 찾아보자.
    for (int i = 0; i < 26; ++i)
        if (outdegree[i] == indegree[i] + 1){
            // 오일러 트레일의 조건을 갖춘 정점을 찾는 것
            getEulerCircuit(i, circuit);
            return circuit;
        }
    // 그게 아니면 서킷을 찾자, 아무 정점에서나 시작.
    for (int i = 0; i < 26; ++i)
        // 그러나 그 정점에서의 간선이 존재하는 정점에서 시작
        if (outdegree[i]){
            getEulerCircuit(i, circuit);
            return circuit;
        }
    // 그러나 이런것들이 하나도 없으면 빈 벡터를 리턴
    return circuit;
}
// 아래의 경우를 만족할 때만, 오일러 서킷 혹은 트레일이 ㅣ존재한다.
// 차수가 1, -1 인 지점이 1개씩 존재하거나
// 아니면 모두 0인 서킷이 존재하거나
// 그렇지 않아서 불가능한 경우
bool checkEuler(){
    // 예비 시작점과 끝점의 수
    int plus1 = 0, minus1 = 0;
    for (int i = 0; i < 26; ++i) {
        int delta = outdegree[i] - indegree[i];
        // 모든 정점의 차수는 1, -1, 0 이여야 함.
        if(delta < -1 || 1 < delta) return false;
        if(delta == 1) plus1++;
        if (delta == -1) minus1;
    }
    return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}
string solve(const vector<string>& words){
    makeGraph(words);
    // 차수를 이용해서 서킷, 트레일이 존재하는지 확인.
    // 존재하지 않으면 IMPOSSIBLE 출력
    if(!checkEuler()) return "IMPOSSIBLE";

    vector<int> circuit = getEulerTrailOrCircuit();
    // 모든 간선을 체크한 것이 아니면, 컴포넌트가 1개가 아닌것.
    // 실패 한 경우임
    if(circuit.size() != words.size() + 1) return "IMPOSSIBLE";

    // 방문 순서를 뒤집어 문자열로 만들어 반환하자.
    reverse(circuit.begin(), circuit.end());
    string ret;
    for (int i = 1; i < circuit.size(); ++i) {
        int a = circuit[i - 1], b = circuit[i];
        if (ret.size()) ret += " ";
        ret += graph[a][b].back();
        graph[a][b].pop_back();
    }
    return ret;
}