//
// Created by NEW on 2021-02-12.
//
#include "vector"
using namespace std;

const int MAX_N = 100000;
int n;
vector <int> child[MAX_N];
// 트리의 번호와 일련 번호 사이의 대응
int no2serial[MAX_N], serial2no[MAX_N];
// 각 노드가 trip에 처음 등장하는 위치, 그리고 각 노드의 깊이.
int locInTrip[MAX_N], depth[MAX_N];

int nextSerial;
//깊이가 d인 노드 here 이하를 전위 탐색한다.
void traverse(int here, int d, vector<int>& trip){
    // traverse()가 처음 방문하자 마자 일련 번호를 부여.
    // 항상 부모는 자손보다 작은 일련 번호를 가짐.
    // 부모 노드에 우선적으로 방문하기 때문에.
    no2serial[here] = nextSerial;
    serial2no[nextSerial] = here;
    // 깊이 계산
    depth[here] = d;
    //trip에 현재 노드의 일련 번호를 추가.
    locInTrip[here] = trip.size();
    trip.push_back(no2serial[here]);
    // 모든 자식 노드를 방문.
    for (int i = 0; i < child[here].size(); ++i) {
        traverse(child[here][i], d + 1, trip);
        // 자식 노드를 방문하고 돌아올 때마다 다시 추가.
        trip.push_back(no2serial[here]);
    }
}
RMQ* prepareRMQ(){
    nextSerial = 0;
    vector<int> trip;
    traverse(0, 0, trip);
    return new RMQ(trip);
}