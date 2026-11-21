#include <bits/stdc++.h>
using namespace std;

#define ld long double
#define ll long long
const ld EPS=1e-12;
ld px,py;
int n;
struct circle{
    ld x, y, r;
};
vector<circle>v;
pair<ld,ld> calc(ld x){
    ld leftt=-INFINITY;
    ld rightt=INFINITY;
    for(auto &[a,b,c]:v){
        ld hold=c*c-(x-a)*(x-a);
        hold=sqrtl(max((ld)0.0,hold));
        leftt=max(leftt,b-hold);
        rightt=min(rightt,b+hold);
    }
    return {leftt,rightt};
}
ld chk(ld x){
    auto [a,b]=calc(x);
    return a-b;
}
ld dist(ld x){
    auto [a,b]=calc(x);
    ld y=py;
    y=max(a,y);
    y=min(b,y);
    return (x-px)*(x-px)+(y-py)*(y-py);
}
void sol(){
    cin>>n;
    v.resize(n);
    int h1,h2;cin>>h1>>h2;
    px=h1,py=h2;
    ld left=-INFINITY;
    ld right=INFINITY;
    for(int i=0;i<n;i++){
        int x,y,r;
        cin>>x>>y>>r;
        v[i].x=x;
        v[i].y=y;
        v[i].r=r;
        left=max(left,v[i].x-v[i].r);
        right=min(right,v[i].x+v[i].r);
    }
    ld L=left,R=right;
    for(int i=0;i<150;i++){
        ld m1=L+(R-L)/3;
        ld m2=R-(R-L)/3;
        if(chk(m1)<chk(m2)){
            R=m2;
        }else{
            L=m1;
        }
    }
    ld mid=L;
    ld LL=left;
    ld RR=mid;
    for(int i=0;i<80;i++){
        ld m=(LL+RR)/2;
        if(chk(m)<EPS)RR=m;
        else LL=m;
    }
    ld lf=RR;
    LL=mid;
    RR=right;
    for(int i=0;i<80;i++){
        ld m=(LL+RR)/2;
        if(chk(m)<EPS)LL=m;
        else RR=m;
    }
    ld rf=LL;
    for(int i=0;i<150;i++){
        ld m1=lf+(rf-lf)/3;
        ld m2=rf-(rf-lf)/3;
        if(dist(m1)<dist(m2))rf=m2;
        else lf=m1;
    }
    cout<<fixed<<setprecision(15)<<sqrtl(dist((lf+rf)/2));
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sol();
}