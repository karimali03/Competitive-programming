#include <bits/stdc++.h>
#define ll long long
#define vi vector<ll>
using namespace std;
#define int ll
#define pl pair<ll, ll>
#define vp vector<pl>
const int MXN = 1e6+1;
int prime[MXN] = {0};
vi primes;

void INIT() {
    for (int i = 0; i < MXN; i++)
    {
        prime[i]=i;
    }
    
    for (int i = 2; i < MXN; i++)
    {
        for (int j = i; j < MXN; j+=i)
        {
            prime[j]=i;
        }
    }
    for (int i = 2; i < MXN; i++)
    {
        if(i == prime[i]) primes.push_back(i);
    }
}

vector<pl> FP(ll n) {
    vp X;
    for (auto a : primes) {
        ll cnt = 0;
        while (n%a) n/=a, cnt++;
        if (cnt) X.push_back({a, cnt});
    }
    if (n > 1) {
        X.push_back({n, 1});
    }
    return X;
}

ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a%b);
}

void req(vp &Z, vi &X, ll at, ll v) {
    if (at == Z.size()) {
        X.push_back(v);
        return;
    }

    for (int i = 0; i <= Z[at].second; i++)
    {
        req(Z, X, at + 1, v);
        v *= Z[at].first;
    }
}

void solve() {
    ll n;

    cin >> n;

    vi X(n);
    ll g = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> X[i];
        g = gcd(g, X[i]);
    }

    vi Z;
    auto fp = FP(g);

    req(fp, Z, 0, 1);

    sort(Z.begin(), Z.end());
    cout << Z.size() << '\n';
    for (auto a : Z) cout << a << ' ';
    cout << '\n';
}

signed main() {
    int size = 1;
   cin >> size;
    while (size--)
    {
        solve();
    }
    
}