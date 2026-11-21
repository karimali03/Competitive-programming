#include <bits/stdc++.h>
using namespace std;
#define ll long long

#define vi vector<ll>
#define vii vector<vi>

const int N = 2e5+10;



void solve(){
    ll n, k;

    cin >> n >> k;

    ll c = 0;
    vi frq(n+10);
    for (int i = 0; i < n; i++)
    {
        ll a; cin >> a;
        if (a < frq.size() && !frq[a]) frq[a]=1;
        else c++;
    }

    
    ll r = frq.size()-1;
    ll at = 0;
    while (true)
    {
        if (frq[at]) {
            at++;
            continue;
        }
        if (!k) break;
        if (c) {
            at++;
            c--, k--;
            continue;
        }
        
        if (r < at) break;
        if (frq[r]) {
            frq[r] = 0;
            c++;    
        }
        r--;
    }

    cout << at << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
