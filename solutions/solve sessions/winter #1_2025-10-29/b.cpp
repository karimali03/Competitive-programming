#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}



const int N=2e6+5;
// spf ( smallest prime factor )
vector<int>spf(N+5);   
void SPF(){   //  O(n*log(log(n)))
    for(int i=1;i<=N;i++) spf[i]=i;

     for(int i=2; i*i<=N; i++)
    {
        if(spf[i]==i)
           for(int j=i*i; j<=N; j+=i)
               if(spf[j]==j)   spf[j]=i;
    }
}

vi fast_fact(int n){   // O ( log(n) )
     vector<int>res;
     while (n>1){
        res.push_back(spf[n]);
        n/=spf[n];
     }
     sort(all(res));
     res.erase(unique(all(res)),res.end());
     return res;
     
}

pair<int,int> calc(pair<int,int>x,int val){
    pair<int,int> ret = x;
    if(ret.first > val) ret.second=ret.first,ret.first=val;
    else if(ret.second > val) ret.second = val;
    return ret;
}
void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;
    map<int,pair<int,int>>m1,m2;
    for(int i = 0; i < n ; i++){
        if(a[i] != 1){
            auto cur1 = fast_fact(a[i]);
            for(auto &it : cur1){
                if(!m1.count(it)) m1[it] = {1e16,1e16};
                m1[it] = calc(m1[it],b[i]);
            }
        }
        auto cur2 = fast_fact(a[i]+1);
        for(auto &it : cur2){
            if(!m2.count(it)) m2[it] = {1e16,1e16};
            m2[it] = calc(m2[it],b[i]);
        } 
    }
    int res = 1e16;
    for(auto &[x,y] : m1){
        if(y.second != 1e16) res = 0;
    }
    for(auto &[x,y] : m2){
        if(m1.count(x)) res = min(res , y.first);
        res = min(res , y.first  + y.second);
    }
    auto mn = min_element(all(b)) - b.begin();
    for(int i = 0; i < n ; i++){
        if(i == mn || a[i] == 1) continue;
        auto x = fast_fact(a[i]);
        for(auto &it : x){
            res = min(res , b[mn] * ((it - (a[mn]%it))%it) );
        }
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SPF();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}