//
// Created by NEW on 2021-02-10.
//

#include <vector>
#include <functional>
#include <queue>

using namespace std;

// 원소가 하나 추가 될때 마다의 중간값을 찾아주는 것이다.
// 이진 검색 트리를 이용하면 이 트리의 형태도 유지 하고,
// k번째 원소를 찾는 것도 빠르니 수월한데 대회에선 구현하기 귀찮다.


struct RNG{
    int seed, a, b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983){}
    int next(){
        int ret = seed;
        seed = ((seed * (long long)a) + b) % 20090711;
        return ret;
    }
};
// 최대힙, 최소힙을 이용해서 반반 나눈다.
// 최대 힙이 언제나 원소를 1개 더 혹은, 길이가 동일 하게 있어
// 중간 값은 최대 힙에 존재하도록 하자.
int runningMedian(int n, RNG rng){
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int ret = 0;
    // 반복문 불변식.
    // 1. maxHeap의 크기가 minHeap 보다 크거나 1 더 크다.
    // 2. maxHeap.top() <= minHeap.top()
    for (int cnt = 0; cnt <= n; ++cnt) {
        // 1 번 불변식을 만족 시켜 보자.
        if(maxHeap.size() == minHeap.size())
            maxHeap.push(rng.next());
        else
            // 숫자 값은 이 쪽이 작은데, 큐의 크기 때문에 이쪽에 들어 가서 2번 불변식을 깰 수 있다.
            minHeap.push(rng.next());
        // 2번 불변식이 깨지면 복구해야 한다.
        if(!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()){
            int a = maxHeap.top(), b = minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret = (ret + maxHeap.top()) % 20090711;
    }
    return ret;
}