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


int cmpr(string l,string r,int idx,int n){
    int mx1 = 0; bool fn1 = false;
    int mx2 = 0; bool fn2 = false;
    for(int i = idx ; i < n ; i++){
        if(r[i] == '0' && !fn1){
            mx1++;
            if(l[i] == '0') mx1++;
        }
        else if(!fn1){
            if(l[i] == '0' && r[i] == '1') mx1++;
            fn1 = true;
        }
         if(l[i] == '9' && !fn2){
            mx2++;
            if(r[i] == '9') mx2++;
        }
        else if(!fn2){
            if(r[i] == '9' && l[i] == '8') mx2++;
            fn2 = true;
        }
    }
    return min(mx1,mx2);
}
void solve(int test_case) {
    string l,r; cin>>l>>r;
    int dif = (int)r.size() - (int)l.size();
    if(dif){
        string z(dif,'0');
        for(auto it : l) z.push_back(it);
        l = z;
    }   
    int n = l.size();
    int res = n*2;
    for(int  i = 0  ; i < n ;i++){
        if(l[i] == r[i]) continue;
        if(l[i] != r[i]){
            if(l[i]-'0'+1 == r[i]-'0'){
                int mn = cmpr(l,r,i+1,n);
              
                res = i*2 + 1 +  mn;
                break;
            }
            else{
                res = i*2;
                break;
            }
        }
    }
    cout<<res<<ln;
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