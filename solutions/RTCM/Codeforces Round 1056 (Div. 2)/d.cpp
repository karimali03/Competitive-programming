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


mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rand_range(ll l, ll r) { return l + (ull) rng() % (r - l + 1); }
void shuffle(vector<int> &v) { shuffle(v.begin(), v.end(), rng); }
char rand_char() { return 'a' + rand_range(0, 25); }

void solve(int test_case) {
    int n = 40;
    int a = 4;
    int q = 0;
    set<int>st;
    st.insert(1);
    st.insert(14);
    st.insert(27);
    st.insert(40);
    // for(int i = 1 ; i <= a ; i++){
    //     int x = rand_range(1,n);
    //     while(st.count(x)) x = rand_range(1,n);
    //     st.insert(x); 
    // }
    auto ask = [&](int x,int y){
        q++;
        return st.count(x) && st.count(y);
    };
    int k = sqrt(n);
    if(k < 2) k = 2;
    vii groups(k);
    for(int i = 1 ; i < n ; i++) groups[(i-1)%k].push_back(i);
    f(i,0,k){
        int sz = groups[i].size();
        f(j,0,sz) f(k,j+1,sz) if(ask(groups[i][j],groups[i][k])) goto xx;
    }
    f(i,0,k) f(j,i+1,k){
        int s1 = groups[i].size();
        int s2 = groups[j].size();
        f(a,0,s1) f(b,0,s2) if(ask(groups[i][a],groups[j][b])) goto xx; 
    }
    
    xx:
    cout<<q<<ln;
    if(q > (n*n)/a){
        cout<<n<<" "<<a<<ln;
        for(auto it : st) cout<<it<<" ";
        cout<<ln;
    }
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