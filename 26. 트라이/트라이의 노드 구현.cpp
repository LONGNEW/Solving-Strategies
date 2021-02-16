//
// Created by NEW on 2021-02-15.
//
#include <cstring>
#include "vector"
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch){
    return ch - 'A';
}
// 트라이의 한 노드를 나타내는 객체
struct TrieNode{
    // 필요한 정보들은 자손의 목록을 나타내는 포인터들, 종료노드인지 확인을 위한 bool 값.
    TrieNode* children[ALPHABETS];
    bool terminal;
    TrieNode() : terminal(false) {
        memset(children, 0, sizeof(children));
    }
    // 어떻게 수행되는건지 찾아봅시다.
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i) {
            if (children[i])
                delete children[i];
        }
    }
    // 이 노드를 루트로 하는 트라이에 문자열 key를 추가.
    void insert(const char* key){
        // 문자열이 종료 되면 terminal만 참으로 바꾸어 준다.
        if(*key == 0)
            terminal = true;
        else{
            int next = toNumber(*key);
            // 해당 자식노드가 없다면 생성한다.
            if(children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1);
        }
    }
    // 현재 노드에서 문자열 key와 대응되는 노드를 찾자.
    TrieNode* find(const char* key){
        if(*key == 0)
            return this;
        int next = toNumber(*key);
        if(children[next] == NULL)
            return NULL;
        return children[next]->find(key + 1);
    }
};
