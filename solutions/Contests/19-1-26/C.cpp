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


int ask(int i,int j){
    cout<<"? "<<i<<" "<<j<<endl;
    int x; cin>>x;
    return x;
}
void solve(int test_case) {
    int n; cin>>n;
    vi v(n);
    iota(all(v),1);
    int sz = n;
    while(sz > 5){
        auto x = v.back(); v.pop_back();
        auto y = v.back(); v.pop_back();
        if(ask(x,y) != ask(y,x)){
            int imp = y;
            if(ask(x,v[0]) != ask(v[0],x)) imp = x;
            cout<<"! "<<imp<<endl;
            return;
        }
        sz -=2;
    }
    if(sz == 3){
        if(ask(v[0],v[1]) != ask(v[1],v[0])){
            if(ask(v[0],v[2]) != ask(v[2],v[0])) cout<<"! "<<v[0]<<endl;
            else cout<<"! "<<v[1]<<endl;
        }else cout<<"! "<<v[2]<<endl;
    }else if(sz == 4){
        bool ch1 = ask(v[0],v[1]) == ask(v[1],v[0]);
        bool ch2 = ask(v[0],v[2]) == ask(v[2],v[0]);
        int imp = v[0];
        if(ch1 && ch2) imp = v[3];
        else if(ch1 && !ch2) imp = v[2];
        else if(!ch1 && ch2) imp = v[1];
        cout<<"! "<<imp<<endl;
    }else{
        bool ch1 = ask(v[0],v[1]);
        bool ch2 = ask(v[1],v[2]);
        bool ch3 = ask(v[2],v[0]);
        int cnt = ch1 + ch2 + ch3;
        int imp = v[0];
        if(cnt == 3 || cnt == 1){
            if(ask(v[3],v[0]) == ask(v[0],v[3])) imp = v[4];
            else imp = v[3];
        }else{
            bool x1 = ask(v[1],v[0]) == ch1;
            bool x2 = ask(v[2],v[1]) == ch2;
            if(!x1 && !x2) imp = v[1];
            else if(!x1 && x2) imp = v[0];
            else imp = v[2]; 
        }
        cout<<"! "<<imp<<endl;
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