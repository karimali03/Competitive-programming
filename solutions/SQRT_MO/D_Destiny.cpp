#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long



void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
  //  cin >> t;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}


int SQ;
int v[300005];
int frq[300005];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Query
{
    int l, r,val, idx;
    bool operator < (const Query &other) const
    {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return (l/SQ) & 1 ? r > other.r : r < other.r;
    }
};
 
void add(int val) {

    frq[val]++;
  
}

void del(int val) {
   
    frq[val]--;

}

vector<int> MO(vector<Query> &q,int n){
    SQ = sqrt(n) + 1;
    vector<int> res(q.size());
    sort(q.begin(), q.end());
    int l = 0 ,r = -1;
    for(auto [lq,rq,val,idx] : q){
        while(lq < l) add(v[--l]);
        while(rq > r) add(v[++r]);
        while(lq > l) del(v[l++]);
        while(rq < r) del(v[r--]);
        int mn = 1e9;
        for(int i = 0 ; i < 100 ; i++){
            int rnd = v[l + rng()%(r-l+1)];
            if(frq[rnd] > val && rnd < mn) mn = rnd;
        }
        res[idx] = (mn==1e9?-1:mn);
    }
    return res;
}


void solve(int test_case){
    int n,q; cin>>n>>q;
    f(i,0,n) cin>>v[i];
  
    vec<Query>x(q);
    for(int i = 0 ; i < q;  i++){
        int l,r,k; cin>>l>>r>>k;
        if(l > r) swap(l,r); l--,r--;
        x[i] = {l,r,(r-l+1)/k,i};
    }
    auto res = MO(x,n);
    for(auto it : res) cout<<it<<ln;

}