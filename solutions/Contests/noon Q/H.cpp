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

int SQ;
int frq[1'000'001]{};
int odds = 0;
int tot = 0;
struct Query
{
    int l, r, idx;
    bool operator < (const Query &other) const
    {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return (l/SQ) & 1 ? r > other.r : r < other.r;
    }
};
 
bool ze = 0;
void add(int val) {
    if(ze && val == 0) return;
    frq[val]++;
    if(frq[val]&1) odds++;
    else odds--;
    tot -= (frq[val]-1)/2;
    tot += frq[val]/2;
}

void del(int val) {
    if(ze && val == 0) return;
    frq[val]--;
    if(frq[val]&1) odds++;
    else odds--;
    tot -= (frq[val]+1)/2;
    tot += frq[val]/2;
}


vector<int> MO(vector<Query> &q, vector<int> &v){
    int n = v.size();
    SQ = sqrt(n) + 1;
    tot = 0 , odds = 0;
    vector<int> res(q.size());
    sort(q.begin(), q.end());
    int l = 0 ,r = -1;
    for(auto [lq,rq,idx] : q){
        while(lq < l) add(v[--l]);
        while(rq > r) add(v[++r]);
        while(lq > l) del(v[l++]);
        while(rq < r) del(v[r--]);
      //  cout<<idx<<" "<<tot<<" "<<odds<<ln;
        res[idx] = tot + ((odds+1)/2) * 2;
    }
    return res;
}

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    vi val = v;
    sort(all(val)); 
    val.erase(unique(all(val)),val.end());
    if(val[0] == 0) ze = true;
    f(i,0,n) v[i] = lower_bound(all(val),v[i])-val.begin();
    vector<Query>qu(q);
    for(int i = 0;i < q ; i++){
        int l,r; cin>>l>>r; l--,r--;
        qu[i] = {l,r,i};
    }
    auto res = MO(qu,v);
    for(auto it : res) cout<<it<<ln;
    
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