//
// Created by NEW on 2021-02-09.
//

int n, shifted[50000];
int A[50000];
// n, shifted[] 를 보고 A[]에 저장한다.
void solve(){
    //1 ~ N 까지의 숫자를 모두 저장하는 트립을 만든다.
    Node* cadidates = NULL;
    for (int i = 0; i < n; ++i) {
        cadidates = insert(cadidates, new Node(i + 1));
    }
    // 뒤에서 부터 A[i]를 채워감.
    for (int i = n - 1; i >= 0; --i) {
        // 후보 숫자들 중에 이 수보다 큰 수가 larger개 있는 것을 찾자.
        int larger = shifted[i];
        Node* k = kth(candidates, i + 1 - larger);
        A[i] = k->key;
        candidates = erase(candidates, k->key);
    }
}