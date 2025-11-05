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


const int LOG = 22;
const int MX = (1<<LOG);
vector<pair<int,int>>dp1(MX,pair<int,int>{-1,-1});



void SOS1(){ // sum over subsets
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<MX;i++) if((i>>bit)&1){
            if(dp1[i^(1<<bit)].first != -1){
                if(dp1[i].first == -1) dp1[i].first = dp1[i^(1<<bit)].first;
                else if(dp1[i].second == -1) dp1[i].second = dp1[i^(1<<bit)].first;
            }
            if(dp1[i^(1<<bit)].second == -1){
                if(dp1[i].first == -1) dp1[i].first = dp1[i^(1<<bit)].first;
                else if(dp1[i].second == -1) dp1[i].second = dp1[i^(1<<bit)].first;
            }
        }
    }
}


void solve(int test_case) {
    int n; cin>>n;
    vi v(n);
    for(int i =0 ;i < n; i++){
        cin>>v[i];
        if(dp1[v[i]].first == -1) dp1[v[i]].first = i;
        else if(dp1[v[i]].second == -1) dp1[v[i]].second = i;
    }
    SOS1();
    for(int i =0;i<n;i++){
        if(dp1[(MX-1)^v[i]].first == i){
            int idx = dp1[(MX-1)^v[i]].second;
            if(idx == -1) cout<<-1<<" ";
            else cout<<v[idx]<<" ";
        } 
        else{
            int idx = dp1[(MX-1)^v[i]].first;
            if(idx == -1) cout<<-1<<" ";
            else cout<<v[idx]<<" ";
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}