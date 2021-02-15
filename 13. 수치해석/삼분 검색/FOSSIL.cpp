//
// Created by NEW on 2021-02-03.
//

#include "FOSSIL.h"
#include <vector>
#include <algorithm>
using namespace std;

struct point{
    double y, x;
};
//입력으로 들어가는 볼록 다각형.
vector<point> hull1, hull2;
// 볼록다각형들을 윗껍질, 아랫껍질로 찢자.
vector<pair<point, point>> upper, lower;
// hull 이 입력될 떄를 보면 x 값이 증가하면서 입력이 되면 아랫껍질이고,
// 감소하며 입력이 되면 윗껍질이 된다.
void decompose(const vector<point>& hull){
    int n = hull.size();
    for(int i = 0; i < n; i++){
        if(hull[i].x < hull[(i + 1) % n].x){
            //연속하는 다음 x 좌표가 감소하는 경우로 윗껍질에 해당.
            // n으로 나머지 연산을 해주며 원형을 그리게 해준다.
            lower.push_back(make_pair(hull[i], hull[(i + 1) % n]));
        } else if (hull[i].x > hull[(i + 1) % n].x){
            //다음 x 좌표가 증가하는 경우로 아랫껍질에 해당.
            // 위와 동일하게 나머지 연산으로 원형을 그리게 한다.
            upper.push_back(make_pair(hull[i], hull[(i + 1) % n]));
        }
    }
}
//[a.x / b.x] 구간 안에 x가 포함되는 지 확인.. 뭐땜에 필요하지?
bool between(const point& a, const point& b, double x){
    return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}
double at(const point& a, const point& b, double x){
    double dy = b.y - a.y, dx = b.x - a.x;
    return a.y + dy * (x - a.x) / dx;
}
// 두 다각형의 교집합을 수직선으로 잘랐을 떄, 길이를 반환.
double vertical(double x){
    double minUp = 1e20, maxLow = -1e20;
    //위 껍질을 순회하며 최소 y 좌표를 찾자.
    //껍질의 교집합을 나타낼때 윗 껍질에선 최소 y 좌표를, 아래 껍질에선 최대 y 좌표를 구해서 이를 빼면 최대 길이를 구할 수 있다.
    for(int i = 0; i < upper.size(); i++)
        if(between(upper[i].first, upper[i].second, x))
            minUp = min(minUp, at(upper[i].first, upper[i].second, x));
    //아래 껍질을 순회.
    for(int i = 0; i < lower.size(); i++)
        if(between(lower[i].first, lower[i].second, x))
            maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
    return minUp - maxLow;
}
double solve(){
    double lo = max(minX(hull1), minX(hull2));
    double hi = min(maxX(hull1), maxX(hull2));

    if(hi < lo) return 0;

    for(int i = 0; i < 100; i++){
        double aab = (lo * 2 + hi) / 3;
        double abb = (lo + 2 * hi) / 3;

        if (vertical(aab) < vertical(abb)){
            lo = aab;
        } else{
            hi = abb;
        }
    }
    return max(0, 0, vertical(hi));
}