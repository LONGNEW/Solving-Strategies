//
// Created by NEW on 2021-02-08.
//

// 다른 점에 지배당하지 않는 점들의 목록을 저장한다.
//cords[x] = y
// 이진 검색 트리 라이브러리 임.
map<int, int> coords;
// 새로운 점 (x, y)가 기존의 다른 점들에 지배당하는지 확인한다.
bool isDominated(int x, int y){
    // x보다 오른쪽에 있는 점 중 가장 왼쪽에 있는 점을 찾기.
    // x 보다 오른쪽에 있는 점중 가장 왼쪽에 있는 것이 높이가 제일 큰 것이기 때문에
    // 이를 찾아서 비교를 해서 지배되는지 안 되는지를 확인하자.
    map<int, int>::iterator it = coords.lower_bound(x);
    // lower_bound(something)을 쓰면.
    // something 이상의 값중 가장 작은 값을 리턴해준다.
    if(it == coords.end()) return false;
    // 점(x, y) 가 지배되려면.
    // 현재 찾은 it의 y 보다 작아야 된다.
    return y < it->second;
}
// 새로운 점이 다른 점들을 지배하는지 확인하고, 삭제하는 연산.
void removeDominated(int x, int y){
    map<int, int>::iterator it = coords.lower_bound(x);
    // 왼쪽에 존재하는 점이 없다면? 삭제할 것도 없다.
    if(it == coords.begin()) return;

    // 반복문의 조건 : it는 (x, y)의 바로 왼쪽에 있는점.
    // it의 위치를 시작하기 전에 조정해 줘야 한다.
    --it;
    while (true){
        //(x, y) 바로 왼쪽에 오는 점을 찾기.
        // it가 가리키는 점이 (x, y)에 지배되지 않으면 바로 종료.
        // 지배 되지 않으려면 y보다 second의 값이 커야 한다.
        if(it->second > y) break;

        if (it == coords.begin()){
            // 위의 조건문에 걸리지 않는 경우엔
            // 그 다음 점들 부터는 높이가 작은 거기 때문에 지배되는 점들이라고 볼 수 있다.
            coords.erase(it);
            break;
        } else{
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}
// 새 점(x, y)가 추가되었을 때 coords를 갱신.
// 다른 점에 지배당하지 않는 점들의 개수를 반환.
int registered(int x, int y){
    // 지배 당하는 경우에는 그냥 버림.
    if(isDominated(x, y)) return coords.size();
    removeDominated(x, y);
    coords[x] = y;
    return coords.size();
}