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

void solve(int test_case) {
    int n; cin>>n;
    pair<int,int>ev = {-1,-1};
    vi od;
    for(int i = 0;i < n ; i++){
        int x; cin>>x;
        if(x&1) od.push_back(x);
        else{
            if(ev.first !=-1) ev.second = x;
            if(ev.first==-1)  ev.first=x;
        } 
    }
    if(ev.first != -1 && ev.second != -1){
        cout<<ev.first<<" "<<ev.second<<ln;
        return;
    }
    if(ev.first != -1){
        for(auto it : od) if( it < ev.first && (ev.first%it)%2==0){
            cout<<it<<" "<<ev.first<<ln;
            return;
        }
    }
    for(int i = 0; i < (int)od.size() ; i++){
        for(int j = i+1 ; j < (int)od.size() ; j++){
            if((od[j]%od[i])%2==0){
                cout<<od[i]<<" "<<od[j]<<ln;
                return;
            }
        }
    }
    NA;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}