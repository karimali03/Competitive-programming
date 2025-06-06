#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
 
#define ll long long
#define ld long double
#define pl pair<ll, ll>
#define vi vector<ll>
#define vii vector<vi>
#define vc vector<char>
#define vcc vector<vc>
#define vp vector<pl>
#define mi map<ll,ll>
#define mc map<char,int>
#define sortx(X) sort(X.begin(),X.end());
#define all(X) X.begin(),X.end()
#define allr(X) X.rbegin(),X.rend()
#define ln '\n'
#define YES {cout << "YES\n"; return;}
#define NO {cout << "NO\n"; return;}
#define MUN {cout << "-1\n"; return;}
 
const int MODE = 998244353;
 
using namespace std;
 
void solve(int tc) {
    ll n, m;
 
    cin >> n >> m;
 
    vi X(n);
    for (int i = 0; i < n; i++)
    {
        cin >> X[i];
    }
    sortx(X);    
 
    ll l = 0, r = 1e9;
    while (l < r)
    {
        ll mid = (l + r) / 2;
        ll cnt = 1;
        ll ls = 0;
        for (int i = 0; i < n; i++)
        {
            if (X[i] - X[ls] > mid) {
                cnt++;
                ls = i;
            }
        }
 
        if (cnt > m) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
 
    cout << l << ln;
} 
 
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int size = 1;
 
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
 
    // cin >> size;
    for (int i = 1; i <= size; i++)
        solve(i);
}
