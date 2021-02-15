//
// Created by NEW on 2021-02-11.
//

#include "vector"
using namespace std;

// 부분 구간의 계산 결과
struct RangeResult{
    int size;
    // 가장 자주 등장하는 숫자의 출현 횟수.
    int mostFrequent;
    // 왼쪽 끝 숫자와, 이 숫자의 출현 횟수.
    int leftNumber, leftFreq;
    // 오른쪽 끝 숫자와, 이 숫자의 출현 횟수
    int rightNumber, rightFreq;
};
// 왼쪽 부분 구간의 계산 결과 a, 오른쪽 부분 구간의 계산 결과 b를 합침.
RangeResult merge(const RangeResult& a, const RangeResult& b){
    RangeResult ret;
    // 합쳐질 구간의 크기 계산.
    ret.size = a.size + b.size;

    // 왼쪽 숫자는 a.leftNumber에 저장되어 있다.
    // 왼쪽 부분 구간이 전부 a.leftNumber인 경우만 별도로 처리.
    // ex : [1, 1, 1, 1] [1, 2, 2, 2]
    ret.leftNumber = a.leftNumber;
    ret.leftFreq = a.leftFreq;
    if(a.size == a.leftFreq && a.leftNumber == b.leftNumber)
        ret.leftFreq += b.leftFreq;

    // 오른쪽 끝 숫자도 비슷 하게 처리.
    ret.rightNumber = b.rightNumber;
    ret.rightFreq = b.rightFreq;
    if(b.size == b.rightFreq && a.rightNumber == b.rightNumber)
        ret.rightFreq += a.rightFreq;

    // 기본적으로 가장 많이 출현하는 수의 빈도수는 둘 중 큰 쪽.
    ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
    // 왼쪽 구간의 오른쪽 끝 숫자가, 오른쪽 구간의 왼쪽 끝 숫자와 연결이 되는 경우.
    // 이 수를 합친 것이 mostFrequent보다 커지는지 확인.
    if(a.rightNumber == b.leftNumber)
        ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);

    return ret
}