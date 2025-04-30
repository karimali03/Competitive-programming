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
    ll n, x, k;
 
    cin >> n >> x >> k;
 
    x--;
    vi X(n);
    for (int i = 0; i < n; i++)
    {
        cin >> X[i]; X[i]--;
    }
 
    if (!k) {
        cout << x + 1 << ln;
        return;
    }
    
    vii B(n, vi(32));
    for (int i = 0; i < n; i++)
    {
        B[i][0] = X[i];
    }
 
    for (int j = 1; j < 32; j++)
    {
        for (int i = 0; i < n; i++)
        {
            B[i][j] = B[B[i][j - 1]][j - 1];
        }
    }
    
    for (int i = 0; i < 32; i++)
    {
        if (k & (1 << i)) {
            x = B[x][i];
        }
    }
    
    cout << x + 1 << ln;
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
