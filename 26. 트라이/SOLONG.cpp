//
// Created by NEW on 2021-02-16.
//
#include <cstring>
#include <string>
#include <algorithm>
#include "vector"
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch){
    return ch - 'A';
}
struct TrieNode{
    TrieNode* children[ALPHABETS];
    // 이 노드에서 종료하는 문자열의 번호. 없으면 -1(그니까 각 노드에서 어떤 문자열이 끝나는지 확인하는 것이네
    int terminal;
    // 이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호.
    int first;
    TrieNode();
    ~TrieNode();
    // 이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가한다.
    void insert(const char* key, int id){
        // first를 우선 갱신
        if(first == -1)
            first = id;
        else{
            int next = toNumber(*key);
            //해당 자식 노드 없으면 생성하기
            if(children[next] == NULL)
                children[next] = new TrieNode();

            // 왜 key + 1을 하는 것일까 했는데.
            // 트라이는 문자열의 인덱스가 하나씩 밀리면서 새로운 문자열을 추가한다.
            // 이를 생각해보면 배열이나, 벡터? 의 주소를 하나씩 밀면서 확인하는 것이라고
            // 보면 될거 같다.
            children[next] -> insert(key + 1, id);
        }
    }

    // 이 노드까지 타이핑해 왔을 떄, 번호 id인 key를 타이핑하기 위해
    // 최소 몇 번의 키를 더 눌러야 하는지
    int type(const char* key, int id){
        // 문자열 종료 될 때
        if(*key == 0) return 0;
        // 이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료
        if(first == id) return 1;
        // 아니면 다음 문자를 타이핑 하자.
        int next = toNumber(*key);
        // 현재 문자열 까지 타이핑 해서 들어오기 때문에
        // 1을 더하면서 재귀를 호출하자.
        return 1 + children[next]->type(key + 1, id);
    }
};

// 트라이를 다 만들어놓고, 단어 word를 타이핑하는 데
// 몇 번이나 키를 눌러야 하는지 계산하자.
int countKeys(TrieNode* trie, const char* word){
    // 이 문자열이 사전에 있는지 확인.
    // 있다면 그 번호를 찾는다.
    TrieNode* node = trie->find(word);

    if(node == NULL || node->terminal == -1)
        return strlen(word);
    return trie->type(word, node->terminal);
}

TrieNode* readInput(int words){
    // 단어들의 정렬을 풀현 빈도의 경우 내림차순 -> 가장 연관된 단어를 빠르게 찾기.
    // 그리고 단어의 오름차순으로 정렬.
    vector<pair<int, string>> input;
    for (int i = 0; i < words; ++i) {
        char buf[11];
        int freq;
        scanf("%s %d", buf[i], &freq);
        input.push_back(make_pair(-freq, buf));
    }
    sort(input.begin(), input.end());

    TrieNode* trie = new TrieNode();
    for (int i = 0; i < input.size(); ++i) {
        trie->insert(input[i].second.c_str(), i);
    }
    trie->first = -1;
    return trie;
}