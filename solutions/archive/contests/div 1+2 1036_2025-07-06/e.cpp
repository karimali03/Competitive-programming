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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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

pair<int,int> bs(vi &pre,vi &suf,int n,int st,int en,int dif){
    int l = st , r = en;
    dif = abs(dif);
    int ans = -1;
    while(l<=r){
        int mid = l + (r-l)/2;
        int val = pre[mid] - ( st ? pre[st-1] : 0);
        if(val < dif/2) l = mid+1;
        else{
            r = mid-1;
            ans = mid;
        }
    }
    if(ans == -1) return {-1,-1};
    l = st , r = en;
    int ans2 = -1;
    while (l<=r)
    {
        int mid = l +(r-l)/2;
        int val = suf[mid] - (en+1 < n ? suf[en+1] : 0);
        if(val < dif/2){
            r = mid-1;
        }
        else{
            l = mid+1;
            ans2 = mid;
        }
    }
    if(ans2 == -1) return {-1,-1};
    if(ans >= ans2) return {-1,-1};
    return {ans,ans2};
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi pre(n),suf(n);
    pre[0] = v[0]; suf[n-1] = v[n-1];
    for(int i=1;i<n;i++) pre[i]=pre[i-1]+v[i];
    for(int i=n-2;i>=0;i--) suf[i]=suf[i+1]+v[i];
    for(int i=0;i<n-1;i++){
        if(pre[i]-suf[i+1]==0){
            cout<<1<<ln;
            for(auto it : v) cout<<it<<" ";
            cout<<ln;
            return;
        }
    }
    for(int i = 0 ; i < n-1 ; i++){
        int dif = pre[i]-suf[i+1];
        if(abs(dif)&1) continue;
        if(dif > 0){
            if(i == 0) continue;
            auto res = bs(pre,suf,n,0,i,dif);
            if(res.first == -1) continue;
            cout<<2<<ln;
            int rem = dif/2;
            for(int x = 0 ; x <= res.first ; x++){
                int use = min(v[x],rem);
                cout<<use<<" ";
                rem-=use , v[x]-=use;
            }
            for(int x = res.first+1 ; x < res.second ; x++) cout<<0<<" ";
            rem = dif/2;
            for(int x = res.second ; x < n ;x++){
                int use = min(v[x],rem);
                cout<<use<<" ";
                rem-=use , v[x]-=use;
            }
            cout<<ln;
            for(auto it : v) cout<<it<<" ";
            cout<<ln;
            return;
        }else{
            dif *=-1;
            if(i == n-2) continue;
            auto res = bs(pre,suf,n,i+1,n-1,dif);
            if(res.first == -1) continue;
            cout<<2<<ln;
            int rem = dif/2;
            for(int x = 0 ; x <= i ; x++) cout<<0<<" ";
            for(int x = i+1 ; x <= res.first ; x++){
                int use = min(v[x],rem);
                cout<<use<<" ";
                rem-=use , v[x]-=use;
            }
            for(int x = res.first+1 ; x < res.second ; x++) cout<<0<<" ";
            rem = dif/2;
            for(int x = res.second ; x < n ;x++){
                int use = min(v[x],rem);
                cout<<use<<" ";
                rem-=use , v[x]-=use;
            }
            cout<<ln;
            for(auto it : v) cout<<it<<" ";
            cout<<ln;
            return;
        }
    }   
    cout<<-1<<ln;
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