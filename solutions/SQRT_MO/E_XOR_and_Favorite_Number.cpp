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

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}


int SQ,sum;
int frq[(1<<20)]{};
int prefix[1000005]{};
int v[1000005]{};
int n,k;

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
    sum += frq[val^k];
    frq[val]++;
}

void del(int val) {
    frq[val]--;
    sum -= frq[val^k];
}

vector<int> MO(vector<Query> &q){
    SQ = sqrt(n) + 1;
    sum = 0;
    vector<int> res(q.size());
    sort(q.begin(), q.end());
    int l = 1 ,r = 0;
    for(auto [lq,rq,idx] : q){
        while(lq < l) add(prefix[--l]);
        while(rq > r) add(prefix[++r]);
        while(lq > l) del(prefix[l++]);
        while(rq < r) del(prefix[r--]);
        res[idx] = sum;
    }
    return res;
}


void solve(int test_case){
    int m;  cin>>n>>m>>k;
    f(i,0,n) cin>>v[i];
    prefix[0] = 0;
    for(int i = 1 ;i  <= n ; i++){
        prefix[i] = v[i-1] ^ prefix[i-1]; 
    }

    vector<Query>x(m);
    f(i,0,m){
        int l,r; cin>>l>>r; l--,r;
        x[i] = {l,r,i};
    }
    auto res = MO(x);
    for(auto it : res) cout<<it<<ln;
}