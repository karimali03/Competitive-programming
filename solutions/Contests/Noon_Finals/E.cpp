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


vii split(const vi &v, int k) {
    int n = v.size();
    k = max(2ll, k);
    vii g(k);
    for (int i = 0; i < n; i++)
        g[i % k].push_back(v[i]);
    return g;
}

int ask(int i,int j){
    cout<<"? 2 "<<i+1<<" "<<j+1<<endl;
    int x; cin>>x;
    return x;
}

int ask(vi &v){
    cout<<"? ";
    cout<<v.size()<<" ";
    for(auto &it : v) cout<<it+1<<" ";
    cout<<endl;
    int x; cin>>x;
    return x;
}

int ask(vi &v,int l,int r){
    cout<<"? ";
    cout<<r-l+1<<" ";
    for(int i = l ; i <= r ; i++) cout<<v[i]+1<<" ";
    cout<<endl;
    int x; cin>>x;
    return x; 
}
void solve(int n) {
    n*=2;
    vi v(n);
    f(i,0,n) v[i] = i;
    vi pr(n,-1);
    int cur = 0;
    int i  = 2;
    while(true){
        auto x = ask(v,0,i-1) - cur;
        cout<<i<<" "<<x<<endl;
        if(x){
            vi l,r;
            for(int x = 0; x < i/2 ; x++) if(pr[x] == -1) l.push_back(x);
            for(int x = i/2 ; x <= i-1 ; x++)
            if(pr[x] == -1) r.push_back(x);
            int cnt = x;
            int s1 = l.size();
            int s2 = r.size();
            for(int a = 0 ; a < s1 && cnt ; a++){
                for(int b= 0; b < s2 && cnt; b++){
                    if(ask(l[a],r[b])){
                        pr[l[a]] = r[b];
                        pr[r[b]] = l[a];
                        cnt--;
                        cur++;
                        break;
                    }
                }
            }
        }
        if(i == n) break;
        i*=2;
        if(i > n) i = n;
    }
  
    cout<<"!"<<endl;
    set<int>st;
    for(int i = 0;i < n ; i++){
        if(st.count(min(i,pr[i]))) continue;
        cout<<i+1<<" "<<pr[i]+1<<endl;
        st.insert(min(i,pr[i]));
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; 
    while(cin>>n && n){
        solve(n);
    }
    

    return 0;
}