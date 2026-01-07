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

void solve(int test_case) {
    string s; cin>>s;
    int n = s.size();
    vii last(26,vi(n,-1));
    vii frq(n,vi(26));
    vi id(n);
    vii inv(26,vi(n,-1));
    for(int i = 0;i < n; i++){
        if(i){
            for(int ch = 0; ch < 26 ; ch++){
                frq[i][ch] += frq[i-1][ch];
                last[ch][i] = last[ch][i-1];
            } 
        }
        last[s[i]-'a'][i] = i;
        frq[i][s[i]-'a']++;
    } 
    for(int i = 0; i < 26 ; i++){
        int c = 0;
        for(int j = 0;j < n ; j++) if(s[j]-'a' == i){
            inv[i][c] = j;
            id[j] = c++;
        }
    }


    auto get = [&] (int l,int r) -> vi{
        auto ret = frq[r];
        if(l) for(int ch=0;ch<26 ;ch++) ret[ch] -= frq[l-1][ch];
        return ret;
    };
    int ans = n;
    for(int x = n; x >= 1 ; x--){
        int l = 0 , r = 0;
        bool vld = true;
        int cnt = 0;
        //cout<<" "<<x<<" "<<ln;
        while(vld && r < n){
         //   cout<<l<<" "<<r<<endl;
            auto fr = get(l,r);
            int jump = -1;
            for(int ch=0;ch<26;ch++){
                int it = fr[ch];
                if(it > x) vld = 0;
                else if(it < x && it){
                  int c = id[last[ch][r]];
                  int dif = x - it;
               //   cout<<c<<" "<<dif<<ln;
                  if(c + dif < n && inv[ch][c+dif] != -1) jump = max(jump , inv[ch][c+dif]);
                  else vld = 0;
                }
            }
          //  cout<<vld<<ln;
            if(jump == -1) l = r = r+1,cnt++;
            else r = jump;
        }
        if(vld){
          //  cout<<cnt<<' '<<x<<ln;
            ans = min(ans , cnt);
        } 
    }
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}