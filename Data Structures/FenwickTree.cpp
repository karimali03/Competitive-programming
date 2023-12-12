#include <iostream>
#include <cassert>
using namespace std;
#include <vector>
#include <climits>
#define ll long long

const int N=1e5+5;
struct FenwickTree{
    ll bit[N]={};
    void add(int idx,ll val)
    {
        while(idx<N)
        {
            bit[idx]+=val;
            idx+=idx&-idx;
        }
    }
    ll query(int idx)
    {
        ll ret=0;
        while(idx>0)
        {
            ret+=bit[idx];
            idx-=idx&-idx;
        }
        return ret;
    }
    ll prefix(int l,int r)
    {
        return query(r)-query(l-1);
    }
};
