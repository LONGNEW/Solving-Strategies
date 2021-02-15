//
// Created by NEW on 2021-02-10.
//
#include "vector"
using namespace std;

vector<int> heap;
void push_heap(vector<int>& heap, int newValue){
    // 힙의 맨 끝에 newValue를 삽입.
    heap.push_back(newValue);
    //현재 newValue의 위치.
    int idx = heap.size() - 1;
    // 루트에 도달하거나, 자기 자신 이상의 부모를 만날 때 까지.
    while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]){
        swap(heap[idx], heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}
// 숫자 중 최댓값을 리턴 하는 pop
void pop_heap(vector<int>& heap){
    // 힙의 가장 마지막 값을 루트에 넣는 것으로 시작.
    heap[0] = heap.back();
    heap.pop_back();
    int here = 0;
    while (true){
        int left = here * 2 + 1, right = here * 2 + 2;
        // 리프 노드에 도달 했을 때.
        if(left >= heap.size()) break;
        //heap[here]가 내려갈 위치를 찾는다.

        int next = here;
        if(heap[next] < heap[left])
            next = left;

        if (right < heap.size() && heap[next] < heap[right])
            next = right;
        if (next == here) break;

        swap(heap[here], heap[next]);
        here = next;
    }
}