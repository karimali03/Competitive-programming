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


int ask(int mask){
    cout<<mask<<endl;
    int ret; cin>>ret;
    return ret;
}

void solve(int test_case) {
    int mask_1 = 0;
    int mask_2 = 0;
    for(int i = 0;i < 30 ; i++){
        if(i&1) mask_1 |= (1 << i);
        else mask_2 |= (1 << i);
    }
    int ret = ask(mask_1);
    bitset<64>m1(mask_1*2);
    bitset<64>m2(mask_2*2);
    bitset<64>r1(ret);
    int a = 0, b = 0;
    for(int i = 0;i < 60 ; i+=2){
        if( i > 0 && r1[i] == 0 && r1[i+1] == 0) break;
        if(i == 0){
            if(r1[i] == 1 && r1[i+1] == 0) a |= (1ll << i);
            else if(r1[i] == 0 && r1[i+1] == 1){
                a |= (1ll << i);
                b |= (1ll << i);
            }
        }else{
            if(r1[i] == m1[i] && r1[i+1] == m1[i+1]) continue;
            if(r1[i] == 1 && r1[i+1] == 1){
                a |= (1ll << i);
                b |= (1ll << i);
            }
            else{
                a |= (1ll << i);
            }
        }
    }
    
    ret = ask(mask_2);
   
    bitset<64>r2(ret);
    for(int i = 1 ; i < 60 ; i+=2){
        if(r2[i] == 0 && r2[i+1] == 0) break;
        if(r2[i] == m2[i] && r2[i+1] == m2[i+1]) continue;
        if(r2[i] == 1 && r2[i+1] == 1){
            a |= (1ll << i);
            b |= (1ll << i);
        }
        else{
            a |= (1ll << i);
        }
    }

    cout<<"!"<<endl;
    int m; cin>>m;
    int res = (m|a) + (m|b);
    cout<<res<<endl;
    // cout<<bitset<64>(a).to_string()<<ln;
    // cout<<bitset<64>(b).to_string()<<ln;
   
    // cout<<bitset<35>((mask_1|x)+(mask_1|y)).to_string()<<ln;
    // cout<<bitset<35>((mask_2|x)+(mask_2|y)).to_string()<<ln;
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