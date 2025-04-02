#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int SQ,sum;
int frq[1'000'001]{};
struct Query
{
    int l, r, idx;
    bool operator < (const Query &other) const
    {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return (l/SQ) & 1 ? r > other.r : r < other.r;
    }
};
 
void add(int val) {
    sum -= val * (frq[val]*frq[val]);
    frq[val]++;
    sum += val * (frq[val]*frq[val]);
}

void del(int val) {
    sum -= val * (frq[val]*frq[val]);
    frq[val]--;   
    sum += val * (frq[val]*frq[val]);
}

vector<int> MO(vector<Query> &q, vector<int> &v){
    int n = v.size();
    SQ = sqrt(n) + 1;
    sum = 0;
    vector<int> res(q.size());
    sort(q.begin(), q.end());
    int l = 0 ,r = -1;
    for(auto [lq,rq,idx] : q){
        while(lq < l) add(v[--l]);
        while(rq > r) add(v[++r]);
        while(lq > l) del(v[l++]);
        while(rq < r) del(v[r--]);
        res[idx] = sum;
    }
    return res;
}


int main(){
    return 0;
}