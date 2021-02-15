//
// Created by NEW on 2021-02-07.
//

struct TreeNode{
    // 저장할 자료.
    string label;
    // 부모노드에 대한 레퍼런스
    TreeNode* parent;
    // 자식 노드에 대한 레퍼런스
    vector<TreeNode*> children;
};

// 재귀적 속성을 이용해야 한다.
// 트리의 루트를 '방문' 하고 각 서브트리를 재귀적으로 방문하도록.
void printLabels(TreeNode* root){
    // 루트 노드에 저장된 값을 출력한다.
    cout << root->label << endl;
    // 각 자손들을 '루트'로 하는 서브트리에 재귀적으로 들어가자.
    for (int i = 0; i < root->children.size(); ++i) {
        printLabels(root->children[i]);
    }
}
// 트리의 높이를 구하고 싶을 때.
// 서브트리의 높이 들 중 최대치에 1을 더한 것.
// 이 또한 재귀적으로 리턴 값들에 대한 최대 값을 구별해야 할 듯 하다.
int height(TreeNode* root){
    int h = 0;
    for (int i = 0; i < root->children.size(); ++i) {
        h = max(h, 1 + height(root->children[i]));
    }
    return h;
}