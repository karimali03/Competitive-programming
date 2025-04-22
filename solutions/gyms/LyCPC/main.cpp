#include <bits/stdc++.h>
#define ll long long
#define vi vector<ll>
using namespace std;
#define pl pair<ll, ll>
#define vp vector<pl>
#define int ll

void solve() {
    ll n;
 
    cin >> n;
 
    vi X(n);
    ll g = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> X[i];
        if (X[i]) g=  X[i];
    }
    
    for(auto a : X) if (a) g = gcd(a, g);
 
    vi Z;
 
    for (int i = 1; i * i <= g; i++)
    {
        if (g%i == 0) {
            Z.push_back(i);
            if (i*i!=g)Z.push_back(g/i);
        }
    }
    
    sort(Z.begin(), Z.end());
    cout << Z.size() << '\n';
    for (auto a : Z) cout << a << ' ';
    cout << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int size = 1;
   cin >> size;
    while (size--)
    {
        solve();
    }
    
}