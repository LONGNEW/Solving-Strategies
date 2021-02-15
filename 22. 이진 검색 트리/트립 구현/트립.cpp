//
// Created by NEW on 2021-02-09.
//

#include <cstdlib>

typedef int KeyType;

struct Node{
    // 노드에 저장된 원소.
    KeyType key;
    // 이 노드의 우선순위, 서브트리의 크기.
    int priority, size;
    // 자식 노드에 대한 포인터
    Node *left, *right;

    Node(const KeyType& _key) :key(_key), priority(rand()), size(1), left(NULL), right(NULL){}
    void setLeft(Node* newLeft){
        left = newLeft;
        calcSize();
    }

    void setRight(Node* newRight){
        right = newRight;
        calcSize();
    }

    void calcSize(){
        size = 1;
        if(left)
            size += left->size;
        if(right)
            size += right->size;
    }
};
typedef pair<Node*, Node*> NodePair;
//root를 루트로 하는 서브트리를 key 미만의 값, 이상의 값을 가지는 두개의 트립으로 분리.
NodePair split(Node* root, KeyType key){
    if(root == NULL)
        return NodePair(NULL, NULL);
    //루트가 key 미만이면 오른쪽 서브트리를 쪼갠다.
    if(root->key < key){
        NodePair rs = split(root->right, key);
        // 새로운 노드를 insert() 할 경우에 루트가 기존 트리의 루트와 다를 수 있기 때문에
        // 새롭게 set 해주어야 한다.
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    // key 이상이면 왼쪽 서브트리를 쪼갠다.
    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}
//root 를 루트로 가지는 트립에 새 노드 node를 삽입하고 결과 트립의 루트를 반환한다.
Node* insert(Node* root, Node* node){
    if(root == NULL)
        return node;
    // 새 노드 node의 우선순위가 root 보다 높을 때는 root를 대체해야 한다.
    // 해당 서브 트리를 반으로 잘라 각각 자손으로 한다.
    if(root->priority < node -> priority){
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    } else if(node->key < root->key){
        root->setLeft(insert(root->left, node));
    } else{
        root->setRight((insert(root->right, node)));
    }
    return root;
}
// a와 b가 두 개의 트립이고, max(a) < min(b)일 떄 이 둘을 합친다.
Node* merge(Node* a, Node* b){
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (a->priority < b->priority){
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}
// root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환,
Node* erase(Node* root, KeyType key){
    if (root == NULL)
        return root;
    // root 를 지우고 양 서브트리를 합친 후 반환.
    if (root->key == key){
        Node* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if (key < root->key){
        root->setLeft(erase(root->left, key));
    } else{
        root->setRight(erase(root->right, key));
    }
    return root
}
// root를 루트로 하는 트리 중에서 k번째 원소를 반환한다.
Node* kth(Node* root, int k){
    // 왼쪽 서브트리의 크기를 계산.
    int leftSize = 0;
    if(root->left != NULL) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left, k);
    if(k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}
int countLessThan(Node* root, KeyType key) {
    if(root == NULL) return 0;
    if(root->key >= key)
        return countLessThan(root->left, key);
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
}