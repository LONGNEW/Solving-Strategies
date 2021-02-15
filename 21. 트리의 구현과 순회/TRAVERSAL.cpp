//
// Created by NEW on 2021-02-07.
//

vector<int> slice(const vector<int>& v, int a, int b){
    return vector<int>(v.begin() + a, v.begin() + b);
}
// 트리의 전위 탐색 결과, 중위탐색 결과를 이용해서 후위 탐색 결과를 출력하자.
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder){
    //트리의 노드의 수 확인.
    const int N = preorder.size();

    // 기저 사례 : 빈 트리이면 바로 종료,
    if(preorder.empty()) return;

    //트리의 루트는 전위 탐색 결과로 알 수 있다.
    const int root = preorder[0];

    // 서브트리의 길이를 알아내자.
    // 트리의 루트가 중위 탐색 결과의 어느 위치에 있는지 찾아서 크기를 알아내자.
    // vector.begin()의 경우 주소 값을 반환한다고 하니까.
    // find()를 통해 루트 노드의 주소 값을 가지고 저기다가 빼면 그 크기를 알 수 있다.
    const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
    // 루트 노드에 L 길이를 빼면 R 길이도 알 수 있다.
    const int R = N - 1 - L;

    // 후위 순위의 경우 모든 자식 노드를 visit 한 후에 각각의 저장하고 있는 정보를 출력한다.
    // 위의 과정을 서브트리에서도 반복을 할 것인데.
    // 왼쪽을 방문하는 재귀적 과정.
    printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
    // 이래서 슬라이스 함수를 만드는 거였네;;
    // 주소값을 가지고 노는 거 때문에 길이를 구해서 주소값을 더해준다.

    // 오른쪽 방문
    printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));

    cout << root << " ";
}