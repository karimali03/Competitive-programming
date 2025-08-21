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

int fp(int x,int y){
    int res = 1;
    while(y > 0){
        if(y&1) res *=x;
        x = x*x;
        y/=2;
    }
    return res;
}

const int N = 200005;
// spf ( smallest prime factor )
vector<int>spf(N);   
 void SPF(){   //  O(n*log(log(n)))
    for(int i=1;i<N;i++) spf[i]=i;

     for(int i=2; i*i<=N; i++)
    {
        if(spf[i]==i)
           for(int j=i*i; j<=N; j+=i)
               if(spf[j]==j)   spf[j]=i;
    }
 }


 map<int,int> fast_fact(int n){   // O ( log(n) )
     map<int,int>res;
     while (n>1)
     {
        res[spf[n]]++;
        n/=spf[n];
     }
     return res;
     
 }

void solve(int test_case){
    SPF();
    int n; cin>>n;
    vi v(n); cin>>v;
    map<int,pair<int,int>>mp;
    map<int,int>cnt;
    for(int i = 0 ; i <  n; i++){
        auto x = fast_fact(v[i]);
        for(auto [a,b] :  x){
            cnt[a]++;
            if(!mp.count(a)) mp[a] = {b,INT_MAX};
            else{
                if(b < mp[a].first) 
                mp[a].second=mp[a].first,mp[a].first=b;
                else if(b < mp[a].second) mp[a].second = b;
            }
        }
    }

    int res = 1;
    for(auto [x,y] :  mp){
        int pw = y.first + (y.second!=INT_MAX ? y.second : 0);
        if(n - cnt[x] >= 2) pw = 0;
        cout<<x<<" "<<pw<<ln;
        res *= fp(x,pw);
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}