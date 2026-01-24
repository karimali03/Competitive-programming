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
    int sus = -1;
    set<int>st;
    f(i,1,n+1) st.insert(i);
    for(int i = 2 ; i <= n ; i +=2){
        if(ask(i-1,i) != ask(i,i-1)) sus = i;
    }
    if(sus == -1){
        cout<<"! "<<n<<endl;
        return;
    }
    st.erase(sus); st.erase(sus-1);
    int x = *st.begin();
    if(ask(x,sus) != ask(sus,x)){
            cout<<"! "<<sus<<endl;
    }else{
         cout<<"! "<<sus-1<<endl;
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