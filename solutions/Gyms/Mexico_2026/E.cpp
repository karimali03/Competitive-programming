#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vii vector<vi>
#define all(X) X.begin(),X.end()
#define int ll 

const int N = 2e5+10;
const int M = 998244353;
int fp(int x,int y){
    int ret = 1;
    while(y > 0){
        if(y&1) ret  = ret * x %  M;
        x = x * x % M;
        y >>= 1;
    }
    return ret;
}

int inv(int x){
    return fp(x,M-2);
}

ll dp[N]{};
ll C[N]{}, U[N]{};
ll fac[N]{}, facinv[N]{};

ll brutarr(vi &X, ll l, ll r) {
    // cout << l << ' ' << r << '\n';
    if (l == r) return 0;
    bool isr = 1;
    for (int i = l+1; i <= r; i++)
    { 
        if (X[i-1] > X[i]) {
            isr = 0;
            break;
        }
    }
    if (isr) return 0;
    ll mid = (l+r)/2;
    ll v = brutarr(X, l, mid) + brutarr(X, mid+1, r);
    v *= inv(2);
    v++;
    v %= M;
    return v;
}

ll getbrut(ll n, ll k) {
    n = (1ll << n);
    ll m = fp(k, n);
    // cout << m << '\n';
    // return 0;
    ll sol = 0;
    for (int i = 0; i < m; i++){
        vi X(n, 0);
        ll at = 0;
        ll v = i;
        while(v) {
            X[at] = v%k;
            v /= k;
            at++;
        }
        for (auto a : X) cout << a << ' ';
        cout << '\n';
        sol += brutarr(X, 0, X.size()-1);
    }
    sol *= inv(m);
    sol %= M;
    return sol;        
}


int rec(int cur,int idx,int k,int n){
    if(idx == n+1) return 1;
    int ret = 0;
    for(int i = cur ; i <= k ; i++) ret += rec(i,idx+1,k,n);
    return ret;
}
int calc(int n,int k){
    return rec(1,1,k,n);
}

ll A[N]{};

void solve(){
    ll n, k;
    cin >> n >> k;
   // cout << getbrut(n, k) << '\n';
   // return;
    dp[0] = 0;
    C[0]= k;
    U[0] = 0;
    A[0] = k;

    fac[0] = facinv[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fac[i] = i * fac[i-1] % M;
        facinv[i] = inv(fac[i]);
    }
    
    for (int i = 1; i <= n; i++){
        ll sz = (1ll << i);
        C[i] = fac[sz+k-1];
        (C[i] *= facinv[sz]) %= M;
        (C[i] *= facinv[k-1]) %= M;
        
        A[i] = fp(k, 1ll<<i); // optmize
        
        U[i] = A[i]-C[i];
        U[i] %= M;
        U[i] += M;
        U[i] %= M;
    }
    // for(int i = 1 ; i <= n  ;i++){
    //     cout<<C[i]<<" "<<calc(1<<i,k)<<"\n";
    // }
    
    // cout << C[1] << "|\n";
    for (int i = 1; i <= n; i++)
    {

        ll c = C[i] * C[i] - C[i+1];        
        c %= M;
        c += M;
        c %= M;

        c += C[i] * U[i];
        c %= M;

        ll u = U[i] * A[i] % M;
        ll all = A[i+1];

        // cout << all << "|\n";
        ll p = u * inv(all) % M;
        // cout << dp[i-1] << "|\n";
        dp[i] = (dp[i-1] + 1) * (p) % M;
    }
    
    ll sol = p * (1+dp[n-1]);

    sol += dp[]
    sol %= M;
    cout << sol << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
