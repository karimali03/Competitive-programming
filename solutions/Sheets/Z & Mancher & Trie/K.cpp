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

vector<int> d[10];
ll pw[19];
struct Trie {
    static const int MAX_BITS = 18;
    struct node {
        int nxt[10];
        node() {
            memset(nxt,-1,sizeof(nxt));
        }
    };
    vector<node> child;

    Trie(int n){
        child.reserve(19ll * n + 1);
        child.push_back(node());
    }

    void insert(string& num){
        int cur = 0;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = num[shift]-'0'; 
            if(child[cur].nxt[bit] == -1){
                child[cur].nxt[bit] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[bit];
        }
    }
    
    ll find_max(string& num){
        ll ret = 0;
        int cur = 0;
        for(int sh = MAX_BITS ; sh >= 0 && cur != -1; sh--){
            int bit = num[sh]-'0';
            for(int dig = 9 ; dig >= 0 ; dig--){
                int x = d[bit][dig];
                if(child[cur].nxt[x] != -1){
                    ret += pw[sh] * ((x+bit)%10);
                    cur = child[cur].nxt[x];
                    break;
                }
            }
        }
        return ret;
    }


    ll find_min(string& num){
        ll ret = 0;
        int cur = 0;
        for(int sh = MAX_BITS ; sh >= 0 && cur != -1; sh--){
            int bit = num[sh] - '0'; 
            for(int dig = 0 ; dig < 10 ; dig++){
                int x = d[bit][dig];
                if(child[cur].nxt[x] != -1){
                    ret += pw[sh] * ((x+bit)%10);
                    cur = child[cur].nxt[x];
                    break;
                }
            }
        }
        return ret;
    }
    
    
};


void solve(int test_case) {
    int n; cin>>n;
    vector<ll> v(n); cin>>v;
    vector<string>s(n);
    for(int i = 0;i < n ; i++){
        s[i] = to_string(v[i]);
        reverse(all(s[i]));
        while((int)s[i].size() < 19) s[i] += '0';
    }

    Trie st(n);
    ll mn = INT64_MAX,mx = 0;
    st.insert(s[0]);
    for(int i = 1 ;i  < n ; i++){
        mn = min(mn , st.find_min(s[i]));
        mx = max(mx , st.find_max(s[i]));
        st.insert(s[i]);
    }
    cout<<mn<<" "<<mx<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for(int i = 0 ;i < 10 ; i++){
        vector<pair<int,int>> s(10);
        for(int j = 0 ;j  < 10 ; j++){
            s[j] = {(i+j)%10,j};
        }
        sort(all(s));
        for(int j = 0 ;j < 10 ; j++){
            d[i].push_back(s[j].second);
        }
    }   
    pw[0] = 1;
    for(int i = 1 ; i < 19 ; i++){
        pw[i] = 10 * pw[i-1];
    }
    
    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}