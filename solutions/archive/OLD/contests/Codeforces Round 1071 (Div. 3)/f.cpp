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

void first(){
    int n,m; cin>>n>>m;
    vii g(n);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi color(n,-1);
    queue<int>q; q.push(0); 
    color[0] = 0;
    int lvl = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto cur = q.front(); q.pop();
            for(auto &it : g[cur]){
                if(color[it] != -1) continue;
                q.push(it);
                color[it] = (lvl+1)%3;
            }
        }
        lvl++;
    }
    map<int,char> mp = {{0,'r'},{1,'b'},{2,'g'}};
    for(int i = 0;i< n ; i++){
        cout<<mp[color[i]];
    }
    cout<<ln;
}
void second(){
    map<char,int> to = {{'r',0},{'b',1},{'g',2}};
    map<int,char> from = {{0,'r'},{1,'b'},{2,'g'}};
    int q; cin>>q;
    while(q--){
        int sz; cin>>sz;
        string s; cin>>s;
        set<int>st;
        for(auto &ch : s) st.insert(to[ch]);
        char tag;
        if(st.size() == 1){
            tag = from[*st.begin()];
        }else{
            int sum = 3 - *st.begin() - *st.rbegin();
            tag = from[(sum-1+3)%3];
        }
        for(int i = 0;i < sz ; i++){
            if(s[i] == tag){
                cout<<i+1<<ln;
                goto xx;
            }
        }
        xx:;
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string op; cin>>op;
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        if(op == "first") first();
        else second();
    }

    return 0;
}