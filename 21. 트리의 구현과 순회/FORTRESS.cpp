//
// Created by NEW on 2021-02-07.
//

// 이 문제는 트리를 생성하는 과정과, 트리의 최장경로를 구하는 두 부분으로 나눌 수 있다.

// isChild() 함수를 만들 때 생각할 점.
// 주어진 두 성벽 사이에 다른 성벽이 존재하는 지 확인 하는 것.
// 현재 비교하려는 성벽 사이에 또 다른 성벽이 존재한다면.
// 그 성벽이 부모 가 되기 때문에 관계가 성립 되지 못한다.
int n, y[100], x[100], radius[100];

int sqr(int x){
    return x * x;
}
// 두 성벽 a, b의 '중심점 간의 거리'의 제곱을 반환.
int sqrdist(int a, int b){
    return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}
// 성벽 a가 성벽 b를  포함하는지 확인.
bool encloses(int a, int b){
    // 원의 내접 관계를 찾아보면 되는데.
    // 큰 원의 반지름 - 작은 원의 반지름 > 각 원끼리의 중심에 대한 거리
    // 이면 두 원은 포함관계라고 볼 수 있다.
    return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
}
bool isChild(int parent, int child){
    if(!encloses(parent, child)) return false;
    for(int i = 0; i < n; ++i)
        if(i != parent && i != child && encloses(parent, i) && encloses(i, child))
            return false;
    return true;
}

// 트리를 생성해보자..
TreeNode* getTree(int root){
    TreeNode* ret = new TreeNode();
    for(int ch = 0; ch < n; ++ch)
        // ch 성벽이 root 성벽에 '직접'적으로 포함되어 있다면.
        // 트리를 만들고 자손목록에 추가하자.
        if(isChild(root, ch))
            ret->children.push_back(getTree(ch));
    return ret;
}



//트리에서 가장 긴 경로를 찾는 재귀 호출 알고리즘.
struct TreeNode{
    vector<TreeNode*> children;
};
// 현재까지의 가장 긴 leaf node - leaf node의 경로의 길이를 저장.
int longest;

// root 변수를 루트로 가지는 서브트리의 높이를 반환한다.
int height(TreeNode* root){
    vector<int> heights;
    for (int i = 0; i < root->children.size(); ++i) {
        // 각 자식들의 높이를 재귀적으로 들어가서 리턴 하는 값들을
        // 벡터에 저장한다.
        heights.push_back(height(root->children[i]));
    }
    // 만약 자식이 하나도 없다면 0을 반환.
    if(heights.empty()) return 0;

    sort(heights.begin(), heights.end());
    if(heights.size() >= 2)
        // 2를 더하는 이유:
        // 각 자식 노드의 높이를 구하게 되면 자식 노드에서 부모노드로 오는 간선을 빼게 된다.
        // 자식 노드 두 개에 대한 것이기 때문에 남는 간선을 넣어주기 위해 2를 더해야 한다.
        // sort를 하면 오름차순으로 정렬하기 때문에 뒤에서 2개를 더해 주어야 한다.
        longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);

    // 이 함수는 재귀적으로 수행하면서 현재 노드의 가장 긴 길이를 반환 해주어야 한다.
    // 그러려면 포함하지 않았던 간선 1개(현재의 root로 이동하는)를 더해주어야 하기에
    // 아래의 것을 반환한다.
    return heights.back() + 1;
}
int solve(TreeNode* root){
    longest = 0;
    int h = height(root);
    return max(longest, h);
}

//