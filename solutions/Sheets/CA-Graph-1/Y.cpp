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


const int N = 300005;
// spf ( smallest prime factor )
vector<int>spf(N+5);   
 void SPF(){   //  O(n*log(log(n)))
    for(int i=1;i<=N;i++) spf[i]=i;

     for(int i=2; i*i<=N; i++)
    {
        if(spf[i]==i)
           for(int j=i*i; j<=N; j+=i)
               if(spf[j]==j)   spf[j]=i;
    }
 }


vector<int> fast_fact(int n){   // O ( log(n) )
     vi res;
     while (n>1){
        if(res.empty() || spf[n] != res.back()) res.push_back(spf[n]);
        n/=spf[n];
     }
     return res;
 }
 

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int s,t; cin>>s>>t; s--,t--;
    if(s == t){
        cout<<"1\n"<<s+1<<ln;
        return;
    }
    vii primes(n);
    f(i,0,n) primes[i] = fast_fact(v[i]);
    map<int,vi>mp;
    f(i,0,n){
        for(auto &it : primes[i]){
            mp[it].push_back(i);
        }
    }
    queue<int>q;
    vi dist(n,-1);
    vi prv(n,-1);
    vector<bool> vis_prime(N + 5, false); 

    q.push(s); dist[s] = 1;

    while(!q.empty()){
        auto cur = q.front(); q.pop();
        
        for(auto &it : primes[cur]){
            if(vis_prime[it]) continue; 
            vis_prime[it] = true;
            
            for(auto &x : mp[it]){
                if(dist[x] != -1) continue;
                prv[x] = cur;
                q.push(x); dist[x] = dist[cur]+1;
                if(x == t) goto XX;
            }
        }
    }
    XX:
    vi path;
    for(int v = t ; v != -1 ; v = prv[v]){
        path.push_back(v+1);
    }
    reverse(all(path));
    int sz = path.size();
    if(sz != dist[t]) NA;
    else{
        cout<<sz<<ln;
        cout<<path<<ln;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SPF();
    int t = 1;
  
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}