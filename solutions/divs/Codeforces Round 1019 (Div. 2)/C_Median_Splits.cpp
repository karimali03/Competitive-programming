#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <numeric>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
//#include "./cmake-build-debug/functions.h"

#define ABDELWAHAB ios_base::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
#define ll long long
#define mod 1000000007
#define CIN(v) for(auto &i:v) cin >> i;
#define COUT(v) for(auto &i:v) cout << i <<" ";
#define SORT(v) sort(v.begin(),v.end());
#define SORT_reverse(v) sort(v.rbegin(),v.rend());
#define F first
#define S second

using namespace std;
int n,c;
vector<ll>ups, ele;
ll dp[1000005][2];

ll func(int i=0, int state = 0)
{
    if(i == n-1) return 0;
    auto &ret = dp[i][state];
    if(~ret) return ret;
    ret = min({
        func(i+1, 0) + ups[i],
        func(i+1, 1) + ele[i] + ((state == 0) ? c : 0)
    });
    return ret;
}
ll sum =0;
void print(int i=0, int state=0)
{
    cout << sum <<" ";
    if(i == n-1) return;
    if(dp[i][state] == func(i+1, 0) + ups[i])
    {
        sum += ups[i];
        print(i+1, 0);
    }
    else if(dp[i][state] == func(i+1, 1) + ele[i] + ((state == 0) ? c : 0))
    {
        sum += ele[i] + ((state == 0) ? c : 0);
        print(i+1, 1);
    }
}

int main() {
    //freopen("mex.in", "r", stdin);
    //freopen("mex.in", "w", stdout);
    ABDELWAHAB
    memset(dp, -1, sizeof(dp));
    cin >> n >> c;
    ups.resize(n-1);
    ele.resize(n-1);
    CIN(ups)
    CIN(ele)
    func();
    print();
    return 0;
}